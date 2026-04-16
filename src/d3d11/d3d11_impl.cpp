/*
    Undocumented function prototypes were determined using IDA Pro and the following references:
        https://github.com/doitsujin/dxvk/blob/master/src/d3d11/d3d11_main.cpp
        https://github.com/bo3b/3Dmigoto/blob/master/DirectX11/D3D11Wrapper.cpp
        https://chromium.googlesource.com/external/p3/regal/+/cass/src/apitrace/wrappers/d3d11stubs.cpp
        https://github.com/wine-mirror/wine/blob/master/dlls/d3d11/d3d11_main.c
        https://github.com/apitrace/dxsdk/blob/master/Include/d3d11.h
*/

#include "d3d11/d3d11_impl.h"
#include "d3d11/d3d11_hook.h"

/**
 * @file d3d11_impl.cpp
 * @brief D3D11 Proxy - Hybrid Interception Layer
 * @section Architecture Strategy
 * To maintain 100% stack integrity, this proxy uses two distinct methods:
 * 1. C++ Wrappers: Used ONLY for well-documented functions with stable signatures.
 * 2. ASM Jump-Stubs (Transparent Forwarding): Used for undocumented or volatile
 * "Core" functions. This avoids the C++ 'call' instruction, which would
 * push a return address onto the stack and displace function parameters.
 *
 * @section Signature Audit Status (HIGH RISK)
 * THE FOLLOWING FUNCTIONS MUST REMAIN IN ASM JUMP-STUBS.
 * Implementation in C++ (even with 'void' or 'auto') will cause stack
 * misalignment and immediate crashes due to undocumented/variable parameter counts:
 * - D3D11CoreCreateDevice         (Known stack variance: 6 vs 10 params)
 * - D3D11CoreRegisterLayers       (Undocumented)
 * - D3D11CoreCreateLayeredDevice  (Undocumented)
 * - D3D11CoreGetLayeredDeviceSize (Undocumented)
 * - D3D11CreateDeviceForD3D12     (Internal/Volatile)
 * - EnableFeatureLevelUpgrade     (Internal/Volatile)
 * - OpenAdapter10                 (Legacy/Internal)
 * - OpenAdapter10_2               (Legacy/Internal)
 * @see jump_stubs.asm for the implementation of these functions.
 */

namespace d3d11 {

    // ============================================================================
    // DIRECT3D 11 PROXY DLL - MODULE ARCHITECTURE & TABLE OF CONTENTS
    // ============================================================================
    //
    // [1] PUBLIC SDK APIs (Stable & Documented)
    //      - D3D11CreateDevice_
    //      - D3D11CreateDeviceAndSwapChain_
    //      - D3D11On12CreateDevice_
    //      - CreateDirect3D11DeviceFromDXGIDevice_
    //      - CreateDirect3D11SurfaceFromDXGISurface_
    //
    // [2] INTERNAL & UNDOCUMENTED "CORE" APIs (High Volatility)
    //      - D3D11CoreCreateDevice_
    //      - D3D11CoreRegisterLayers_
    //      - D3D11CoreCreateLayeredDevice_
    //      - D3D11CoreGetLayeredDeviceSize_
    //      - D3D11CreateDeviceForD3D12_
    //      - EnableFeatureLevelUpgrade_
    //
    // [3] USER-MODE DRIVER
    //      - OpenAdapter10_
    //      - OpenAdapter10_2_
    //
    // [4] D3D PERFORMANCE TOOLING
    //      - D3DPerformance_BeginEvent_
    //      - D3DPerformance_EndEvent_
    //      - D3DPerformance_SetMarker_
    //      - D3DPerformance_GetStatus_
    //
    // [5] KERNEL-MODE THUNKS (D3DKMT)
    //     A. Adapter & Device Management:
    //        - D3DKMTOpenAdapterFromHdc_
    //        - D3DKMTQueryAdapterInfo_
    //        - D3DKMTCloseAdapter_
    //        - D3DKMTCreateDevice_
    //        - D3DKMTGetDeviceState_
    //        - D3DKMTDestroyDevice_
    //
    //     B. Context & Scheduling:
    //        - D3DKMTCreateContext_
    //        - D3DKMTGetContextSchedulingPriority_
    //        - D3DKMTSetContextSchedulingPriority_
    //        - D3DKMTDestroyContext_
    //
    //     C. Allocation & Resource Management:
    //        - D3DKMTCreateAllocation_
    //        - D3DKMTQueryResourceInfo_
    //        - D3DKMTOpenResource_
    //        - D3DKMTGetSharedPrimaryHandle_
    //        - D3DKMTLock_
    //        - D3DKMTUnlock_
    //        - D3DKMTQueryAllocationResidency_
    //        - D3DKMTSetAllocationPriority_
    //        - D3DKMTDestroyAllocation_
    //
    //     D. Rendering & Display:
    //        - D3DKMTSetVidPnSourceOwner_
    //        - D3DKMTSetDisplayMode_
    //        - D3DKMTGetDisplayModeList_
    //        - D3DKMTSetDisplayPrivateDriverFormat_
    //        - D3DKMTSetGammaRamp_
    //        - D3DKMTGetMultisampleMethodList_
    //        - D3DKMTWaitForVerticalBlankEvent_
    //        - D3DKMTRender_
    //        - D3DKMTPresent_
    //
    //     E. Synchronization:
    //        - D3DKMTCreateSynchronizationObject_
    //        - D3DKMTSignalSynchronizationObject_
    //        - D3DKMTWaitForSynchronizationObject_
    //        - D3DKMTDestroySynchronizationObject_
    //
    //     F. System & Misc:
    //        - D3DKMTEscape_
    //        - D3DKMTGetRuntimeData_
    //
    // ============================================================================

