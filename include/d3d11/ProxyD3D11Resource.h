#pragma once

#include "d3d11/d3d11_version.h"
#include "d3d/ProxyD3D.h"

namespace d3d11 {

    /**
     * Intermediate Proxy for all ID3D11Resource types (Buffers, Textures).
     * Handles shared resource methods.
     */
    template <typename T>
    class ProxyD3D11Resource : public d3d::ProxyD3D<T> {
    public:
        ProxyD3D11Resource(T* pReal) : d3d::ProxyD3D<T>(pReal) {}

        virtual ~ProxyD3D11Resource() = default;

        // --- ID3D11DeviceChild Methods ---
        virtual void STDMETHODCALLTYPE GetDevice(ID3D11Device** ppDevice) override {
            this->m_pReal->GetDevice(ppDevice);
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

        // --- ID3D11Resource Methods ---
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