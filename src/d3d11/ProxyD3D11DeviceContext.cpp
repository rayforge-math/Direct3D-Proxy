#pragma once

#include "d3d11/ProxyD3D11DeviceContext.h"
#include "debug.h"

namespace d3d11 {

    // --- Constructor & Destructor ---

    ProxyD3D11DeviceContext::ProxyD3D11DeviceContext(ID3D11DeviceContext* context)
        : ProxyD3D<ID3D11DeviceContext>(context)
    { }

    // --- ID3D11DeviceChild methods ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetDevice(ID3D11Device** ppDevice) {
        m_pReal->GetDevice(ppDevice);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) {
        return m_pReal->GetPrivateData(guid, pDataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) {
        return m_pReal->SetPrivateData(guid, DataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) {
        return m_pReal->SetPrivateDataInterface(guid, pData);
    }

    // --- ID3D11DeviceContext methods ---

    // Vertex Shader
    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {
        m_pReal->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {
        m_pReal->VSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSSetShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {
        m_pReal->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {
        m_pReal->VSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {
        m_pReal->VSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {
        m_pReal->VSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSGetShader(ID3D11VertexShader** ppVertexShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {
        m_pReal->VSGetShader(ppVertexShader, ppClassInstances, pNumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {
        m_pReal->VSGetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    // Hull Shader
    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {
        m_pReal->HSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSSetShader(ID3D11HullShader* pHullShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {
        m_pReal->HSSetShader(pHullShader, ppClassInstances, NumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {
        m_pReal->HSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {
        m_pReal->HSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {
        m_pReal->HSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSGetShader(ID3D11HullShader** ppHullShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {
        m_pReal->HSGetShader(ppHullShader, ppClassInstances, pNumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {
        m_pReal->HSGetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {
        m_pReal->HSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    // Domain Shader
    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {
        m_pReal->DSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSSetShader(ID3D11DomainShader* pDomainShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {
        m_pReal->DSSetShader(pDomainShader, ppClassInstances, NumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {
        m_pReal->DSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {
        m_pReal->DSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {
        m_pReal->DSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSGetShader(ID3D11DomainShader** ppDomainShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {
        m_pReal->DSGetShader(ppDomainShader, ppClassInstances, pNumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {
        m_pReal->DSGetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {
        m_pReal->DSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    // Geometry Shader
    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {
        m_pReal->GSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSSetShader(ID3D11GeometryShader* pShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {
        m_pReal->GSSetShader(pShader, ppClassInstances, NumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {
        m_pReal->GSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {
        m_pReal->GSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {
        m_pReal->GSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSGetShader(ID3D11GeometryShader** ppGeometryShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {
        m_pReal->GSGetShader(ppGeometryShader, ppClassInstances, pNumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {
        m_pReal->GSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {
        m_pReal->GSGetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    // Pixel Shader
    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {
        m_pReal->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSSetShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {
        m_pReal->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {
        m_pReal->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {
        m_pReal->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {
        m_pReal->PSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSGetShader(ID3D11PixelShader** ppPixelShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {
        m_pReal->PSGetShader(ppPixelShader, ppClassInstances, pNumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {
        m_pReal->PSGetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {
        m_pReal->PSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    // Compute Shader
    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {
        m_pReal->CSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView* const* ppUnorderedAccessViews, const UINT* pUAVInitialCounts) {
        m_pReal->CSSetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSSetShader(ID3D11ComputeShader* pComputeShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {
        m_pReal->CSSetShader(pComputeShader, ppClassInstances, NumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {
        m_pReal->CSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {
        m_pReal->CSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {
        m_pReal->CSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView** ppUnorderedAccessViews) {
        m_pReal->CSGetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSGetShader(ID3D11ComputeShader** ppComputeShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {
        m_pReal->CSGetShader(ppComputeShader, ppClassInstances, pNumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {
        m_pReal->CSGetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {
        m_pReal->CSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    // Compute Dispatch

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ) {
        m_pReal->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DispatchIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs) {
        m_pReal->DispatchIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
    }

    // --- Input Assembler ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout) {
        m_pReal->IASetInputLayout(pInputLayout);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets) {
        m_pReal->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset) {
        m_pReal->IASetIndexBuffer(pIndexBuffer, Format, Offset);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology) {
        m_pReal->IASetPrimitiveTopology(Topology);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IAGetInputLayout(ID3D11InputLayout** ppInputLayout) {
        m_pReal->IAGetInputLayout(ppInputLayout);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppVertexBuffers, UINT* pStrides, UINT* pOffsets) {
        m_pReal->IAGetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IAGetIndexBuffer(ID3D11Buffer** pIndexBuffer, DXGI_FORMAT* Format, UINT* Offset) {
        m_pReal->IAGetIndexBuffer(pIndexBuffer, Format, Offset);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY* pTopology) {
        m_pReal->IAGetPrimitiveTopology(pTopology);
    }

    // --- Drawing ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) {
        m_pReal->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::Draw(UINT VertexCount, UINT StartVertexLocation) {
        m_pReal->Draw(VertexCount, StartVertexLocation);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation) {
        m_pReal->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation) {
        m_pReal->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DrawAuto() {
        m_pReal->DrawAuto();
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DrawIndexedInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs) {
        m_pReal->DrawIndexedInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DrawInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs) {
        m_pReal->DrawInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
    }

    // --- Output Merger ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView) {
        m_pReal->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView* const* ppUnorderedAccessViews, const UINT* pUAVInitialCounts) {
        m_pReal->OMSetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, pDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMSetBlendState(ID3D11BlendState* pBlendState, const FLOAT BlendFactor[4], UINT SampleMask) {
        m_pReal->OMSetBlendState(pBlendState, BlendFactor, SampleMask);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMSetDepthStencilState(ID3D11DepthStencilState* pDepthStencilState, UINT StencilRef) {
        m_pReal->OMSetDepthStencilState(pDepthStencilState, StencilRef);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMGetRenderTargets(UINT NumViews, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView** ppDepthStencilView) {
        m_pReal->OMGetRenderTargets(NumViews, ppRenderTargetViews, ppDepthStencilView);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView** ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView** ppUnorderedAccessViews) {
        m_pReal->OMGetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, ppDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMGetBlendState(ID3D11BlendState** ppBlendState, FLOAT BlendFactor[4], UINT* pSampleMask) {
        m_pReal->OMGetBlendState(ppBlendState, BlendFactor, pSampleMask);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMGetDepthStencilState(ID3D11DepthStencilState** ppDepthStencilState, UINT* pStencilRef) {
        m_pReal->OMGetDepthStencilState(ppDepthStencilState, pStencilRef);
    }

    // --- Rasterizer Stage ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::RSSetState(ID3D11RasterizerState* pRasterizerState) {
        m_pReal->RSSetState(pRasterizerState);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::RSSetViewports(UINT NumViewports, const D3D11_VIEWPORT* pViewports) {
        m_pReal->RSSetViewports(NumViewports, pViewports);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::RSSetScissorRects(UINT NumRects, const D3D11_RECT* pRects) {
        m_pReal->RSSetScissorRects(NumRects, pRects);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::RSGetState(ID3D11RasterizerState** ppRasterizerState) {
        m_pReal->RSGetState(ppRasterizerState);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::RSGetViewports(UINT* pNumViewports, D3D11_VIEWPORT* pViewports) {
        m_pReal->RSGetViewports(pNumViewports, pViewports);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::RSGetScissorRects(UINT* pNumRects, D3D11_RECT* pRects) {
        m_pReal->RSGetScissorRects(pNumRects, pRects);
    }

    // --- Stream Output ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::SOSetTargets(UINT NumBuffers, ID3D11Buffer* const* ppSOTargets, const UINT* pOffsets) {
        m_pReal->SOSetTargets(NumBuffers, ppSOTargets, pOffsets);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::SOGetTargets(UINT NumBuffers, ID3D11Buffer** ppSOTargets) {
        m_pReal->SOGetTargets(NumBuffers, ppSOTargets);
    }

    // --- Resource Manipulation & Predication ---

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::Map(ID3D11Resource* pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE* pMappedResource) {
        return m_pReal->Map(pResource, Subresource, MapType, MapFlags, pMappedResource);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::Unmap(ID3D11Resource* pResource, UINT Subresource) {
        m_pReal->Unmap(pResource, Subresource);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CopySubresourceRegion(ID3D11Resource* pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource* pSrcResource, UINT SrcSubresource, const D3D11_BOX* pSrcBox) {
        m_pReal->CopySubresourceRegion(pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CopyResource(ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource) {
        m_pReal->CopyResource(pDstResource, pSrcResource);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::UpdateSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) {
        m_pReal->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CopyStructureCount(ID3D11Buffer* pDstBuffer, UINT DstAlignedByteOffset, ID3D11UnorderedAccessView* pSrcView) {
        m_pReal->CopyStructureCount(pDstBuffer, DstAlignedByteOffset, pSrcView);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, const FLOAT ColorRGBA[4]) {
        m_pReal->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ClearUnorderedAccessViewUint(ID3D11UnorderedAccessView* pUnorderedAccessView, const UINT Values[4]) {
        m_pReal->ClearUnorderedAccessViewUint(pUnorderedAccessView, Values);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ClearUnorderedAccessViewFloat(ID3D11UnorderedAccessView* pUnorderedAccessView, const FLOAT Values[4]) {
        m_pReal->ClearUnorderedAccessViewFloat(pUnorderedAccessView, Values);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil) {
        m_pReal->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GenerateMips(ID3D11ShaderResourceView* pShaderResourceView) {
        m_pReal->GenerateMips(pShaderResourceView);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::SetResourceMinLOD(ID3D11Resource* pResource, FLOAT MinLOD) {
        m_pReal->SetResourceMinLOD(pResource, MinLOD);
    }

    FLOAT STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetResourceMinLOD(ID3D11Resource* pResource) {
        return m_pReal->GetResourceMinLOD(pResource);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ResolveSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, ID3D11Resource* pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format) {
        m_pReal->ResolveSubresource(pDstResource, DstSubresource, pSrcResource, SrcSubresource, Format);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::SetPredication(ID3D11Predicate* pPredicate, BOOL PredicateValue) {
        m_pReal->SetPredication(pPredicate, PredicateValue);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetPredication(ID3D11Predicate** ppPredicate, BOOL* pPredicateValue) {
        m_pReal->GetPredication(ppPredicate, pPredicateValue);
    }

    // --- Execution & Queries ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ClearState() {
        m_pReal->ClearState();
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::Begin(ID3D11Asynchronous* pAsync) {
        m_pReal->Begin(pAsync);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::End(ID3D11Asynchronous* pAsync) {
        m_pReal->End(pAsync);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetData(ID3D11Asynchronous* pAsync, void* pData, UINT DataSize, UINT GetDataFlags) {
        return m_pReal->GetData(pAsync, pData, DataSize, GetDataFlags);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ExecuteCommandList(ID3D11CommandList* pCommandList, BOOL RestoreContextState) {
        m_pReal->ExecuteCommandList(pCommandList, RestoreContextState);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::Flush() {
        m_pReal->Flush();
    }

    D3D11_DEVICE_CONTEXT_TYPE STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetType() {
        return m_pReal->GetType();
    }

    UINT STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetContextFlags() {
        return m_pReal->GetContextFlags();
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList** ppCommandList) {
        return m_pReal->FinishCommandList(RestoreDeferredContextState, ppCommandList);
    }

} // namespace d3d11