    extern "C" {

        // ============================================================================
        // SECTION 1: PUBLIC SDK APIs (Stable & Documented)
        // ============================================================================

#ifdef PROXY_D3D11_CREATE_DEVICE
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
            _Out_opt_ ID3D11DeviceContext** ppImmediateContext)
        {
            /**
             * @note STRATEGIC HOOK POINT:
             * This is the most critical function in a D3D11 proxy. Successful
             * interception allows you to:
             * 1. Force certain flags (like adding D3D11_CREATE_DEVICE_DEBUG).
             * 2. Force a specific Feature Level to test compatibility.
             * 3. Wrap the resulting 'ppDevice' and 'ppImmediateContext' in your
             * own proxy classes to intercept all subsequent rendering calls.
             */

            HRESULT result = reinterpret_cast<D3D11CreateDevice_t>(proc_D3D11CreateDevice)(
                pAdapter,
                DriverType,
                Software,
                Flags,
                pFeatureLevels,
                FeatureLevels,
                SDKVersion,
                ppDevice,
                pFeatureLevel,
                ppImmediateContext
                );
            return result;
        }
#else
#pragma comment(linker, "/export:D3D11CreateDevice=D3D11CreateDevice_ASM")
#endif

#ifdef PROXY_D3D11_CREATE_DEVICE_AND_SWCHAIN
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
            _Out_opt_ ID3D11DeviceContext** ppImmediateContext)
        {
            /**
             * @note STRATEGIC HOOK POINT:
             * This function is more complex than 'D3D11CreateDevice' because it
             * also returns an 'IDXGISwapChain'.
             * 1. If you proxy the Device, you must also proxy the Context.
             * 2. If you proxy the SwapChain, you can intercept the 'Present'
             * calls, which is where frame-rate limiting or overlay
             * rendering usually happens.
             */

            HRESULT result = reinterpret_cast<D3D11CreateDeviceAndSwapChain_t>(proc_D3D11CreateDeviceAndSwapChain)(
                pAdapter,
                DriverType,
                Software,
                Flags,
                pFeatureLevels,
                FeatureLevels,
                SDKVersion,
                pSwapChainDesc,
                ppSwapChain,
                ppDevice,
                pFeatureLevel,
                ppImmediateContext
                );
            return result;
        }
#else
#pragma comment(linker, "/export:D3D11CreateDeviceAndSwapChain=D3D11CreateDeviceAndSwapChain_ASM")
#endif

#ifdef PROXY_D3D11_ON12_CREATE_DEVICE
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
            _Out_opt_ D3D_FEATURE_LEVEL* pChosenFeatureLevel)
        {
            /**
             * @note INTERNAL IMPLEMENTATION:
             * This function is the public entry point for D3D11-to-D3D12 mapping.
             * 1. 'pDevice' is an ID3D12Device and 'ppCommandQueues' contains
             * ID3D12CommandQueue pointers.
             * 2. If your proxy aims to intercept D3D12-level execution, you must
             * ensure these pointers are correctly unwrapped to the original
             * system pointers before calling the real function.
             * 3. Successful return of 'ppDevice' provides a D3D11 device that
             * can be wrapped in your D3D11 proxy class.
             */

            HRESULT result = reinterpret_cast<D3D11On12CreateDevice_t>(proc_D3D11On12CreateDevice)(
                pDevice,
                Flags,
                pFeatureLevels,
                FeatureLevels,
                ppCommandQueues,
                NumQueues,
                NodeMask,
                ppDevice,
                ppImmediateContext,
                pChosenFeatureLevel
                );
            return result;
        }
#else
#pragma comment(linker, "/export:D3D11On12CreateDevice=D3D11On12CreateDevice_ASM")
#endif

#ifdef PROXY_CREATE_D3D11_DEV_FROM_DXGI
        HRESULT WINAPI CreateDirect3D11DeviceFromDXGIDevice_(_In_ IDXGIDevice* dxgiDevice, _Out_ IInspectable** graphicsDevice)
        {
            /**
             * @note INTERNAL NOTE:
             * This function acts as an interop bridge. If you are proxying the DXGI device,
             * ensure the 'dxgiDevice' passed here is your proxy pointer (if applicable)
             * to maintain the hook chain into the WinRT/UWP environment.
             */

            HRESULT result = reinterpret_cast<CreateDirect3D11DeviceFromDXGIDevice_t>(proc_CreateDirect3D11DeviceFromDXGIDevice)(
                dxgiDevice,
                graphicsDevice
                );
            return result;
        }
#else
#pragma comment(linker, "/export:CreateDirect3D11DeviceFromDXGIDevice=CreateDirect3D11DeviceFromDXGIDevice_ASM")
#endif

#ifdef PROXY_CREATE_D3D11_SURF_FROM_DXGI
        HRESULT WINAPI CreateDirect3D11SurfaceFromDXGISurface_(IDXGISurface* dxgiSurface, _Out_ IInspectable** graphicsSurface)
        {
            /**
             * @note INTERNAL IMPLEMENTATION:
             * This function bridges the gap between DXGI and WinRT surfaces.
             * If you are proxying DXGI surfaces to intercept 'Present' calls or
             * modification of frame data, ensure that 'dxgiSurface' is handled
             * correctly to maintain the proxy chain.
             */

            HRESULT result = reinterpret_cast<CreateDirect3D11SurfaceFromDXGISurface_t>(proc_CreateDirect3D11SurfaceFromDXGISurface)(
                dxgiSurface,
                graphicsSurface
                );
            return result;
        }
#else
#pragma comment(linker, "/export:CreateDirect3D11SurfaceFromDXGISurface=CreateDirect3D11SurfaceFromDXGISurface_ASM")
#endif

        // ============================================================================
        // SECTION 2: INTERNAL & UNDOCUMENTED "CORE" APIs (High Volatility)
        // ============================================================================

