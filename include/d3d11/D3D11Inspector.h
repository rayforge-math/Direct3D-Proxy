/*
    Feature docs: https://learn.microsoft.com/en-us/windows/win32/api/_direct3d11/
*/

#pragma once

#include "d3d11/d3d11_version.h"
#include "dxgi/dxgi_version.h"

namespace d3d11 {

    struct DeviceInfo {
        // --- Creation Context ---
        D3D_FEATURE_LEVEL SelectedFeatureLevel;
        UINT CreationFlags;

        // --- Hardware Details ---
        DXGI_ADAPTER_DESC1 AdapterDesc;

        // --- Driver Capabilities ---
        BOOL DriverConcurrentCreates;
        BOOL DriverCommandLists;

        struct {
            BOOL IsTileBased;
#ifdef DX_SDK_SUPPORTS_D3D11_3
            BOOL SupportsShaderCache;
#endif
#ifdef DX_SDK_SUPPORTS_D3D11_1
            BOOL SupportsConstantBufferOffsetting;
#endif
        } Architecture;

        struct {
            BOOL DoublePrecision;       // FP64
#ifdef DX_SDK_SUPPORTS_D3D11_1
            BOOL OutputMergerLogicOp;   // Logic Ops (XOR, etc.)
#endif
            BOOL MinPrecision;          // Support for half-floats (16-bit)
#ifdef DX_SDK_SUPPORTS_D3D11_2
            //BOOL TiledResources;        // Support for sparse textures
#endif
        } Features;
    };

    struct SwapChainInfo {
        DXGI_SWAP_CHAIN_DESC Desc;
        DXGI_SWAP_CHAIN_DESC1 Desc1;   // Extended info for modern Flip-Model
        BOOL IsModernFlipModel;        // Check if using FLIP_SEQUENTIAL/DISCARD
        HWND OutputWindow;
        float EffectiveRefreshRate;    // Calculated from Num/Denom
    };

    struct InteropInfo {
        const char* BridgeType;
        void* InputPointer;
        void* OutputPointer;
        bool IsValidChain;
    };

    struct SurfaceInfo {
        DXGI_SURFACE_DESC Desc;
        UINT MultisampleCount;
        UINT MultisampleQuality;
        BOOL IsSharedResource;
    };

    /**
     * @class D3D11Inspector
     * @brief Static utility class for extracting metadata from DirectX interfaces.
     * * This class operates in a read-only manner to observe and capture the state
     * and capabilities of graphics objects created by the application without
     * interfering with the rendering pipeline.
     */
    class D3D11Inspector {
    public:
        static DeviceInfo CollectDeviceInfo(ID3D11Device* dev, IDXGIAdapter* pInAdapter, D3D_FEATURE_LEVEL* pInFLevel, UINT creationFlags);
        static DeviceInfo CollectDeviceInfo(IDXGIDevice* dxgiDev);
        static SwapChainInfo CollectSwapChainInfo(IDXGISwapChain* swChain);
        static InteropInfo CollectInteropInfo(const char* type, void* input, void* output);
        static SurfaceInfo CollectSurfaceInfo(IDXGISurface* dxgiSurface);
    };

} // namespace d3d11