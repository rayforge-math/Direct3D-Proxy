#pragma once

#include "dxgi/ProxyDXGIFactory.h"
#include "dxgi/ProxyDXGIAdapter.h"
#include "dxgi/ProxyDXGISwapChain.h"
#include "d3d/ProxyWrapper.h"
#include "debug/debug_dxgi.h"

using namespace d3d;

namespace dxgi {

    ProxyDXGIFactory::ProxyDXGIFactory(IDXGIFactory2* factory)
        : ProxyD3D<IDXGIFactory2, ProxyDXGIFactory>(factory)
    {
    }

    // --- IDXGIObject Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::SetPrivateData(REFGUID Name, UINT DataSize, const void* pData) {
        LOG_MSG("ProxyDXGIFactory::SetPrivateData called");
        return m_pReal->SetPrivateData(Name, DataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown) {
        LOG_MSG("ProxyDXGIFactory::SetPrivateDataInterface called");
        return m_pReal->SetPrivateDataInterface(Name, pUnknown);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData) {
        LOG_MSG("ProxyDXGIFactory::GetPrivateData called");
        return m_pReal->GetPrivateData(Name, pDataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::GetParent(REFIID riid, void** ppParent) {
        LOG_MSG("ProxyDXGIFactory::GetParent called");
        HRESULT hr = m_pReal->GetParent(riid, ppParent);
        if (SUCCEEDED(hr) && ppParent && *ppParent) {

        }
        return hr;
    }

    // --- IDXGIFactory Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::EnumAdapters(UINT Adapter, IDXGIAdapter** ppAdapter) {
        LOG_MSG("ProxyDXGIFactory::EnumAdapters called");
        HRESULT hr = m_pReal->EnumAdapters(Adapter, ppAdapter);
        if (SUCCEEDED(hr) && ppAdapter && *ppAdapter) {
            ProxyWrapper::Wrap<ProxyDXGIAdapter>(ppAdapter);
        }
        return hr;
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::MakeWindowAssociation(HWND WindowHandle, UINT Flags) {
        LOG_MSG("ProxyDXGIFactory::MakeWindowAssociation called");
        return m_pReal->MakeWindowAssociation(WindowHandle, Flags);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::GetWindowAssociation(HWND* pWindowHandle) {
        LOG_MSG("ProxyDXGIFactory::GetWindowAssociation called");
        return m_pReal->GetWindowAssociation(pWindowHandle);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::CreateSwapChain(IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain) {
        LOG_MSG("ProxyDXGIFactory::CreateSwapChain called");
        HRESULT hr = m_pReal->CreateSwapChain(pDevice, pDesc, ppSwapChain);
        if (SUCCEEDED(hr) && ppSwapChain && *ppSwapChain) {
            ProxyWrapper::Wrap<ProxyDXGISwapChain>(ppSwapChain);
        }
        return hr;
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter** ppAdapter) {
        LOG_MSG("ProxyDXGIFactory::CreateSoftwareAdapter called");
        HRESULT hr = m_pReal->CreateSoftwareAdapter(Module, ppAdapter);
        if (SUCCEEDED(hr) && ppAdapter && *ppAdapter) {
            ProxyWrapper::Wrap<ProxyDXGIAdapter>(ppAdapter);
        }
        return hr;
    }

    // --- IDXGIFactory1 Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::EnumAdapters1(UINT Adapter, IDXGIAdapter1** ppAdapter) {
        LOG_MSG("ProxyDXGIFactory::EnumAdapters1 called");
        HRESULT hr = m_pReal->EnumAdapters1(Adapter, ppAdapter);
        if (SUCCEEDED(hr) && ppAdapter && *ppAdapter) {
            ProxyWrapper::Wrap<ProxyDXGIAdapter>(ppAdapter);
        }
        return hr;
    }

    BOOL STDMETHODCALLTYPE ProxyDXGIFactory::IsCurrent(void) {
        LOG_MSG("ProxyDXGIFactory::IsCurrent called");
        return m_pReal->IsCurrent();
    }

    // --- IDXGIFactory2 Methods ---

    BOOL STDMETHODCALLTYPE ProxyDXGIFactory::IsWindowedStereoEnabled(void) {
        LOG_MSG("ProxyDXGIFactory::IsWindowedStereoEnabled called");
        return m_pReal->IsWindowedStereoEnabled();
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::CreateSwapChainForHwnd(IUnknown* pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) {
        LOG_MSG("ProxyDXGIFactory::CreateSwapChainForHwnd called");
        HRESULT hr = m_pReal->CreateSwapChainForHwnd(pDevice, hWnd, pDesc, pFullscreenDesc, pRestrictToOutput, ppSwapChain);
        if (SUCCEEDED(hr) && ppSwapChain && *ppSwapChain) {
            ProxyWrapper::Wrap<ProxyDXGISwapChain>(ppSwapChain);
        }
        return hr;
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::CreateSwapChainForCoreWindow(IUnknown* pDevice, IUnknown* pWindow, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) {
        LOG_MSG("ProxyDXGIFactory::CreateSwapChainForCoreWindow called");
        HRESULT hr = m_pReal->CreateSwapChainForCoreWindow(pDevice, pWindow, pDesc, pRestrictToOutput, ppSwapChain);
        if (SUCCEEDED(hr) && ppSwapChain && *ppSwapChain) {
            ProxyWrapper::Wrap<ProxyDXGISwapChain>(ppSwapChain);
        }
        return hr;
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::GetSharedResourceAdapterLuid(HANDLE hResource, LUID* pLuid) {
        LOG_MSG("ProxyDXGIFactory::GetSharedResourceAdapterLuid called");
        return m_pReal->GetSharedResourceAdapterLuid(hResource, pLuid);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::RegisterStereoStatusWindow(HWND WindowHandle, UINT Message, DWORD* pCookie) {
        LOG_MSG("ProxyDXGIFactory::RegisterStereoStatusWindow called");
        return m_pReal->RegisterStereoStatusWindow(WindowHandle, Message, pCookie);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::RegisterStereoStatusEvent(HANDLE hEvent, DWORD* pCookie) {
        LOG_MSG("ProxyDXGIFactory::RegisterStereoStatusEvent called");
        return m_pReal->RegisterStereoStatusEvent(hEvent, pCookie);
    }

    void STDMETHODCALLTYPE ProxyDXGIFactory::UnregisterStereoStatus(DWORD Cookie) {
        LOG_MSG("ProxyDXGIFactory::UnregisterStereoStatus called");
        m_pReal->UnregisterStereoStatus(Cookie);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::RegisterOcclusionStatusWindow(HWND WindowHandle, UINT Message, DWORD* pCookie) {
        LOG_MSG("ProxyDXGIFactory::RegisterOcclusionStatusWindow called");
        return m_pReal->RegisterOcclusionStatusWindow(WindowHandle, Message, pCookie);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::RegisterOcclusionStatusEvent(HANDLE hEvent, DWORD* pCookie) {
        LOG_MSG("ProxyDXGIFactory::RegisterOcclusionStatusEvent called");
        return m_pReal->RegisterOcclusionStatusEvent(hEvent, pCookie);
    }

    void STDMETHODCALLTYPE ProxyDXGIFactory::UnregisterOcclusionStatus(DWORD Cookie) {
        LOG_MSG("ProxyDXGIFactory::UnregisterOcclusionStatus called");
        m_pReal->UnregisterOcclusionStatus(Cookie);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIFactory::CreateSwapChainForComposition(IUnknown* pDevice, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) {
        LOG_MSG("ProxyDXGIFactory::CreateSwapChainForComposition called");
        HRESULT hr = m_pReal->CreateSwapChainForComposition(pDevice, pDesc, pRestrictToOutput, ppSwapChain);
        if (SUCCEEDED(hr) && ppSwapChain && *ppSwapChain) {
            ProxyWrapper::Wrap<ProxyDXGISwapChain>(ppSwapChain);
        }
        return hr;
    }

} // namespace dxgi