#ifdef PROXY_D3D11_CORE_CREATE_DEVICE
#ifdef PROXY_D3D11_CORE_CREATE_DEVICE_LEGACY
        HRESULT WINAPI D3D11CoreCreateDevice_(
            IDXGIFactory* pFactory,
            IDXGIAdapter* pAdapter,
            UINT Flags,
            const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            ID3D11Device** ppDevice)
        {
            /**
             * @note INTERNAL IMPLEMENTATION:
             * This is a critical hooking point. Even if an application calls the
             * public 'D3D11CreateDevice', the runtime often eventually routes the
             * call through this core function.
             * Ensure that if you are wrapping the resulting ID3D11Device, you do so
             * here to capture devices created via internal runtime paths.
             */

            HRESULT result = reinterpret_cast<D3D11CoreCreateDevice_t>(proc_D3D11CoreCreateDevice)(
                pFactory, 
                pAdapter, 
                Flags, 
                pFeatureLevels, 
                FeatureLevels, 
                ppDevice
                );
            return result;
        }
#else
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
            D3D_FEATURE_LEVEL* pOutFeatureLevel)
        {
            /**
             * @note INTERNAL IMPLEMENTATION:
             * This is a critical hooking point. Even if an application calls the
             * public 'D3D11CreateDevice', the runtime often eventually routes the
             * call through this core function.
             * Ensure that if you are wrapping the resulting ID3D11Device, you do so
             * here to capture devices created via internal runtime paths.
             */

            HRESULT result = reinterpret_cast<D3D11CoreCreateDevice_t>(proc_D3D11CoreCreateDevice)(
                pFactory,
                pAdapter,
                DriverType,
                Software,
                Flags,
                pFeatureLevels,
                FeatureLevels,
                SDKVersion,
                ppDevice,
                pOutFeatureLevel
                );
            return result;
        }
#endif
#else
#pragma comment(linker, "/export:D3D11CoreCreateDevice=D3D11CoreCreateDevice_ASM")
#endif

#ifdef PROXY_D3D11_CORE_REGISTER_LAYERS
        HRESULT WINAPI D3D11CoreRegisterLayers_(const void* pLayerInfo, DWORD LayerCount)
        {
            /**
             * @note INTERNAL IMPLEMENTATION:
             * This is an undocumented entry point. It is typically called before or
             * during 'D3D11CoreCreateDevice'.
             * Because this function populates internal global states within the
             * D3D11 runtime, failing to pass this call through to the original
             * DLL will likely prevent any layered device from initializing,
             * effectively breaking features like the DirectX Debug Layer.
             */

            HRESULT result = reinterpret_cast<D3D11CoreRegisterLayers_t>(proc_D3D11CoreRegisterLayers)(
                pLayerInfo,
                LayerCount
                );
            return result;
        }
#else
#pragma comment(linker, "/export:D3D11CoreRegisterLayers=D3D11CoreRegisterLayers_ASM")
#endif

#ifdef PROXY_D3D11_CORE_CREATE_LAYERED_DEV
        HRESULT WINAPI D3D11CoreCreateLayeredDevice_(
            const void* pLayerContexts,
            DWORD ContextCount,
            const void* pDeviceDesc,
            REFIID riid,
            void** ppvDevice)
        {
            /**
             * @note INTERNAL IMPLEMENTATION:
             * These are vital for the internal D3D11 "Layer" infrastructure.
             * Interference here is dangerous; any modification to these pointers
             * without deep knowledge of the specific Windows build's runtime
             * will likely result in an immediate crash or device loss.
             */

            HRESULT result = reinterpret_cast<D3D11CoreCreateLayeredDevice_t>(proc_D3D11CoreCreateLayeredDevice)(
                pLayerContexts,
                ContextCount,
                pDeviceDesc,
                riid,
                ppvDevice
                );
            return result;
        }
#else
#pragma comment(linker, "/export:D3D11CoreCreateLayeredDevice=D3D11CoreCreateLayeredDevice_ASM")
#endif

#ifdef PROXY_D3D11_CORE_GET_LAYERED_SIZE
        SIZE_T WINAPI D3D11CoreGetLayeredDeviceSize_(const void* pLayerContexts, DWORD ContextCount)
        {
            /**
             * @note INTERNAL IMPLEMENTATION:
             * This function is purely informational for the D3D11 runtime's memory
             * allocator. Like 'D3D11CoreCreateLayeredDevice', it uses undocumented
             * parameters that must be passed through untouched.
             * Returning an incorrect size here will lead to heap corruption or
             * buffer overflows when the runtime later attempts to initialize the
             * device memory.
             */

            SIZE_T result = reinterpret_cast<D3D11CoreGetLayeredDeviceSize_t>(proc_D3D11CoreGetLayeredDeviceSize)(
                pLayerContexts,
                ContextCount
                );
            return result;
        }
#else
#pragma comment(linker, "/export:D3D11CoreGetLayeredDeviceSize=D3D11CoreGetLayeredDeviceSize_ASM")
#endif

#ifdef PROXY_D3D11_CREATE_DEVICE_FOR_D3D12
        HRESULT WINAPI D3D11CreateDeviceForD3D12_(
            IUnknown* pDevice,
            UINT Flags,
            const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            UINT NumQueues,
            UINT NodeMask,
            ID3D11Device** ppDevice,
            ID3D11DeviceContext** ppImmediateContext,
            D3D_FEATURE_LEVEL* pChosenFeatureLevel)
        {
            /**
             * @note INTERNAL IMPLEMENTATION:
             * This is the entry point for D3D11On12 translation.
             * 1. 'pDevice' is actually an ID3D12Device. If you are proxying D3D12,
             * you must ensure the real D3D12 pointer is passed here.
             * 2. The resulting 'ppDevice' behaves like a D3D11 device but
             * internally generates D3D12 command lists.
             * 3. Intercepting this is vital for proxies that need to function in
             * hybrid environments or modern Windows "System" apps.
             */

            HRESULT result = reinterpret_cast<D3D11CreateDeviceForD3D12_t>(proc_D3D11CreateDeviceForD3D12)(
                pDevice,
                Flags,
                pFeatureLevels,
                FeatureLevels,
                NumQueues,
                NodeMask,
                ppDevice,
                ppImmediateContext,
                pChosenFeatureLevel
                );
            return result;
        }
