#pragma once

#include "d3d11/d3d11_version.h"
#include "ProxyD3D11Resource.h"

namespace d3d11 {

    /**
     * Proxy for ID3D11Buffer.
     * Caches the complete D3D11_BUFFER_DESC for high-performance tracking and
     * zero-overhead GetDesc calls.
     */
    class ProxyD3D11Buffer : public ProxyD3D11Resource<ID3D11Buffer, ProxyD3D11Buffer> {
    public:
        ProxyD3D11Buffer(ID3D11Buffer* pReal, const D3D11_BUFFER_DESC* pDesc = nullptr);

        virtual ~ProxyD3D11Buffer() override;

        // --- ID3D11Buffer Methods ---
        virtual void STDMETHODCALLTYPE GetDesc(D3D11_BUFFER_DESC* pDesc) override;

        // --- Custom Proxy Helpers ---

        /**
         * Direct access to the cached descriptor via const ref.
         */
        const D3D11_BUFFER_DESC& GetCachedDesc() const { return m_Desc; }

        UINT GetByteWidth() const { return m_Desc.ByteWidth; }
        UINT GetBindFlags() const { return m_Desc.BindFlags; }
        D3D11_USAGE GetUsage() const { return m_Desc.Usage; }

    private:
        // Full descriptor cached from D3D11_BUFFER_DESC.
        // This avoids calling the real driver in GetDesc.
        D3D11_BUFFER_DESC m_Desc;
    };

} // namespace d3d11