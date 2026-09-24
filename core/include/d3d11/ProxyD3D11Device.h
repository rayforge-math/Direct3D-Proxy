#pragma once

#include "coreapi.h"
#include "d3d/ProxyD3D.h"
#include "d3d11/d3d11_version.h"

namespace d3d11 {

    /**
     * @class ProxyD3D11Device
     * @brief A virtualized wrapper for the ID3D11Device interface, serving as a resource factory interceptor.
     *
     * @details
     * This class implements the Proxy pattern for the primary Direct3D 11 resource creator.
     * By intercepting the creation of all graphical objects, it provides a centralized
     * point for resource management and metadata tracking.
     *
     * Core Functional Purposes:
     * - **Resource Lifetime Tracking:** Monitors the allocation and deallocation of buffers,
     * textures, and shaders to detect resource leaks or excessive memory usage.
     * - **Descriptor Modification:** Allows for the real-time modification of resource
     * descriptions (e.g., adding D3D11_RESOURCE_MISC_SHARED flags to textures) before
     * they are finalized by the real driver.
     * - **Automatic Proxy Wrapping:** Ensures that any child objects created (like
     * Immediate or Deferred Contexts) are automatically wrapped in their respective
     * proxy classes before being returned to the application.
     * - **Capability Shimming:** Intercepts hardware capability queries (CheckFeatureSupport)
     * to report specific compatibility profiles or to hide certain features from the application.
     *
     * Use Cases in Proxy Engineering:
     * 1. **Asset Interception:** Capturing shader bytecode or texture data during the creation
     * phase for export or external analysis.
     * 2. **Shared Resource Injection:** Facilitating cross-API interoperability by injecting
     * sharing flags into resources that the host application originally intended to be private.
     * 3. **Validation Layer:** Providing a custom diagnostic layer to log resource creation
     * parameters that may be inconsistent with modern hardware requirements.
     */
    class CORE_API ProxyD3D11Device : public d3d::ProxyD3D<ProxyD3D11Device, ID3D11Device5, IDXGIDevice4> {
    private:
		IDXGIDevice4* m_pRealDXGI;

    public:
        ProxyD3D11Device(ID3D11Device5* pReal);

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override;