#else
#pragma comment(linker, "/export:D3D11CreateDeviceForD3D12=D3D11CreateDeviceForD3D12_ASM")
#endif

#ifdef PROXY_ENABLE_FEATURE_LEVEL_UPGRADE
        void* WINAPI EnableFeatureLevelUpgrade_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This thunk is rarely called but critical for hardware compatibility.
             * 1. It bridges the Gap between older hardware and newer D3D features.
             * 2. If your proxy returns E_NOTIMPL here, it may prevent some engines
             * from utilizing advanced hardware tiers (like 12_1 or 12_2) even if
             * the GPU technically supports them.
             */

            auto fn = reinterpret_cast<EnableFeatureLevelUpgrade_t>(proc_EnableFeatureLevelUpgrade);
            void* result = fn ? fn() : (void*)E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:EnableFeatureLevelUpgrade=EnableFeatureLevelUpgrade_ASM")
#endif

        // ============================================================================
        // SECTION 3: User-Mode Driver
        // ============================================================================

#ifdef PROXY_OPEN_ADAPTER_10
        HRESULT WINAPI OpenAdapter10_(_Inout_ void* pOpenData)
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This is the "Handshake" function.
             * 1. The runtime provides its version and required callback functions.
             * 2. The driver (via this thunk) fills in its own function table (DDI).
             * 3. CRITICAL: Any modification to pOpenData in a proxy can fundamentally
             * change how the runtime perceives the GPU's capabilities.
             */

            HRESULT result = reinterpret_cast<OpenAdapter10_t>(proc_OpenAdapter10)(pOpenData);
            return result;
        }
#else
#pragma comment(linker, "/export:OpenAdapter10=OpenAdapter10_ASM")
#endif

#ifdef PROXY_OPEN_ADAPTER_10_2
        HRESULT WINAPI OpenAdapter10_2_(_Inout_ void* pOpenData)
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * Revision 2 of the OpenAdapter call.
             * 1. This version is often preferred by modern Windows OS versions.
             * 2. It handles more granular feature reporting.
             * 3. Forwarding this correctly ensures that the application can utilize
             * the full performance of the WDDM 1.1+ driver model.
             */

            HRESULT result = reinterpret_cast<OpenAdapter10_2_t>(proc_OpenAdapter10_2)(pOpenData);
            return result;
        }
#else
#pragma comment(linker, "/export:OpenAdapter10_2=OpenAdapter10_2_ASM")
#endif

        // ============================================================================
        // SECTION 4: D3D Performance Tooling
        // ============================================================================

#ifdef PROXY_D3D_PERF_BEGIN_EVENT
        void* D3DPerformance_BeginEvent_(void* unknown0, void* unknown1)
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a passthrough for the Direct3D performance instrumentation.
             * 1. 'unknown0' is typically a wide-string (LPCWSTR) event name.
             * 2. These calls are often compiled out in retail builds but remain active
             * in 'Debug' or 'Profile' builds of games.
             */

            auto fn = reinterpret_cast<D3DPerformance_BeginEvent_t>(proc_D3DPerformance_BeginEvent);
            void* result = fn ? fn(unknown0, unknown1) : (void*)E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DPerformance_BeginEvent=D3DPerformance_BeginEvent_ASM")
#endif

#ifdef PROXY_D3D_PERF_END_EVENT
        void* D3DPerformance_EndEvent_(void** unknown0)
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * Counterpart to BeginEvent. If your proxy intercepts these, it can
             * provide insights into the internal organization of a game's frame
             * by logging the string names passed to BeginEvent.
             */

            auto fn = reinterpret_cast<D3DPerformance_EndEvent_t>(proc_D3DPerformance_EndEvent);
            void* result = fn ? fn(unknown0) : (void*)E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DPerformance_EndEvent=D3DPerformance_EndEvent_ASM")
#endif

#ifdef PROXY_D3D_PERF_SET_MARKER
        UINT D3DPerformance_SetMarker_(void* unknown0, void* unknown1)
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This is a "fire-and-forget" diagnostic thunk.
             * 1. 'unknown0' is the label (e.g., "Clear Render Target").
             * 2. It does not require a matching 'End' call.
             * 3. Useful for identifying exactly where a specific draw call occurs
             * within a massive capture of GPU commands.
             */

            auto fn = reinterpret_cast<D3DPerformance_SetMarker_t>(proc_D3DPerformance_SetMarker);
            UINT result = fn ? fn(unknown0, unknown1) : (UINT)E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DPerformance_SetMarker=D3DPerformance_SetMarker_ASM")
#endif

#ifdef PROXY_D3D_PERF_GET_STATUS
        void* D3DPerformance_GetStatus_(void** unknown0)
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * Used by engines to toggle instrumentation. If you force this to
             * return '1' (Active), you might trick a game into sending more
             * detailed metadata than it normally would in a production environment.
             */

            auto fn = reinterpret_cast<D3DPerformance_GetStatus_t>(proc_D3DPerformance_GetStatus);
            void* result = fn ? fn(unknown0) : (void*)E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DPerformance_GetStatus=D3DPerformance_GetStatus_ASM")
#endif

        // ============================================================================
        // SECTION 5: Kernel-Mode Thunks (D3DKMT)
        // ============================================================================

        // ============================================================================
        // 5.A: Adapter & Device Management
        // ============================================================================

#ifdef PROXY_D3DKMT_OPEN_ADAPTER_FROM_HDC
        HRESULT WINAPI D3DKMTOpenAdapterFromHdc_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This is used during initialization to connect a window (via its HDC)
             * to the hardware. Since this is often a one-time call per window,
             * ensuring a clean passthrough of the structure in RCX is essential
             * for the application to correctly identify its primary GPU.
             */

            auto fn = reinterpret_cast<D3DKMTOpenAdapterFromHdc_t>(proc_D3DKMTOpenAdapterFromHdc);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTOpenAdapterFromHdc=D3DKMTOpenAdapterFromHdc_ASM")
