#include "d3d11/ProxyD3D11Texture3D.h"

namespace d3d11 {

    ProxyD3D11Texture3D::ProxyD3D11Texture3D(ID3D11Texture3D* pReal, const D3D11_TEXTURE3D_DESC* pDesc)
        : ProxyD3D11Resource<ID3D11Texture3D, ProxyD3D11Texture3D>(pReal, D3D11_RESOURCE_DIMENSION_TEXTURE3D)
    {
        if (pDesc) {
            m_Desc = *pDesc;
        }
        else {
            this->m_pReal->GetDesc(&m_Desc);
        }
    }

    ProxyD3D11Texture3D::~ProxyD3D11Texture3D() {
    }

    void STDMETHODCALLTYPE ProxyD3D11Texture3D::GetDesc(D3D11_TEXTURE3D_DESC* pDesc) {
        if (pDesc) {
            *pDesc = m_Desc;
        }
    }

} // namespace d3d11