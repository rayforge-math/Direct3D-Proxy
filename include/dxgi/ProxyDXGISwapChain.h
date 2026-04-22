#pragma once

#include "dxgi.h"
#include "dxgi/dxgi_version.h"

namespace dxgi {

    class ProxyDXGISwapChain : public IDXGISwapChain {
    private:
        IDXGISwapChain* m_pReal;
        ULONG m_RefCount;

        virtual ~ProxyDXGISwapChain();

    public:
        ProxyDXGISwapChain(IDXGISwapChain* pReal);

        // --- Rule of Three: Disable copying ---
        ProxyDXGISwapChain(const ProxyDXGISwapChain&) = delete;
        ProxyDXGISwapChain& operator=(const ProxyDXGISwapChain&) = delete;

        // --- IUnknown Methods ---
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override;
        virtual ULONG STDMETHODCALLTYPE AddRef() override;
        virtual ULONG STDMETHODCALLTYPE Release() override;

        // --- IDXGIObject Methods ---
        virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void* pData) override;
        virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown) override;
        virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData) override;
        virtual HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void** ppParent) override;

        // --- IDXGIDeviceSubObject Methods ---
        virtual HRESULT STDMETHODCALLTYPE GetDevice(REFIID riid, void** ppDevice) override;

        // --- IDXGISwapChain Methods ---
        virtual HRESULT STDMETHODCALLTYPE Present(UINT SyncInterval, UINT Flags) override;
        virtual HRESULT STDMETHODCALLTYPE GetBuffer(UINT Buffer, REFIID riid, void** ppSurface) override;
        virtual HRESULT STDMETHODCALLTYPE SetFullscreenState(BOOL Fullscreen, IDXGIOutput* pTarget) override;
        virtual HRESULT STDMETHODCALLTYPE GetFullscreenState(BOOL* pFullscreen, IDXGIOutput** ppTarget) override;
        virtual HRESULT STDMETHODCALLTYPE GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc) override;
        virtual HRESULT STDMETHODCALLTYPE ResizeBuffers(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) override;
        virtual HRESULT STDMETHODCALLTYPE ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters) override;
        virtual HRESULT STDMETHODCALLTYPE GetContainingOutput(IDXGIOutput** ppOutput) override;
        virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats) override;
        virtual HRESULT STDMETHODCALLTYPE GetLastPresentCount(UINT* pLastPresentCount) override;
    };

} // namespace dxgi