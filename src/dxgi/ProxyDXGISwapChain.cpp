#pragma once

#include "dxgi/ProxyDXGISwapChain.h"

namespace dxgi {

    ProxyDXGISwapChain::ProxyDXGISwapChain(IDXGISwapChain* swapChain)
        : m_pReal(swapChain), m_RefCount(1)
    {
        if (m_pReal) {
            m_pReal->AddRef();
        }
    }

    ProxyDXGISwapChain::~ProxyDXGISwapChain() {
        if (m_pReal) {
            m_pReal->Release();
            m_pReal = nullptr;
        }
    }

    // --- IUnknown Implementation ---

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::QueryInterface(REFIID riid, void** ppvObject) {
        if (riid == __uuidof(IDXGISwapChain) || riid == __uuidof(IUnknown)) {
            AddRef();
            *ppvObject = this;
            return S_OK;
        }
        return m_pReal->QueryInterface(riid, ppvObject);
    }

    ULONG STDMETHODCALLTYPE ProxyDXGISwapChain::AddRef() {
        m_pReal->AddRef();
        return InterlockedIncrement(&m_RefCount);
    }

    ULONG STDMETHODCALLTYPE ProxyDXGISwapChain::Release() {
        m_pReal->Release();
        ULONG newCount = InterlockedDecrement(&m_RefCount);
        if (newCount == 0) {
            delete this;
        }
        return newCount;
    }

    // --- IDXGIObject Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::SetPrivateData(REFGUID Name, UINT DataSize, const void* pData) {
        return m_pReal->SetPrivateData(Name, DataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown) {
        return m_pReal->SetPrivateDataInterface(Name, pUnknown);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData) {
        return m_pReal->GetPrivateData(Name, pDataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetParent(REFIID riid, void** ppParent) {
        return m_pReal->GetParent(riid, ppParent);
    }

    // --- IDXGIDeviceSubObject Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetDevice(REFIID riid, void** ppDevice) {
        return m_pReal->GetDevice(riid, ppDevice);
    }

    // --- IDXGISwapChain Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::Present(UINT SyncInterval, UINT Flags) {
        return m_pReal->Present(SyncInterval, Flags);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetBuffer(UINT Buffer, REFIID riid, void** ppSurface) {
        return m_pReal->GetBuffer(Buffer, riid, ppSurface);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::SetFullscreenState(BOOL Fullscreen, IDXGIOutput* pTarget) {
        return m_pReal->SetFullscreenState(Fullscreen, pTarget);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetFullscreenState(BOOL* pFullscreen, IDXGIOutput** ppTarget) {
        return m_pReal->GetFullscreenState(pFullscreen, ppTarget);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc) {
        return m_pReal->GetDesc(pDesc);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
        return m_pReal->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters) {
        return m_pReal->ResizeTarget(pNewTargetParameters);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetContainingOutput(IDXGIOutput** ppOutput) {
        return m_pReal->GetContainingOutput(ppOutput);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats) {
        return m_pReal->GetFrameStatistics(pStats);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGISwapChain::GetLastPresentCount(UINT* pLastPresentCount) {
        return m_pReal->GetLastPresentCount(pLastPresentCount);
    }

} // namespace dxgi