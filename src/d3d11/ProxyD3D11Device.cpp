#pragma once

#include "d3d11/ProxyD3D11Device.h"

namespace d3d11 {

    ProxyD3D11Device::ProxyD3D11Device(ID3D11Device* pReal)
        : m_pReal(pReal), m_RefCount(1)
    {
        if (m_pReal) {
            m_pReal->AddRef();
        }
    }

    ProxyD3D11Device::~ProxyD3D11Device() {
        if (m_pReal) {
            m_pReal->Release();
            m_pReal = nullptr;
        }
    }

    // --- IUnknown Methods ---
    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::QueryInterface(REFIID riid, void** ppvObject) {
        if (riid == __uuidof(ID3D11Device) || riid == __uuidof(IUnknown)) {
            AddRef();
            *ppvObject = this;
            return S_OK;
        }
        return m_pReal->QueryInterface(riid, ppvObject);
    }

    ULONG STDMETHODCALLTYPE ProxyD3D11Device::AddRef() {
        m_pReal->AddRef();
        return InterlockedIncrement(&m_RefCount);
    }

    ULONG STDMETHODCALLTYPE ProxyD3D11Device::Release() {
        m_pReal->Release();
        ULONG count = InterlockedDecrement(&m_RefCount);
        if (count == 0) delete this;
        return count;
    }

    // --- ID3D11Device Methods ---

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer) {
        return m_pReal->CreateBuffer(pDesc, pInitialData, ppBuffer);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateTexture1D(const D3D11_TEXTURE1D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture1D** ppTexture1D) {
        return m_pReal->CreateTexture1D(pDesc, pInitialData, ppTexture1D);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D) {
        return m_pReal->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateTexture3D(const D3D11_TEXTURE3D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture3D** ppTexture3D) {
        return m_pReal->CreateTexture3D(pDesc, pInitialData, ppTexture3D);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView) {
        return m_pReal->CreateShaderResourceView(pResource, pDesc, ppSRView);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView) {
        return m_pReal->CreateUnorderedAccessView(pResource, pDesc, ppUAView);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView) {
        return m_pReal->CreateRenderTargetView(pResource, pDesc, ppRTView);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView) {
        return m_pReal->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout) {
        return m_pReal->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader) {
        return m_pReal->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader) {
        return m_pReal->CreateGeometryShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateGeometryShaderWithStreamOutput(const void* pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY* pSODeclaration, UINT NumEntries, const UINT* pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader) {
        return m_pReal->CreateGeometryShaderWithStreamOutput(pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries, pBufferStrides, NumStrides, RasterizedStream, pClassLinkage, ppGeometryShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader) {
        return m_pReal->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateHullShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11HullShader** ppHullShader) {
        return m_pReal->CreateHullShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateDomainShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11DomainShader** ppDomainShader) {
        return m_pReal->CreateDomainShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11ComputeShader** ppComputeShader) {
        return m_pReal->CreateComputeShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateClassLinkage(ID3D11ClassLinkage** ppLinkage) {
        return m_pReal->CreateClassLinkage(ppLinkage);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState) {
        return m_pReal->CreateBlendState(pBlendStateDesc, ppBlendState);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState) {
        return m_pReal->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState) {
        return m_pReal->CreateRasterizerState(pRasterizerDesc, ppRasterizerState);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState) {
        return m_pReal->CreateSamplerState(pSamplerDesc, ppSamplerState);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateQuery(const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery) {
        return m_pReal->CreateQuery(pQueryDesc, ppQuery);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreatePredicate(const D3D11_QUERY_DESC* pPredicateDesc, ID3D11Predicate** ppPredicate) {
        return m_pReal->CreatePredicate(pPredicateDesc, ppPredicate);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateCounter(const D3D11_COUNTER_DESC* pCounterDesc, ID3D11Counter** ppCounter) {
        return m_pReal->CreateCounter(pCounterDesc, ppCounter);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateDeferredContext(UINT ContextFlags, ID3D11DeviceContext** ppDeferredContext) {
        return m_pReal->CreateDeferredContext(ContextFlags, ppDeferredContext);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::OpenSharedResource(HANDLE hResource, REFIID ReturnedInterface, void** ppResource) {
        return m_pReal->OpenSharedResource(hResource, ReturnedInterface, ppResource);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CheckFormatSupport(DXGI_FORMAT Format, UINT* pFormatSupport) {
        return m_pReal->CheckFormatSupport(Format, pFormatSupport);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CheckMultisampleQualityLevels(DXGI_FORMAT Format, UINT SampleCount, UINT* pNumQualityLevels) {
        return m_pReal->CheckMultisampleQualityLevels(Format, SampleCount, pNumQualityLevels);
    }

    void STDMETHODCALLTYPE ProxyD3D11Device::CheckCounterInfo(D3D11_COUNTER_INFO* pCounterInfo) {
        m_pReal->CheckCounterInfo(pCounterInfo);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CheckCounter(const D3D11_COUNTER_DESC* pDesc, D3D11_COUNTER_TYPE* pType, UINT* pActiveCounters, LPSTR szName, UINT* pNameLength, LPSTR szUnits, UINT* pUnitsLength, LPSTR szUnitsDescription, UINT* pDescriptionLength) {
        return m_pReal->CheckCounter(pDesc, pType, pActiveCounters, szName, pNameLength, szUnits, pUnitsLength, szUnitsDescription, pDescriptionLength);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CheckFeatureSupport(D3D11_FEATURE Feature, void* pFeatureSupportData, UINT FeatureSupportDataSize) {
        return m_pReal->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) {
        return m_pReal->GetPrivateData(guid, pDataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) {
        return m_pReal->SetPrivateData(guid, DataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) {
        return m_pReal->SetPrivateDataInterface(guid, pData);
    }

    D3D_FEATURE_LEVEL STDMETHODCALLTYPE ProxyD3D11Device::GetFeatureLevel(void) {
        return m_pReal->GetFeatureLevel();
    }

    UINT STDMETHODCALLTYPE ProxyD3D11Device::GetCreationFlags(void) {
        return m_pReal->GetCreationFlags();
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::GetDeviceRemovedReason(void) {
        return m_pReal->GetDeviceRemovedReason();
    }

    void STDMETHODCALLTYPE ProxyD3D11Device::GetImmediateContext(ID3D11DeviceContext** ppImmediateContext) {
        m_pReal->GetImmediateContext(ppImmediateContext);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::SetExceptionMode(UINT RaiseFlags) {
        return m_pReal->SetExceptionMode(RaiseFlags);
    }

    UINT STDMETHODCALLTYPE ProxyD3D11Device::GetExceptionMode(void) {
        return m_pReal->GetExceptionMode();
    }

} // namespace d3d11