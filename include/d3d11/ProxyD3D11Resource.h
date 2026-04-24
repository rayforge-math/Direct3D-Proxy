#pragma once

#include "d3d11/d3d11_version.h"
#include "d3d/ProxyD3D.h"
#include <concepts>
#include <atomic>

namespace d3d11 {

    template <typename T>
    concept IsResourceInterface = std::derived_from<T, ID3D11Resource>;

    /**
     * Intermediate Proxy for all ID3D11Resource types.
     * Manages the identity (ID and Dimension) for the StateTracker.
     */
    template <IsResourceInterface T>
    class ProxyD3D11Resource : public d3d::ProxyD3D<T> {
    protected:
        uint64_t m_UniqueId;
        D3D11_RESOURCE_DIMENSION m_Dimension;

        // Static atomic counter for thread-safe ID generation
        static inline std::atomic<uint64_t> s_NextId{ 1 };

    public:
        /**
         * @param pReal The real D3D11 resource.
         * @param dim The dimension (e.g., D3D11_RESOURCE_DIMENSION_BUFFER).
         */
        ProxyD3D11Resource(T* pReal, D3D11_RESOURCE_DIMENSION dim)
            : d3d::ProxyD3D<T>(pReal),
            m_UniqueId(s_NextId.fetch_add(1)),
            m_Dimension(dim)
        { }

        virtual ~ProxyD3D11Resource() = default;

        // --- Identity Getters ---

        uint64_t GetUniqueId() const { return m_UniqueId; }
        D3D11_RESOURCE_DIMENSION GetCachedType() const { return m_Dimension; }

        // --- ID3D11DeviceChild Methods ---

        virtual void STDMETHODCALLTYPE GetDevice(ID3D11Device** ppDevice) override {
            if (ppDevice) this->m_pReal->GetDevice(ppDevice);
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
            if (pResourceDimension) {
                *pResourceDimension = m_Dimension;
            }
        }

        virtual void STDMETHODCALLTYPE SetEvictionPriority(UINT EvictionPriority) override {
            this->m_pReal->SetEvictionPriority(EvictionPriority);
        }

        virtual UINT STDMETHODCALLTYPE GetEvictionPriority() override {
            return this->m_pReal->GetEvictionPriority();
        }
    };

} // namespace d3d11