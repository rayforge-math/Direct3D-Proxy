#pragma once

#include "COMRegistry.h"
#include "d3d/ProxyD3D.h"
#include <cassert>
#include <unknwn.h>

namespace d3d {

    template <typename T, size_t MaxCount>
    struct UnwrappedArray {
        T* Data[MaxCount];
        inline operator T* const* () const { return Data; }
    };

    /**
     * @brief Static utility for zero-zero-copy proxy management using IUnknown identity.
     */
    class ProxyWrapper {
    public:
        /**
         * @brief Wraps a raw COM pointer into a proxy, reusing existing ones from the registry.
         */
        template <typename TProxy, typename... Args>
            requires IsProxyFor<TProxy, typename TProxy::InterfaceType>
        static HRESULT Wrap(typename TProxy::InterfaceType** ppInterface, Args&&... args) {
            using TReal = typename TProxy::InterfaceType;
            if (!ppInterface || !*ppInterface) return S_OK;

            TReal* pReal = *ppInterface;

            // Check registry using IUnknown* for correct COM identity lookup
            if (TProxy* pExisting = dll::COMRegistry<TProxy>::Find(pReal)) {
                pExisting->AddRef();
                pReal->Release();
                *ppInterface = static_cast<TReal*>(pExisting);
                return S_OK;
            }

            TProxy* pProxy = new (std::nothrow) TProxy(pReal, std::forward<Args>(args)...);
            if (!pProxy) {
                pReal->Release();
                return E_OUTOFMEMORY;
            }

            *ppInterface = static_cast<TReal*>(pProxy);
            return S_OK;
        }

        /**
         * @brief In-place wrapping for arrays of COM pointers.
         */
        template <typename TProxy, typename... Args>
            requires IsProxyFor<TProxy, typename TProxy::InterfaceType>
        static HRESULT WrapArray(typename TProxy::InterfaceType** ppInterfaces, UINT count, Args&&... args) {
            if (!ppInterfaces || count == 0) return S_OK;
            for (UINT i = 0; i < count; ++i) {
                if (ppInterfaces[i]) {
                    HRESULT hr = Wrap<TProxy>(&ppInterfaces[i], std::forward<Args>(args)...);
                    if (FAILED(hr)) return hr;
                }
            }
            return S_OK;
        }

        /**
         * @brief Extracts the real COM pointer from a proxy instance.
         */
        template <typename TProxy>
            requires IsProxy<TProxy>
        static inline typename TProxy::InterfaceType* Unwrap(typename TProxy::InterfaceType* pInterface) {
            using TReal = typename TProxy::InterfaceType;
            if (!pInterface) return nullptr;

            if (TProxy* pProxy = dll::COMRegistry<TProxy>::Find(pInterface)) {
                return static_cast<TReal*>(pProxy->GetReal());
            }

            return pInterface; // Pass through if not a known proxy
        }

        /**
         * @brief Stack-allocated unwrap for array-based API calls (e.g., SetConstantBuffers).
         */
        template <typename TProxy, size_t MaxCount>
            requires IsProxy<TProxy>
        static inline UnwrappedArray<typename TProxy::InterfaceType, MaxCount>
            UnwrapArray(typename TProxy::InterfaceType* const* ppProxies, UINT count) {
            assert(count <= MaxCount && "UnwrapArray: count exceeds MaxCount buffer limit!");
            using TReal = typename TProxy::InterfaceType;
            UnwrappedArray<TReal, MaxCount> result{};

            if (ppProxies) {
                const UINT n = (count < MaxCount) ? count : static_cast<UINT>(MaxCount);
                for (UINT i = 0; i < n; ++i) {
                    result.Data[i] = Unwrap<TProxy>(const_cast<TReal*>(ppProxies[i]));
                }
            }
            return result;
        }
    };

} // namespace d3d