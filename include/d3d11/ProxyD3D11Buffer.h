#pragma once

#include "d3d11/d3d11_version.h"
#include "ProxyD3D11Resource.h"

namespace d3d11 {

    class ProxyD3D11Buffer : public ProxyD3D11Resource<ID3D11Buffer> {
    public:
        ProxyD3D11Buffer(ID3D11Buffer* pReal, const D3D11_BUFFER_DESC* pDesc);
        virtual ~ProxyD3D11Buffer() override;

        // --- ID3D11Buffer Methods ---
        //virtual void STDMETHODCALLTYPE GetDesc(D3D11_BUFFER_DESC* pDesc) override;

        // --- Custom Proxy Helpers ---

        /**
         * Returns the cached ByteWidth.
         */
        UINT GetByteWidth() const { return m_ByteWidth; }

        /**
         * Identifies the type (Vertex, Index, Constant).
         */
        UINT GetBindFlags() const { return m_BindFlags; }

    private:
        UINT m_ByteWidth;
        UINT m_BindFlags;
    };

} // namespace d3d11