#endif

#ifdef PROXY_D3DKMT_QUERY_ADAPTER_INFO
        HRESULT WINAPI D3DKMTQueryAdapterInfo_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This is a primary discovery thunk. The 'pData' structure contains a
             * 'Type' field that determines what information is being requested.
             * Maintaining the RCX register integrity is vital for the kernel to
             * correctly interpret the specific sub-query being performed.
             */

            auto fn = reinterpret_cast<D3DKMTQueryAdapterInfo_t>(proc_D3DKMTQueryAdapterInfo);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTQueryAdapterInfo=D3DKMTQueryAdapterInfo_ASM")
#endif

#ifdef PROXY_D3DKMT_CREATE_DEVICE
        HRESULT WINAPI D3DKMTCreateDevice_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT) entry point.
             * 1. It acts as a gatekeeper to 'dxgkrnl.sys'.
             * 2. The parameterless signature allows for a transparent binary forward.
             * 3. CRITICAL: The calling convention must be preserved exactly. Since
             * 'D3DKMTCreateDevice_t' is typed as the original API, invoking it
             * without arguments ensures the CPU registers (RCX on x64) containing
             * the 'pData' pointer are passed to the destination function unmodified.
             */

            auto fn = reinterpret_cast<D3DKMTCreateDevice_t>(proc_D3DKMTCreateDevice);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTCreateDevice=D3DKMTCreateDevice_ASM")
#endif
        
#ifdef PROXY_D3DKMT_GET_DEVICE_STATE
        HRESULT WINAPI D3DKMTGetDeviceState_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT) for status querying.
             * 1. It acts as a bridge to 'dxgkrnl.sys' for device monitoring.
             * 2. The parameterless signature enables a transparent binary forward.
             * 3. IMPORTANT: Preservation of the RCX register (on x64) is vital.
             * Since the OS writes results directly back into the memory pointed to
             * by the caller's 'pData' structure, any pointer corruption will
             * result in an invalid memory write and a system crash.
             */

            auto fn = reinterpret_cast<D3DKMTGetDeviceState_t>(proc_D3DKMTGetDeviceState);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTGetDeviceState=D3DKMTGetDeviceState_ASM")
#endif

#ifdef PROXY_D3DKMT_DESTROY_DEVICE
        HRESULT WINAPI D3DKMTDestroyDevice_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT) for device teardown.
             * 1. It bridges the request to the DirectX Graphics Kernel (dxgkrnl.sys).
             * 2. The parameterless signature allows for a transparent binary forward.
             * 3. CRITICAL: The calling convention must be preserved. The processor state
             * (RCX on x64) must be maintained so the original function receives
             * the correct pointer to the D3DKMT_DESTROYDEVICE structure.
             */

            auto fn = reinterpret_cast<D3DKMTDestroyDevice_t>(proc_D3DKMTDestroyDevice);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTDestroyDevice=D3DKMTDestroyDevice_ASM")
#endif

#ifdef PROXY_D3DKMT_CLOSE_ADAPTER
        HRESULT WINAPI D3DKMTCloseAdapter_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function relies on a transparent passthrough.
             * The 'D3DKMTCloseAdapter_t' cast must match the original calling convention
             * to ensure the caller's arguments (pData) remain untouched on the stack
             * or in registers when jumping to the original function.
             */

            auto fn = reinterpret_cast<D3DKMTCloseAdapter_t>(proc_D3DKMTCloseAdapter);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTCloseAdapter=D3DKMTCloseAdapter_ASM")
#endif

        // ============================================================================
        // 5.B: Context & Scheduling
        // ============================================================================

#ifdef PROXY_D3DKMT_CREATE_CONTEXT
        HRESULT WINAPI D3DKMTCreateContext_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT).
             * 1. It acts as a bridge between the user-mode runtime and 'dxgkrnl.sys'.
             * 2. We use a parameterless signature to perform a "blind forward."
             * 3. Do not introduce local variables or stack-heavy logic before the call
             * to 'fn', as this could overwrite the 'pData' pointer residing in the
             * volatile registers or the caller's stack frame.
             */

            auto fn = reinterpret_cast<D3DKMTCreateContext_t>(proc_D3DKMTCreateContext);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTCreateContext=D3DKMTCreateContext_ASM")
#endif

#ifdef PROXY_D3DKMT_GET_CONTEXT_SCHED_PRIO
        HRESULT WINAPI D3DKMTGetContextSchedulingPriority_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT) used for scheduler diagnostics.
             * 1. It acts as a bridge to the Windows Graphics Scheduler.
             * 2. The parameterless signature allows for a transparent binary forward.
             * 3. CRITICAL: The processor state (RCX on x64) must remain untouched.
             * Since this function writes the result back into the 'pData' structure,
             * any corruption of the input pointer will cause the kernel to write
             * data to an invalid memory address, resulting in an immediate crash.
             */

            auto fn = reinterpret_cast<D3DKMTGetContextSchedulingPriority_t>(proc_D3DKMTGetContextSchedulingPriority);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTGetContextSchedulingPriority=D3DKMTGetContextSchedulingPriority_ASM")
#endif

#ifdef PROXY_D3DKMT_SET_CONTEXT_SCHED_PRIO
        HRESULT WINAPI D3DKMTSetContextSchedulingPriority_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * Used by the runtime to elevate or depress the GPU priority of
             * the process. Failure to forward this correctly could result in
             * the application being unfairly starved of GPU time by the OS.
             */

            auto fn = reinterpret_cast<D3DKMTSetContextSchedulingPriority_t>(proc_D3DKMTSetContextSchedulingPriority);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTSetContextSchedulingPriority=D3DKMTSetContextSchedulingPriority_ASM")
#endif

