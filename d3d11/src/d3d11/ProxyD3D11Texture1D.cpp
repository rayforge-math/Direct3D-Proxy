#include "d3d11/ProxyD3D11Texture1D.h"

namespace d3d11 {

    ProxyD3D11Texture1D::ProxyD3D11Texture1D(ID3D11Texture1D* pReal, const D3D11_TEXTURE1D_DESC* pDesc)
        : ProxyD3D11Resource<ID3D11Texture1D, ProxyD3D11Texture1D>(pReal, D3D11_RESOURCE_DIMENSION_TEXTURE1D)
    {
        if (pDesc) {
            m_Desc = *pDesc;
        }
        else {
            this->m_pReal->GetDesc(&m_Desc);
        }
    }

    ProxyD3D11Texture1D::~ProxyD3D11Texture1D() {
    }

    void STDMETHODCALLTYPE ProxyD3D11Texture1D::GetDesc(D3D11_TEXTURE1D_DESC* pDesc) {
        if (pDesc) {
            *pDesc = m_Desc;
        }
    }

} // namespace d3d11