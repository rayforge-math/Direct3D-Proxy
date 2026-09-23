#pragma once

#include "coreapi.h"
#include "d3d/ProxyD3D.h"
#include "dxgi_version.h"

namespace dxgi {

    /**
     * @class ProxyIDXGIFactory
     * @brief A virtualized wrapper for the IDXGIFactory2 interface (inheriting from IDXGIFactory1), serving as an advanced adapter, composition, and swap chain creation interceptor.
     *
     * @details
     * This class implements the Proxy pattern for the DXGI 1.2 factory interface.
     * By intercepting modern windowed/composition swap chain creation and stereo status registrations,
     * it enables comprehensive manipulation of modern Windows presentation layers.
     *
     * Core Functional Purposes:
     * - **Modern Swap Chain Interception:** Wraps `CreateSwapChainForHwnd`, `CreateSwapChainForCoreWindow`, and `CreateSwapChainForComposition` to inject presentation logic or custom render targets.
     * - **Stereo & Occlusion Management:** Intercepts window association, stereo status events, and occlusion monitoring.
     * - **Automatic Proxy Wrapping:** Ensures that all created swap chains (IDXGISwapChain1) and adapters are automatically wrapped in their corresponding proxy implementations.
     */
    class CORE_API ProxyDXGIFactory : public d3d::ProxyD3D<ProxyDXGIFactory, IDXGIFactory4> {
    public:
        ProxyDXGIFactory(IDXGIFactory4* pReal);

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override;

        // --- IDXGIObject Methods ---
        virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void* pData) override;
        virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown) override;
        virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData) override;
        virtual HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void** ppParent) override;

        // --- IDXGIFactory Methods ---
        virtual HRESULT STDMETHODCALLTYPE EnumAdapters(UINT Adapter, IDXGIAdapter** ppAdapter) override;
        virtual HRESULT STDMETHODCALLTYPE MakeWindowAssociation(HWND WindowHandle, UINT Flags) override;
        virtual HRESULT STDMETHODCALLTYPE GetWindowAssociation(HWND* pWindowHandle) override;
        virtual HRESULT STDMETHODCALLTYPE CreateSwapChain(IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain) override;
        virtual HRESULT STDMETHODCALLTYPE CreateSoftwareAdapter(HMODULE Module, IDXGIAdapter** ppAdapter) override;

        // --- IDXGIFactory1 Methods ---
        virtual HRESULT STDMETHODCALLTYPE EnumAdapters1(UINT Adapter, IDXGIAdapter1** ppAdapter) override;
        virtual BOOL STDMETHODCALLTYPE IsCurrent(void) override;

        // --- IDXGIFactory2 Methods ---
        virtual BOOL STDMETHODCALLTYPE IsWindowedStereoEnabled(void) override;
        virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForHwnd(IUnknown* pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) override;
        virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForCoreWindow(IUnknown* pDevice, IUnknown* pWindow, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) override;
        virtual HRESULT STDMETHODCALLTYPE GetSharedResourceAdapterLuid(HANDLE hResource, LUID* pLuid) override;
        virtual HRESULT STDMETHODCALLTYPE RegisterStereoStatusWindow(HWND WindowHandle, UINT Message, DWORD* pCookie) override;
        virtual HRESULT STDMETHODCALLTYPE RegisterStereoStatusEvent(HANDLE EventHandle, DWORD* pCookie) override;
        virtual void  STDMETHODCALLTYPE UnregisterStereoStatus(DWORD Cookie) override;
        virtual HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusWindow(HWND WindowHandle, UINT Message, DWORD* pCookie) override;
        virtual HRESULT STDMETHODCALLTYPE RegisterOcclusionStatusEvent(HANDLE EventHandle, DWORD* pCookie) override;
        virtual void  STDMETHODCALLTYPE UnregisterOcclusionStatus(DWORD Cookie) override;
        virtual HRESULT STDMETHODCALLTYPE CreateSwapChainForComposition(IUnknown* pDevice, const DXGI_SWAP_CHAIN_DESC1* pDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain) override;

        // --- IDXGIFactory3 Methods ---
        virtual UINT STDMETHODCALLTYPE GetCreationFlags(void) override;

        // --- IDXGIFactory4 Methods ---
        virtual HRESULT STDMETHODCALLTYPE EnumAdapterByLuid(LUID AdapterLuid, REFIID riid, void** ppvAdapter) override;
        virtual HRESULT STDMETHODCALLTYPE EnumWarpAdapter(REFIID riid, void** ppvAdapter) override;
    };

} // namespace dxgi