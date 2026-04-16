/*
    Undocumented function prototypes were determined using IDA Pro and the following references:
        https://github.com/doitsujin/dxvk/blob/master/src/d3d11/d3d11_main.cpp
        https://github.com/bo3b/3Dmigoto/blob/master/DirectX11/D3D11Wrapper.cpp
        https://chromium.googlesource.com/external/p3/regal/+/cass/src/apitrace/wrappers/d3d11stubs.cpp
        https://github.com/wine-mirror/wine/blob/master/dlls/d3d11/d3d11_main.c
        https://github.com/apitrace/dxsdk/blob/master/Include/d3d11.h
        https://github.com/crosire/reshade/blob/main/source/d3d11/d3d11.cpp
*/
#pragma once

#include "D3D11.h"
#include "Windows.Graphics.DirectX.Direct3D11.interop.h"

// ============================================================================
// PROXY CONFIGURATION - FEATURE TOGGLES
// ============================================================================
// Comment out a define to disable the C++ Hook and use the ASM Pass-Through.

//#define PROXY_BYPASS_ALL
#ifndef PROXY_BYPASS_ALL

    // [1] PUBLIC SDK APIs
    #define PROXY_SECTION_1
    #ifdef PROXY_SECTION_1
        #define PROXY_D3D11_CREATE_DEVICE
        #define PROXY_D3D11_CREATE_DEVICE_AND_SWCHAIN
        #define PROXY_D3D11_ON12_CREATE_DEVICE
        #define PROXY_CREATE_D3D11_DEV_FROM_DXGI
        #define PROXY_CREATE_D3D11_SURF_FROM_DXGI
    #endif

    // [2] INTERNAL & UNDOCUMENTED "CORE" APIs
    //#define PROXY_SECTION_2
    #ifdef PROXY_SECTION_2
        #define PROXY_D3D11_CORE_CREATE_DEVICE
        #define PROXY_D3D11_CORE_REGISTER_LAYERS
        #define PROXY_D3D11_CORE_CREATE_LAYERED_DEV
        #define PROXY_D3D11_CORE_GET_LAYERED_SIZE
        #define PROXY_D3D11_CREATE_DEVICE_FOR_D3D12
        #define PROXY_ENABLE_FEATURE_LEVEL_UPGRADE
    #endif

    // [3] USER-MODE DRIVER
    //#define PROXY_SECTION_3
    #ifdef PROXY_SECTION_3
        #define PROXY_OPEN_ADAPTER_10
        #define PROXY_OPEN_ADAPTER_10_2
    #endif

    // [4] D3D PERFORMANCE TOOLING
    //#define PROXY_SECTION_4
    #ifdef PROXY_SECTION_4
        #define PROXY_D3D_PERF_BEGIN_EVENT
        #define PROXY_D3D_PERF_END_EVENT
        #define PROXY_D3D_PERF_SET_MARKER
        #define PROXY_D3D_PERF_GET_STATUS
    #endif

    // [5] KERNEL-MODE THUNKS (D3DKMT)
    //#define PROXY_SECTION_5
    #ifdef PROXY_SECTION_5

        // A. Adapter & Device Management
        #define PROXY_SECTION_5_A
        #ifdef PROXY_SECTION_5_A
            #define PROXY_D3DKMT_OPEN_ADAPTER_FROM_HDC
            #define PROXY_D3DKMT_QUERY_ADAPTER_INFO
            #define PROXY_D3DKMT_CLOSE_ADAPTER
            #define PROXY_D3DKMT_CREATE_DEVICE
            #define PROXY_D3DKMT_GET_DEVICE_STATE
            #define PROXY_D3DKMT_DESTROY_DEVICE
        #endif

        // B. Context & Scheduling
        #define PROXY_SECTION_5_B
        #ifdef PROXY_SECTION_5_B
            #define PROXY_D3DKMT_CREATE_CONTEXT
            #define PROXY_D3DKMT_GET_CONTEXT_SCHED_PRIO
            #define PROXY_D3DKMT_SET_CONTEXT_SCHED_PRIO
            #define PROXY_D3DKMT_DESTROY_CONTEXT
        #endif

        // C. Allocation & Resource Management
        #define PROXY_SECTION_5_C
        #ifdef PROXY_SECTION_5_C
            #define PROXY_D3DKMT_CREATE_ALLOCATION
            #define PROXY_D3DKMT_QUERY_RESOURCE_INFO
            #define PROXY_D3DKMT_OPEN_RESOURCE
            #define PROXY_D3DKMT_GET_SHARED_PRIMARY
            #define PROXY_D3DKMT_LOCK
            #define PROXY_D3DKMT_UNLOCK
            #define PROXY_D3DKMT_QUERY_ALLOC_RESIDENCY
            #define PROXY_D3DKMT_SET_ALLOC_PRIORITY
            #define PROXY_D3DKMT_DESTROY_ALLOCATION
        #endif

        // D. Rendering & Display
        #define PROXY_SECTION_5_D
        #ifdef PROXY_SECTION_5_D
            #define PROXY_D3DKMT_SET_VIDPN_SOURCE_OWNER
            #define PROXY_D3DKMT_SET_DISPLAY_MODE
            #define PROXY_D3DKMT_GET_DISPLAY_MODE_LIST
            #define PROXY_D3DKMT_SET_DISPLAY_PRIV_DRIVER
            #define PROXY_D3DKMT_SET_GAMMA_RAMP
            #define PROXY_D3DKMT_GET_MULTISAMPLE_LIST
            #define PROXY_D3DKMT_WAIT_FOR_VBLANK
            #define PROXY_D3DKMT_RENDER
            #define PROXY_D3DKMT_PRESENT
        #endif

        // E. Synchronization
        #define PROXY_SECTION_5_E
        #ifdef PROXY_SECTION_5_E
            #define PROXY_D3DKMT_CREATE_SYNC_OBJ
            #define PROXY_D3DKMT_SIGNAL_SYNC_OBJ
            #define PROXY_D3DKMT_WAIT_FOR_SYNC_OBJ
            #define PROXY_D3DKMT_DESTROY_SYNC_OBJ
        #endif

        // F. System & Misc
        #define PROXY_SECTION_5_F
        #ifdef PROXY_SECTION_5_F
            #define PROXY_D3DKMT_ESCAPE
            #define PROXY_D3DKMT_GET_RUNTIME_DATA
        #endif

    #endif

#endif

// ============================================================================
// ARCHITECTURAL FALLBACK MAPPING
// ============================================================================
// This internal logic enables legacy options for proxy functions.

#ifdef PROXY_D3D11_CORE_CREATE_DEVICE
#define PROXY_D3D11_CORE_CREATE_DEVICE_LEGACY
#endif

namespace d3d11 {

