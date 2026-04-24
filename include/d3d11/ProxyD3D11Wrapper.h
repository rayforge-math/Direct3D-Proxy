#pragma once

#include "d3d/ProxyWrapper.h"
#include "d3d11/ProxyD3D11Buffer.h"

using namespace d3d;

namespace d3d11 {

    class ProxyD3D11Wrapper {
    public:
        // --- WRAPPING (Output from Driver -> Game) ---

        static inline void WrapBuffers(ID3D11Buffer** ppBuffers, UINT count) {
            ProxyWrapper::WrapArray<ProxyD3D11Buffer>(ppBuffers, count);
        }

        // --- UNWRAPPING (Input from Game -> Driver) ---

        /**
         * Constant Buffers: Max 14 slots
         */
        static inline auto UnwrapCBs(ID3D11Buffer* const* ppCBs, UINT count) {
            return ProxyWrapper::UnwrapArray<ID3D11Buffer, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT>(ppCBs, count);
        }

        /**
         * Vertex Buffers: Max 32 slots
         */
        static inline auto UnwrapVBs(ID3D11Buffer* const* ppVBs, UINT count) {
            return ProxyWrapper::UnwrapArray<ID3D11Buffer, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT>(ppVBs, count);
        }

        /**
         * Stream-Output: Max 4 slots
         */
        static inline auto UnwrapSOBs(ID3D11Buffer* const* ppSOBs, UINT count) {
            return ProxyWrapper::UnwrapArray<ID3D11Buffer, D3D11_SO_BUFFER_SLOT_COUNT>(ppSOBs, count);
        }

    };

} // namespace d3d11