#ifdef PROXY_D3DKMT_DESTROY_CONTEXT
        HRESULT WINAPI D3DKMTDestroyContext_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT) used for context cleanup.
             * 1. It bridges the request to the DirectX Graphics Kernel (dxgkrnl.sys).
             * 2. The parameterless signature allows for a transparent binary forward.
             * 3. CRITICAL: Ensure that the calling convention is not disrupted. The
             * processor state (specifically RCX on x64) must be preserved so that the
             * original function receives the correct pointer to the destroy structure.
             */

            auto fn = reinterpret_cast<D3DKMTDestroyContext_t>(proc_D3DKMTDestroyContext);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTDestroyContext=D3DKMTDestroyContext_ASM")
#endif

        // ============================================================================
        // 5.C: Allocation & Resource Management
        // ============================================================================

#ifdef PROXY_D3DKMT_CREATE_ALLOCATION
        HRESULT WINAPI D3DKMTCreateAllocation_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This KMT (Kernel-Mode Thunk) function is a high-frequency call during
             * resource creation.
             * 1. It performs a "blind" forward to the original d3d11.dll entry point.
             * 2. Maintaining the integrity of the 'pData' pointer is critical, as
             * incorrect memory allocation parameters can trigger a Kernel Security
             * Check Failure (BSOD) or heap corruption in the graphics subsystem.
             */

            auto fn = reinterpret_cast<D3DKMTCreateAllocation_t>(proc_D3DKMTCreateAllocation);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTCreateAllocation=D3DKMTCreateAllocation_ASM")
#endif

#ifdef PROXY_D3DKMT_QUERY_RESOURCE_INFO
        HRESULT WINAPI D3DKMTQueryResourceInfo_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * Used in conjunction with D3DKMTOpenResource. It allows the runtime to
             * validate the shared resource's properties (like width/height/stride)
             * before committing to opening the handle, preventing cross-process
             * memory corruption.
             */

            auto fn = reinterpret_cast<D3DKMTQueryResourceInfo_t>(proc_D3DKMTQueryResourceInfo);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTQueryResourceInfo=D3DKMTQueryResourceInfo_ASM")
#endif

#ifdef PROXY_D3DKMT_OPEN_RESOURCE
        HRESULT WINAPI D3DKMTOpenResource_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * Cross-process communication relies on this thunk. If your proxy
             * is used in an environment with multiple processes (like a web browser
             * or a game launcher), any disruption to this call will prevent
             * shared surfaces from being visible across process boundaries.
             */

            auto fn = reinterpret_cast<D3DKMTOpenResource_t>(proc_D3DKMTOpenResource);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTOpenResource=D3DKMTOpenResource_ASM")
#endif

#ifdef PROXY_D3DKMT_GET_SHARED_PRIMARY
        HRESULT WINAPI D3DKMTGetSharedPrimaryHandle_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT) for surface handle sharing.
             * 1. It acts as a bridge to 'dxgkrnl.sys' to access shared global resources.
             * 2. The parameterless signature enables a transparent binary forward.
             * 3. CRITICAL: On x64, the 'pData' pointer is stored in RCX. Since the
             * kernel writes the shared handle back into this structure, any pointer
             * corruption will cause a memory access violation (BSOD or process crash).
             */

            auto fn = reinterpret_cast<D3DKMTGetSharedPrimaryHandle_t>(proc_D3DKMTGetSharedPrimaryHandle);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTGetSharedPrimaryHandle=D3DKMTGetSharedPrimaryHandle_ASM")
#endif
        
#ifdef PROXY_D3DKMT_LOCK
        HRESULT WINAPI D3DKMTLock_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT) for memory synchronization.
             * 1. It bridges the request to 'dxgkrnl.sys' to synchronize CPU/GPU access.
             * 2. The parameterless signature enables a transparent binary forward.
             * 3. CRITICAL: Locking is a synchronous operation that can stall the GPU
             * pipeline. Any delay or corruption of the 'pData' pointer in RCX (x64)
             * can lead to deadlocks in the graphics scheduler or a system-wide
             * TDR (Timeout Detection and Recovery) event.
             */

            auto fn = reinterpret_cast<D3DKMTLock_t>(proc_D3DKMTLock);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTLock=D3DKMTLock_ASM")
#endif
        
#ifdef PROXY_D3DKMT_UNLOCK
        HRESULT WINAPI D3DKMTUnlock_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This must be called as soon as CPU-side access to a resource is
             * finished. In a proxy, timing this call can help diagnose how
             * long the CPU is 'stalling' the GPU by holding onto shared allocations.
             */

            auto fn = reinterpret_cast<D3DKMTUnlock_t>(proc_D3DKMTUnlock);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTUnlock=D3DKMTUnlock_ASM")
#endif

#ifdef PROXY_D3DKMT_QUERY_ALLOC_RESIDENCY
        HRESULT WINAPI D3DKMTQueryAllocationResidency_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This thunk interfaces with the Video Memory Manager (VidMm).
             * Since residency is dynamic, this function is used to ensure resources
             * are "ready" for GPU execution. Any failure to forward this correctly
             * can lead to "Device Lost" errors as the runtime loses track of VRAM state.
             */

            auto fn = reinterpret_cast<D3DKMTQueryAllocationResidency_t>(proc_D3DKMTQueryAllocationResidency);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTQueryAllocationResidency=D3DKMTQueryAllocationResidency_ASM")
#endif

#ifdef PROXY_D3DKMT_SET_ALLOC_PRIORITY
        HRESULT WINAPI D3DKMTSetAllocationPriority_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * Interfaces with the memory manager to weight resources. Keeping
             * this thunk transparent ensures that the driver's own resource
             * management strategies (e.g., favoring textures currently in the
             * frustum) remain intact.
             */

            auto fn = reinterpret_cast<D3DKMTSetAllocationPriority_t>(proc_D3DKMTSetAllocationPriority);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTSetAllocationPriority=D3DKMTSetAllocationPriority_ASM")
#endif

