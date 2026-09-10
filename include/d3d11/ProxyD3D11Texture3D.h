#pragma once
#include "d3d11/d3d11_version.h"
#include "d3d11/ProxyD3D11Resource.h"

namespace d3d11 {

    class ProxyD3D11Texture3D : public ProxyD3D11Resource<ID3D11Texture3D, ProxyD3D11Texture3D> {
    public:
        ProxyD3D11Texture3D(ID3D11Texture3D* pReal, const D3D11_TEXTURE3D_DESC* pDesc = nullptr);
        virtual ~ProxyD3D11Texture3D() override;

        // --- ID3D11Texture3D Methods ---
        virtual void STDMETHODCALLTYPE GetDesc(D3D11_TEXTURE3D_DESC* pDesc) override;

        // --- Custom Helpers ---
        const D3D11_TEXTURE3D_DESC& GetCachedDesc() const { return m_Desc; }

    private:
        D3D11_TEXTURE3D_DESC m_Desc;
    };

} // namespace d3d11