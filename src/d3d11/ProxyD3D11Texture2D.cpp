#include "d3d11/ProxyD3D11Texture2D.h"

namespace d3d11 {

    ProxyD3D11Texture2D::ProxyD3D11Texture2D(ID3D11Texture2D* pReal, const D3D11_TEXTURE2D_DESC* pDesc)
        : ProxyD3D11Resource<ID3D11Texture2D, ProxyD3D11Texture2D>(pReal, D3D11_RESOURCE_DIMENSION_TEXTURE2D)
    {
        if (pDesc) {
            m_Desc = *pDesc;
        }
        else {
            this->m_pReal->GetDesc(&m_Desc);
        }
    }

    ProxyD3D11Texture2D::~ProxyD3D11Texture2D() {
    }

    void STDMETHODCALLTYPE ProxyD3D11Texture2D::GetDesc(D3D11_TEXTURE2D_DESC* pDesc) {
        if (pDesc) {
            *pDesc = m_Desc;
        }
    }

} // namespace d3d11