    extern "C" {

        // ============================================================================
        // SECTION 1: PUBLIC SDK APIs (Stable & Documented)
        // ============================================================================

        typedef HRESULT(WINAPI* D3D11CreateDevice_t)(
            _In_opt_ IDXGIAdapter*,
            D3D_DRIVER_TYPE,
            HMODULE,
            UINT,
            _In_opt_ const D3D_FEATURE_LEVEL*,
            UINT,
            UINT,
            _Out_opt_ ID3D11Device**,
            _Out_opt_ D3D_FEATURE_LEVEL*,
            _Out_opt_ ID3D11DeviceContext**
            );
        /**
         * @brief Creates a device that represents the display adapter.
         * This is the primary entry point for Direct3D 11 applications. It initializes
         * the virtualized representation of the GPU (ID3D11Device) and the pipeline
         * that performs rendering (ID3D11DeviceContext).
         * @param pAdapter           [in, opt] The video adapter to use.
         * @param DriverType         [in]      The type of driver to create (Hardware, Warp, etc.).
         * @param Software           [in]      Handle to a software rasterizer.
         * @param Flags              [in]      Runtime layers to enable (e.g., DEBUG, SINGLETHREADED).
         * @param pFeatureLevels     [in, opt] Targeted hardware feature levels.
         * @param FeatureLevels      [in]      Number of feature levels provided.
         * @param SDKVersion         [in]      The SDK version (usually D3D11_SDK_VERSION).
         * @param ppDevice           [out, opt] Returns the created ID3D11Device.
         * @param pFeatureLevel      [out, opt] Returns the actual feature level supported.
         * @param ppImmediateContext [out, opt] Returns the created ID3D11DeviceContext.
         * @return HRESULT Standard Direct3D 11 return codes.
         * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-d3d11createdevice
         */
        HRESULT WINAPI D3D11CreateDevice_(
            _In_opt_ IDXGIAdapter* pAdapter,
            D3D_DRIVER_TYPE DriverType,
            HMODULE Software,
            UINT Flags,
            _In_opt_ const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            UINT SDKVersion,
            _Out_opt_ ID3D11Device** ppDevice,
            _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
            _Out_opt_ ID3D11DeviceContext** ppImmediateContext
        );

        typedef HRESULT(WINAPI* D3D11CreateDeviceAndSwapChain_t)(
            _In_opt_ IDXGIAdapter*,
            D3D_DRIVER_TYPE,
            HMODULE,
            UINT,
            _In_opt_ const D3D_FEATURE_LEVEL*,
            UINT,
            UINT,
            _In_opt_ const DXGI_SWAP_CHAIN_DESC*,
            _Out_opt_ IDXGISwapChain**,
            _Out_opt_ ID3D11Device**,
            _Out_opt_ D3D_FEATURE_LEVEL*,
            _Out_opt_ ID3D11DeviceContext**
            );
        /**
         * @brief Creates a Direct3D 11 device, an immediate context, and a swap chain.
         * This is a helper function that combines D3D11CreateDevice and
         * IDXGIFactory::CreateSwapChain into a single call. It is the most common
         * entry point for applications that render directly to a window.
         * @param pAdapter           [in, opt] The video adapter to use.
         * @param DriverType         [in]      The type of driver to create.
         * @param Software           [in]      Handle to a software rasterizer.
         * @param Flags              [in]      Runtime creation flags.
         * @param pFeatureLevels     [in, opt] Targeted feature levels.
         * @param FeatureLevels      [in]      Number of feature levels provided.
         * @param SDKVersion         [in]      The SDK version.
         * @param pSwapChainDesc     [in, opt] Description of the swap chain to create.
         * @param ppSwapChain        [out, opt] Returns the created DXGI swap chain.
         * @param ppDevice           [out, opt] Returns the created D3D11 device.
         * @param pFeatureLevel      [out, opt] Returns the actual supported feature level.
         * @param ppImmediateContext [out, opt] Returns the created D3D11 immediate context.
         * @return HRESULT Standard Direct3D 11 return codes.
         * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-d3d11createdeviceandswapchain
         */
        HRESULT WINAPI D3D11CreateDeviceAndSwapChain_(
            _In_opt_ IDXGIAdapter* pAdapter,
            D3D_DRIVER_TYPE DriverType,
            HMODULE Software,
            UINT Flags,
            _In_opt_ const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            UINT SDKVersion,
            _In_opt_ const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
            _Out_opt_ IDXGISwapChain** ppSwapChain,
            _Out_opt_ ID3D11Device** ppDevice,
            _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
            _Out_opt_ ID3D11DeviceContext** ppImmediateContext
        );

        typedef HRESULT(WINAPI* D3D11On12CreateDevice_t)(
            _In_ IUnknown*,
            UINT,
            _In_opt_ const D3D_FEATURE_LEVEL*,
            UINT,
            _In_opt_ IUnknown* const*,
            UINT,
            UINT,
            _Out_opt_ ID3D11Device**,
            _Out_opt_ ID3D11DeviceContext**,
            _Out_opt_ D3D_FEATURE_LEVEL*
            );
        /**
         * @brief Explicitly creates a D3D11 device built on top of a D3D12 device.
         * This function initializes the D3D11On12 translation layer. It is used
         * to leverage D3D11 rendering techniques or legacy middleware within
         * an application that primarily uses the D3D12 API.
         * @param pDevice               [in]      The underlying D3D12 device.
         * @param Flags                 [in]      Device creation flags (D3D11_CREATE_DEVICE_FLAG).
         * @param pFeatureLevels        [in, opt] Array of requested feature levels.
         * @param FeatureLevels         [in]      Number of feature levels in the array.
         * @param ppCommandQueues       [in, opt] Array of D3D12 command queues to use.
         * @param NumQueues             [in]      Number of command queues provided.
         * @param NodeMask              [in]      Node mask for multi-adapter support.
         * @param ppDevice              [out, opt] Returns the D3D11On12 device.
         * @param ppImmediateContext    [out, opt] Returns the D3D11On12 immediate context.
         * @param pChosenFeatureLevel   [out, opt] Returns the actual supported feature level.
         * @return HRESULT Standard Direct3D return codes.
         * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11on12/nf-d3d11on12-d3d11on12createdevice
         */
        HRESULT WINAPI D3D11On12CreateDevice_(
            _In_ IUnknown* pDevice,
            UINT Flags,
            _In_opt_ const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            _In_opt_ IUnknown* const* ppCommandQueues,
            UINT NumQueues,
            UINT NodeMask,
            _Out_opt_ ID3D11Device** ppDevice,
            _Out_opt_ ID3D11DeviceContext** ppImmediateContext,
            _Out_opt_ D3D_FEATURE_LEVEL* pChosenFeatureLevel
        );

        typedef HRESULT(WINAPI* CreateDirect3D11DeviceFromDXGIDevice_t)(_In_ IDXGIDevice*, _Out_ IInspectable**);
        /**
         * @brief Creates a WinRT IDirect3DDevice instance from a native DXGI device.
         * This function is used to interop between the native D3D11/DXGI layer and the
         * Windows Runtime (WinRT) graphics APIs. It wraps the native device so it can
         * be used by modern Windows.Graphics.DirectX.Direct3D11 namespaces.
         * @param dxgiDevice     [in]  The native DXGI device to wrap.
         * @param graphicsDevice [out] Returns the WinRT IInspectable pointer to the device.
         * @return HRESULT Standard COM return codes (S_OK on success).
         * @see https://learn.microsoft.com/en-us/windows/win32/api/windows.graphics.directx.direct3d11.interop/nf-windows-graphics-directx-direct3d11-interop-createdirect3d11devicefromdxgidevice
         */
        HRESULT WINAPI CreateDirect3D11DeviceFromDXGIDevice_(_In_ IDXGIDevice* dxgiDevice, _Out_ IInspectable** graphicsDevice);

        typedef HRESULT(WINAPI* CreateDirect3D11SurfaceFromDXGISurface_t)(IDXGISurface*, _Out_ IInspectable**);
        /**
         * @brief Creates a WinRT IDirect3DSurface instance from a native DXGI surface.
         * * This interop function wraps a native IDXGISurface into a Windows Runtime
         * IInspectable object. This is essential for sharing textures between
         * classic D3D11 and modern WinRT-based UI frameworks or capture APIs.
         * * @param dxgiSurface   [in]  The native DXGI surface to wrap.
         * @param graphicsSurface [out] Returns the WinRT IInspectable pointer to the surface.
         * @return HRESULT Standard COM return codes (S_OK on success).
         * @see https://learn.microsoft.com/en-us/windows/win32/api/windows.graphics.directx.direct3d11.interop/nf-windows-graphics-directx-direct3d11-interop-createdirect3d11surfacefromdxgisurface
         */
        HRESULT WINAPI CreateDirect3D11SurfaceFromDXGISurface_(IDXGISurface* dxgiSurface, _Out_ IInspectable** graphicsSurface);

        // ============================================================================
        // SECTION 2: INTERNAL & UNDOCUMENTED "CORE" APIs (High Volatility)
        // ============================================================================

#ifdef PROXY_D3D11_CORE_CREATE_DEVICE_LEGACY
        typedef HRESULT(WINAPI* D3D11CoreCreateDevice_t)(
            IDXGIFactory*,
            IDXGIAdapter*,
            UINT,
            const D3D_FEATURE_LEVEL*,
            UINT,
            ID3D11Device**
            );
        /**
         * @brief Internal core function to create a Direct3D 11 device.
         * This function is an internal entry point used by the D3D11 runtime to
         * initialize the device. Unlike the public D3D11CreateDevice, this version
         * requires an explicit IDXGIFactory and IDXGIAdapter. It is frequently
         * targeted by proxy DLLs to ensure all device creation paths are hooked.
         * @param pFactory       [in]  Pointer to the DXGI factory.
         * @param pAdapter       [in]  Pointer to the DXGI adapter to use.
         * @param Flags          [in]  Runtime creation flags (e.g., D3D11_CREATE_DEVICE_DEBUG).
         * @param pFeatureLevels [in]  Pointer to an array of D3D_FEATURE_LEVELs.
         * @param FeatureLevels  [in]  Number of feature levels in the array.
         * @param ppDevice       [out] Returns the created ID3D11Device.
         * @return HRESULT Standard Direct3D 11 return codes.
         * @see https://github.com/doitsujin/dxvk/blob/master/src/d3d11/d3d11_main.cpp
         */
        HRESULT WINAPI D3D11CoreCreateDevice_(
            IDXGIFactory* pFactory,
            IDXGIAdapter* pAdapter,
            UINT Flags,
            const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            ID3D11Device** ppDevice
        );
#else
        typedef HRESULT(WINAPI* D3D11CoreCreateDevice_t)(
            IDXGIFactory* pFactory,
            IDXGIAdapter* pAdapter,
            D3D_DRIVER_TYPE DriverType,
            HMODULE Software,
            UINT Flags,
            const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            UINT SDKVersion,
            ID3D11Device** ppDevice,
            D3D_FEATURE_LEVEL* pOutFeatureLevel
            );
        /**
         * @brief Internal core function to create a Direct3D 11 device.
         * This is the actual internal entry point within d3d11.dll that the public
         * D3D11CreateDevice API eventually calls. It provides granular control over
         * the device creation process, including explicit factory and adapter handling.
         * @param pFactory       [in]  Pointer to the IDXGIFactory used for adapter enumeration.
         * @param pAdapter       [in]  Pointer to the IDXGIAdapter (Hardware/Software) to use.
         * @param DriverType     [in]  The type of driver to create (Hardware, Warp, etc.).
         * @param Software       [in]  Handle to a software rasterizer DLL (usually nullptr).
         * @param Flags          [in]  Runtime creation flags (D3D11_CREATE_DEVICE_FLAG).
         * @param pFeatureLevels [in]  Pointer to an array of D3D_FEATURE_LEVELs to attempt.
         * @param FeatureLevels  [in]  Number of feature levels in the input array.
         * @param SDKVersion     [in]  The SDK version (usually D3D11_SDK_VERSION).
         * @param ppDevice       [out] Address of a pointer to the returned ID3D11Device.
         * @param pOutFeatureLevel [out] Returns the actual feature level successfully created.
         * @return HRESULT Standard Direct3D 11 return codes (S_OK on success).
         * @see Verified against DXVK implementation: https://github.com/doitsujin/dxvk/blob/master/src/d3d11/d3d11_main.cpp
         */
        HRESULT WINAPI D3D11CoreCreateDevice_(
            IDXGIFactory* pFactory,
            IDXGIAdapter* pAdapter,
            D3D_DRIVER_TYPE DriverType,
            HMODULE Software,
            UINT Flags,
            const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            UINT SDKVersion,
            ID3D11Device** ppDevice,
            D3D_FEATURE_LEVEL* pOutFeatureLevel
        );
#endif

        typedef HRESULT(WINAPI* D3D11CoreRegisterLayers_t)(const void*, DWORD);
        /**
         * @brief Internal function to register Direct3D 11 device layers.
         * This function is part of the internal infrastructure that allows the D3D11
         * runtime to recognize and initialize optional layers (such as the Debug
         * or D3D11On12 layers). It is called during the early stages of device
         * initialization.
         * @param pLayerInfo [in] Opaque pointer to the layer registration data.
         * @param LayerCount [in] Internal versioning or configuration flags.
         * @return HRESULT Returns S_OK if the layers were registered successfully.
         */
        HRESULT WINAPI D3D11CoreRegisterLayers_(const void* pLayerInfo, DWORD LayerCount);

        typedef HRESULT(WINAPI* D3D11CoreCreateLayeredDevice_t)(
            const void*,
            DWORD,
            const void*,
            REFIID,
            void**
            );
        /**
         * @brief Internal function to create a layered Direct3D 11 device.
         * This function is used by the D3D11 runtime to initialize layered devices,
         * which allow for features like the SDK Debug Layer or the D3D11On12
         * translation layer. It is a lower-level entry point than the standard
         * device creation APIs.
         * @param pLayerContexts [in]  Opaque pointer to internal layer data.
         * @param ContextCount   [in]  Internal flags or bitmask for layer configuration.
         * @param pDeviceDesc    [in]  Opaque pointer to secondary layer configuration.
         * @param riid           [in]  The GUID of the interface being requested (usually ID3D11Device).
         * @param ppvDevice      [out] Returns the created layered device or object.
         * @return HRESULT Standard Direct3D return codes.
         */
        HRESULT WINAPI D3D11CoreCreateLayeredDevice_(
            const void* pLayerContexts,
            DWORD ContextCount,
            const void* pDeviceDesc,
            REFIID riid,
            void** ppvDevice
        );

        typedef SIZE_T(WINAPI* D3D11CoreGetLayeredDeviceSize_t)(const void*, DWORD);
        /**
         * @brief Retrieves the memory size required for a layered Direct3D 11 device.
         * Part of the internal D3D11 layer infrastructure. This function calculates
         * the allocation size necessary to house the internal data structures for
         * a specific set of device layers.
         * @param pLayerContexts    [in] Opaque pointer to internal layer configuration data.
         * @param ContextCount      [in] Internal flags or bitmask associated with the layers.
         * @return SIZE_T The required size in bytes for the layered device structure.
         */
        SIZE_T WINAPI D3D11CoreGetLayeredDeviceSize_(const void* pLayerContexts, DWORD ContextCount);

        typedef HRESULT(WINAPI* D3D11CreateDeviceForD3D12_t)(
            IUnknown*,
            UINT,
            const D3D_FEATURE_LEVEL*,
            UINT,
            UINT,
            UINT,
            ID3D11Device**,
            ID3D11DeviceContext**,
            D3D_FEATURE_LEVEL*
            );
        /**
         * @brief Creates a D3D11 device that routes commands through a D3D12 device.
         * This function initializes the D3D11On12 translation layer. It allows
         * applications to use D3D11 objects and rendering commands which are
         * then translated into D3D12 calls for the provided D3D12 device.
         * @param pDevice               [in]  The underlying D3D12 device (as IUnknown).
         * @param Flags                 [in]  Creation flags (D3D11_CREATE_DEVICE_FLAG).
         * @param pFeatureLevels        [in]  Array of requested feature levels.
         * @param FeatureLevels         [in]  Number of feature levels in the array.
         * @param NumQueues             [in]  Number of command queues to use from the D3D12 device.
         * @param NodeMask              [in]  The node mask for multi-adapter configurations.
         * @param ppDevice              [out] Returns the D3D11On12 device.
         * @param ppImmediateContext    [out] Returns the D3D11On12 immediate context.
         * @param pChosenFeatureLevel   [out] Returns the actual supported feature level.
         * @return HRESULT Standard Direct3D return codes.
         * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11on12/nf-d3d11on12-d3d11on12createdevice
         */
        HRESULT WINAPI D3D11CreateDeviceForD3D12_(
            IUnknown* pDevice,
            UINT Flags,
            const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            UINT NumQueues, // ? SDKVersion ?
            UINT NodeMask, // ? NumQueues ?
            ID3D11Device** ppDevice,
            ID3D11DeviceContext** ppImmediateContext,
            D3D_FEATURE_LEVEL* pChosenFeatureLevel
        );

        typedef void* (WINAPI* EnableFeatureLevelUpgrade_t)();
        /**
         * @brief Enables the upgrading of the Direct3D Feature Level.
         * An internal, undocumented function. It allows the runtime to negotiate with
         * the User-Mode Driver (UMD) to elevate the reported hardware capabilities
         * beyond the initial handshake level.
         * @note This is part of the "D3D11 Core" internal exports.
         * @return void* A status handle. Returns E_NOTIMPL (0x80004001) if not supported.
         * @see Reference: Internal symbol exported by d3d11.dll (see Windows Research Kernel or MinGW headers)
         * @see https://github.com/tpn/winsdk-10/blob/master/Include/10.0.16299.0/um/d3d11_1.h (Related Internal Header)
         */
        void* WINAPI EnableFeatureLevelUpgrade_();

        // ============================================================================
        // SECTION 3: User-Mode Driver
        // ============================================================================

        typedef HRESULT(WINAPI* OpenAdapter10_t)(_Inout_ void*);
        /**
         * @brief Creates a Direct3D 10 graphics adapter object.
         * This is the primary entry point for the D3D10 User-Mode Driver. It initializes
         * the driver's capabilities and returns a table of function pointers (the DDI)
         * that the runtime will use for all subsequent hardware communication.
         * @param pOpenData [in, out] Pointer to a D3D10DDIARG_OPENADAPTER structure
         * containing version info and table pointers.
         * @return HRESULT Returns S_OK if the adapter was successfully opened.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3d10umddi/nc-d3d10umddi-pfnd3d10ddi_openadapter
         */
        HRESULT WINAPI OpenAdapter10_(_Inout_ void* pOpenData);

        typedef HRESULT(WINAPI* OpenAdapter10_2_t)(_Inout_ void*);
        /**
         * @brief Creates a Direct3D 10.2 graphics adapter object.
         * An updated version of the adapter initialization introduced with D3D10.2
         * (Windows 7 SP1 / WDDM 1.1). It provides extended initialization data and
         * improved support for newer hardware features.
         * @param pOpenData [in, out] Pointer to a D3D10DDIARG_OPENADAPTER structure.
         * @return HRESULT Returns S_OK on success.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3d10umddi/nc-d3d10umddi-pfnd3d10ddi_openadapter
         */
        HRESULT WINAPI OpenAdapter10_2_(_Inout_ void* pOpenData);

        // ============================================================================
        // SECTION 4: D3D Performance Tooling
        // ============================================================================

        typedef void* (*D3DPerformance_BeginEvent_t)(void*, void*);
        /**
         * @brief Marks the beginning of a user-defined event range.
         * This function is the flat-export equivalent of ID3DUserDefinedAnnotation::BeginEvent.
         * It allows profiling tools like PIX, Intel GPA, or NVIDIA NSight to group
         * graphics commands into logical blocks.
         * @param pName [in] A Unicode string containing the name of the event.
         * @param Color [in] A color value (often ARGB) used to visualize the event in a profiler's timeline.
         * @return int The current level of nested events. Returns a negative value or E_NOTIMPL if failed.
         * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11_1/nf-d3d11_1-id3duserdefinedannotation-beginevent
         */
        void* D3DPerformance_BeginEvent_(void* unknown0, void* unknown1); // ? D3DPerformance_BeginEvent_(void* unknown0) ?

        typedef void* (*D3DPerformance_EndEvent_t)(void**);
        /**
         * @brief Marks the end of the most recent user-defined event range.
         * This function is the flat-export equivalent of ID3DUserDefinedAnnotation::EndEvent.
         * It stops the profiling timer for the current event block. These calls
         * must be strictly balanced with BeginEvent calls.
         * @param unknown0 Traditionally a pointer to a status value, though largely unused
         * in modern runtime implementations (typically passed as NULL).
         * @return void* The remaining nesting level of events.
         * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11_1/nf-d3d11_1-id3duserdefinedannotation-endevent
         */
        void* D3DPerformance_EndEvent_(void** unknown0);

        typedef UINT(*D3DPerformance_SetMarker_t)(void*, void*);
        /**
         * @brief Inserts a single-point performance marker into the command stream.
         * This function is the flat-export equivalent of ID3DUserDefinedAnnotation::SetMarker.
         * Unlike BeginEvent, SetMarker represents a single point in time rather
         * than a range. It is used to label specific GPU commands or synchronization
         * points for easier identification in profiling tools like PIX or NVIDIA NSight.
         * @param pName [in] A Unicode string containing the name of the marker.
         * @param Color [in] A color value (ARGB) used to visualize the marker in the profiler's timeline.
         * @return UINT The current event nesting level. Returns E_NOTIMPL (0x80004001) if failed.
         * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11_1/nf-d3d11_1-id3duserdefinedannotation-setmarker
         */
        UINT D3DPerformance_SetMarker_(void* unknown0, void* unknown1);

        typedef void* (*D3DPerformance_GetStatus_t)(void**);
        /**
         * @brief Retrieves the current status of performance profiling.
         * This function is the flat-export equivalent of ID3DUserDefinedAnnotation::GetStatus.
         * It allows the application (and your proxy) to determine if a profiling tool
         * is actively monitoring the command stream. If it returns FALSE, you can
         * skip calling BeginEvent/SetMarker to save CPU cycles.
         * @param unknown0 Traditionally an output pointer, but in modern d3d11
         * implementations, the status is primarily communicated via the return value.
         * @return void* Returns TRUE (non-zero) if a profiler is attached; otherwise FALSE.
         * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11_1/nf-d3d11_1-id3duserdefinedannotation-getstatus
         */
        void* D3DPerformance_GetStatus_(void** unknown0);

        // ============================================================================
        // SECTION 5: Kernel-Mode Thunks (D3DKMT)
        // ============================================================================

        // ============================================================================
        // 5.A: Adapter & Device Management
        // ============================================================================

        typedef HRESULT(WINAPI* D3DKMTOpenAdapterFromHdc_t)();
        /**
         * @brief Maps a GDI Device Context (HDC) to a graphics adapter handle and monitor.
         * This function is the primary bridge between traditional Windows GDI (Graphics
         * Device Interface) and the modern WDDM Kernel-Mode Thunk layer. It allows
         * the runtime to identify which physical GPU is responsible for a specific HDC.
         * @param pData [in, out] Pointer to a D3DKMT_OPENADAPTERFROMHDC structure that
         * contains the HDC and receives the adapter handle and monitor handle.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the mapping was successful;
         * otherwise, an error code (e.g., STATUS_INVALID_PARAMETER).
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtopenadapterfromhdc
         */
        HRESULT WINAPI D3DKMTOpenAdapterFromHdc_();

        typedef HRESULT(WINAPI* D3DKMTQueryAdapterInfo_t)();
        /**
         * @brief Retrieves comprehensive graphics adapter information from the kernel-mode driver.
         * This function is used to query various capabilities of the physical GPU,
         * including driver version, memory segment details, and hardware-specific
         * feature support (e.g., WDDM version).
         * @param pData [in, out] Pointer to a D3DKMT_QUERYADAPTERINFO structure. The 'Type'
         * field determines what specific info is being requested.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the query was successful;
         * otherwise, an NTSTATUS error code.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtqueryadapterinfo
         */
        HRESULT WINAPI D3DKMTQueryAdapterInfo_();

        typedef HRESULT(WINAPI* D3DKMTCreateDevice_t)();
        /**
         * @brief Creates a kernel-mode graphics device handle.
         * Establishes a logical connection to the graphics adapter for kernel-mode
         * operations. This handle is required for subsequent calls to other KMT
         * functions like context or allocation creation.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTCreateDevice(D3DKMT_CREATEDEVICE* pData)
         * This wrapper uses an implicit passthrough. The 'pData' pointer is passed
         * via the caller's stack or registers directly to the original implementation.
         * @param pData [in, out] Pointer to a D3DKMT_CREATEDEVICE structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the device handle was created.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtcreatedevice
         */
        HRESULT WINAPI D3DKMTCreateDevice_();

        typedef HRESULT(WINAPI* D3DKMTGetDeviceState_t)();
        /**
         * @brief Retrieves the current state of a graphics device.
         * This KMT function allows the runtime to query a variety of device-specific
         * information, including reset status, present stats, and engine utilization.
         * It is often used to detect "Device Lost" scenarios at the kernel level.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTGetDeviceState(D3DKMT_GETDEVICESTATE* pData)
         * This wrapper uses an implicit passthrough. The 'pData' structure specifies
         * the type of state to retrieve and receives the requested data upon success.
         * @param pData [in, out] Pointer to a D3DKMT_GETDEVICESTATE structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the state was successfully retrieved.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtgetdevicestate
         */
        HRESULT WINAPI D3DKMTGetDeviceState_();

        typedef HRESULT(WINAPI* D3DKMTDestroyDevice_t)();
        /**
         * @brief Destroys a kernel-mode graphics device handle.
         * This function terminates the logical connection to the graphics adapter
         * previously established by D3DKMTCreateDevice. It is a fundamental part
         * of the driver-level cleanup process.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTDestroyDevice(const D3DKMT_DESTROYDEVICE* pData)
         * This wrapper uses an implicit passthrough. The 'pData' argument is expected
         * to be provided by the caller in the appropriate registers or stack location.
         * @param pData [in] Pointer to a D3DKMT_DESTROYDEVICE structure containing the device handle.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the device handle was destroyed.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtdestroydevice
         */
        HRESULT WINAPI D3DKMTDestroyDevice_();

        typedef HRESULT(WINAPI* D3DKMTCloseAdapter_t)();
        /**
         * @brief Closes a graphics adapter handle that was previously opened.
         * Releases the kernel-mode connection to the graphics adapter established via
         * D3DKMTOpenAdapter or D3DKMTOpenAdapterFromHdc.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTCloseAdapter(const D3DKMT_CLOSEADAPTER* pData)
         * This proxy uses an implicit passthrough. Parameters are handled via the
         * calling convention's register/stack state at the time of the call.
         * @param pData [in] Pointer to a D3DKMT_CLOSEADAPTER structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the adapter was closed successfully.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtcloseadapter
         */
        HRESULT WINAPI D3DKMTCloseAdapter_();

        // ============================================================================
        // 5.B: Context & Scheduling
        // ============================================================================

        typedef HRESULT(WINAPI* D3DKMTCreateContext_t)();
        /**
         * @brief Creates a kernel-mode device context.
         * Establishes a GPU context for the application, setting up the command
         * buffer and scheduling priorities within the Windows Display Driver Model (WDDM).
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTCreateContext(D3DKMT_CREATECONTEXT* pData)
         * This wrapper relies on a transparent passthrough. The 'pData' argument
         * is passed implicitly via the CPU registers or stack from the original caller.
         * @param pData [in, out] Pointer to a D3DKMT_CREATECONTEXT structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the context was created.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtcreatecontext
         */
        HRESULT WINAPI D3DKMTCreateContext_();

        typedef HRESULT(WINAPI* D3DKMTGetContextSchedulingPriority_t)();
        /**
         * @brief Retrieves the scheduling priority for a device context.
         * This KMT function queries the current priority level assigned to a GPU
         * context. The priority dictates how the graphics scheduler (part of
         * dxgkrnl.sys) interleaves command buffers from this context with others.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTGetContextSchedulingPriority(D3DKMT_GETCONTEXTSCHEDULINGPRIORITY* pData)
         * This wrapper uses an implicit passthrough. The 'pData' structure contains
         * the context handle and will receive the priority value upon success.
         * @param pData [in, out] Pointer to a D3DKMT_GETCONTEXTSCHEDULINGPRIORITY structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the priority was retrieved.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtgetcontextschedulingpriority
         */
        HRESULT WINAPI D3DKMTGetContextSchedulingPriority_();

        typedef HRESULT(WINAPI* D3DKMTSetContextSchedulingPriority_t)();
        /**
         * @brief Sets the scheduling priority for a specific graphics processing unit (GPU) context.
         * This function interacts directly with the Windows Graphics Scheduler (part of dxgkrnl.sys).
         * It adjusts the relative importance of a context, influencing how the scheduler
         * interleaves its command buffers with those from other processes or other
         * contexts within the same process.
         * @param pData [in] Pointer to a D3DKMT_SETCONTEXTSCHEDULINGPRIORITY structure
         * that specifies the context handle and the new priority level.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the scheduling priority was successfully set;
         * otherwise, an NTSTATUS error code.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtsetcontextschedulingpriority
         */
        HRESULT WINAPI D3DKMTSetContextSchedulingPriority_();

        typedef HRESULT(WINAPI* D3DKMTDestroyContext_t)();
        /**
         * @brief Destroys a kernel-mode device context.
         * This function releases the GPU context previously established for the application.
         * Once destroyed, the context handle becomes invalid, and any pending commands
         * in the associated command buffer are typically flushed or discarded.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTDestroyContext(const D3DKMT_DESTROYCONTEXT* pData)
         * This wrapper uses an implicit passthrough. The 'pData' argument is expected
         * to be provided by the caller in the appropriate registers or stack location.
         * @param pData [in] Pointer to a D3DKMT_DESTROYCONTEXT structure containing the handle.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the context was successfully destroyed.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtdestroycontext
         */
        HRESULT WINAPI D3DKMTDestroyContext_();

        // ============================================================================
        // 5.C: Allocation & Resource Management
        // ============================================================================

        typedef HRESULT(WINAPI* D3DKMTCreateAllocation_t)();
        /**
         * @brief Creates allocations of system or video memory.
         * Communicates directly with the DirectX Graphics Kernel (Dxgkrnl.sys) to
         * allocate physical or virtual memory segments for GPU resources.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTCreateAllocation(D3DKMT_CREATEALLOCATION* pData)
         * This wrapper uses an implicit passthrough. The 'pData' argument is expected
         * to be on the stack/registers as provided by the original caller.
         * @param pData [in, out] Pointer to a D3DKMT_CREATEALLOCATION structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the allocation was successful.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtcreateallocation
         */
        HRESULT WINAPI D3DKMTCreateAllocation_();

        typedef HRESULT(WINAPI* D3DKMTQueryResourceInfo_t)();
        /**
         * @brief Retrieves metadata about a shared resource before it is opened.
         * This function queries the graphics kernel (dxgkrnl.sys) for the specific
         * attributes of a shared resource—such as its format, size, alignment, and
         * allocation flags—using a global or shared handle.
         * This "pre-flight" check ensures that the calling process can allocate
         * sufficient memory and prepare the correct structures before calling D3DKMTOpenResource.
         * @param pData [in, out] Pointer to a D3DKMT_QUERYRESOURCEINFO structure. The
         * caller provides the handle, and the kernel fills in the resource metadata.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the info was successfully retrieved;
         * otherwise, an NTSTATUS error code like STATUS_INVALID_PARAMETER.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtqueryresourceinfo
         */
        HRESULT WINAPI D3DKMTQueryResourceInfo_();

        typedef HRESULT(WINAPI* D3DKMTOpenResource_t)();
        /**
         * @brief Opens a shared graphics resource created by another process.
         * This function establishes a connection to an existing allocation (such as a
         * texture, buffer, or surface) using a shared handle. It is the final step in
         * cross-process resource sharing, allowing the calling process to use the
         * memory as if it were its own.
         * @param pData [in, out] Pointer to a D3DKMT_OPENRESOURCE structure. The caller
         * provides the shared handle, and the kernel returns process-local handles for
         * the resource and its allocations.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the resource was successfully opened;
         * otherwise, an NTSTATUS error code such as STATUS_INVALID_HANDLE or STATUS_ACCESS_DENIED.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtopenresource
         */
        HRESULT WINAPI D3DKMTOpenResource_();

        typedef HRESULT(WINAPI* D3DKMTGetSharedPrimaryHandle_t)();
        /**
         * @brief Retrieves the global shared handle for the primary surface.
         * This KMT function allows a process to obtain a handle to the primary
         * surface currently associated with a specific video present source.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTGetSharedPrimaryHandle(D3DKMT_GETSHAREDPRIMARYHANDLE* pData)
         * This wrapper uses an implicit passthrough. The 'pData' structure contains
         * the adapter and source information and receives the shared handle.
         * @param pData [in, out] Pointer to a D3DKMT_GETSHAREDPRIMARYHANDLE structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the handle was retrieved.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtgetsharedprimaryhandle
         */
        HRESULT WINAPI D3DKMTGetSharedPrimaryHandle_();
        
        typedef HRESULT(WINAPI* D3DKMTLock_t)();
        /**
         * @brief Locks an entire allocation or specific pages within an allocation.
         * Provides the CPU with a virtual address to access the contents of an
         * allocation. This is typically used when the CPU needs to read from or
         * write to a resource (like a staging texture) that the GPU also uses.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTLock(D3DKMT_LOCK* pData)
         * This wrapper uses an implicit passthrough. The 'pData' structure contains
         * the allocation handle and receives the CPU virtual address upon success.
         * @param pData [in, out] Pointer to a D3DKMT_LOCK structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the lock was acquired.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtlock
         */
        HRESULT WINAPI D3DKMTLock_();

        typedef HRESULT(WINAPI* D3DKMTUnlock_t)();
        /**
         * @brief Unlocks a list of allocations.
         * The counterpart to D3DKMTLock. It releases the CPU's hold on the memory
         * allocations, allowing the GPU to resume using those resources.
         * @param pData [in] Pointer to a D3DKMT_UNLOCK structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) on success.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtunlock
         */
        HRESULT WINAPI D3DKMTUnlock_();

        typedef HRESULT(WINAPI* D3DKMTQueryAllocationResidency_t)();
        /**
         * @brief Retrieves the current residency status of specific memory allocations.
         * This function queries the Video Memory Manager (VidMm) within the graphics
         * kernel to determine if a set of allocations is currently "resident" in
         * GPU-accessible memory (VRAM or AGP/PCIe Aperture) or if they have been
         * paged out to system memory or the disk's page file.
         * @param pData [in] Pointer to a D3DKMT_QUERYALLOCATIONRESIDENCY structure
         * containing the device handle and the list of allocations to check.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the residency status was
         * successfully retrieved; otherwise, an NTSTATUS error code.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtqueryallocationresidency
         */
        HRESULT WINAPI D3DKMTQueryAllocationResidency_();

        typedef HRESULT(WINAPI* D3DKMTSetAllocationPriority_t)();
        /**
         * @brief Sets the eviction priority for specific memory allocations.
         * This function provides hints to the Video Memory Manager (VidMm) regarding
         * the relative importance of resources. When GPU memory pressure occurs, the
         * kernel uses these priority levels to decide which allocations stay in
         * high-speed VRAM and which are "evicted" (paged out) to system memory.
         * @param pData [in] Pointer to a D3DKMT_SETALLOCATIONPRIORITY structure
         * containing the allocation handles and their new priority levels.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the priority was successfully
         * updated; otherwise, an NTSTATUS error code.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtsetallocationpriority
         */
        HRESULT WINAPI D3DKMTSetAllocationPriority_();

        typedef HRESULT(WINAPI* D3DKMTDestroyAllocation_t)();
        /**
         * @brief Releases a resource, a list of allocations, or both.
         * This KMT function deallocates memory segments previously reserved by
         * the graphics kernel. It is a critical part of the GPU memory lifecycle
         * and helps prevent memory leaks in the kernel-mode driver.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTDestroyAllocation(const D3DKMT_DESTROYALLOCATION* pData)
         * This wrapper uses an implicit passthrough. The 'pData' pointer is passed
         * via the caller's stack or registers directly to the original implementation.
         * @param pData [in] Pointer to a D3DKMT_DESTROYALLOCATION structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the allocation was destroyed.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtdestroyallocation
         */
        HRESULT WINAPI D3DKMTDestroyAllocation_();

        // ============================================================================
        // 5.D: Rendering & Display
        // ============================================================================

        typedef HRESULT(WINAPI* D3DKMTSetVidPnSourceOwner_t)();
        /**
         * @brief Sets or releases the video present source owner in a VidPN topology.
         * This function defines which functional unit (source) owns a specific output
         * path. It is essential for managing which application or process has control
         * over a particular display output.
         * @param pData [in] Pointer to a D3DKMT_SETVIDPNSOURCEOWNER structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) on success.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtsetvidpnsourceowner
         */
        HRESULT WINAPI D3DKMTSetVidPnSourceOwner_();

        typedef HRESULT(WINAPI* D3DKMTSetDisplayMode_t)();
        /**
         * @brief Sets the allocation used for scanning out to the display.
         * This function configures the primary surface for the display and defines
         * which memory areas are directly sent to the monitor by the display controller.
         * It is frequently called during resolution changes or when entering exclusive
         * fullscreen mode.
         * @param pData [in] Pointer to a D3DKMT_SETDISPLAYMODE structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) on success.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtsetdisplaymode
         */
        HRESULT WINAPI D3DKMTSetDisplayMode_();

        typedef HRESULT(WINAPI* D3DKMTGetDisplayModeList_t)();
        /**
         * @brief Retrieves a list of available display modes, including extended formats.
         * Queries the display miniport driver for all supported screen resolutions,
         * refresh rates, and scanline ordering for a specific display source.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTGetDisplayModeList(D3DKMT_GETDISPLAYMODELIST* pData)
         * This wrapper uses an implicit passthrough. The 'pData' structure contains
         * the source handle and will be populated with the mode list upon success.
         * @param pData [in, out] Pointer to a D3DKMT_GETDISPLAYMODELIST structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the mode list was retrieved.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtgetdisplaymodelist
         */
        HRESULT WINAPI D3DKMTGetDisplayModeList_();

        typedef HRESULT(WINAPI* D3DKMTSetDisplayPrivateDriverFormat_t)();
        /**
         * @brief Changes the private format attribute of a video present source.
         * This function allows the runtime or the driver to adjust vendor-specific
         * format properties for a display source. It is often used to toggle
         * special hardware-accelerated modes or proprietary compression formats
         * that are not part of the standard DXGI format enumeration.
         * @param pData [in] Pointer to a D3DKMT_SETDISPLAYPRIVATEDRIVERFORMAT structure
         * specifying the adapter, the source, and the private format data.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) on success; otherwise, an NTSTATUS error code.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtsetdisplayprivatedriverformat
         */
        HRESULT WINAPI D3DKMTSetDisplayPrivateDriverFormat_();

        typedef HRESULT(WINAPI* D3DKMTSetGammaRamp_t)();
        /**
         * @brief Sets the hardware gamma ramp for the display device.
         * This function directly controls the hardware lookup tables (LUT) of the
         * graphics adapter to manipulate brightness, contrast, and color correction
         * at the kernel level for the associated VidPN source.
         * @param pData [in] Pointer to a D3DKMT_SETGAMMARAMP structure containing
         * the adapter handle and the specific gamma ramp data.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) on success; otherwise, an NTSTATUS error code.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtsetgammaramp
         */
        HRESULT WINAPI D3DKMTSetGammaRamp_();

        typedef HRESULT(WINAPI* D3DKMTGetMultisampleMethodList_t)();
        /**
         * @brief Retrieves a list of multiple-sample methods supported for an allocation.
         * This KMT function queries the display miniport driver for the available
         * multi-sampling (MSAA) configurations for a specific pixel format and
         * resolution on a given adapter.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTGetMultisampleMethodList(D3DKMT_GETMULTISAMPLEMETHODLIST* pData)
         * This wrapper uses an implicit passthrough. The 'pData' structure contains
         * the adapter handle and format, and will be populated with the method list.
         * @param pData [in, out] Pointer to a D3DKMT_GETMULTISAMPLEMETHODLIST structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the method list was retrieved.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtgetmultisamplemethodlist
         */
        HRESULT WINAPI D3DKMTGetMultisampleMethodList_();

        typedef HRESULT(WINAPI* D3DKMTWaitForVerticalBlankEvent_t)();
        /**
         * @brief Waits for the vertical blanking interval (V-Sync) to occur.
         * Blocks the calling thread until the monitor finishes drawing the current
         * frame and enters the vertical blanking period. This is essential for
         * tear-free rendering and precise timing of frame presentations.
         * @param pData [in] Pointer to a D3DKMT_WAITFORVERTICALBLANKEVENT structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) on success.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtwaitforverticalblankevent
         */
        HRESULT WINAPI D3DKMTWaitForVerticalBlankEvent_();

        typedef HRESULT(WINAPI* D3DKMTRender_t)();
        /**
         * @brief Submits a command buffer to the graphics kernel for GPU execution.
         * This is a high-frequency, performance-critical thunk that transfers the
         * user-mode command stream to the kernel-mode scheduler (dxgkrnl.sys). It
         * represents the final stage of work submission before the GPU processes the commands.
         * @param pData [in, out] Pointer to a D3DKMT_RENDER structure. The kernel
         * updates this structure with the current status and command buffer residency info.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the buffer was successfully submitted;
         * otherwise, an NTSTATUS error code.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtrender
         */
        HRESULT WINAPI D3DKMTRender_();

        typedef HRESULT(WINAPI* D3DKMTPresent_t)();
        /**
         * @brief Submits a present command to the graphics kernel.
         * This is the final step in the rendering pipeline. It triggers the "flip" or
         * "copy" operation that moves the completed frame from the back buffer to the
         * display controller (scan-out) or the Desktop Window Manager (DWM).
         * @param pData [in] Pointer to a D3DKMT_PRESENT structure containing handles
         * for the source/destination allocations and presentation flags (e.g., VSync).
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the present command was successfully
         * submitted; otherwise, an NTSTATUS error code.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtpresent
         */
        HRESULT WINAPI D3DKMTPresent_();

        // ============================================================================
        // 5.E: Synchronization
        // ============================================================================

        typedef HRESULT(WINAPI* D3DKMTCreateSynchronizationObject_t)();
        /**
         * @brief Creates a kernel-mode synchronization object.
         * Synchronization objects are used to coordinate execution between the CPU
         * and the GPU, or between different GPU contexts. This is a low-level KMT
         * function that interfaces with the graphics scheduler.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTCreateSynchronizationObject(D3DKMT_CREATESYNCHRONIZATIONOBJECT* pData)
         * This wrapper uses an implicit passthrough. The 'pData' pointer is passed
         * via the caller's stack or registers directly to the original implementation.
         * @param pData [in, out] Pointer to a D3DKMT_CREATESYNCHRONIZATIONOBJECT structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the object was created.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtcreatesynchronizationobject
         */
        HRESULT WINAPI D3DKMTCreateSynchronizationObject_();

        typedef HRESULT(WINAPI* D3DKMTSignalSynchronizationObject_t)();
        /**
         * @brief Inserts a signal command for synchronization objects into the context stream.
         * Used to signal a fence or semaphore from the GPU side. This allows the
         * graphics scheduler to coordinate dependencies between different GPU contexts
         * or between the CPU and GPU.
         * @param pData [in] Pointer to a D3DKMT_SIGNALSYNCHRONIZATIONOBJECT structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) on success.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtsignalsynchronizationobject
         */
        HRESULT WINAPI D3DKMTSignalSynchronizationObject_();

        typedef HRESULT(WINAPI* D3DKMTWaitForSynchronizationObject_t)();
        /**
         * @brief Inserts a wait command for synchronization objects into a context stream.
         * This function instructs the GPU scheduler to pause execution of the specified
         * context until the synchronization objects (fences/semaphores) are signaled.
         * It is the primary mechanism for managing cross-queue dependencies.
         * @param pData [in] Pointer to a D3DKMT_WAITFORSYNCHRONIZATIONOBJECT structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) on success.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtwaitforsynchronizationobject
         */
        HRESULT WINAPI D3DKMTWaitForSynchronizationObject_();
        
        typedef HRESULT(WINAPI* D3DKMTDestroySynchronizationObject_t)();
        /**
         * @brief Destroys a kernel-mode synchronization object.
         * Releases the GPU synchronization primitive (fence, semaphore, etc.)
         * previously created. This informs the graphics scheduler that the object
         * is no longer needed for coordinating engine tasks.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTDestroySynchronizationObject(const D3DKMT_DESTROYSYNCHRONIZATIONOBJECT* pData)
         * This wrapper uses an implicit passthrough. The 'pData' pointer is passed
         * via the caller's stack or registers directly to the original implementation.
         * @param pData [in] Pointer to a D3DKMT_DESTROYSYNCHRONIZATIONOBJECT structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the object was destroyed.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtdestroysynchronizationobject
         */
        HRESULT WINAPI D3DKMTDestroySynchronizationObject_();
       
        // ============================================================================
        // 5.F: System & Misc
        // ============================================================================
        
        typedef HRESULT(WINAPI* D3DKMTEscape_t)();
        /**
         * @brief Exchanges information with the display miniport driver.
         * This KMT function allows applications to send private data and commands
         * directly to the kernel-mode display driver. It is typically used for
         * vendor-specific extensions, diagnostics, or status queries.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTEscape(const D3DKMT_ESCAPE* pData)
         * This wrapper uses an implicit passthrough. The 'pData' pointer is expected
         * to be provided by the caller in the appropriate registers or stack location.
         * @param pData [in] Pointer to a D3DKMT_ESCAPE structure containing the command.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the escape command was processed.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtescape
         */
        HRESULT WINAPI D3DKMTEscape_();
        
        typedef HRESULT(WINAPI* D3DKMTGetRuntimeData_t)();
        /**
         * @brief Retrieves internal runtime-specific data from the graphics kernel.
         * This KMT function is reserved for system use. It allows the Direct3D runtime
         * to exchange private data with the display miniport driver to maintain
         * internal state consistency.
         * @note Official Signature: NTSTATUS APIENTRY D3DKMTGetRuntimeData(const D3DKMT_GETRUNTIMEDATA* pData)
         * This wrapper uses an implicit passthrough. The 'pData' argument is expected
         * to be provided by the caller in the appropriate registers or stack location.
         * @param pData [in, out] Pointer to a D3DKMT_GETRUNTIMEDATA structure.
         * @return NTSTATUS Returns STATUS_SUCCESS (0) if the data was retrieved.
         * @see https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/d3dkmthk/nf-d3dkmthk-d3dkmtgetruntimedata
         */
        HRESULT WINAPI D3DKMTGetRuntimeData_();
        
    }

} // namespace d3d11