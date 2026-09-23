#include "d3d11/ProxyD3D11Buffer.h"

namespace d3d11 {

    ProxyD3D11Buffer::ProxyD3D11Buffer(ID3D11Buffer* pReal, const D3D11_BUFFER_DESC* pDesc)
        : ProxyD3D11Resource<ProxyD3D11Buffer, ID3D11Buffer>(pReal)
    {
        if (pDesc) {
            m_Desc = *pDesc;
        }
        else {
            this->m_pReal->GetDesc(&m_Desc);
        }
    }

    ProxyD3D11Buffer::~ProxyD3D11Buffer() {
        
    }

    void STDMETHODCALLTYPE ProxyD3D11Buffer::GetDesc(D3D11_BUFFER_DESC* pDesc) {
        if (pDesc) {
            *pDesc = m_Desc;
        }
    }

} // namespace d3d11