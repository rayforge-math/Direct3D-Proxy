#pragma once
#include "d3d/ProxyWrapper.h"
#include "d3d11/ProxyD3D11Buffer.h"
// Inkludiere hier bei Bedarf weitere Proxy-Header (z.B. SRV, RTV, Sampler etc.)
// #include "d3d11/ProxyD3D11ShaderResourceView.h"
// #include "d3d11/ProxyD3D11RenderTargetView.h"
// #include "d3d11/ProxyD3D11UnorderedAccessView.h"
// #include "d3d11/ProxyD3D11DepthStencilView.h"
// #include "d3d11/ProxyD3D11SamplerState.h"
// #include "d3d11/ProxyD3D11Resource.h"
#include "debug.h"

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
            LOG_MSG("ProxyD3D11Wrapper::WrapBuffers called");
            return ProxyWrapper::WrapArray<ProxyD3D11Buffer>(pp, count);
        }

        static inline HRESULT Wrap(ID3D11Buffer** pp) {
            LOG_MSG("ProxyD3D11Wrapper::Wrap (Buffer) called");
            return ProxyWrapper::Wrap<ProxyD3D11Buffer>(pp);
        }
        /*
        static inline HRESULT Wrap(ID3D11ShaderResourceView** pp) {
            LOG_MSG("ProxyD3D11Wrapper::Wrap (SRV) called");
            return ProxyWrapper::Wrap<ProxyD3D11ShaderResourceView>(pp);
        }

        static inline HRESULT Wrap(ID3D11UnorderedAccessView** pp) {
            LOG_MSG("ProxyD3D11Wrapper::Wrap (UAV) called");
            return ProxyWrapper::Wrap<ProxyD3D11UnorderedAccessView>(pp);
        }

        static inline HRESULT Wrap(ID3D11RenderTargetView** pp) {
            LOG_MSG("ProxyD3D11Wrapper::Wrap (RTV) called");
            return ProxyWrapper::Wrap<ProxyD3D11RenderTargetView>(pp);
        }

        static inline HRESULT Wrap(ID3D11DepthStencilView** pp) {
            LOG_MSG("ProxyD3D11Wrapper::Wrap (DSV) called");
            return ProxyWrapper::Wrap<ProxyD3D11DepthStencilView>(pp);
        }

        static inline HRESULT Wrap(ID3D11SamplerState** pp) {
            LOG_MSG("ProxyD3D11Wrapper::Wrap (Sampler) called");
            return ProxyWrapper::Wrap<ProxyD3D11SamplerState>(pp);
        }
        */
        static inline HRESULT Wrap(ID3D11Resource** pp) {
            LOG_MSG("ProxyD3D11Wrapper::Wrap (Resource) called");
            if (!pp || !*pp) return S_OK;

            D3D11_RESOURCE_DIMENSION dim = D3D11_RESOURCE_DIMENSION_UNKNOWN;
            (*pp)->GetType(&dim);

            if (dim == D3D11_RESOURCE_DIMENSION_BUFFER) {
                return ProxyWrapper::Wrap<ProxyD3D11Buffer>(reinterpret_cast<ID3D11Buffer**>(pp));
            }/*
            else if (dim == D3D11_RESOURCE_DIMENSION_TEXTURE2D) {
                return ProxyWrapper::Wrap<ProxyD3D11Texture2D>(reinterpret_cast<ID3D11Texture2D**>(pp));
            }
            else if (dim == D3D11_RESOURCE_DIMENSION_TEXTURE1D) {
                return ProxyWrapper::Wrap<ProxyD3D11Texture1D>(reinterpret_cast<ID3D11Texture1D**>(pp));
            }
            else if (dim == D3D11_RESOURCE_DIMENSION_TEXTURE3D) {
                return ProxyWrapper::Wrap<ProxyD3D11Texture3D>(reinterpret_cast<ID3D11Texture3D**>(pp));
            }*/

            return S_OK;
        }

        // ================================================================
        // UNWRAPPING (Input from Game -> Driver)
        // ================================================================

        /**         
        * Unwraps an ID3D11Buffer array for a specific pipeline context.         
        * TSlotContext must be one of: D3D11CB, D3D11VB, D3D11SOB         
        */
        template <typename TSlotContext>
            requires HasD3D11SlotCount<TSlotContext>
        static inline auto UnwrapBuffers(ID3D11Buffer* const* pp, UINT count) {
            LOG_MSG("ProxyD3D11Wrapper::UnwrapBuffers called");
            return ProxyWrapper::UnwrapArray<ProxyD3D11Buffer, D3D11SlotCount<TSlotContext>::value>(pp, count);
        }

        /**         
        * Unwraps any interface array whose slot count is registered in D3D11SlotCount.         
        */
        template <typename T>
            requires HasD3D11SlotCount<T>
        static inline auto UnwrapViews(T* const* pp, UINT count) {
            LOG_MSG("ProxyD3D11Wrapper::UnwrapViews called");
            return ProxyWrapper::UnwrapArray<T, D3D11SlotCount<T>::value>(pp, count);
        }

        // Single Pointer Unwrapping
        static inline ID3D11Buffer* Unwrap(ID3D11Buffer* p) {
            LOG_MSG("ProxyD3D11Wrapper::Unwrap (Buffer) called");
            return ProxyWrapper::Unwrap<ProxyD3D11Buffer>(p);
        }
        /*
        static inline ID3D11ShaderResourceView* Unwrap(ID3D11ShaderResourceView* p) {
            LOG_MSG("ProxyD3D11Wrapper::Unwrap (SRV) called");
            return ProxyWrapper::Unwrap<ProxyD3D11ShaderResourceView>(p);
        }

        static inline ID3D11UnorderedAccessView* Unwrap(ID3D11UnorderedAccessView* p) {
            LOG_MSG("ProxyD3D11Wrapper::Unwrap (UAV) called");
            return ProxyWrapper::Unwrap<ProxyD3D11UnorderedAccessView>(p);
        }

        static inline ID3D11RenderTargetView* Unwrap(ID3D11RenderTargetView* p) {
            LOG_MSG("ProxyD3D11Wrapper::Unwrap (RTV) called");
            return ProxyWrapper::Unwrap<ProxyD3D11RenderTargetView>(p);
        }

        static inline ID3D11DepthStencilView* Unwrap(ID3D11DepthStencilView* p) {
            LOG_MSG("ProxyD3D11Wrapper::Unwrap (DSV) called");
            return ProxyWrapper::Unwrap<ProxyD3D11DepthStencilView>(p);
        }

        static inline ID3D11SamplerState* Unwrap(ID3D11SamplerState* p) {
            LOG_MSG("ProxyD3D11Wrapper::Unwrap (Sampler) called");
            return ProxyWrapper::Unwrap<ProxyD3D11SamplerState>(p);
        }
        */
        static inline ID3D11Resource* Unwrap(ID3D11Resource* p) {
            LOG_MSG("ProxyD3D11Wrapper::Unwrap (Resource) called");
            if (!p) return nullptr;

            if (auto* pReal = ProxyWrapper::Unwrap<ProxyD3D11Buffer>(reinterpret_cast<ID3D11Buffer*>(p)))
                return pReal;/*
            if (auto* pReal = ProxyWrapper::Unwrap<ProxyD3D11Texture2D>(reinterpret_cast<ID3D11Texture2D*>(p)))
                return pReal;
            if (auto* pReal = ProxyWrapper::Unwrap<ProxyD3D11Texture1D>(reinterpret_cast<ID3D11Texture1D*>(p)))
                return pReal;
            if (auto* pReal = ProxyWrapper::Unwrap<ProxyD3D11Texture3D>(reinterpret_cast<ID3D11Texture3D*>(p)))
                return pReal;
                */
            return p;
        }
    };

} // namespace d3d11