        // --- ID3D11Device Methods ---
        virtual HRESULT STDMETHODCALLTYPE CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer) override;
        virtual HRESULT STDMETHODCALLTYPE CreateTexture1D(const D3D11_TEXTURE1D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture1D** ppTexture1D) override;
        virtual HRESULT STDMETHODCALLTYPE CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D) override;
        virtual HRESULT STDMETHODCALLTYPE CreateTexture3D(const D3D11_TEXTURE3D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture3D** ppTexture3D) override;
        virtual HRESULT STDMETHODCALLTYPE CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView) override;
        virtual HRESULT STDMETHODCALLTYPE CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView) override;
        virtual HRESULT STDMETHODCALLTYPE CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView) override;
        virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView) override;
        virtual HRESULT STDMETHODCALLTYPE CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout) override;
        virtual HRESULT STDMETHODCALLTYPE CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader) override;
        virtual HRESULT STDMETHODCALLTYPE CreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader) override;
        virtual HRESULT STDMETHODCALLTYPE CreateGeometryShaderWithStreamOutput(const void* pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY* pSODeclaration, UINT NumEntries, const UINT* pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader) override;
        virtual HRESULT STDMETHODCALLTYPE CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader) override;
        virtual HRESULT STDMETHODCALLTYPE CreateHullShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11HullShader** ppHullShader) override;
        virtual HRESULT STDMETHODCALLTYPE CreateDomainShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11DomainShader** ppDomainShader) override;
        virtual HRESULT STDMETHODCALLTYPE CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11ComputeShader** ppComputeShader) override;
        virtual HRESULT STDMETHODCALLTYPE CreateClassLinkage(ID3D11ClassLinkage** ppLinkage) override;
        virtual HRESULT STDMETHODCALLTYPE CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState) override;
        virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState) override;
        virtual HRESULT STDMETHODCALLTYPE CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState) override;
        virtual HRESULT STDMETHODCALLTYPE CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState) override;
        virtual HRESULT STDMETHODCALLTYPE CreateQuery(const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery) override;
        virtual HRESULT STDMETHODCALLTYPE CreatePredicate(const D3D11_QUERY_DESC* pPredicateDesc, ID3D11Predicate** ppPredicate) override;
        virtual HRESULT STDMETHODCALLTYPE CreateCounter(const D3D11_COUNTER_DESC* pCounterDesc, ID3D11Counter** ppCounter) override;
        virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext(UINT ContextFlags, ID3D11DeviceContext** ppDeferredContext) override;
        virtual HRESULT STDMETHODCALLTYPE OpenSharedResource(HANDLE hResource, REFIID ReturnedInterface, void** ppResource) override;
        virtual HRESULT STDMETHODCALLTYPE CheckFormatSupport(DXGI_FORMAT Format, UINT* pFormatSupport) override;
        virtual HRESULT STDMETHODCALLTYPE CheckMultisampleQualityLevels(DXGI_FORMAT Format, UINT SampleCount, UINT* pNumQualityLevels) override;
        virtual void STDMETHODCALLTYPE CheckCounterInfo(D3D11_COUNTER_INFO* pCounterInfo) override;
        virtual HRESULT STDMETHODCALLTYPE CheckCounter(const D3D11_COUNTER_DESC* pDesc, D3D11_COUNTER_TYPE* pType, UINT* pActiveCounters, LPSTR szName, UINT* pNameLength, LPSTR szUnits, UINT* pUnitsLength, LPSTR szDescription, UINT* pDescriptionLength) override;
        virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport(D3D11_FEATURE Feature, void* pFeatureSupportData, UINT FeatureSupportDataSize) override;
        virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) override;
        virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) override;
        virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) override;
        virtual D3D_FEATURE_LEVEL STDMETHODCALLTYPE GetFeatureLevel(void) override;
        virtual UINT STDMETHODCALLTYPE GetCreationFlags(void) override;
        virtual HRESULT STDMETHODCALLTYPE GetDeviceRemovedReason(void) override;
        virtual void STDMETHODCALLTYPE GetImmediateContext(ID3D11DeviceContext** ppImmediateContext) override;
        virtual HRESULT STDMETHODCALLTYPE SetExceptionMode(UINT RaiseFlags) override;
        virtual UINT STDMETHODCALLTYPE GetExceptionMode(void) override;

        // --- ID3D11Device1 Methods ---
        virtual void STDMETHODCALLTYPE GetImmediateContext1(ID3D11DeviceContext1** ppImmediateContext) override;
        virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext1(UINT ContextFlags, ID3D11DeviceContext1** ppDeferredContext) override;
        virtual HRESULT STDMETHODCALLTYPE CreateBlendState1(const D3D11_BLEND_DESC1* pBlendStateDesc, ID3D11BlendState1** ppBlendState) override;
        virtual HRESULT STDMETHODCALLTYPE CreateRasterizerState1(const D3D11_RASTERIZER_DESC1* pRasterizerDesc, ID3D11RasterizerState1** ppRasterizerState) override;
        virtual HRESULT STDMETHODCALLTYPE CreateDeviceContextState(UINT Flags, const D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, REFIID EmulatedInterface, D3D_FEATURE_LEVEL* pChosenFeatureLevel, ID3DDeviceContextState** ppContextState) override;
        virtual HRESULT STDMETHODCALLTYPE OpenSharedResource1(HANDLE hResource, REFIID ReturnedInterface, void** ppResource) override;
        virtual HRESULT STDMETHODCALLTYPE OpenSharedResourceByName(LPCWSTR lpName, DWORD dwDesiredAccess, REFIID ReturnedInterface, void** ppResource) override;

        // --- ID3D11Device2 Methods ---
        virtual void STDMETHODCALLTYPE GetImmediateContext2(ID3D11DeviceContext2** ppImmediateContext) override;
        virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext2(UINT ContextFlags, ID3D11DeviceContext2** ppDeferredContext) override;
        virtual void STDMETHODCALLTYPE GetResourceTiling(ID3D11Resource* pTiledResource, UINT* pNumTilesForEntireResource, D3D11_PACKED_MIP_DESC* pPackedMipDesc, D3D11_TILE_SHAPE* pStandardTileShapeForNonPackedMips, UINT* pNumSubresourceTilings, UINT FirstSubresourceTilingToGet, D3D11_SUBRESOURCE_TILING* pSubresourceTilingsForNonPackedMips) override;
        virtual HRESULT STDMETHODCALLTYPE CheckMultisampleQualityLevels1(DXGI_FORMAT Format, UINT SampleCount, UINT Flags, UINT* pNumQualityLevels) override;

        // --- ID3D11Device3 Methods ---
        virtual HRESULT STDMETHODCALLTYPE CreateTexture2D1(const D3D11_TEXTURE2D_DESC1* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D1** ppTexture2D) override;
        virtual HRESULT STDMETHODCALLTYPE CreateTexture3D1(const D3D11_TEXTURE3D_DESC1* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture3D1** ppTexture3D) override;
        virtual HRESULT STDMETHODCALLTYPE CreateRasterizerState2(const D3D11_RASTERIZER_DESC2* pRasterizerDesc, ID3D11RasterizerState2** ppRasterizerState) override;
        virtual HRESULT STDMETHODCALLTYPE CreateShaderResourceView1(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC1* pDesc, ID3D11ShaderResourceView1** ppSRView) override;
        virtual HRESULT STDMETHODCALLTYPE CreateUnorderedAccessView1(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC1* pDesc, ID3D11UnorderedAccessView1** ppUAView) override;
        virtual HRESULT STDMETHODCALLTYPE CreateRenderTargetView1(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC1* pDesc, ID3D11RenderTargetView1** ppRTView) override;
        virtual HRESULT STDMETHODCALLTYPE CreateQuery1(const D3D11_QUERY_DESC1* pQueryDesc, ID3D11Query1** ppQuery) override;
        virtual void STDMETHODCALLTYPE GetImmediateContext3(ID3D11DeviceContext3** ppImmediateContext) override;
        virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext3(UINT ContextFlags, ID3D11DeviceContext3** ppDeferredContext) override;
        virtual void STDMETHODCALLTYPE WriteToSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) override;
        virtual void STDMETHODCALLTYPE ReadFromSubresource(void* pDstData, UINT DstRowPitch, UINT DstDepthPitch, ID3D11Resource* pSrcResource, UINT SrcSubresource, const D3D11_BOX* pSrcBox) override;

        // --- ID3D11Device4 Methods ---
        virtual HRESULT STDMETHODCALLTYPE RegisterDeviceRemovedEvent(HANDLE hEvent, DWORD* pdwCookie) override;
        virtual void STDMETHODCALLTYPE UnregisterDeviceRemoved(DWORD dwCookie) override;

        // --- ID3D11Device5 Methods ---
        virtual HRESULT STDMETHODCALLTYPE OpenSharedFence(HANDLE hFence, REFIID ReturnedInterface, void** ppFence) override;
        virtual HRESULT STDMETHODCALLTYPE CreateFence(UINT64 InitialValue, D3D11_FENCE_FLAG Flags, REFIID ReturnedInterface, void** ppFence) override;

        // --- IDXGIObject Methods ---
        virtual HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void** ppParent) override;

        // --- IDXGIDevice Methods ---
        virtual HRESULT STDMETHODCALLTYPE GetAdapter(IDXGIAdapter** pAdapter) override;
        virtual HRESULT STDMETHODCALLTYPE CreateSurface(const DXGI_SURFACE_DESC* pDesc, UINT NumSurfaces, DXGI_USAGE Usage, const DXGI_SHARED_RESOURCE* pSharedResource, IDXGISurface** ppSurface) override;
        virtual HRESULT STDMETHODCALLTYPE QueryResourceResidency(IUnknown* const* ppResources, DXGI_RESIDENCY* pResidencyStatus, UINT NumResources) override;
        virtual HRESULT STDMETHODCALLTYPE SetGPUThreadPriority(INT Priority) override;
        virtual HRESULT STDMETHODCALLTYPE GetGPUThreadPriority(INT* pPriority) override;

        // --- IDXGIDevice1 Methods ---
        virtual HRESULT STDMETHODCALLTYPE SetMaximumFrameLatency(UINT MaxLatency) override;
        virtual HRESULT STDMETHODCALLTYPE GetMaximumFrameLatency(UINT* pMaxLatency) override;

        // --- IDXGIDevice2 Methods ---
        virtual HRESULT STDMETHODCALLTYPE OfferResources(UINT NumResources, IDXGIResource* const* ppResources, DXGI_OFFER_RESOURCE_PRIORITY Priority) override;
        virtual HRESULT STDMETHODCALLTYPE ReclaimResources(UINT NumResources, IDXGIResource* const* ppResources, BOOL* pDiscarded) override;
        virtual HRESULT STDMETHODCALLTYPE EnqueueSetEvent(HANDLE hEvent) override;

        // --- IDXGIDevice3 Methods ---
        virtual void STDMETHODCALLTYPE Trim(void) override;

        // --- IDXGIDevice4 Methods ---
        virtual HRESULT STDMETHODCALLTYPE OfferResources1(UINT NumResources, IDXGIResource* const* ppResources, DXGI_OFFER_RESOURCE_PRIORITY Priority, UINT Flags) override;
        virtual HRESULT STDMETHODCALLTYPE ReclaimResources1(UINT NumResources, IDXGIResource* const* ppResources, DXGI_RECLAIM_RESOURCE_RESULTS* pResults) override;
    };

} // namespace d3d11