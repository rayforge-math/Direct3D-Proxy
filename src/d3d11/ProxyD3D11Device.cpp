#pragma once

#include "d3d11/ProxyD3D11Device.h"
#include "d3d11/ProxyD3D11Buffer.h"
#include "d3d/ProxyWrapper.h"
#include "debug.h"
#include <d3d11/ProxyD3D11DeviceContext.h>

using namespace d3d;

namespace d3d11 {

    ProxyD3D11Device::ProxyD3D11Device(ID3D11Device* device)
        : ProxyD3D<ID3D11Device, ProxyD3D11Device>(device)
    { }

    // --- ID3D11Device Methods ---

    // --- ID3D11Device Creation & Management Methods ---

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer) {
        LOG_MSG("ProxyD3D11Device::CreateBuffer called");
        HRESULT hr = m_pReal->CreateBuffer(pDesc, pInitialData, ppBuffer);
        /*
        if (SUCCEEDED(hr)) {
            hr = ProxyWrapper::Wrap<ProxyD3D11Buffer>(ppBuffer, pDesc);
        }
        */
        
        return hr;
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateTexture1D(const D3D11_TEXTURE1D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture1D** ppTexture1D) {
        LOG_MSG("ProxyD3D11Device::CreateTexture1D called");
        return m_pReal->CreateTexture1D(pDesc, pInitialData, ppTexture1D);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D) {
        LOG_MSG("ProxyD3D11Device::CreateTexture2D called");
        return m_pReal->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateTexture3D(const D3D11_TEXTURE3D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture3D** ppTexture3D) {
        LOG_MSG("ProxyD3D11Device::CreateTexture3D called");
        return m_pReal->CreateTexture3D(pDesc, pInitialData, ppTexture3D);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView) {
        LOG_MSG("ProxyD3D11Device::CreateShaderResourceView called");
        return m_pReal->CreateShaderResourceView(pResource, pDesc, ppSRView);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView) {
        LOG_MSG("ProxyD3D11Device::CreateUnorderedAccessView called");
        return m_pReal->CreateUnorderedAccessView(pResource, pDesc, ppUAView);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView) {
        LOG_MSG("ProxyD3D11Device::CreateRenderTargetView called");
        return m_pReal->CreateRenderTargetView(pResource, pDesc, ppRTView);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView) {
        LOG_MSG("ProxyD3D11Device::CreateDepthStencilView called");
        return m_pReal->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout) {
        LOG_MSG("ProxyD3D11Device::CreateInputLayout called");
        return m_pReal->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader) {
        LOG_MSG("ProxyD3D11Device::CreateVertexShader called");
        return m_pReal->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader) {
        LOG_MSG("ProxyD3D11Device::CreateGeometryShader called");
        return m_pReal->CreateGeometryShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateGeometryShaderWithStreamOutput(const void* pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY* pSODeclaration, UINT NumEntries, const UINT* pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader) {
        LOG_MSG("ProxyD3D11Device::CreateGeometryShaderWithStreamOutput called");
        return m_pReal->CreateGeometryShaderWithStreamOutput(pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries, pBufferStrides, NumStrides, RasterizedStream, pClassLinkage, ppGeometryShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader) {
        LOG_MSG("ProxyD3D11Device::CreatePixelShader called");
        return m_pReal->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateHullShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11HullShader** ppHullShader) {
        LOG_MSG("ProxyD3D11Device::CreateHullShader called");
        return m_pReal->CreateHullShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateDomainShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11DomainShader** ppDomainShader) {
        LOG_MSG("ProxyD3D11Device::CreateDomainShader called");
        return m_pReal->CreateDomainShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11ComputeShader** ppComputeShader) {
        LOG_MSG("ProxyD3D11Device::CreateComputeShader called");
        return m_pReal->CreateComputeShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateClassLinkage(ID3D11ClassLinkage** ppLinkage) {
        LOG_MSG("ProxyD3D11Device::CreateClassLinkage called");
        return m_pReal->CreateClassLinkage(ppLinkage);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState) {
        LOG_MSG("ProxyD3D11Device::CreateBlendState called");
        return m_pReal->CreateBlendState(pBlendStateDesc, ppBlendState);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState) {
        LOG_MSG("ProxyD3D11Device::CreateDepthStencilState called");
        return m_pReal->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState) {
        LOG_MSG("ProxyD3D11Device::CreateRasterizerState called");
        return m_pReal->CreateRasterizerState(pRasterizerDesc, ppRasterizerState);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState) {
        LOG_MSG("ProxyD3D11Device::CreateSamplerState called");
        return m_pReal->CreateSamplerState(pSamplerDesc, ppSamplerState);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateQuery(const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery) {
        LOG_MSG("ProxyD3D11Device::CreateQuery called");
        return m_pReal->CreateQuery(pQueryDesc, ppQuery);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreatePredicate(const D3D11_QUERY_DESC* pPredicateDesc, ID3D11Predicate** ppPredicate) {
        LOG_MSG("ProxyD3D11Device::CreatePredicate called");
        return m_pReal->CreatePredicate(pPredicateDesc, ppPredicate);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateCounter(const D3D11_COUNTER_DESC* pCounterDesc, ID3D11Counter** ppCounter) {
        LOG_MSG("ProxyD3D11Device::CreateCounter called");
        return m_pReal->CreateCounter(pCounterDesc, ppCounter);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateDeferredContext(UINT ContextFlags, ID3D11DeviceContext** ppDeferredContext) {
        LOG_MSG("ProxyD3D11Device::CreateDeferredContext called");
        return m_pReal->CreateDeferredContext(ContextFlags, ppDeferredContext);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::OpenSharedResource(HANDLE hResource, REFIID ReturnedInterface, void** ppResource) {
        LOG_MSG("ProxyD3D11Device::OpenSharedResource called");
        return m_pReal->OpenSharedResource(hResource, ReturnedInterface, ppResource);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CheckFormatSupport(DXGI_FORMAT Format, UINT* pFormatSupport) {
        LOG_MSG("ProxyD3D11Device::CheckFormatSupport called");
        return m_pReal->CheckFormatSupport(Format, pFormatSupport);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CheckMultisampleQualityLevels(DXGI_FORMAT Format, UINT SampleCount, UINT* pNumQualityLevels) {
        LOG_MSG("ProxyD3D11Device::CheckMultisampleQualityLevels called");
        return m_pReal->CheckMultisampleQualityLevels(Format, SampleCount, pNumQualityLevels);
    }

    void STDMETHODCALLTYPE ProxyD3D11Device::CheckCounterInfo(D3D11_COUNTER_INFO* pCounterInfo) {
        LOG_MSG("ProxyD3D11Device::CheckCounterInfo called");
        m_pReal->CheckCounterInfo(pCounterInfo);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CheckCounter(const D3D11_COUNTER_DESC* pDesc, D3D11_COUNTER_TYPE* pType, UINT* pActiveCounters, LPSTR szName, UINT* pNameLength, LPSTR szUnits, UINT* pUnitsLength, LPSTR szUnitsDescription, UINT* pDescriptionLength) {
        LOG_MSG("ProxyD3D11Device::CheckCounter called");
        return m_pReal->CheckCounter(pDesc, pType, pActiveCounters, szName, pNameLength, szUnits, pUnitsLength, szUnitsDescription, pDescriptionLength);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CheckFeatureSupport(D3D11_FEATURE Feature, void* pFeatureSupportData, UINT FeatureSupportDataSize) {
        LOG_MSG("ProxyD3D11Device::CheckFeatureSupport called");
        return m_pReal->CheckFeatureSupport(Feature, pFeatureSupportData, FeatureSupportDataSize);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) {
        LOG_MSG("ProxyD3D11Device::GetPrivateData called");
        return m_pReal->GetPrivateData(guid, pDataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) {
        LOG_MSG("ProxyD3D11Device::SetPrivateData called");
        return m_pReal->SetPrivateData(guid, DataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) {
        LOG_MSG("ProxyD3D11Device::SetPrivateDataInterface called");
        return m_pReal->SetPrivateDataInterface(guid, pData);
    }

    D3D_FEATURE_LEVEL STDMETHODCALLTYPE ProxyD3D11Device::GetFeatureLevel(void) {
        LOG_MSG("ProxyD3D11Device::GetFeatureLevel called");
        return m_pReal->GetFeatureLevel();
    }

    UINT STDMETHODCALLTYPE ProxyD3D11Device::GetCreationFlags(void) {
        LOG_MSG("ProxyD3D11Device::GetCreationFlags called");
        return m_pReal->GetCreationFlags();
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::GetDeviceRemovedReason(void) {
        LOG_MSG("ProxyD3D11Device::GetDeviceRemovedReason called");
        return m_pReal->GetDeviceRemovedReason();
    }

    void STDMETHODCALLTYPE ProxyD3D11Device::GetImmediateContext(ID3D11DeviceContext** ppImmediateContext) {
        LOG_MSG("ProxyD3D11Device::GetImmediateContext called");

        m_pReal->GetImmediateContext(ppImmediateContext);

        if (ppImmediateContext && *ppImmediateContext) {
            ProxyWrapper::Wrap<ProxyD3D11DeviceContext>(ppImmediateContext);
        }
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::SetExceptionMode(UINT RaiseFlags) {
        LOG_MSG("ProxyD3D11Device::SetExceptionMode called");
        return m_pReal->SetExceptionMode(RaiseFlags);
    }

    UINT STDMETHODCALLTYPE ProxyD3D11Device::GetExceptionMode(void) {
        LOG_MSG("ProxyD3D11Device::GetExceptionMode called");
        return m_pReal->GetExceptionMode();
    }

} // namespace d3d11