#pragma once

#include "d3d/ProxyD3D.h"
#include "dxgi/dxgi_version.h"

namespace dxgi {

    /**
     * @class ProxyDXGISwapChain
     * @brief A virtualization wrapper for the IDXGISwapChain interface, controlling the presentation layer.
     *
     * @details
     * This class serves as the final interceptor in the graphics pipeline, sitting between the
     * rendered frame buffers and the OS windowing system. It is the most critical point for
     * synchronization and frame-based logic.
     *
     * Core Functional Purposes:
     * - **Frame Interception (The Render Loop):** By hooking the 'Present' method, this class
     * gains control over the exact moment a frame is finished, allowing for custom logic to
     * execute before the image is sent to the display.
     * - **Output Redirection:** Facilitates the capturing of backbuffers via 'GetBuffer' to
     * redirect or copy the final image to external consumers (e.g., shared textures or video encoders).
     * - **Resolution & State Monitoring:** Observes 'ResizeBuffers' and 'SetFullscreenState'
     * to ensure that internal bridge components (like overlay dimensions) stay in sync with
     * the application's window size and display mode.
     * - **Performance Telemetry:** Provides access to 'GetFrameStatistics', enabling the
     * measurement of frame times, refresh rates, and presentation latency.
     *
     * Use Cases in Proxy Engineering:
     * 1. **Final Frame Injection:** The ideal location to trigger the rendering of external
     * UI, overlays, or post-processing effects right before the swap chain flips.
     * 2. **Buffer Manipulation:** Modifying swap chain flags or formats during 'ResizeBuffers'
     * to force modern features like the Flip Model (FLIP_DISCARD) on older applications.
     * 3. **Window Management:** Preventing or handling forced fullscreen transitions that
     * might otherwise break external window focus or overlay stability.
     */
    class ProxyDXGISwapChain : public ProxyD3D<IDXGISwapChain> {
    public:
        ProxyDXGISwapChain(IDXGISwapChain* pReal);

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