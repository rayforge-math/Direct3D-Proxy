#pragma once
#include "d3d/COMRegistry.h"
#include "d3d/ProxyD3D.h"
#include "debug.h"
#include <cassert>

namespace d3d {

    template <typename T, size_t MaxCount>
    struct UnwrappedArray {
        T* Data[MaxCount];
        inline operator T* const* () const { return Data; }
    };

    /**     
    * Static utility for zero-copy proxy management.     
    * Version-agnostic base — no D3D11/D3D12-specific slot counts or types.     
    * Registry write is owned by the proxy constructor/destructor — ProxyWrapper is read-only.     
    */
    class ProxyWrapper {
    public:
        /**         
        * Wraps a raw COM pointer into a proxy.         
        * Checks the registry first — reuses an existing proxy if present,         
        * otherwise creates a new one and takes ownership of the raw reference.         
        */
        template <typename TProxy, typename... Args>
            requires IsProxyFor<TProxy, typename TProxy::InterfaceType>
        static HRESULT Wrap(typename TProxy::InterfaceType** ppInterface, Args&&... args)
        {
            LOG_MSG("ProxyWrapper::Wrap called");
            using TReal = typename TProxy::InterfaceType;
            if (!ppInterface || !*ppInterface) return S_OK;
            TReal* pReal = *ppInterface;

            if (TProxy* pExisting = COMRegistry<TReal, TProxy>::Find(pReal)) {
                LOG_MSG("ProxyWrapper::Wrap - Existing proxy found, reusing");
                pExisting->AddRef();
                pReal->Release();
                *ppInterface = static_cast<TReal*>(pExisting);
                return S_OK;
            }

            LOG_MSG("ProxyWrapper::Wrap - Creating new proxy instance");
            TProxy* pProxy = new TProxy(pReal, std::forward<Args>(args)...);
            if (!pProxy) {
                LOG_MSG("ProxyWrapper::Wrap - Failed to allocate new proxy (out of memory)");
                pReal->Release();
                return E_OUTOFMEMORY;
            }

            *ppInterface = static_cast<TReal*>(pProxy);
            return S_OK;
        }

        /**         
        * In-place wrapping for arrays (e.g. from Get-methods returning multiple objects).         
        * Stops and returns the first failure HRESULT if any element fails.         
        */
        template <typename TProxy, typename... Args>
            requires IsProxyFor<TProxy, typename TProxy::InterfaceType>
        static HRESULT WrapArray(typename TProxy::InterfaceType** ppInterfaces, UINT count, Args&&... args)
        {
            LOG_MSG("ProxyWrapper::WrapArray called");
            if (!ppInterfaces || count == 0) return S_OK;
            for (UINT i = 0; i < count; ++i) {
                if (ppInterfaces[i]) {
                    HRESULT hr = Wrap<TProxy>(&ppInterfaces[i], std::forward<Args>(args)...);
                    if (FAILED(hr)) {
                        LOG_MSG("ProxyWrapper::WrapArray - Failed at index");
                        return hr;
                    }
                }
            }
            return S_OK;
        }

        /**         
        * Extracts the real COM pointer from a proxy.         
        * TProxy must be explicit — the registry maps interface -> concrete proxy type.         
        * Returns the pointer as-is if it is not a known proxy (already unwrapped or external).         
        *         
        * Usage:  ProxyWrapper::Unwrap<ProxyD3D11Buffer>(pBuffer)         
        */
        template <typename TProxy>
            requires IsProxy<TProxy>
        static inline typename TProxy::InterfaceType* Unwrap(typename TProxy::InterfaceType* pInterface)
        {
            LOG_MSG("ProxyWrapper::Unwrap called");
            using TReal = typename TProxy::InterfaceType;
            if (!pInterface) return nullptr;

            if (TProxy* pProxy = COMRegistry<TReal, TProxy>::Find(pInterface)) {
                LOG_MSG("ProxyWrapper::Unwrap - Found proxy in registry, returning real pointer");
                return pProxy->GetReal();
            }

            LOG_MSG("ProxyWrapper::Unwrap - Pointer is not a known proxy, passing through as-is");
            return pInterface; // already unwrapped or external — pass through
        }

        /**         
        * Stack-allocated unwrap for array-based Set-calls.         
        * MaxCount must be provided explicitly — use a version-specific wrapper         
        * (e.g. ProxyD3D11Wrapper) to bind slot counts to types.         
        *         
        * Usage:  auto real = ProxyWrapper::UnwrapArray<ProxyD3D11Buffer, 14>(ppBuffers, count);         
        *         ctx->VSSetConstantBuffers(0, count, real);         
        */
        template <typename TProxy, size_t MaxCount>
            requires IsProxy<TProxy>
        static inline UnwrappedArray<typename TProxy::InterfaceType, MaxCount>
            UnwrapArray(typename TProxy::InterfaceType* const* ppProxies, UINT count)
        {
            LOG_MSG("ProxyWrapper::UnwrapArray called");
            assert(count <= MaxCount && "UnwrapArray: count exceeds MaxCount buffer limit!");
            using TReal = typename TProxy::InterfaceType;
            UnwrappedArray<TReal, MaxCount> result{};
            if (ppProxies) {
                const UINT n = (count < MaxCount) ? count : static_cast<UINT>(MaxCount);
                for (UINT i = 0; i < n; ++i)
                    result.Data[i] = Unwrap<TProxy>(ppProxies[i]);
            }
            return result;
        }
    };

} // namespace d3d