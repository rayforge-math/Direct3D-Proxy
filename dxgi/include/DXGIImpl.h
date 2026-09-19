/*
    Undocumented function prototypes were determined using IDA Pro and the following references:

*/
#pragma once

#include "d3d11/d3d11_version.h"
#include "dxgi/dxgi_version.h"

// ============================================================================
// DXGI PROXY CONFIGURATION - FEATURE TOGGLES
// ============================================================================
// Comment out a define to disable the C++ Hook and use the ASM Pass-Through.
//#define PROXY_BYPASS_ALL
#ifndef PROXY_BYPASS_ALL

    // [1] CORE DXGI FACTORY APIs
    #define PROXY_SECTION_1
    #ifdef PROXY_SECTION_1
        #define PROXY_CREATE_DXGI_FACTORY
        #define PROXY_CREATE_DXGI_FACTORY_1
        #define PROXY_CREATE_DXGI_FACTORY_2
    #endif

    // [2] D3D10 DXGI INTEROP
    //#define PROXY_SECTION_2
    #ifdef PROXY_SECTION_2
        #define PROXY_DXGI_D3D10_CREATE_DEVICE
        #define PROXY_DXGI_D3D10_CREATE_LAYERED_DEV
        #define PROXY_DXGI_D3D10_GET_LAYERED_SIZE
        #define PROXY_DXGI_D3D10_REGISTER_LAYERS
    #endif

    // [3] DEBUG & DIAGNOSTICS
    //#define PROXY_SECTION_3
    #ifdef PROXY_SECTION_3
        #define PROXY_DXGI_GET_DEBUG_INTERFACE_1
        #define PROXY_DXGI_DUMP_JOURNAL
    #endif

    // [4] PIX CAPTURE & TOOLING
    //#define PROXY_SECTION_4
    #ifdef PROXY_SECTION_4
        #define PROXY_PIX_BEGIN_CAPTURE
        #define PROXY_PIX_END_CAPTURE
        #define PROXY_PIX_GET_CAPTURE_STATE
    #endif

    // [5] COMPATIBILITY & SYSTEM QUIRKS
    //#define PROXY_SECTION_5
    #ifdef PROXY_SECTION_5
        #define PROXY_APPLY_COMPAT_RESOLUTION_QUIRKING
        #define PROXY_COMPAT_STRING
        #define PROXY_COMPAT_VALUE
        #define PROXY_SET_APP_COMPAT_STRING_PTR
        #define PROXY_UPDATE_HMD_EMULATION_STATUS
        #define PROXY_DXGI_DECLARE_ADAPTER_REMOVAL_SUPPORT
        #define PROXY_DXGI_DISABLE_VBLANK_VIRTUALIZATION
        #define PROXY_DXGI_REPORT_ADAPTER_CONFIG
    #endif

#endif

// ============================================================================
// ARCHITECTURAL FALLBACK MAPPING
// ============================================================================
// This internal logic enables legacy options for proxy functions.

namespace dll {

