#include "d3d11/ProxyD3D11Buffer.h"

namespace d3d11 {

    ProxyD3D11Buffer::ProxyD3D11Buffer(ID3D11Buffer* pReal, const D3D11_BUFFER_DESC* pDesc)
        : ProxyD3D11Resource<ID3D11Buffer>(pReal),
        m_ByteWidth(pDesc->ByteWidth),
        m_BindFlags(pDesc->BindFlags)
    { }

    ProxyD3D11Buffer::~ProxyD3D11Buffer() {

        //D3D11StateTracker::Get().UnregisterBuffer(this);
    }

} // namespace d3d11