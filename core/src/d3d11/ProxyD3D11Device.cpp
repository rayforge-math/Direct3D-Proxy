#pragma once

#include "d3d11/ProxyD3D11Device.h"
#include "d3d11/ProxyD3D11Buffer.h"
#include "d3d/ProxyWrapper.h"
#include "logging/debug_d3d11.h"
#include <d3d11/ProxyD3D11DeviceContext.h>

using namespace d3d;

namespace d3d11 {

    ProxyD3D11Device::ProxyD3D11Device(ID3D11Device5* device)
        : ProxyD3D<ProxyD3D11Device, ID3D11Device5>(device)
    {
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::QueryInterface(REFIID riid, void** ppvObject)
    {
        if (!ppvObject)
            return E_POINTER;

        *ppvObject = nullptr;

        if (riid == __uuidof(ID3D11Device) ||
            riid == __uuidof(ID3D11Device1) ||
            riid == __uuidof(ID3D11Device2) ||
            riid == __uuidof(ID3D11Device3) ||
            riid == __uuidof(ID3D11Device4) ||
            riid == __uuidof(ID3D11Device5))
        {
            *ppvObject = static_cast<ID3D11Device5*>(this);
            AddRef();
            return S_OK;
        }

        return d3d::ProxyD3D<ProxyD3D11Device, ID3D11Device5>::QueryInterface(riid, ppvObject);
    }

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

    // --- ID3D11Device1 Methods ---

    void STDMETHODCALLTYPE ProxyD3D11Device::GetImmediateContext1(ID3D11DeviceContext1** ppImmediateContext) {
        LOG_MSG("ProxyD3D11Device::GetImmediateContext1 called");
        m_pReal->GetImmediateContext1(ppImmediateContext);

        if (ppImmediateContext && *ppImmediateContext) {
            ProxyWrapper::Wrap<ProxyD3D11DeviceContext>(ppImmediateContext);
        }
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateDeferredContext1(UINT ContextFlags, ID3D11DeviceContext1** ppDeferredContext) {
        LOG_MSG("ProxyD3D11Device::CreateDeferredContext1 called");
        return m_pReal->CreateDeferredContext1(ContextFlags, ppDeferredContext);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateBlendState1(const D3D11_BLEND_DESC1* pBlendStateDesc, ID3D11BlendState1** ppBlendState) {
        LOG_MSG("ProxyD3D11Device::CreateBlendState1 called");
        return m_pReal->CreateBlendState1(pBlendStateDesc, ppBlendState);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateRasterizerState1(const D3D11_RASTERIZER_DESC1* pRasterizerDesc, ID3D11RasterizerState1** ppRasterizerState) {
        LOG_MSG("ProxyD3D11Device::CreateRasterizerState1 called");
        return m_pReal->CreateRasterizerState1(pRasterizerDesc, ppRasterizerState);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateDeviceContextState(UINT Flags, const D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, REFIID EmulatedInterface, D3D_FEATURE_LEVEL* pChosenFeatureLevel, ID3DDeviceContextState** ppContextState) {
        LOG_MSG("ProxyD3D11Device::CreateDeviceContextState called");
        return m_pReal->CreateDeviceContextState(Flags, pFeatureLevels, FeatureLevels, SDKVersion, EmulatedInterface, pChosenFeatureLevel, ppContextState);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::OpenSharedResource1(HANDLE hResource, REFIID ReturnedInterface, void** ppResource) {
        LOG_MSG("ProxyD3D11Device::OpenSharedResource1 called");
        return m_pReal->OpenSharedResource1(hResource, ReturnedInterface, ppResource);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::OpenSharedResourceByName(LPCWSTR lpName, DWORD dwDesiredAccess, REFIID ReturnedInterface, void** ppResource) {
        LOG_MSG("ProxyD3D11Device::OpenSharedResourceByName called");
        return m_pReal->OpenSharedResourceByName(lpName, dwDesiredAccess, ReturnedInterface, ppResource);
    }

    // --- ID3D11Device2 Methods ---

    void STDMETHODCALLTYPE ProxyD3D11Device::GetImmediateContext2(ID3D11DeviceContext2** ppImmediateContext) {
        LOG_MSG("ProxyD3D11Device::GetImmediateContext2 called");
        m_pReal->GetImmediateContext2(ppImmediateContext);

        if (ppImmediateContext && *ppImmediateContext) {
            ProxyWrapper::Wrap<ProxyD3D11DeviceContext>(ppImmediateContext);
        }
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateDeferredContext2(UINT ContextFlags, ID3D11DeviceContext2** ppDeferredContext) {
        LOG_MSG("ProxyD3D11Device::CreateDeferredContext2 called");
        return m_pReal->CreateDeferredContext2(ContextFlags, ppDeferredContext);
    }

    void STDMETHODCALLTYPE ProxyD3D11Device::GetResourceTiling(ID3D11Resource* pTiledResource, UINT* pNumTilesForEntireResource, D3D11_PACKED_MIP_DESC* pPackedMipDesc, D3D11_TILE_SHAPE* pStandardTileShapeForNonPackedMips, UINT* pNumSubresourceTilings, UINT FirstSubresourceTilingToGet, D3D11_SUBRESOURCE_TILING* pSubresourceTilingsForNonPackedMips) {
        LOG_MSG("ProxyD3D11Device::GetResourceTiling called");
        m_pReal->GetResourceTiling(pTiledResource, pNumTilesForEntireResource, pPackedMipDesc, pStandardTileShapeForNonPackedMips, pNumSubresourceTilings, FirstSubresourceTilingToGet, pSubresourceTilingsForNonPackedMips);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CheckMultisampleQualityLevels1(DXGI_FORMAT Format, UINT SampleCount, UINT Flags, UINT* pNumQualityLevels) {
        LOG_MSG("ProxyD3D11Device::CheckMultisampleQualityLevels1 called");
        return m_pReal->CheckMultisampleQualityLevels1(Format, SampleCount, Flags, pNumQualityLevels);
    }

    // --- ID3D11Device3 Methods ---

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateTexture2D1(const D3D11_TEXTURE2D_DESC1* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D1** ppTexture2D) {
        LOG_MSG("ProxyD3D11Device::CreateTexture2D1 called");
        return m_pReal->CreateTexture2D1(pDesc, pInitialData, ppTexture2D);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateTexture3D1(const D3D11_TEXTURE3D_DESC1* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture3D1** ppTexture3D) {
        LOG_MSG("ProxyD3D11Device::CreateTexture3D1 called");
        return m_pReal->CreateTexture3D1(pDesc, pInitialData, ppTexture3D);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateRasterizerState2(const D3D11_RASTERIZER_DESC2* pRasterizerDesc, ID3D11RasterizerState2** ppRasterizerState) {
        LOG_MSG("ProxyD3D11Device::CreateRasterizerState2 called");
        return m_pReal->CreateRasterizerState2(pRasterizerDesc, ppRasterizerState);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateShaderResourceView1(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC1* pDesc, ID3D11ShaderResourceView1** ppSRView) {
        LOG_MSG("ProxyD3D11Device::CreateShaderResourceView1 called");
        return m_pReal->CreateShaderResourceView1(pResource, pDesc, ppSRView);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateUnorderedAccessView1(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC1* pDesc, ID3D11UnorderedAccessView1** ppUAView) {
        LOG_MSG("ProxyD3D11Device::CreateUnorderedAccessView1 called");
        return m_pReal->CreateUnorderedAccessView1(pResource, pDesc, ppUAView);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateRenderTargetView1(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC1* pDesc, ID3D11RenderTargetView1** ppRTView) {
        LOG_MSG("ProxyD3D11Device::CreateRenderTargetView1 called");
        return m_pReal->CreateRenderTargetView1(pResource, pDesc, ppRTView);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateQuery1(const D3D11_QUERY_DESC1* pQueryDesc, ID3D11Query1** ppQuery) {
        LOG_MSG("ProxyD3D11Device::CreateQuery1 called");
        return m_pReal->CreateQuery1(pQueryDesc, ppQuery);
    }

    void STDMETHODCALLTYPE ProxyD3D11Device::GetImmediateContext3(ID3D11DeviceContext3** ppImmediateContext) {
        LOG_MSG("ProxyD3D11Device::GetImmediateContext3 called");
        m_pReal->GetImmediateContext3(ppImmediateContext);

        if (ppImmediateContext && *ppImmediateContext) {
            ProxyWrapper::Wrap<ProxyD3D11DeviceContext>(ppImmediateContext);
        }
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateDeferredContext3(UINT ContextFlags, ID3D11DeviceContext3** ppDeferredContext) {
        LOG_MSG("ProxyD3D11Device::CreateDeferredContext3 called");
        return m_pReal->CreateDeferredContext3(ContextFlags, ppDeferredContext);
    }

    void STDMETHODCALLTYPE ProxyD3D11Device::WriteToSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) {
        LOG_MSG("ProxyD3D11Device::WriteToSubresource called");
        m_pReal->WriteToSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
    }

    void STDMETHODCALLTYPE ProxyD3D11Device::ReadFromSubresource(void* pDstData, UINT DstRowPitch, UINT DstDepthPitch, ID3D11Resource* pSrcResource, UINT SrcSubresource, const D3D11_BOX* pSrcBox) {
        LOG_MSG("ProxyD3D11Device::ReadFromSubresource called");
        m_pReal->ReadFromSubresource(pDstData, DstRowPitch, DstDepthPitch, pSrcResource, SrcSubresource, pSrcBox);
    }

    // --- ID3D11Device4 Methods ---

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::RegisterDeviceRemovedEvent(HANDLE hEvent, DWORD* pdwCookie) {
        LOG_MSG("ProxyD3D11Device::RegisterDeviceRemovedEvent called");
        return m_pReal->RegisterDeviceRemovedEvent(hEvent, pdwCookie);
    }

    void STDMETHODCALLTYPE ProxyD3D11Device::UnregisterDeviceRemoved(DWORD dwCookie) {
        LOG_MSG("ProxyD3D11Device::UnregisterDeviceRemoved called");
        m_pReal->UnregisterDeviceRemoved(dwCookie);
    }

    // --- ID3D11Device5 Methods ---

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::OpenSharedFence(HANDLE hFence, REFIID ReturnedInterface, void** ppFence) {
        LOG_MSG("ProxyD3D11Device::OpenSharedFence called");
        return m_pReal->OpenSharedFence(hFence, ReturnedInterface, ppFence);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11Device::CreateFence(UINT64 InitialValue, D3D11_FENCE_FLAG Flags, REFIID ReturnedInterface, void** ppFence) {
        LOG_MSG("ProxyD3D11Device::CreateFence called");
        return m_pReal->CreateFence(InitialValue, Flags, ReturnedInterface, ppFence);
    }

} // namespace d3d11