    extern "C" {

        // ============================================================================
        // SECTION 1: CORE DXGI FACTORY APIs (Stable & Documented)
        // ============================================================================

        typedef HRESULT(WINAPI* CreateDXGIFactory_t)(
            _In_ REFIID riid,
            _COM_Outptr_ void** ppFactory
            );
        /**
         * @brief Creates a DXGI 1.0 factory that can be used to generate other DXGI objects.
         * @param riid      [in]      The globally unique identifier (GUID) of the DXGI factory object requested.
         * @param ppFactory [out, com] Address of a pointer to an IDXGIFactory object.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI CreateDXGIFactory_(
            _In_ REFIID riid,
            _COM_Outptr_ void** ppFactory
        );

        typedef HRESULT(WINAPI* CreateDXGIFactory1_t)(
            _In_ REFIID riid,
            _COM_Outptr_ void** ppFactory
            );
        /**
         * @brief Creates a DXGI 1.1 factory that can be used to generate other DXGI objects with full-screen caching support.
         * @param riid      [in]      The GUID of the requested factory interface (e.g., __uuidof(IDXGIFactory1)).
         * @param ppFactory [out, com] Address of a pointer to an IDXGIFactory1 object.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI CreateDXGIFactory1_(
            _In_ REFIID riid,
            _COM_Outptr_ void** ppFactory
        );

        typedef HRESULT(WINAPI* CreateDXGIFactory2_t)(
            UINT Flags,
            _In_ REFIID riid,
            _COM_Outptr_ void** ppFactory
            );
        /**
         * @brief Creates a DXGI factory that can be used to generate other DXGI objects, with support for debugging flags.
         * @param Flags     [in]      DXGI factory flags (e.g., DXGI_CREATE_FACTORY_DEBUG).
         * @param riid      [in]      The GUID of the requested factory interface (e.g., __uuidof(IDXGIFactory2)).
         * @param ppFactory [out, com] Address of a pointer to the created factory object.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI CreateDXGIFactory2_(
            UINT Flags,
            _In_ REFIID riid,
            _COM_Outptr_ void** ppFactory
        );

        // ============================================================================
        // SECTION 2: D3D10 DXGI INTEROP APIs (Internal & Interoperability)
        // ============================================================================

        typedef HRESULT(WINAPI* DXGID3D10CreateDevice_t)(
            _In_opt_ HMODULE hModule,
            _In_opt_ IDXGIFactory* pFactory,
            _In_opt_ IDXGIAdapter* pAdapter,
            UINT Flags,
            _In_opt_ const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            UINT SDKVersion,
            _Out_opt_ void** ppDevice
            );
        /**
         * @brief Creates a Direct3D 10.0 or 10.1 device using DXGI interoperability.
         * @param hModule        [in, opt] Handle to a software rasterizer DLL, or NULL for hardware/WARP.
         * @param pFactory       [in, opt] The DXGI factory to use for creating the device.
         * @param pAdapter       [in, opt] The video adapter to use for the device.
         * @param Flags          [in]      Device creation flags (e.g., D3D10_CREATE_DEVICE_DEBUG).
         * @param pFeatureLevels [in, opt] Array of feature levels supported by the device.
         * @param FeatureLevels  [in]      Number of elements in the feature levels array.
         * @param SDKVersion     [in]      The SDK version (typically D3D10_1_SDK_VERSION or D3D10_SDK_VERSION).
         * @param ppDevice       [out, com] Address of a pointer to the created D3D10 device.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI DXGID3D10CreateDevice_(
            _In_opt_ HMODULE hModule,
            _In_opt_ IDXGIFactory* pFactory,
            _In_opt_ IDXGIAdapter* pAdapter,
            UINT Flags,
            _In_opt_ const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            UINT SDKVersion,
            _Out_opt_ void** ppDevice
        );

        typedef HRESULT(WINAPI* DXGID3D10CreateLayeredDevice_t)(
            _In_ const void* pUnknown1,
            _In_ SIZE_T Unknown2,
            _In_opt_ void* pUnknown3,
            _In_ REFIID riid,
            _COM_Outptr_ void** ppDevice
            );
        /**
         * @brief Internal helper function to create a layered D3D10 device on top of DXGI.
         * @param pUnknown1  [in]      Pointer to internal initialization data or device description.
         * @param Unknown2   [in]      Size or version identifier associated with the initialization data.
         * @param pUnknown3  [in, opt] Optional interface pointer (e.g., underlying adapter or factory).
         * @param riid       [in]      The GUID of the requested interface.
         * @param ppDevice   [out, com] Address of a pointer to the created layered device.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI DXGID3D10CreateLayeredDevice_(
            _In_ const void* pUnknown1,
            _In_ SIZE_T Unknown2,
            _In_opt_ void* pUnknown3,
            _In_ REFIID riid,
            _COM_Outptr_ void** ppDevice
        );

        typedef SIZE_T(WINAPI* DXGID3D10GetLayeredDeviceSize_t)(
            _In_ const void* pUnknown1,
            _In_ REFIID riid
            );
        /**
         * @brief Returns the memory buffer size required for a layered D3D10 device.
         * @param pUnknown1  [in]      Pointer to internal initialization parameters or device description.
         * @param riid       [in]      The GUID of the target interface.
         * @return SIZE_T Returns the size in bytes required to allocate the layered device.
         */
        SIZE_T WINAPI DXGID3D10GetLayeredDeviceSize_(
            _In_ const void* pUnknown1,
            _In_ REFIID riid
        );

        typedef HRESULT(WINAPI* DXGID3D10RegisterLayers_t)(
            _In_ const void* pLayers,
            _In_ UINT NumLayers
            );
        /**
         * @brief Registers internal D3D10 runtime layers with DXGI.
         * @param pLayers    [in]      Pointer to an array of layer definition structures or pointers.
         * @param NumLayers  [in]      Number of layers to register.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI DXGID3D10RegisterLayers_(
            _In_ const void* pLayers,
            _In_ UINT NumLayers
        );

        // ============================================================================
        // SECTION 3: DEBUG & DIAGNOSTICS APIs
        // ============================================================================

        typedef HRESULT(WINAPI* DXGIGetDebugInterface1_t)(
            UINT Flags,
            _In_ REFIID riid,
            _COM_Outptr_ void** pDebug
            );
        /**
         * @brief Returns a DXGI debug interface (such as IDXGIDebug1) to inspect device states and leaks.
         * @param Flags  [in]      Reserved or flags (typically 0).
         * @param riid   [in]      The GUID of the requested debug interface (e.g., __uuidof(IDXGIDebug1)).
         * @param pDebug [out, com] Address of a pointer to the requested debug interface object.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI DXGIGetDebugInterface1_(
            UINT Flags,
            _In_ REFIID riid,
            _COM_Outptr_ void** pDebug
        );

        typedef HRESULT(WINAPI* DXGIDumpJournal_t)(
            void
            );
        /**
         * @brief Dumps internal DXGI journal and diagnostic event information for troubleshooting.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI DXGIDumpJournal_(
            void
        );

        // ============================================================================
        // SECTION 4: PIX CAPTURE & TOOLING APIs
        // ============================================================================

        typedef HRESULT(WINAPI* PIXBeginCapture_t)(
            _In_ REFIID riid,
            _In_opt_ const void* pParameters
            );
        /**
         * @brief Begins a PIX graphics capture session programmatically.
         * @param riid        [in]      The GUID of the capture interface or format (often __uuidof(IUnknown) or similar).
         * @param pParameters [in, opt] Optional parameters governing the capture settings.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI PIXBeginCapture_(
            _In_ REFIID riid,
            _In_opt_ const void* pParameters
        );

        typedef HRESULT(WINAPI* PIXEndCapture_t)(
            void
            );
        /**
         * @brief Ends the current PIX graphics capture session.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI PIXEndCapture_(
            void
        );

        typedef DWORD(WINAPI* PIXGetCaptureState_t)(
            void
            );
        /**
         * @brief Retrieves the current state of PIX capture activities.
         * @return DWORD Returns flags indicating whether a capture is currently running or pending.
         */
        DWORD WINAPI PIXGetCaptureState_(
            void
        );

        // ============================================================================
        // SECTION 5: COMPATIBILITY & SYSTEM QUIRKS APIs
        // ============================================================================

        typedef HRESULT(WINAPI* ApplyCompatResolutionQuirking_t)(
            _In_opt_ void* pUnknown
            );
        /**
         * @brief Applies compatibility resolution quirks for specific full-screen or windowed scaling behaviours.
         * @param pUnknown [in, opt] Pointer to window or swap chain configuration parameters.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI ApplyCompatResolutionQuirking_(
            _In_opt_ void* pUnknown
        );

        typedef LPCWSTR(WINAPI* CompatString_t)(
            UINT ID
            );
        /**
         * @brief Retrieves an internal compatibility string associated with specific application quirks.
         * @param ID [in] Identifier or index for the requested compatibility string.
         * @return LPCWSTR Pointer to the null-terminated wide compatibility string, or nullptr.
         */
        LPCWSTR WINAPI CompatString_(
            UINT ID
        );

        typedef ULONGLONG(WINAPI* CompatValue_t)(
            UINT ID
            );
        /**
         * @brief Retrieves an internal compatibility numeric configuration value or flag.
         * @param ID [in] Identifier or index for the requested compatibility value.
         * @return ULONGLONG The configuration value associated with the specified identifier.
         */
        ULONGLONG WINAPI CompatValue_(
            UINT ID
        );

        typedef void(WINAPI* SetAppCompatStringPointer_t)(
            _In_ int Index,
            _In_opt_ LPCSTR pString
            );
        /**
         * @brief Sets an application compatibility string pointer used by the DXGI runtime layer.
         * @param Index   [in]      Index slot for the compatibility string.
         * @param pString [in, opt] Pointer to the ASCII compatibility string.
         */
        void WINAPI SetAppCompatStringPointer_(
            _In_ int Index,
            _In_opt_ LPCSTR pString
        );

        typedef HRESULT(WINAPI* UpdateHMDEmulationStatus_t)(
            _In_ BOOL Enable
            );
        /**
         * @brief Updates head-mounted display (HMD) emulation status and presentation behavior.
         * @param Enable [in] TRUE to enable HMD emulation mode, FALSE to disable.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI UpdateHMDEmulationStatus_(
            _In_ BOOL Enable
        );

        typedef HRESULT(WINAPI* DXGIDeclareAdapterRemovalSupport_t)(
            void
            );
        /**
         * @brief Declares application support for dynamic adapter removal and hardware surprise-removal events.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI DXGIDeclareAdapterRemovalSupport_(
            void
        );

        typedef HRESULT(WINAPI* DXGIDisableVBlankVirtualization_t)(
            void
            );
        /**
         * @brief Disables vertical blank virtualization features for timing or performance adjustments.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI DXGIDisableVBlankVirtualization_(
            void
        );

        typedef HRESULT(WINAPI* DXGIReportAdapterConfiguration_t)(
            void
            );
        /**
         * @brief Reports adapter configuration details and diagnostic telemetry to the system runtime.
         * @return HRESULT Standard HRESULT error code.
         */
        HRESULT WINAPI DXGIReportAdapterConfiguration_(
            void
        );

    }

} // namespace dll