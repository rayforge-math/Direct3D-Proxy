#pragma once

#include "d3d11/d3d11_version.h"
#include "d3d/ProxyD3D.h"
#include "COMRegistry.h"
#include "d3d11/ProxyD3D11Device.h"
#include <concepts>

using namespace d3d;

namespace d3d11 {

    template <typename T>
    concept IsResourceObject = std::is_base_of_v<ID3D11Resource, T>;

    /**
     * @brief Intermediate Proxy for all ID3D11Resource types.
     */
    template <typename TDerived, IsResourceObject T>
    class ProxyD3D11Resource : public ProxyD3D<TDerived, T> {
    public:
        /**
         * @brief Constructor: Takes exclusive ownership of the provided pointer.
         */
        explicit ProxyD3D11Resource(T* pReal)
            : ProxyD3D<TDerived, T>(pReal)
        {
        }

        virtual ~ProxyD3D11Resource() noexcept = default;

        // Non-copyable, non-movable (Rule of Five)
        ProxyD3D11Resource(const ProxyD3D11Resource&) = delete;
        ProxyD3D11Resource& operator=(const ProxyD3D11Resource&) = delete;
        ProxyD3D11Resource(ProxyD3D11Resource&&) = delete;
        ProxyD3D11Resource& operator=(ProxyD3D11Resource&&) = delete;

        // --- ID3D11DeviceChild ---

        virtual void STDMETHODCALLTYPE GetDevice(ID3D11Device** ppDevice) override {
            if (!ppDevice) return;
            this->m_pReal->GetDevice(ppDevice);

            if (*ppDevice) {
                if (auto* pProxy = dll::COMRegistry::Find<ProxyD3D11Device>(*ppDevice)) {
                    (*ppDevice)->Release();
                    pProxy->AddRef();
                    *ppDevice = static_cast<ID3D11Device*>(pProxy);
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
            this->m_pReal->GetType(pResourceDimension);
        }

        virtual void STDMETHODCALLTYPE SetEvictionPriority(UINT EvictionPriority) override {
            this->m_pReal->SetEvictionPriority(EvictionPriority);
        }

        virtual UINT STDMETHODCALLTYPE GetEvictionPriority() override {
            return this->m_pReal->GetEvictionPriority();
        }
    };

} // namespace d3d11