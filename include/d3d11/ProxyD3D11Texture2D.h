#pragma once
#include "d3d11/d3d11_version.h"
#include "d3d11/ProxyD3D11Resource.h"

namespace d3d11 {

    class ProxyD3D11Texture2D : public ProxyD3D11Resource<ID3D11Texture2D, ProxyD3D11Texture2D> {
    public:
        ProxyD3D11Texture2D(ID3D11Texture2D* pReal, const D3D11_TEXTURE2D_DESC* pDesc = nullptr);
        virtual ~ProxyD3D11Texture2D() override;

        // --- ID3D11Texture2D Methods ---
        virtual void STDMETHODCALLTYPE GetDesc(D3D11_TEXTURE2D_DESC* pDesc) override;

        // --- Custom Helpers ---
        const D3D11_TEXTURE2D_DESC& GetCachedDesc() const { return m_Desc; }
        UINT GetWidth() const { return m_Desc.Width; }
        UINT GetHeight() const { return m_Desc.Height; }
        DXGI_FORMAT GetFormat() const { return m_Desc.Format; }
        UINT GetMipLevels() const { return m_Desc.MipLevels; }

    private:
        D3D11_TEXTURE2D_DESC m_Desc;
    };

} // namespace d3d11