#ifdef PROXY_D3DKMT_DESTROY_ALLOCATION
        HRESULT WINAPI D3DKMTDestroyAllocation_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT) entry point for memory cleanup.
             * 1. It bridges the user-mode destruction request to 'dxgkrnl.sys'.
             * 2. The parameterless signature enables a transparent binary passthrough.
             * 3. IMPORTANT: Because this function is often called during rapid resource
             * recycling or application shutdown, ensure no stack-clobbering logic
             * is added here. Any corruption of the 'pData' pointer can lead to
             * invalid memory access within the kernel context.
             */

            auto fn = reinterpret_cast<D3DKMTDestroyAllocation_t>(proc_D3DKMTDestroyAllocation);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTDestroyAllocation=D3DKMTDestroyAllocation_ASM")
#endif

        // ============================================================================
        // 5.D: Rendering & Display
        // ============================================================================

#ifdef PROXY_D3DKMT_SET_VIDPN_SOURCE_OWNER
        HRESULT WINAPI D3DKMTSetVidPnSourceOwner_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This thunk is vital for multi-monitor management. It informs the
             * Video Present Network (VidPN) which context 'owns' the display
             * real estate. Incorrect forwarding can cause display flickering
             * or loss of windowed/fullscreen exclusivity.
             */

            auto fn = reinterpret_cast<D3DKMTSetVidPnSourceOwner_t>(proc_D3DKMTSetVidPnSourceOwner);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTSetVidPnSourceOwner=D3DKMTSetVidPnSourceOwner_ASM")
#endif

#ifdef PROXY_D3DKMT_SET_DISPLAY_MODE
        HRESULT WINAPI D3DKMTSetDisplayMode_()
        {
            /**
             * @note IMPLEMENTATION DETAILS:
             * This function is frequently invoked during transitions to exclusive
             * fullscreen mode or during display resolution changes. It interacts
             * directly with the VidPN (Video Present Network) manager.
             */

            auto fn = reinterpret_cast<D3DKMTSetDisplayMode_t>(proc_D3DKMTSetDisplayMode);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTSetDisplayMode=D3DKMTSetDisplayMode_ASM")
#endif

#ifdef PROXY_D3DKMT_GET_DISPLAY_MODE_LIST
        HRESULT WINAPI D3DKMTGetDisplayModeList_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT) for display capability querying.
             * 1. It bridges the request to 'dxgkrnl.sys' to communicate with the monitor driver.
             * 2. The parameterless signature enables a transparent binary forward.
             * 3. CRITICAL: On x64, the 'pData' pointer resides in RCX. If the caller
             * provides a buffer that is too small, the driver will return an error
             * code and specify the required size. Maintaining the register state
             * ensures this back-and-forth negotiation works correctly.
             */

            auto fn = reinterpret_cast<D3DKMTGetDisplayModeList_t>(proc_D3DKMTGetDisplayModeList);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTGetDisplayModeList=D3DKMTGetDisplayModeList_ASM")
#endif

#ifdef PROXY_D3DKMT_SET_DISPLAY_PRIV_DRIVER
        HRESULT WINAPI D3DKMTSetDisplayPrivateDriverFormat_()
        {
            /**
             * @note IMPLEMENTATION DETAILS:
             * A specialized thunk used for driver-specific optimizations.
             * Since the structure can be vendor-dependent (IHV specific),
             * a transparent forward without parameter manipulation is
             * mandatory to ensure compatibility.
             */

            auto fn = reinterpret_cast<D3DKMTSetDisplayPrivateDriverFormat_t>(proc_D3DKMTSetDisplayPrivateDriverFormat);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTSetDisplayPrivateDriverFormat=D3DKMTSetDisplayPrivateDriverFormat_ASM")
#endif

#ifdef PROXY_D3DKMT_SET_GAMMA_RAMP
        HRESULT WINAPI D3DKMTSetGammaRamp_()
        {
            /**
             * @note IMPLEMENTATION DETAILS:
             * This function is commonly used by calibration software or in-game
             * brightness sliders. Since it accesses the monitor's hardware LUT
             * (Lookup Table), any failure in forwarding can lead to color
             * distortion across the entire desktop.
             */

            auto fn = reinterpret_cast<D3DKMTSetGammaRamp_t>(proc_D3DKMTSetGammaRamp);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTSetGammaRamp=D3DKMTSetGammaRamp_ASM")
#endif

#ifdef PROXY_D3DKMT_GET_MULTISAMPLE_LIST
        HRESULT WINAPI D3DKMTGetMultisampleMethodList_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT) for MSAA capability discovery.
             * 1. It acts as a bridge to 'dxgkrnl.sys' to negotiate hardware AA support.
             * 2. The parameterless signature enables a transparent binary forward.
             * 3. CRITICAL: The processor state (RCX on x64) must be preserved. The kernel
             * writes the list of supported methods back into the caller's memory buffer.
             * Any alteration of the pointer in RCX before calling 'fn' will lead to
             * memory corruption and a likely system crash.
             */

            auto fn = reinterpret_cast<D3DKMTGetMultisampleMethodList_t>(proc_D3DKMTGetMultisampleMethodList);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTGetMultisampleMethodList=D3DKMTGetMultisampleMethodList_ASM")
#endif

#ifdef PROXY_D3DKMT_WAIT_FOR_VBLANK
        HRESULT WINAPI D3DKMTWaitForVerticalBlankEvent_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This call bridges the CPU with the physical refresh rate of the monitor.
             * 1. It is a blocking call, meaning the calling thread will sleep until
             * the V-Blank event.
             * 2. In a proxy, this is an excellent place to measure 'Frame Latency'
             * and 'Display Lag' relative to the hardware refresh cycle.
             */

            auto fn = reinterpret_cast<D3DKMTWaitForVerticalBlankEvent_t>(proc_D3DKMTWaitForVerticalBlankEvent);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTWaitForVerticalBlankEvent=D3DKMTWaitForVerticalBlankEvent_ASM")
#endif

#ifdef PROXY_D3DKMT_RENDER
        HRESULT WINAPI D3DKMTRender_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This is arguably the most performance-critical KMT thunk.
             * 1. It is called multiple times per frame to flush command batches.
             * 2. The 'pData' in RCX contains the command buffer address and size.
             * 3. Any latency introduced here directly translates to CPU-side stutter.
             */

            auto fn = reinterpret_cast<D3DKMTRender_t>(proc_D3DKMTRender);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTRender=D3DKMTRender_ASM")
#endif

#ifdef PROXY_D3DKMT_PRESENT
        HRESULT WINAPI D3DKMTPresent_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * CRITICAL: This is a high-frequency call (once per frame).
             * 1. This is the ultimate "Hook Point" for measuring Frame Time.
             * 2. Any overhead introduced here will directly impact the game's FPS.
             * 3. The 'pData' pointer in RCX contains the vertical sync (VSync)
             * settings and the source/destination surface handles.
             */

            auto fn = reinterpret_cast<D3DKMTPresent_t>(proc_D3DKMTPresent);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTPresent=D3DKMTPresent_ASM")
#endif

        // ============================================================================
        // 5.E: Synchronization
        // ============================================================================

#ifdef PROXY_D3DKMT_CREATE_SYNC_OBJ
        HRESULT WINAPI D3DKMTCreateSynchronizationObject_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT) entry point.
             * 1. It operates at the WDDM boundary to allocate synchronization primitives.
             * 2. The parameterless signature allows for a transparent binary forward.
             * 3. CAUTION: Ensure the calling convention is preserved. On x64, the
             * address of the 'pData' structure must remain in the RCX register.
             * Avoid adding any code in this function that might modify volatile
             * registers before the jump to 'fn'.
             */

            auto fn = reinterpret_cast<D3DKMTCreateSynchronizationObject_t>(proc_D3DKMTCreateSynchronizationObject);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTCreateSynchronizationObject=D3DKMTCreateSynchronizationObject_ASM")
