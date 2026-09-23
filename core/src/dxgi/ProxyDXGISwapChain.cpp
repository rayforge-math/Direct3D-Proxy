#pragma once

#include "dxgi/ProxyDXGISwapChain.h"
//#include "dxgi/ProxyDXGIOutput.h"
#include "dxgi/ProxyDXGIFactory.h"
#include "d3d/ProxyWrapper.h"
#include "logging/debug_dxgi.h"

using namespace d3d;

namespace dxgi {

    ProxyDXGISwapChain::ProxyDXGISwapChain(IDXGISwapChain4* swapChain)
        : ProxyD3D<IDXGISwapChain4, ProxyDXGISwapChain>(swapChain)
    {
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::QueryInterface(REFIID riid, void** ppvObject)
    {
        if (!ppvObject)
            return E_POINTER;

        *ppvObject = nullptr;

        if (riid == __uuidof(IDXGISwapChain) ||
            riid == __uuidof(IDXGISwapChain1) ||
            riid == __uuidof(IDXGISwapChain2) ||
            riid == __uuidof(IDXGISwapChain3) ||
            riid == __uuidof(IDXGISwapChain4))
        {
            *ppvObject = static_cast<IDXGISwapChain4*>(this);
            AddRef();
            return S_OK;
        }

        return d3d::ProxyD3D<IDXGISwapChain4, ProxyDXGISwapChain>::QueryInterface(riid, ppvObject);
    }

    // --- IDXGIObject Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::SetPrivateData(REFGUID Name, UINT DataSize, const void* pData) {
        LOG_MSG("ProxyDXGISwapChain::SetPrivateData called");
        return m_pReal->SetPrivateData(Name, DataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown) {
        LOG_MSG("ProxyDXGISwapChain::SetPrivateDataInterface called");
        return m_pReal->SetPrivateDataInterface(Name, pUnknown);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData) {
        LOG_MSG("ProxyDXGISwapChain::GetPrivateData called");
        return m_pReal->GetPrivateData(Name, pDataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetParent(REFIID riid, void** ppParent) {
        LOG_MSG("ProxyDXGISwapChain::GetParent called");
        HRESULT hr = m_pReal->GetParent(riid, ppParent);
        if (SUCCEEDED(hr) && ppParent && *ppParent) {
            ProxyWrapper::Wrap<ProxyDXGIFactory>(reinterpret_cast<ProxyDXGIFactory::InterfaceType**>(ppParent));
        }
        return hr;
    }

    // --- IDXGIDeviceSubObject Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetDevice(REFIID riid, void** ppDevice) {
        LOG_MSG("ProxyDXGISwapChain::GetDevice called");
        return m_pReal->GetDevice(riid, ppDevice);
    }

    // --- IDXGISwapChain Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::Present(UINT SyncInterval, UINT Flags) {
        LOG_MSG("ProxyDXGISwapChain::Present called");
        return m_pReal->Present(SyncInterval, Flags);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetBuffer(UINT Buffer, REFIID riid, void** ppSurface) {
        LOG_MSG("ProxyDXGISwapChain::GetBuffer called");
        return m_pReal->GetBuffer(Buffer, riid, ppSurface);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::SetFullscreenState(BOOL Fullscreen, IDXGIOutput* pTarget) {
        LOG_MSG("ProxyDXGISwapChain::SetFullscreenState called");
        return m_pReal->SetFullscreenState(Fullscreen, pTarget);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetFullscreenState(BOOL* pFullscreen, IDXGIOutput** ppTarget) {
        LOG_MSG("ProxyDXGISwapChain::GetFullscreenState called");
        HRESULT hr = m_pReal->GetFullscreenState(pFullscreen, ppTarget);
        if (SUCCEEDED(hr) && ppTarget && *ppTarget) {
            //ProxyWrapper::Wrap<ProxyDXGIOutput>(ppTarget);
        }
        return hr;
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc) {
        LOG_MSG("ProxyDXGISwapChain::GetDesc called");
        return m_pReal->GetDesc(pDesc);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
        LOG_MSG("ProxyDXGISwapChain::ResizeBuffers called");
        return m_pReal->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters) {
        LOG_MSG("ProxyDXGISwapChain::ResizeTarget called");
        return m_pReal->ResizeTarget(pNewTargetParameters);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetContainingOutput(IDXGIOutput** ppOutput) {
        LOG_MSG("ProxyDXGISwapChain::GetContainingOutput called");
        HRESULT hr = m_pReal->GetContainingOutput(ppOutput);
        if (SUCCEEDED(hr) && ppOutput && *ppOutput) {
            //ProxyWrapper::Wrap<ProxyDXGIOutput>(ppOutput);
        }
        return hr;
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats) {
        LOG_MSG("ProxyDXGISwapChain::GetFrameStatistics called");
        return m_pReal->GetFrameStatistics(pStats);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetLastPresentCount(UINT* pLastPresentCount) {
        LOG_MSG("ProxyDXGISwapChain::GetLastPresentCount called");
        return m_pReal->GetLastPresentCount(pLastPresentCount);
    }

    // --- IDXGISwapChain1 Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetDesc1(DXGI_SWAP_CHAIN_DESC1* pDesc) {
        LOG_MSG("ProxyDXGISwapChain::GetDesc1 called");
        return m_pReal->GetDesc1(pDesc);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pDesc) {
        LOG_MSG("ProxyDXGISwapChain::GetFullscreenDesc called");
        return m_pReal->GetFullscreenDesc(pDesc);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetHwnd(HWND* pHwnd) {
        LOG_MSG("ProxyDXGISwapChain::GetHwnd called");
        return m_pReal->GetHwnd(pHwnd);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetCoreWindow(REFIID refiid, void** ppUnk) {
        LOG_MSG("ProxyDXGISwapChain::GetCoreWindow called");
        return m_pReal->GetCoreWindow(refiid, ppUnk);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::Present1(UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS* pPresentParameters) {
        LOG_MSG("ProxyDXGISwapChain::Present1 called");
        return m_pReal->Present1(SyncInterval, PresentFlags, pPresentParameters);
    }

    BOOL STDMETHODCALLTYPE ProxyDXGISwapChain::IsTemporaryMonoSupported(void) {
        LOG_MSG("ProxyDXGISwapChain::IsTemporaryMonoSupported called");
        return m_pReal->IsTemporaryMonoSupported();
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetRestrictToOutput(IDXGIOutput** ppRestrictToOutput) {
        LOG_MSG("ProxyDXGISwapChain::GetRestrictToOutput called");
        HRESULT hr = m_pReal->GetRestrictToOutput(ppRestrictToOutput);
        if (SUCCEEDED(hr) && ppRestrictToOutput && *ppRestrictToOutput) {
            //ProxyWrapper::Wrap<ProxyDXGIOutput>(ppRestrictToOutput);
        }
        return hr;
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::SetBackgroundColor(const DXGI_RGBA* pColor) {
        LOG_MSG("ProxyDXGISwapChain::SetBackgroundColor called");
        return m_pReal->SetBackgroundColor(pColor);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetBackgroundColor(DXGI_RGBA* pColor) {
        LOG_MSG("ProxyDXGISwapChain::GetBackgroundColor called");
        return m_pReal->GetBackgroundColor(pColor);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::SetRotation(DXGI_MODE_ROTATION Rotation) {
        LOG_MSG("ProxyDXGISwapChain::SetRotation called");
        return m_pReal->SetRotation(Rotation);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetRotation(DXGI_MODE_ROTATION* pRotation) {
        LOG_MSG("ProxyDXGISwapChain::GetRotation called");
        return m_pReal->GetRotation(pRotation);
    }

    // --- IDXGISwapChain2 Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::SetSourceSize(UINT Width, UINT Height) {
        LOG_MSG("ProxyDXGISwapChain::SetSourceSize called");
        return m_pReal->SetSourceSize(Width, Height);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetSourceSize(UINT* pWidth, UINT* pHeight) {
        LOG_MSG("ProxyDXGISwapChain::GetSourceSize called");
        return m_pReal->GetSourceSize(pWidth, pHeight);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::SetMaximumFrameLatency(UINT MaxLatency) {
        LOG_MSG("ProxyDXGISwapChain::SetMaximumFrameLatency called");
        return m_pReal->SetMaximumFrameLatency(MaxLatency);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetMaximumFrameLatency(UINT* pMaxLatency) {
        LOG_MSG("ProxyDXGISwapChain::GetMaximumFrameLatency called");
        return m_pReal->GetMaximumFrameLatency(pMaxLatency);
    }

    HANDLE STDMETHODCALLTYPE ProxyDXGISwapChain::GetFrameLatencyWaitableObject(void) {
        LOG_MSG("ProxyDXGISwapChain::GetFrameLatencyWaitableObject called");
        return m_pReal->GetFrameLatencyWaitableObject();
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::SetMatrixTransform(const DXGI_MATRIX_3X2_F* pMatrix) {
        LOG_MSG("ProxyDXGISwapChain::SetMatrixTransform called");
        return m_pReal->SetMatrixTransform(pMatrix);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetMatrixTransform(DXGI_MATRIX_3X2_F* pMatrix) {
        LOG_MSG("ProxyDXGISwapChain::GetMatrixTransform called");
        return m_pReal->GetMatrixTransform(pMatrix);
    }

    // --- IDXGISwapChain3 Methods ---

    UINT STDMETHODCALLTYPE ProxyDXGISwapChain::GetCurrentBackBufferIndex(void) {
        LOG_MSG("ProxyDXGISwapChain::GetCurrentBackBufferIndex called");
        return m_pReal->GetCurrentBackBufferIndex();
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::CheckColorSpaceSupport(DXGI_COLOR_SPACE_TYPE ColorSpace, UINT* pColorSpaceSupport) {
        LOG_MSG("ProxyDXGISwapChain::CheckColorSpaceSupport called");
        return m_pReal->CheckColorSpaceSupport(ColorSpace, pColorSpaceSupport);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::SetColorSpace1(DXGI_COLOR_SPACE_TYPE ColorSpace) {
        LOG_MSG("ProxyDXGISwapChain::SetColorSpace1 called");
        return m_pReal->SetColorSpace1(ColorSpace);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::ResizeBuffers1(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT Format, UINT SwapChainFlags, const UINT* pCreationNodeMask, IUnknown* const* ppPresentQueue) {
        LOG_MSG("ProxyDXGISwapChain::ResizeBuffers1 called");
        return m_pReal->ResizeBuffers1(BufferCount, Width, Height, Format, SwapChainFlags, pCreationNodeMask, ppPresentQueue);
    }

    // --- IDXGISwapChain4 Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::SetHDRMetaData(DXGI_HDR_METADATA_TYPE Type, UINT Size, void* pMetaData) {
        LOG_MSG("ProxyDXGISwapChain::SetHDRMetaData called");
        return m_pReal->SetHDRMetaData(Type, Size, pMetaData);
    }

} // namespace dxgi