#pragma once

#include "d3d/COMRegistry.h"
#include "d3d/ProxyD3D.h"

namespace d3d {

    /**
     * Container for stack-allocated unwrapping of proxy arrays.
     * Used to pass real COM pointers to the underlying D3D driver.
     */
    template <typename T, size_t MaxCount>
    struct UnwrappedArray {
        T* Data[MaxCount];

        /**
         * Implicit conversion to the pointer-to-pointer type expected by D3D.
         */
        inline operator T* const* () const { return Data; }
    };

    /**
     * Static Utility for Zero-Copy Proxy Management.
     * Manages the transformation between Real COM Objects and Proxy Objects.
     */
    class ProxyWrapper {
    public:
        /**
         * Wraps a raw COM pointer. Checks Registry first to prevent duplicate proxies.
         */
        template <typename TProxy, typename... Args>
            requires IsProxyFor<TProxy, typename TProxy::InterfaceType>
        static HRESULT Wrap(typename TProxy::InterfaceType** ppInterface, Args&&... args) {
            using TResource = typename TProxy::InterfaceType;

            if (!ppInterface || !*ppInterface) return S_OK;

            TResource* pReal = *ppInterface;
            
            TProxy* pExisting = COMRegistry<TProxy>::Find(static_cast<IUnknown*>(pReal));
            if (pExisting) {
                pExisting->AddRef();
                pReal->Release();

                *ppInterface = static_cast<TResource*>(pExisting);
                return S_OK;
            }
            
            TProxy* pProxy = new TProxy(pReal, std::forward<Args>(args)...);
            if (!pProxy) {
                pReal->Release();
                return E_OUTOFMEMORY;
            }

            *ppInterface = static_cast<TResource*>(pProxy);

            return S_OK;
        }

        /**
         * In-place wrapping for arrays (e.g., from 'Get' methods).
         */
        template <typename TProxy>
        static void WrapArray(typename TProxy::InterfaceType** ppInterfaces, UINT count) {
            if (!ppInterfaces || count == 0) return;

            for (UINT i = 0; i < count; ++i) {
                if (ppInterfaces[i] != nullptr) {
                    Wrap<TProxy>(&ppInterfaces[i]);
                }
            }
        }

        /**
         * Extracts the real COM pointer.
         * Uses the IsProxyFor concept implicitly through static_cast.
         */
        template <typename T>
        static inline T* Unwrap(T* pInterface) {
            if (!pInterface) return nullptr;
            return static_cast<ProxyD3D<T>*>(pInterface)->GetReal();
        }

        /**
         * Optimized stack-allocated unwrap for array-based 'Set' calls.
         */
        template <typename T, size_t MaxCount>
        static inline UnwrappedArray<T, MaxCount> UnwrapArray(T* const* ppProxies, UINT count) {
            UnwrappedArray<T, MaxCount> container = { nullptr };

            if (ppProxies) {
                const UINT actualCount = (count < MaxCount) ? count : (UINT)MaxCount;

                for (UINT i = 0; i < actualCount; ++i) {
                    container.Data[i] = Unwrap(ppProxies[i]);
                }
            }
            return container;
        }
    };

} // namespace d3d