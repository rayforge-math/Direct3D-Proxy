#pragma once

#include "d3d/ProxyWrapper.h"
#include "d3d11/ProxyD3D11Buffer.h"

using namespace d3d;

namespace d3d11 {

    /**
     * Binds a D3D11 COM interface type (or buffer context tag) to its maximum pipeline slot count.
     * Specialise for every interface that appears in array-based Set/Get calls.
     *
     * Buffer context tags (ID3D11Buffer is context-dependent):
     *   D3D11SlotCount<D3D11CB>  — constant buffers  (14 slots)
     *   D3D11SlotCount<D3D11VB>  — vertex buffers    (32 slots)
     *   D3D11SlotCount<D3D11SOB> — stream-output     ( 4 slots)
     */
    template <typename T>
    struct D3D11SlotCount;

    // --- Buffer context tags ---
    struct D3D11CB {};      // Constant Buffer context
    struct D3D11VB {};      // Vertex Buffer context
    struct D3D11SOB {};     // Stream-Output Buffer context

    template <> struct D3D11SlotCount<D3D11CB>
    : std::integral_constant<size_t, D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT> {
    };

    template <> struct D3D11SlotCount<D3D11VB>
    : std::integral_constant<size_t, D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT> {
    };

    template <> struct D3D11SlotCount<D3D11SOB>
    : std::integral_constant<size_t, D3D11_SO_BUFFER_SLOT_COUNT> {
    };

    // --- Interface types ---
    template <> struct D3D11SlotCount<ID3D11ShaderResourceView>
    : std::integral_constant<size_t, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT> {
    };

    template <> struct D3D11SlotCount<ID3D11UnorderedAccessView>
    : std::integral_constant<size_t, D3D11_1_UAV_SLOT_COUNT> {
    };

    template <> struct D3D11SlotCount<ID3D11RenderTargetView>
    : std::integral_constant<size_t, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> {
    };

    template <> struct D3D11SlotCount<ID3D11SamplerState>
    : std::integral_constant<size_t, D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT> {
    };

    template <typename T>
    concept HasD3D11SlotCount = requires { D3D11SlotCount<T>::value; };

    /**
     * D3D11-specific proxy wrapper.
     * Binds D3D11 slot counts to types so call sites need no explicit MaxCount.
     * ID3D11Buffer requires an explicit context tag (D3D11CB / D3D11VB / D3D11SOB)
     * since its slot count is pipeline-context-dependent.
     */
    class ProxyD3D11Wrapper {
    public:
        // ================================================================
        // WRAPPING (Output from Driver -> Game)
        // ================================================================

        static inline HRESULT WrapBuffers(ID3D11Buffer** pp, UINT count) {
            return ProxyWrapper::WrapArray<ProxyD3D11Buffer>(pp, count);
        }

        /*
        static inline HRESULT WrapTexture1Ds(ID3D11Texture1D** pp, UINT count) {
            return ProxyWrapper::WrapArray<ProxyD3D11Texture1D>(pp, count);
        }
        static inline HRESULT WrapTexture2Ds(ID3D11Texture2D** pp, UINT count) {
            return ProxyWrapper::WrapArray<ProxyD3D11Texture2D>(pp, count);
        }
        static inline HRESULT WrapTexture3Ds(ID3D11Texture3D** pp, UINT count) {
            return ProxyWrapper::WrapArray<ProxyD3D11Texture3D>(pp, count);
        }
        */

        // ================================================================
        // UNWRAPPING (Input from Game -> Driver)
        // ================================================================

        /**
         * Unwraps an ID3D11Buffer array for a specific pipeline context.
         * TSlotContext must be one of: D3D11CB, D3D11VB, D3D11SOB
         *
         * Usage:
         *   UnwrapBuffers<D3D11CB> (pp, count) — constant buffers (14 slots)
         *   UnwrapBuffers<D3D11VB> (pp, count) — vertex buffers   (32 slots)
         *   UnwrapBuffers<D3D11SOB>(pp, count) — stream-output    ( 4 slots)
         */
        template <typename TSlotContext>
            requires HasD3D11SlotCount<TSlotContext>
        static inline auto UnwrapBuffers(ID3D11Buffer* const* pp, UINT count) {
            return ProxyWrapper::UnwrapArray<ID3D11Buffer,
                D3D11SlotCount<TSlotContext>::value>(pp, count);
        }

        /**
         * Unwraps any interface array whose slot count is registered in D3D11SlotCount.
         * T and MaxCount are fully deduced — no explicit parameters needed.
         *
         * Usage:
         *   UnwrapViews(ppSRVs,    count) — SRVs     (128 slots)
         *   UnwrapViews(ppUAVs,    count) — UAVs     ( 64 slots)
         *   UnwrapViews(ppRTVs,    count) — RTVs     (  8 slots)
         *   UnwrapViews(ppSamplers,count) — Samplers ( 16 slots)
         */
        template <typename T>
            requires HasD3D11SlotCount<T>
        static inline auto UnwrapViews(T* const* pp, UINT count) {
            return ProxyWrapper::UnwrapArray<T, D3D11SlotCount<T>::value>(pp, count);
        }

        /**
         * Unwraps a single COM pointer through the registry.
         * T is deduced from the argument — covers DSV, resources, and any other
         * single-slot interface.
         *
         * Usage:
         *   Unwrap(pDSV)      — depth stencil view
         *   Unwrap(pResource) — generic resource
         */
        template <typename T>
        static inline T* Unwrap(T* p) {
            return ProxyWrapper::Unwrap(p);
        }
    };

} // namespace d3d11