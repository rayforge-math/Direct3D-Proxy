#pragma once

#include "coreapi.h"
#include "d3d/ProxyD3D.h"
#include "dxgi_version.h"

namespace dxgi {

    /**
     * @class ProxyDXGISwapChain
     * @brief A virtualized wrapper for the IDXGISwapChain1 interface, extending swap chain functionality with DXGI 1.2 features.
     *
     * @details
     * This class implements the Proxy pattern for modern DXGI 1.2 swap chains.
     * It intercepts advanced presentation methods such as `Present1`, composition features,
     * and window handle retrieval (`GetHwnd`), ensuring full compatibility with modern windowing and flip models.
     */
    class CORE_API ProxyDXGISwapChain : public d3d::ProxyD3D<ProxyDXGISwapChain, IDXGISwapChain4> {
    public:
        ProxyDXGISwapChain(IDXGISwapChain4* pReal);

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override;

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

        // --- IDXGISwapChain1 Methods ---
        virtual HRESULT STDMETHODCALLTYPE GetDesc1(DXGI_SWAP_CHAIN_DESC1* pDesc) override;
        virtual HRESULT STDMETHODCALLTYPE GetFullscreenDesc(DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pDesc) override;
        virtual HRESULT STDMETHODCALLTYPE GetHwnd(HWND* pHwnd) override;
        virtual HRESULT STDMETHODCALLTYPE GetCoreWindow(REFIID refiid, void** ppUnk) override;
        virtual HRESULT STDMETHODCALLTYPE Present1(UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS* pPresentParameters) override;
        virtual BOOL STDMETHODCALLTYPE IsTemporaryMonoSupported(void) override;
        virtual HRESULT STDMETHODCALLTYPE GetRestrictToOutput(IDXGIOutput** ppRestrictToOutput) override;
        virtual HRESULT STDMETHODCALLTYPE SetBackgroundColor(const DXGI_RGBA* pColor) override;
        virtual HRESULT STDMETHODCALLTYPE GetBackgroundColor(DXGI_RGBA* pColor) override;
        virtual HRESULT STDMETHODCALLTYPE SetRotation(DXGI_MODE_ROTATION Rotation) override;
        virtual HRESULT STDMETHODCALLTYPE GetRotation(DXGI_MODE_ROTATION* pRotation) override;

        // --- IDXGISwapChain2 Methods ---
        virtual HRESULT STDMETHODCALLTYPE SetSourceSize(UINT Width, UINT Height) override;
        virtual HRESULT STDMETHODCALLTYPE GetSourceSize(UINT* pWidth, UINT* pHeight) override;
        virtual HRESULT STDMETHODCALLTYPE SetMaximumFrameLatency(UINT MaxLatency) override;
        virtual HRESULT STDMETHODCALLTYPE GetMaximumFrameLatency(UINT* pMaxLatency) override;
        virtual HANDLE STDMETHODCALLTYPE GetFrameLatencyWaitableObject(void) override;
        virtual HRESULT STDMETHODCALLTYPE SetMatrixTransform(const DXGI_MATRIX_3X2_F* pMatrix) override;
        virtual HRESULT STDMETHODCALLTYPE GetMatrixTransform(DXGI_MATRIX_3X2_F* pMatrix) override;

        // --- IDXGISwapChain3 Methods ---
        virtual UINT STDMETHODCALLTYPE GetCurrentBackBufferIndex(void) override;
        virtual HRESULT STDMETHODCALLTYPE CheckColorSpaceSupport(DXGI_COLOR_SPACE_TYPE ColorSpace, UINT* pColorSpaceSupport) override;
        virtual HRESULT STDMETHODCALLTYPE SetColorSpace1(DXGI_COLOR_SPACE_TYPE ColorSpace) override;
        virtual HRESULT STDMETHODCALLTYPE ResizeBuffers1(UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT Format, UINT SwapChainFlags, const UINT* pCreationNodeMask, IUnknown* const* ppPresentQueue) override;

        // --- IDXGISwapChain4 Methods ---
        virtual HRESULT STDMETHODCALLTYPE SetHDRMetaData(DXGI_HDR_METADATA_TYPE Type, UINT Size, void* pMetaData) override;
    };

} // namespace dxgi