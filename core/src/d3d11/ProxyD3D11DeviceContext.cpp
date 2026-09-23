#pragma once

#include "d3d11/ProxyD3D11DeviceContext.h"
#include "d3d11/ProxyD3D11Wrapper.h"
#include "logging/debug_d3d11.h"
#include <d3d11/ProxyD3D11Buffer.h>

using namespace d3d;

namespace d3d11 {

    // --- Constructor & Destructor ---

    ProxyD3D11DeviceContext::ProxyD3D11DeviceContext(ID3D11DeviceContext4* context)
        : ProxyD3D<ID3D11DeviceContext4, ProxyD3D11DeviceContext>(context)
    {
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::QueryInterface(REFIID riid, void** ppvObject)
    {
        if (!ppvObject)
            return E_POINTER;

        *ppvObject = nullptr;

        if (riid == __uuidof(ID3D11DeviceContext) ||
            riid == __uuidof(ID3D11DeviceContext1) ||
            riid == __uuidof(ID3D11DeviceContext2) ||
            riid == __uuidof(ID3D11DeviceContext3) ||
            riid == __uuidof(ID3D11DeviceContext4))
        {
            *ppvObject = static_cast<ID3D11DeviceContext4*>(this);
            AddRef();
            return S_OK;
        }

        return d3d::ProxyD3D<ID3D11DeviceContext4, ProxyD3D11DeviceContext>::QueryInterface(riid, ppvObject);
    }

    // --- ID3D11DeviceChild methods ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetDevice(ID3D11Device** ppDevice) {
        LOG_MSG("ProxyD3D11DeviceContext::GetDevice called");
        m_pReal->GetDevice(ppDevice);
        if (ppDevice && *ppDevice) {
            ProxyWrapper::Wrap<ProxyD3D11Device>(ppDevice);
        }
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) {
        LOG_MSG("ProxyD3D11DeviceContext::GetPrivateData called");
        return m_pReal->GetPrivateData(guid, pDataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) {
        LOG_MSG("ProxyD3D11DeviceContext::SetPrivateData called");
        return m_pReal->SetPrivateData(guid, DataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) {
        LOG_MSG("ProxyD3D11DeviceContext::SetPrivateDataInterface called");
        return m_pReal->SetPrivateDataInterface(guid, pData);
    }

    // --- ID3D11DeviceContext methods ---

    // Vertex Shader
    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {
        LOG_MSG("ProxyD3D11DeviceContext::VSSetConstantBuffers called");
        m_pReal->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {
        LOG_MSG("ProxyD3D11DeviceContext::VSSetShaderResources called");
        m_pReal->VSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSSetShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {
        LOG_MSG("ProxyD3D11DeviceContext::VSSetShader called");
        m_pReal->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {
        LOG_MSG("ProxyD3D11DeviceContext::VSSetSamplers called");
        m_pReal->VSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {
        LOG_MSG("ProxyD3D11DeviceContext::VSGetConstantBuffers called");

        m_pReal->VSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {
        LOG_MSG("ProxyD3D11DeviceContext::VSGetShaderResources called");
        m_pReal->VSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSGetShader(ID3D11VertexShader** ppVertexShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {
        LOG_MSG("ProxyD3D11DeviceContext::VSGetShader called");
        m_pReal->VSGetShader(ppVertexShader, ppClassInstances, pNumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {
        LOG_MSG("ProxyD3D11DeviceContext::VSGetSamplers called");
        m_pReal->VSGetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    // Hull Shader
    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {
        LOG_MSG("ProxyD3D11DeviceContext::HSSetShaderResources called");
        m_pReal->HSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSSetShader(ID3D11HullShader* pHullShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {
        LOG_MSG("ProxyD3D11DeviceContext::HSSetShader called");
        m_pReal->HSSetShader(pHullShader, ppClassInstances, NumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {
        LOG_MSG("ProxyD3D11DeviceContext::HSSetSamplers called");
        m_pReal->HSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {
        LOG_MSG("ProxyD3D11DeviceContext::HSSetConstantBuffers called");
        m_pReal->HSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {
        LOG_MSG("ProxyD3D11DeviceContext::HSGetShaderResources called");
        m_pReal->HSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSGetShader(ID3D11HullShader** ppHullShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {
        LOG_MSG("ProxyD3D11DeviceContext::HSGetShader called");
        m_pReal->HSGetShader(ppHullShader, ppClassInstances, pNumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {
        LOG_MSG("ProxyD3D11DeviceContext::HSGetSamplers called");
        m_pReal->HSGetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {
        LOG_MSG("ProxyD3D11DeviceContext::HSGetConstantBuffers called");

        m_pReal->HSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    // Domain Shader
    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {
        LOG_MSG("ProxyD3D11DeviceContext::DSSetShaderResources called");
        m_pReal->DSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSSetShader(ID3D11DomainShader* pDomainShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {
        LOG_MSG("ProxyD3D11DeviceContext::DSSetShader called");
        m_pReal->DSSetShader(pDomainShader, ppClassInstances, NumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {
        LOG_MSG("ProxyD3D11DeviceContext::DSSetSamplers called");
        m_pReal->DSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {
        LOG_MSG("ProxyD3D11DeviceContext::DSSetConstantBuffers called");
        m_pReal->DSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {
        LOG_MSG("ProxyD3D11DeviceContext::DSGetShaderResources called");
        m_pReal->DSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSGetShader(ID3D11DomainShader** ppDomainShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {
        LOG_MSG("ProxyD3D11DeviceContext::DSGetShader called");
        m_pReal->DSGetShader(ppDomainShader, ppClassInstances, pNumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {
        LOG_MSG("ProxyD3D11DeviceContext::DSGetSamplers called");
        m_pReal->DSGetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {
        LOG_MSG("ProxyD3D11DeviceContext::DSGetConstantBuffers called");

        m_pReal->DSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    // Geometry Shader
    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {
        LOG_MSG("ProxyD3D11DeviceContext::GSSetConstantBuffers called");
        m_pReal->GSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSSetShader(ID3D11GeometryShader* pShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {
        LOG_MSG("ProxyD3D11DeviceContext::GSSetShader called");
        m_pReal->GSSetShader(pShader, ppClassInstances, NumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {
        LOG_MSG("ProxyD3D11DeviceContext::GSSetShaderResources called");
        m_pReal->GSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {
        LOG_MSG("ProxyD3D11DeviceContext::GSSetSamplers called");
        m_pReal->GSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {
        LOG_MSG("ProxyD3D11DeviceContext::GSGetConstantBuffers called");

        m_pReal->GSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSGetShader(ID3D11GeometryShader** ppGeometryShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {
        LOG_MSG("ProxyD3D11DeviceContext::GSGetShader called");
        m_pReal->GSGetShader(ppGeometryShader, ppClassInstances, pNumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {
        LOG_MSG("ProxyD3D11DeviceContext::GSGetShaderResources called");
        m_pReal->GSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {
        LOG_MSG("ProxyD3D11DeviceContext::GSGetSamplers called");
        m_pReal->GSGetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    // Pixel Shader
    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {
        LOG_MSG("ProxyD3D11DeviceContext::PSSetShaderResources called");
        m_pReal->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSSetShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {
        LOG_MSG("ProxyD3D11DeviceContext::PSSetShader called");
        m_pReal->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {
        LOG_MSG("ProxyD3D11DeviceContext::PSSetSamplers called");
        m_pReal->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {
        LOG_MSG("ProxyD3D11DeviceContext::PSSetConstantBuffers called");
        m_pReal->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {
        LOG_MSG("ProxyD3D11DeviceContext::PSGetShaderResources called");
        m_pReal->PSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSGetShader(ID3D11PixelShader** ppPixelShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {
        LOG_MSG("ProxyD3D11DeviceContext::PSGetShader called");
        m_pReal->PSGetShader(ppPixelShader, ppClassInstances, pNumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {
        LOG_MSG("ProxyD3D11DeviceContext::PSGetSamplers called");
        m_pReal->PSGetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {
        LOG_MSG("ProxyD3D11DeviceContext::PSGetConstantBuffers called");

        m_pReal->PSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    // Compute Shader
    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {
        LOG_MSG("ProxyD3D11DeviceContext::CSSetShaderResources called");
        m_pReal->CSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView* const* ppUnorderedAccessViews, const UINT* pUAVInitialCounts) {
        LOG_MSG("ProxyD3D11DeviceContext::CSSetUnorderedAccessViews called");
        m_pReal->CSSetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSSetShader(ID3D11ComputeShader* pComputeShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {
        LOG_MSG("ProxyD3D11DeviceContext::CSSetShader called");
        m_pReal->CSSetShader(pComputeShader, ppClassInstances, NumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {
        LOG_MSG("ProxyD3D11DeviceContext::CSSetSamplers called");
        m_pReal->CSSetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {
        LOG_MSG("ProxyD3D11DeviceContext::CSSetConstantBuffers called");
        m_pReal->CSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {
        LOG_MSG("ProxyD3D11DeviceContext::CSGetShaderResources called");
        m_pReal->CSGetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView** ppUnorderedAccessViews) {
        LOG_MSG("ProxyD3D11DeviceContext::CSGetUnorderedAccessViews called");
        m_pReal->CSGetUnorderedAccessViews(StartSlot, NumUAVs, ppUnorderedAccessViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSGetShader(ID3D11ComputeShader** ppComputeShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {
        LOG_MSG("ProxyD3D11DeviceContext::CSGetShader called");
        m_pReal->CSGetShader(ppComputeShader, ppClassInstances, pNumClassInstances);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {
        LOG_MSG("ProxyD3D11DeviceContext::CSGetSamplers called");
        m_pReal->CSGetSamplers(StartSlot, NumSamplers, ppSamplers);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {
        LOG_MSG("ProxyD3D11DeviceContext::CSGetConstantBuffers called");

        m_pReal->CSGetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
    }

    // Compute Dispatch
    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ) {
        LOG_MSG("ProxyD3D11DeviceContext::Dispatch called");
        m_pReal->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DispatchIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs) {
        LOG_MSG("ProxyD3D11DeviceContext::DispatchIndirect called");
        m_pReal->DispatchIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
    }

    // --- Input Assembler ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout) {
        LOG_MSG("ProxyD3D11DeviceContext::IASetInputLayout called");
        m_pReal->IASetInputLayout(pInputLayout);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets) {
        LOG_MSG("ProxyD3D11DeviceContext::IASetVertexBuffers called");
        m_pReal->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset) {
        LOG_MSG("ProxyD3D11DeviceContext::IASetIndexBuffer called");

        m_pReal->IASetIndexBuffer(pIndexBuffer, Format, Offset);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology) {
        LOG_MSG("ProxyD3D11DeviceContext::IASetPrimitiveTopology called");
        m_pReal->IASetPrimitiveTopology(Topology);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IAGetInputLayout(ID3D11InputLayout** ppInputLayout) {
        LOG_MSG("ProxyD3D11DeviceContext::IAGetInputLayout called");
        m_pReal->IAGetInputLayout(ppInputLayout);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppVertexBuffers, UINT* pStrides, UINT* pOffsets) {
        LOG_MSG("ProxyD3D11DeviceContext::IAGetVertexBuffers called");

        m_pReal->IAGetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IAGetIndexBuffer(ID3D11Buffer** ppIndexBuffer, DXGI_FORMAT* Format, UINT* Offset) {
        LOG_MSG("ProxyD3D11DeviceContext::IAGetIndexBuffer called");

        m_pReal->IAGetIndexBuffer(ppIndexBuffer, Format, Offset);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY* pTopology) {
        LOG_MSG("ProxyD3D11DeviceContext::IAGetPrimitiveTopology called");
        m_pReal->IAGetPrimitiveTopology(pTopology);
    }

    // --- Drawing ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) {
        LOG_MSG("ProxyD3D11DeviceContext::DrawIndexed called");
        m_pReal->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::Draw(UINT VertexCount, UINT StartVertexLocation) {
        LOG_MSG("ProxyD3D11DeviceContext::Draw called");
        m_pReal->Draw(VertexCount, StartVertexLocation);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation) {
        LOG_MSG("ProxyD3D11DeviceContext::DrawIndexedInstanced called");
        m_pReal->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation) {
        LOG_MSG("ProxyD3D11DeviceContext::DrawInstanced called");
        m_pReal->DrawInstanced(VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DrawAuto() {
        LOG_MSG("ProxyD3D11DeviceContext::DrawAuto called");
        m_pReal->DrawAuto();
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DrawIndexedInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs) {
        LOG_MSG("ProxyD3D11DeviceContext::DrawIndexedInstancedIndirect called");
        m_pReal->DrawIndexedInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DrawInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs) {
        LOG_MSG("ProxyD3D11DeviceContext::DrawInstancedIndirect called");
        m_pReal->DrawInstancedIndirect(pBufferForArgs, AlignedByteOffsetForArgs);
    }

    // --- Output Merger ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView) {
        LOG_MSG("ProxyD3D11DeviceContext::OMSetRenderTargets called");
        m_pReal->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView* const* ppUnorderedAccessViews, const UINT* pUAVInitialCounts) {
        LOG_MSG("ProxyD3D11DeviceContext::OMSetRenderTargetsAndUnorderedAccessViews called");
        m_pReal->OMSetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, pDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews, pUAVInitialCounts);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMSetBlendState(ID3D11BlendState* pBlendState, const FLOAT BlendFactor[4], UINT SampleMask) {
        LOG_MSG("ProxyD3D11DeviceContext::OMSetBlendState called");
        m_pReal->OMSetBlendState(pBlendState, BlendFactor, SampleMask);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMSetDepthStencilState(ID3D11DepthStencilState* pDepthStencilState, UINT StencilRef) {
        LOG_MSG("ProxyD3D11DeviceContext::OMSetDepthStencilState called");
        m_pReal->OMSetDepthStencilState(pDepthStencilState, StencilRef);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMGetRenderTargets(UINT NumViews, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView** ppDepthStencilView) {
        LOG_MSG("ProxyD3D11DeviceContext::OMGetRenderTargets called");
        m_pReal->OMGetRenderTargets(NumViews, ppRenderTargetViews, ppDepthStencilView);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView** ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView** ppUnorderedAccessViews) {
        LOG_MSG("ProxyD3D11DeviceContext::OMGetRenderTargetsAndUnorderedAccessViews called");
        m_pReal->OMGetRenderTargetsAndUnorderedAccessViews(NumRTVs, ppRenderTargetViews, ppDepthStencilView, UAVStartSlot, NumUAVs, ppUnorderedAccessViews);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMGetBlendState(ID3D11BlendState** ppBlendState, FLOAT BlendFactor[4], UINT* pSampleMask) {
        LOG_MSG("ProxyD3D11DeviceContext::OMGetBlendState called");
        m_pReal->OMGetBlendState(ppBlendState, BlendFactor, pSampleMask);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::OMGetDepthStencilState(ID3D11DepthStencilState** ppDepthStencilState, UINT* pStencilRef) {
        LOG_MSG("ProxyD3D11DeviceContext::OMGetDepthStencilState called");
        m_pReal->OMGetDepthStencilState(ppDepthStencilState, pStencilRef);
    }

    // --- Rasterizer Stage ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::RSSetState(ID3D11RasterizerState* pRasterizerState) {
        LOG_MSG("ProxyD3D11DeviceContext::RSSetState called");
        m_pReal->RSSetState(pRasterizerState);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::RSSetViewports(UINT NumViewports, const D3D11_VIEWPORT* pViewports) {
        LOG_MSG("ProxyD3D11DeviceContext::RSSetViewports called");
        m_pReal->RSSetViewports(NumViewports, pViewports);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::RSSetScissorRects(UINT NumRects, const D3D11_RECT* pRects) {
        LOG_MSG("ProxyD3D11DeviceContext::RSSetScissorRects called");
        m_pReal->RSSetScissorRects(NumRects, pRects);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::RSGetState(ID3D11RasterizerState** ppRasterizerState) {
        LOG_MSG("ProxyD3D11DeviceContext::RSGetState called");
        m_pReal->RSGetState(ppRasterizerState);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::RSGetViewports(UINT* pNumViewports, D3D11_VIEWPORT* pViewports) {
        LOG_MSG("ProxyD3D11DeviceContext::RSGetViewports called");
        m_pReal->RSGetViewports(pNumViewports, pViewports);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::RSGetScissorRects(UINT* pNumRects, D3D11_RECT* pRects) {
        LOG_MSG("ProxyD3D11DeviceContext::RSGetScissorRects called");
        m_pReal->RSGetScissorRects(pNumRects, pRects);
    }

    // --- Stream Output ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::SOSetTargets(UINT NumBuffers, ID3D11Buffer* const* ppSOTargets, const UINT* pOffsets) {
        LOG_MSG("ProxyD3D11DeviceContext::SOSetTargets called");
        m_pReal->SOSetTargets(NumBuffers, ppSOTargets, pOffsets);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::SOGetTargets(UINT NumBuffers, ID3D11Buffer** ppSOTargets) {
        LOG_MSG("ProxyD3D11DeviceContext::SOGetTargets called");
        m_pReal->SOGetTargets(NumBuffers, ppSOTargets);
    }

    // --- Resource Manipulation & Predication ---

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::Map(ID3D11Resource* pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE* pMappedResource) {
        LOG_MSG("ProxyD3D11DeviceContext::Map called");
        return m_pReal->Map(pResource, Subresource, MapType, MapFlags, pMappedResource);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::Unmap(ID3D11Resource* pResource, UINT Subresource) {
        LOG_MSG("ProxyD3D11DeviceContext::Unmap called");
        m_pReal->Unmap(pResource, Subresource);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CopySubresourceRegion(ID3D11Resource* pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource* pSrcResource, UINT SrcSubresource, const D3D11_BOX* pSrcBox) {
        LOG_MSG("ProxyD3D11DeviceContext::CopySubresourceRegion called");
        m_pReal->CopySubresourceRegion(pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CopyResource(ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource) {
        LOG_MSG("ProxyD3D11DeviceContext::CopyResource called");
        m_pReal->CopyResource(pDstResource, pSrcResource);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::UpdateSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) {
        LOG_MSG("ProxyD3D11DeviceContext::UpdateSubresource called");
        m_pReal->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CopyStructureCount(ID3D11Buffer* pDstBuffer, UINT DstAlignedByteOffset, ID3D11UnorderedAccessView* pSrcView) {
        LOG_MSG("ProxyD3D11DeviceContext::CopyStructureCount called");

        m_pReal->CopyStructureCount(pDstBuffer, DstAlignedByteOffset, pSrcView);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, const FLOAT ColorRGBA[4]) {
        LOG_MSG("ProxyD3D11DeviceContext::ClearRenderTargetView called");
        m_pReal->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ClearUnorderedAccessViewUint(ID3D11UnorderedAccessView* pUnorderedAccessView, const UINT Values[4]) {
        LOG_MSG("ProxyD3D11DeviceContext::ClearUnorderedAccessViewUint called");
        m_pReal->ClearUnorderedAccessViewUint(pUnorderedAccessView, Values);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ClearUnorderedAccessViewFloat(ID3D11UnorderedAccessView* pUnorderedAccessView, const FLOAT Values[4]) {
        LOG_MSG("ProxyD3D11DeviceContext::ClearUnorderedAccessViewFloat called");
        m_pReal->ClearUnorderedAccessViewFloat(pUnorderedAccessView, Values);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil) {
        LOG_MSG("ProxyD3D11DeviceContext::ClearDepthStencilView called");
        m_pReal->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GenerateMips(ID3D11ShaderResourceView* pShaderResourceView) {
        LOG_MSG("ProxyD3D11DeviceContext::GenerateMips called");
        m_pReal->GenerateMips(pShaderResourceView);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::SetResourceMinLOD(ID3D11Resource* pResource, FLOAT MinLOD) {
        LOG_MSG("ProxyD3D11DeviceContext::SetResourceMinLOD called");
        m_pReal->SetResourceMinLOD(pResource, MinLOD);
    }

    FLOAT STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetResourceMinLOD(ID3D11Resource* pResource) {
        LOG_MSG("ProxyD3D11DeviceContext::GetResourceMinLOD called");
        return m_pReal->GetResourceMinLOD(pResource);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ResolveSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, ID3D11Resource* pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format) {
        LOG_MSG("ProxyD3D11DeviceContext::ResolveSubresource called");
        m_pReal->ResolveSubresource(pDstResource, DstSubresource, pSrcResource, SrcSubresource, Format);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::SetPredication(ID3D11Predicate* pPredicate, BOOL PredicateValue) {
        LOG_MSG("ProxyD3D11DeviceContext::SetPredication called");
        m_pReal->SetPredication(pPredicate, PredicateValue);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetPredication(ID3D11Predicate** ppPredicate, BOOL* pPredicateValue) {
        LOG_MSG("ProxyD3D11DeviceContext::GetPredication called");
        m_pReal->GetPredication(ppPredicate, pPredicateValue);
    }

    // --- Execution & Queries ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ClearState() {
        LOG_MSG("ProxyD3D11DeviceContext::ClearState called");
        m_pReal->ClearState();
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::Begin(ID3D11Asynchronous* pAsync) {
        LOG_MSG("ProxyD3D11DeviceContext::Begin called");
        m_pReal->Begin(pAsync);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::End(ID3D11Asynchronous* pAsync) {
        LOG_MSG("ProxyD3D11DeviceContext::End called");
        m_pReal->End(pAsync);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetData(ID3D11Asynchronous* pAsync, void* pData, UINT DataSize, UINT GetDataFlags) {
        LOG_MSG("ProxyD3D11DeviceContext::GetData called");
        return m_pReal->GetData(pAsync, pData, DataSize, GetDataFlags);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ExecuteCommandList(ID3D11CommandList* pCommandList, BOOL RestoreContextState) {
        LOG_MSG("ProxyD3D11DeviceContext::ExecuteCommandList called");
        m_pReal->ExecuteCommandList(pCommandList, RestoreContextState);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::Flush() {
        LOG_MSG("ProxyD3D11DeviceContext::Flush called");
        m_pReal->Flush();
    }

    D3D11_DEVICE_CONTEXT_TYPE STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetType() {
        LOG_MSG("ProxyD3D11DeviceContext::GetType called");
        return m_pReal->GetType();
    }

    UINT STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetContextFlags() {
        LOG_MSG("ProxyD3D11DeviceContext::GetContextFlags called");
        return m_pReal->GetContextFlags();
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList** ppCommandList) {
        LOG_MSG("ProxyD3D11DeviceContext::FinishCommandList called");
        return m_pReal->FinishCommandList(RestoreDeferredContextState, ppCommandList);
    }

    // --- ID3D11DeviceContext1 methods ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CopySubresourceRegion1(ID3D11Resource* pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource* pSrcResource, UINT SrcSubresource, const D3D11_BOX* pSrcBox, UINT CopyFlags) {
        LOG_MSG("ProxyD3D11DeviceContext::CopySubresourceRegion1 called");
        m_pReal->CopySubresourceRegion1(pDstResource, DstSubresource, DstX, DstY, DstZ, pSrcResource, SrcSubresource, pSrcBox, CopyFlags);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::UpdateSubresource1(ID3D11Resource* pDstResource, UINT DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch, UINT CopyFlags) {
        LOG_MSG("ProxyD3D11DeviceContext::UpdateSubresource1 called");
        m_pReal->UpdateSubresource1(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch, CopyFlags);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DiscardResource(ID3D11Resource* pResource) {
        LOG_MSG("ProxyD3D11DeviceContext::DiscardResource called");
        m_pReal->DiscardResource(pResource);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DiscardView(ID3D11View* pResourceView) {
        LOG_MSG("ProxyD3D11DeviceContext::DiscardView called");
        m_pReal->DiscardView(pResourceView);
    }

    // Constant Buffer Ranges — Set

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants) {
        LOG_MSG("ProxyD3D11DeviceContext::VSSetConstantBuffers1 called");
        m_pReal->VSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants) {
        LOG_MSG("ProxyD3D11DeviceContext::HSSetConstantBuffers1 called");
        m_pReal->HSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants) {
        LOG_MSG("ProxyD3D11DeviceContext::DSSetConstantBuffers1 called");
        m_pReal->DSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants) {
        LOG_MSG("ProxyD3D11DeviceContext::GSSetConstantBuffers1 called");
        m_pReal->GSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants) {
        LOG_MSG("ProxyD3D11DeviceContext::PSSetConstantBuffers1 called");
        m_pReal->PSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants) {
        LOG_MSG("ProxyD3D11DeviceContext::CSSetConstantBuffers1 called");
        m_pReal->CSSetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
    }

    // Constant Buffer Ranges — Get

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::VSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers, UINT* pFirstConstant, UINT* pNumConstants) {
        LOG_MSG("ProxyD3D11DeviceContext::VSGetConstantBuffers1 called");
        m_pReal->VSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::HSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers, UINT* pFirstConstant, UINT* pNumConstants) {
        LOG_MSG("ProxyD3D11DeviceContext::HSGetConstantBuffers1 called");
        m_pReal->HSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers, UINT* pFirstConstant, UINT* pNumConstants) {
        LOG_MSG("ProxyD3D11DeviceContext::DSGetConstantBuffers1 called");
        m_pReal->DSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers, UINT* pFirstConstant, UINT* pNumConstants) {
        LOG_MSG("ProxyD3D11DeviceContext::GSGetConstantBuffers1 called");
        m_pReal->GSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::PSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers, UINT* pFirstConstant, UINT* pNumConstants) {
        LOG_MSG("ProxyD3D11DeviceContext::PSGetConstantBuffers1 called");
        m_pReal->PSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers, UINT* pFirstConstant, UINT* pNumConstants) {
        LOG_MSG("ProxyD3D11DeviceContext::CSGetConstantBuffers1 called");
        m_pReal->CSGetConstantBuffers1(StartSlot, NumBuffers, ppConstantBuffers, pFirstConstant, pNumConstants);
    }

    // Context State & Views

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::SwapDeviceContextState(ID3DDeviceContextState* pState, ID3DDeviceContextState** ppPreviousState) {
        LOG_MSG("ProxyD3D11DeviceContext::SwapDeviceContextState called");
        m_pReal->SwapDeviceContextState(pState, ppPreviousState);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::ClearView(ID3D11View* pView, const FLOAT Color[4], const D3D11_RECT* pRect, UINT NumRects) {
        LOG_MSG("ProxyD3D11DeviceContext::ClearView called");
        m_pReal->ClearView(pView, Color, pRect, NumRects);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::DiscardView1(ID3D11View* pResourceView, const D3D11_RECT* pRects, UINT NumRects) {
        LOG_MSG("ProxyD3D11DeviceContext::DiscardView1 called");
        m_pReal->DiscardView1(pResourceView, pRects, NumRects);
    }

    // --- ID3D11DeviceContext2 methods ---

    // Tiled Resources

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::UpdateTileMappings(ID3D11Resource* pTiledResource, UINT NumTiledResourceRegions, const D3D11_TILED_RESOURCE_COORDINATE* pTiledResourceRegionStartCoordinates, const D3D11_TILE_REGION_SIZE* pTiledResourceRegionSizes, ID3D11Buffer* pTilePool, UINT NumRanges, const UINT* pRangeFlags, const UINT* pTilePoolStartOffsets, const UINT* pRangeTileCounts, UINT Flags) {
        LOG_MSG("ProxyD3D11DeviceContext::UpdateTileMappings called");
        return m_pReal->UpdateTileMappings(pTiledResource, NumTiledResourceRegions, pTiledResourceRegionStartCoordinates, pTiledResourceRegionSizes, pTilePool, NumRanges, pRangeFlags, pTilePoolStartOffsets, pRangeTileCounts, Flags);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::CopyTileMappings(ID3D11Resource* pDstTiledResource, const D3D11_TILED_RESOURCE_COORDINATE* pDstRegionStartCoordinate, ID3D11Resource* pSrcTiledResource, const D3D11_TILED_RESOURCE_COORDINATE* pSrcRegionStartCoordinate, const D3D11_TILE_REGION_SIZE* pTileRegionSize, UINT Flags) {
        LOG_MSG("ProxyD3D11DeviceContext::CopyTileMappings called");
        return m_pReal->CopyTileMappings(pDstTiledResource, pDstRegionStartCoordinate, pSrcTiledResource, pSrcRegionStartCoordinate, pTileRegionSize, Flags);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::CopyTiles(ID3D11Resource* pTiledResource, const D3D11_TILED_RESOURCE_COORDINATE* pTileRegionStartCoordinate, const D3D11_TILE_REGION_SIZE* pTileRegionSize, ID3D11Buffer* pBuffer, UINT64 BufferStartOffsetInBytes, UINT Flags) {
        LOG_MSG("ProxyD3D11DeviceContext::CopyTiles called");
        m_pReal->CopyTiles(pTiledResource, pTileRegionStartCoordinate, pTileRegionSize, pBuffer, BufferStartOffsetInBytes, Flags);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::UpdateTiles(ID3D11Resource* pDestTiledResource, const D3D11_TILED_RESOURCE_COORDINATE* pDestTileRegionStartCoordinate, const D3D11_TILE_REGION_SIZE* pDestTileRegionSize, const void* pSourceTileData, UINT Flags) {
        LOG_MSG("ProxyD3D11DeviceContext::UpdateTiles called");
        m_pReal->UpdateTiles(pDestTiledResource, pDestTileRegionStartCoordinate, pDestTileRegionSize, pSourceTileData, Flags);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::ResizeTilePool(ID3D11Buffer* pTilePool, UINT64 NewSizeInBytes) {
        LOG_MSG("ProxyD3D11DeviceContext::ResizeTilePool called");
        return m_pReal->ResizeTilePool(pTilePool, NewSizeInBytes);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::TiledResourceBarrier(ID3D11DeviceChild* pTiledResourceOrViewAccessBeforeBarrier, ID3D11DeviceChild* pTiledResourceOrViewAccessAfterBarrier) {
        LOG_MSG("ProxyD3D11DeviceContext::TiledResourceBarrier called");
        m_pReal->TiledResourceBarrier(pTiledResourceOrViewAccessBeforeBarrier, pTiledResourceOrViewAccessAfterBarrier);
    }

    // Annotations

    BOOL STDMETHODCALLTYPE ProxyD3D11DeviceContext::IsAnnotationEnabled() {
        LOG_MSG("ProxyD3D11DeviceContext::IsAnnotationEnabled called");
        return m_pReal->IsAnnotationEnabled();
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::SetMarkerInt(LPCWSTR pLabel, INT Data) {
        LOG_MSG("ProxyD3D11DeviceContext::SetMarkerInt called");
        m_pReal->SetMarkerInt(pLabel, Data);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::BeginEventInt(LPCWSTR pLabel, INT Data) {
        LOG_MSG("ProxyD3D11DeviceContext::BeginEventInt called");
        m_pReal->BeginEventInt(pLabel, Data);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::EndEvent() {
        LOG_MSG("ProxyD3D11DeviceContext::EndEvent called");
        m_pReal->EndEvent();
    }

    // --- ID3D11DeviceContext3 methods ---

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::Flush1(D3D11_CONTEXT_TYPE ContextType, HANDLE hEvent) {
        LOG_MSG("ProxyD3D11DeviceContext::Flush1 called");
        m_pReal->Flush1(ContextType, hEvent);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::SetHardwareProtectionState(BOOL HwProtectionEnable) {
        LOG_MSG("ProxyD3D11DeviceContext::SetHardwareProtectionState called");
        m_pReal->SetHardwareProtectionState(HwProtectionEnable);
    }

    void STDMETHODCALLTYPE ProxyD3D11DeviceContext::GetHardwareProtectionState(BOOL* pHwProtectionEnable) {
        LOG_MSG("ProxyD3D11DeviceContext::GetHardwareProtectionState called");
        m_pReal->GetHardwareProtectionState(pHwProtectionEnable);
    }

    // --- ID3D11DeviceContext4 methods ---

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::Signal(ID3D11Fence* pFence, UINT64 Value) {
        LOG_MSG("ProxyD3D11DeviceContext::Signal called");
        return m_pReal->Signal(pFence, Value);
    }

    HRESULT STDMETHODCALLTYPE ProxyD3D11DeviceContext::Wait(ID3D11Fence* pFence, UINT64 Value) {
        LOG_MSG("ProxyD3D11DeviceContext::Wait called");
        return m_pReal->Wait(pFence, Value);
    }

} // namespace d3d11