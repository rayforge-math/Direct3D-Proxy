#pragma once
#include "COMRegistry.h"
#include "d3d/ProxyD3D.h"
#include "logging/debug_core.h"
#include <cassert>
#include <unknwn.h>

namespace d3d {

    template <typename T, size_t MaxCount>
    struct UnwrappedArray {
        T* Data[MaxCount];
        inline operator T* const* () const { return Data; }
    };

    /**
     * @brief Static utility for zero-copy proxy management using IUnknown identity.
     */
    class ProxyWrapper {
    public:
        /**
         * @brief Wraps a raw COM pointer of any compatible interface version into a proxy,
         *        reusing existing ones from the central registry.
         */
        template <typename TProxy, typename TInputInterface = typename TProxy::InterfaceType, typename... Args>
            requires IsProxy<TProxy>&& std::is_base_of_v<IUnknown, TInputInterface>
        static HRESULT Wrap(TInputInterface** ppInterface, Args&&... args) {
            using TReal = typename TProxy::InterfaceType;
            if (!ppInterface || !*ppInterface) return S_OK;

            TInputInterface* pInput = *ppInterface;

            // Query the target real interface version required by the proxy (TReal) from the input pointer
            TReal* pReal = nullptr;
            HRESULT hr = pInput->QueryInterface(__uuidof(TReal), reinterpret_cast<void**>(&pReal));
            if (FAILED(hr) || !pReal) {
                return hr;
            }

            // 1. Check if a proxy for this object already exists in the central registry
            if (TProxy* pExisting = dll::COMRegistry::Find<TProxy>(reinterpret_cast<IUnknown*>(pReal))) {
                pExisting->AddRef();
                pReal->Release(); // Release the QueryInterface reference
                pInput->Release();  // Release the original input reference
                *ppInterface = static_cast<TInputInterface*>(pExisting);
                return S_OK;
            }

            // 2. Create the new proxy instance taking ownership of the upgraded real interface
            TProxy* pProxy = new (std::nothrow) TProxy(pReal, std::forward<Args>(args)...);
            if (!pProxy) {
                pReal->Release();
                pInput->Release();
                return E_OUTOFMEMORY;
            }

            // 3. Register the new proxy in the central COMRegistry
            dll::COMRegistry::Register(pReal, pProxy);

            // Release the original input reference and assign the proxy casted to the input interface type
            pInput->Release();
            *ppInterface = static_cast<TInputInterface*>(pProxy);
            return S_OK;
        }

        /**
         * @brief In-place wrapping for arrays of COM pointers supporting arbitrary interface versions.
         */
        template <typename TProxy, typename TInputInterface = typename TProxy::InterfaceType, typename... Args>
            requires IsProxy<TProxy>&& std::is_base_of_v<IUnknown, TInputInterface>
        static HRESULT WrapArray(TInputInterface** ppInterfaces, UINT count, Args&&... args) {
            if (!ppInterfaces || count == 0) return S_OK;
            for (UINT i = 0; i < count; ++i) {
                if (ppInterfaces[i]) {
                    HRESULT hr = Wrap<TProxy, TInputInterface>(&ppInterfaces[i], std::forward<Args>(args)...);
                    if (FAILED(hr)) return hr;
                }
            }
            return S_OK;
        }

        /**
         * @brief Extracts the real COM pointer from a proxy instance, supporting any input interface version.
         */
        template <typename TProxy, typename TInputInterface = typename TProxy::InterfaceType>
            requires IsProxy<TProxy>
        static inline typename TProxy::InterfaceType* Unwrap(TInputInterface* pInterface) {
            using TReal = typename TProxy::InterfaceType;
            if (!pInterface) return nullptr;

            IUnknown* pUnknown = nullptr;
            if (SUCCEEDED(pInterface->QueryInterface(__uuidof(IUnknown), reinterpret_cast<void**>(&pUnknown)))) {
                if (TProxy* pProxy = dll::COMRegistry::Find<TProxy>(pUnknown)) {
                    pUnknown->Release();
                    return static_cast<TReal*>(pProxy->GetReal());
                }
                pUnknown->Release();
            }

            TReal* pReal = nullptr;
            if (SUCCEEDED(pInterface->QueryInterface(__uuidof(TReal), reinterpret_cast<void**>(&pReal)))) {
                pReal->Release();
                return pReal;
            }

            return reinterpret_cast<TReal*>(pInterface);
        }

        /**
         * @brief Stack-allocated unwrap for array-based API calls (e.g., SetConstantBuffers).
         */
        template <typename TProxy, size_t MaxCount, typename TInputInterface = typename TProxy::InterfaceType>
            requires IsProxy<TProxy>
        static inline UnwrappedArray<typename TProxy::InterfaceType, MaxCount>
            UnwrapArray(TInputInterface* const* ppProxies, UINT count) {
            assert(count <= MaxCount && "UnwrapArray: count exceeds MaxCount buffer limit!");
            using TReal = typename TProxy::InterfaceType;
            UnwrappedArray<TReal, MaxCount> result{};

            if (ppProxies) {
                const UINT n = (count < MaxCount) ? count : static_cast<UINT>(MaxCount);
                for (UINT i = 0; i < n; ++i) {
                    result.Data[i] = Unwrap<TProxy, TInputInterface>(const_cast<TInputInterface*>(ppProxies[i]));
                }
            }
            return result;
        }

        /**
         * @brief Safely retrieves the underlying real IUnknown pointer if the input is a proxy,
         *        otherwise returns the input pointer unchanged.
         */
        static inline IUnknown* GetRealUnknown(IUnknown* pUnknown) {
            if (!pUnknown) return nullptr;

            IProxy* pProxyBase = nullptr;
            HRESULT hr = pUnknown->QueryInterface(__uuidof(IProxy), reinterpret_cast<void**>(&pProxyBase));

            if (SUCCEEDED(hr) && pProxyBase) {
                IUnknown* pReal = pProxyBase->GetRealUnknown();
                return pReal;
            }

            return pUnknown;
        }

        /**
         * @brief Unwraps a proxy by casting directly to TProxy and calling GetReal().
         */
        template <typename TProxy, typename TInputInterface = typename TProxy::InterfaceType>
            requires IsProxy<TProxy>
        static inline typename TProxy::InterfaceType* GetReal(TInputInterface* pInterface) {
            using TReal = typename TProxy::InterfaceType;
            if (!pInterface) return nullptr;

            if (auto* pProxy = dynamic_cast<TProxy*>(pInterface)) {
                return pProxy->GetReal();
            }

            TReal* pReal = nullptr;
            if (SUCCEEDED(pInterface->QueryInterface(__uuidof(TReal), reinterpret_cast<void**>(&pReal)))) {
                pReal->Release();
                return pReal;
            }

            return reinterpret_cast<TReal*>(pInterface);
        }
    };

} // namespace d3d