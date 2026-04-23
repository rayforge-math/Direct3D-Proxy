/*
    Feature docs: https://learn.microsoft.com/en-us/windows/win32/api/_direct3d11/
*/

#pragma once

#include "dxgi/dxgi_version.h"
#include "d3d/D3DInspector.h"

namespace dxgi {

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
#ifdef DX_SDK_SUPPORTS_D3D12
            UINT ResourceBindingTier;
            UINT ResourceHeapTier;
#endif
        } Architecture;

        struct {
            BOOL DoublePrecision;       // FP64
#ifdef DX_SDK_SUPPORTS_D3D11_1
            BOOL OutputMergerLogicOp;   // Logic Ops (XOR, etc.)
#endif
#ifdef DX_SDK_SUPPORTS_D3D10
            BOOL ComputeShader_v4_x;    // CS on DX10 Hardware
#endif
            BOOL MinPrecision;          // Support for half-floats (16-bit)
#ifdef DX_SDK_SUPPORTS_D3D11_2
            //BOOL TiledResources;        // Support for sparse textures
#endif
#ifdef DX_SDK_SUPPORTS_D3D12_RAYTRACING
            BOOL RaytracingSupport;     // DXR Tier 1.0/1.1
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
     * @class DXGIInspector
     * @brief Static utility class for extracting metadata from DirectX interfaces.
     * * This class operates in a read-only manner to observe and capture the state
     * and capabilities of graphics objects created by the application without
     * interfering with the rendering pipeline.
     */
    class DXGIInspector {
    public:
        // data collection
        static SwapChainInfo CollectSwapChainInfo(IDXGISwapChain* swChain);
        static InteropInfo CollectInteropInfo(const char* type, void* input, void* output);
        // string resolver

    };

} // namespace dxgi