#endif

#ifdef PROXY_D3DKMT_SIGNAL_SYNC_OBJ
        HRESULT WINAPI D3DKMTSignalSynchronizationObject_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * High-frequency synchronization call. It places a signal in the
             * GPU's command stream. Because synchronization is the backbone
             * of asynchronous rendering, any register corruption (RCX) here
             * will lead to intermittent GPU hangs or "TDR" resets.
             */

            auto fn = reinterpret_cast<D3DKMTSignalSynchronizationObject_t>(proc_D3DKMTSignalSynchronizationObject);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTSignalSynchronizationObject=D3DKMTSignalSynchronizationObject_ASM")
#endif

#ifdef PROXY_D3DKMT_WAIT_FOR_SYNC_OBJ
        HRESULT WINAPI D3DKMTWaitForSynchronizationObject_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This is a critical synchronization thunk.
             * 1. It acts as a GPU-side 'barrier'.
             * 2. The 'pData' in RCX contains handles to the objects being waited on.
             * 3. Any failure to forward this correctly will cause the GPU to execute
             * commands out of order, leading to visual artifacts or 'Use-After-Free'
             * scenarios in VRAM.
             */

            auto fn = reinterpret_cast<D3DKMTWaitForSynchronizationObject_t>(proc_D3DKMTWaitForSynchronizationObject);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTWaitForSynchronizationObject=D3DKMTWaitForSynchronizationObject_ASM")
#endif

#ifdef PROXY_D3DKMT_DESTROY_SYNC_OBJ
        HRESULT WINAPI D3DKMTDestroySynchronizationObject_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT) for synchronization cleanup.
             * 1. It acts as the final boundary call before the graphics kernel (dxgkrnl.sys)
             * reclaims the synchronization resource.
             * 2. The parameterless signature enables a transparent binary forward.
             * 3. CRITICAL: The processor state (RCX on x64) must be preserved. Any
             * modification to the registers before the call to 'fn' will result in
             * the original function receiving a corrupt pointer, likely causing
             * a system hang or BSOD.
             */

            auto fn = reinterpret_cast<D3DKMTDestroySynchronizationObject_t>(proc_D3DKMTDestroySynchronizationObject);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTDestroySynchronizationObject=D3DKMTDestroySynchronizationObject_ASM")
#endif

        // ============================================================================
        // 5.F: System & Misc
        // ============================================================================

#ifdef PROXY_D3DKMT_ESCAPE
        HRESULT WINAPI D3DKMTEscape_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is a Kernel-Mode Thunk (KMT) used for driver-specific escape calls.
             * 1. It acts as a direct communication tunnel to the miniport driver.
             * 2. The parameterless signature allows for a transparent binary forward.
             * 3. CAUTION: Because escape calls can involve complex, vendor-specific
             * data structures, preserving the 'pData' pointer in RCX (on x64) is
             * mandatory. Any interference with the registers here can lead to
             * unpredictable driver behavior or system instability.
             */

            auto fn = reinterpret_cast<D3DKMTEscape_t>(proc_D3DKMTEscape);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTEscape=D3DKMTEscape_ASM")
#endif

#ifdef PROXY_D3DKMT_GET_RUNTIME_DATA
        HRESULT WINAPI D3DKMTGetRuntimeData_()
        {
            /**
             * @note IMPLEMENTATION DETAIL:
             * This function is an internal Kernel-Mode Thunk (KMT).
             * 1. It is used for opaque data exchange between the D3D runtime and 'dxgkrnl.sys'.
             * 2. The parameterless signature enables a transparent binary forward.
             * 3. CRITICAL: On x64, the 'pData' pointer resides in RCX. Because this
             * is a "system use only" function, its internal structure and requirements
             * may change between Windows versions. Keeping a blind forward ensures
             * compatibility without needing to track internal structure changes.
             */

            auto fn = reinterpret_cast<D3DKMTGetRuntimeData_t>(proc_D3DKMTGetRuntimeData);
            HRESULT result = fn ? fn() : E_NOTIMPL;
            return result;
        }
#else
#pragma comment(linker, "/export:D3DKMTGetRuntimeData=D3DKMTGetRuntimeData_ASM")
#endif

    }

} // namespace d3d11