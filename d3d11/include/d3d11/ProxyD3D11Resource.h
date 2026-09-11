#pragma once

#include "d3d11/d3d11_version.h"
#include "d3d/ProxyD3D.h"
#include "d3d/COMRegistry.h"
#include "d3d11/ProxyD3D11Device.h"
#include "d3d/concepts.h"
#include <concepts>
#include <atomic>

using namespace d3d;

namespace d3d11 {

    template <typename T>
    concept IsResourceInterface = d3d::IsCOMInterface<T> && std::derived_from<T, ID3D11Resource>;

    /**
     * Intermediate Proxy for all ID3D11Resource types.
     * Manages the identity (ID and Dimension) for the StateTracker.
     */
    template <IsResourceInterface T, typename TDerived>
    class ProxyD3D11Resource : public ProxyD3D<T, TDerived> {
    protected:
        const uint64_t           m_UniqueId;
        D3D11_RESOURCE_DIMENSION m_Dimension;

        static inline std::atomic<uint64_t> s_NextId{ 1 };

    public:
        /**
         * Constructor: Takes exclusive ownership of the provided pointer.
         * @param pReal The real D3D11 resource — ownership is transferred.
         * @param dim   The resource dimension (e.g. D3D11_RESOURCE_DIMENSION_BUFFER).
         */
        ProxyD3D11Resource(T* pReal, D3D11_RESOURCE_DIMENSION dim)
            : ProxyD3D<T, TDerived>(pReal)
            , m_UniqueId(s_NextId.fetch_add(1, std::memory_order_relaxed))
            , m_Dimension(dim)
        { }

        virtual ~ProxyD3D11Resource() noexcept = default;

        // Non-copyable, non-movable (Rule of Five)
        ProxyD3D11Resource(const ProxyD3D11Resource&) = delete;
        ProxyD3D11Resource& operator=(const ProxyD3D11Resource&) = delete;
        ProxyD3D11Resource(ProxyD3D11Resource&&) = delete;
        ProxyD3D11Resource& operator=(ProxyD3D11Resource&&) = delete;

        // --- Identity ---
        uint64_t                 GetUniqueId()  const noexcept { return m_UniqueId; }
        D3D11_RESOURCE_DIMENSION GetDimension() const noexcept { return m_Dimension; }

        // --- ID3D11DeviceChild ---

        virtual void STDMETHODCALLTYPE GetDevice(ID3D11Device** ppDevice) override
        {
            if (!ppDevice) return;
            this->m_pReal->GetDevice(ppDevice);

            // Route through the registry so the caller gets the proxy, not the real device.
            // If no proxy is registered for this device, the raw pointer is returned as-is.
            if (*ppDevice) {
                if (auto* pProxy = d3d::COMRegistry<ID3D11Device, ProxyD3D11Device>::Find(*ppDevice)) {
                    (*ppDevice)->Release(); // release the raw ref from GetDevice
                    pProxy->AddRef();
                    *ppDevice = pProxy;
                }
            }
        }

        virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) override {
            return this->m_pReal->GetPrivateData(guid, pDataSize, pData);
        }

        virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) override {
            return this->m_pReal->SetPrivateData(guid, DataSize, pData);
        }

        virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) override {
            return this->m_pReal->SetPrivateDataInterface(guid, pData);
        }

        // --- ID3D11Resource ---

        virtual void STDMETHODCALLTYPE GetType(D3D11_RESOURCE_DIMENSION* pResourceDimension) override {
            if (pResourceDimension)
                *pResourceDimension = m_Dimension;
        }

        virtual void STDMETHODCALLTYPE SetEvictionPriority(UINT EvictionPriority) override {
            this->m_pReal->SetEvictionPriority(EvictionPriority);
        }

        virtual UINT STDMETHODCALLTYPE GetEvictionPriority() override {
            return this->m_pReal->GetEvictionPriority();
        }
    };

    template <typename TProxy>
    concept IsResourceProxy =
        requires { typename TProxy::InterfaceType; }
    && IsResourceInterface<typename TProxy::InterfaceType>
        && std::derived_from<TProxy, ProxyD3D11Resource<typename TProxy::InterfaceType, TProxy>>;

    template <typename TProxy, typename TResource>
    concept IsResourceProxyFor = IsResourceProxy<TProxy>
        && std::same_as<typename TProxy::InterfaceType, TResource>;

} // namespace d3d11