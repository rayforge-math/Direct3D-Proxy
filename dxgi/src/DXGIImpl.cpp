/*
    Undocumented function prototypes were determined using IDA Pro and the following references:
        
*/

#include "DXGIImpl.h"
#include "DXGIJumpStubs.h"
//#include "dxgi/DXGIInspector.h"
#include "d3d/ProxyWrapper.h"
#include "dxgi/ProxyDXGISwapChain.h"
#include "dxgi/ProxyDXGIFactory.h"
#include "logging/debug_dxgi.h"

using namespace dxgi;
using namespace d3d;

/**
 * @file dxgi_impl.cpp
 * @brief DXGI Proxy - Hybrid Interception Layer
 * @section Architecture Strategy
 * To maintain 100% stack integrity, this proxy uses two distinct methods:
 * 1. C++ Wrappers: Used ONLY for well-documented functions with stable signatures.
 * 2. ASM Jump-Stubs (Transparent Forwarding): Used for undocumented or volatile
 *    "Core" functions. This avoids the C++ 'call' instruction, which would
 *    push a return address onto the stack and displace function parameters.
 *
 * @section Signature Audit Status (HIGH RISK)
 * THE FOLLOWING FUNCTIONS MUST REMAIN IN ASM JUMP-STUBS.
 * Implementation in C++ (even with 'void' or 'auto') will cause stack
 * misalignment and immediate crashes due to undocumented/variable parameter counts:
 * - DXGID3D10CreateDevice          (Internal/Interop variance)
 * - DXGID3D10CreateLayeredDevice   (Undocumented)
 * - DXGID3D10GetLayeredDeviceSize  (Undocumented)
 * - DXGID3D10RegisterLayers        (Undocumented)
 * - DXGIDumpJournal                (Internal/Volatile diagnostic)
 * - ApplyCompatResolutionQuirking  (Internal/Volatile quirk)
 * - CompatString                   (Internal string mapping)
 * - CompatValue                    (Internal value mapping)
 * - SetAppCompatStringPointer      (Internal state pointer)
 * - UpdateHMDEmulationStatus       (Internal runtime flag)
 * @see jump_stubs.asm for the implementation of these functions.
 */

namespace dll {

    // ============================================================================
    // DXGI PROXY DLL - MODULE ARCHITECTURE & TABLE OF CONTENTS
    // ============================================================================

    // [1] CORE DXGI FACTORY APIs (Stable & Documented)
    //      - CreateDXGIFactory_
    //      - CreateDXGIFactory1_
    //      - CreateDXGIFactory2_

    // [2] D3D10 DXGI INTEROP APIs (Internal & Interoperability)
    //      - DXGID3D10CreateDevice_
    //      - DXGID3D10CreateLayeredDevice_
    //      - DXGID3D10GetLayeredDeviceSize_
    //      - DXGID3D10RegisterLayers_

    // [3] DEBUG & DIAGNOSTICS APIs
    //      - DXGIGetDebugInterface1_
    //      - DXGIDumpJournal_

    // [4] PIX CAPTURE & TOOLING APIs
    //      - PIXBeginCapture_
    //      - PIXEndCapture_
    //      - PIXGetCaptureState_

    // [5] COMPATIBILITY & SYSTEM QUIRKS APIs
    //      - ApplyCompatResolutionQuirking_
    //      - CompatString_
    //      - CompatValue_
    //      - SetAppCompatStringPointer_
    //      - UpdateHMDEmulationStatus_
    //      - DXGIDeclareAdapterRemovalSupport_
    //      - DXGIDisableVBlankVirtualization_
    //      - DXGIReportAdapterConfiguration_

    // ============================================================================

    extern "C" {

        // ============================================================================
        // SECTION 1: CORE DXGI FACTORY APIs (Stable & Documented)
        // ============================================================================

#ifdef PROXY_CREATE_DXGI_FACTORY
#pragma comment(linker, "/export:CreateDXGIFactory=CreateDXGIFactory_")
        HRESULT WINAPI CreateDXGIFactory_(
            _In_ REFIID riid,
            _COM_Outptr_ void** ppFactory
        )
        {
            /**
             * @note STRATEGIC HOOK POINT:
             * Intercepting CreateDXGIFactory allows you to:
             * 1. Monitor or modify the requested interface GUID (riid).
             * 2. Wrap the resulting 'ppFactory' in a custom proxy implementation
             *    to intercept adapter enumeration and swap chain creation.
             */

            HRESULT result = reinterpret_cast<CreateDXGIFactory_t>(dll::proc_CreateDXGIFactory)(
                riid,
                ppFactory
                );

            if (SUCCEEDED(result) && ppFactory && *ppFactory) {
                ProxyWrapper::Wrap<ProxyDXGIFactory>(reinterpret_cast<ProxyDXGIFactory::InterfaceType**>(ppFactory));
            }

            return result;
        }
#else
#pragma comment(linker, "/export:CreateDXGIFactory=CreateDXGIFactory_ASM")
#endif


#ifdef PROXY_CREATE_DXGI_FACTORY_1
#pragma comment(linker, "/export:CreateDXGIFactory1=CreateDXGIFactory1_")
        HRESULT WINAPI CreateDXGIFactory1_(
            _In_ REFIID riid,
            _COM_Outptr_ void** ppFactory
        )
        {
            /**
             * @note STRATEGIC HOOK POINT:
             * Intercepting CreateDXGIFactory1 (DXGI 1.1) for full-screen caching
             * and adapter monitoring across modern Windows platforms.
             */

            HRESULT result = reinterpret_cast<CreateDXGIFactory1_t>(dll::proc_CreateDXGIFactory1)(
                riid,
                ppFactory
                );

            if (SUCCEEDED(result) && ppFactory && *ppFactory) {
                ProxyWrapper::Wrap<ProxyDXGIFactory>(reinterpret_cast<ProxyDXGIFactory::InterfaceType**>(ppFactory));
            }

            return result;
        }
#else
#pragma comment(linker, "/export:CreateDXGIFactory1=CreateDXGIFactory1_ASM")
#endif


#ifdef PROXY_CREATE_DXGI_FACTORY_2
#pragma comment(linker, "/export:CreateDXGIFactory2=CreateDXGIFactory2_")
        HRESULT WINAPI CreateDXGIFactory2_(
            UINT Flags,
            _In_ REFIID riid,
            _COM_Outptr_ void** ppFactory
        )
        {
            /**
             * @note STRATEGIC HOOK POINT:
             * Intercepting CreateDXGIFactory2 (DXGI 1.2+) to inspect or force
             * debug flags (e.g. DXGI_CREATE_FACTORY_DEBUG) during creation.
             */

            HRESULT result = reinterpret_cast<CreateDXGIFactory2_t>(dll::proc_CreateDXGIFactory2)(
                Flags,
                riid,
                ppFactory
                );

            if (SUCCEEDED(result) && ppFactory && *ppFactory) {
                ProxyWrapper::Wrap<ProxyDXGIFactory>(reinterpret_cast<ProxyDXGIFactory::InterfaceType**>(ppFactory));
            }

            return result;
        }
#else
#pragma comment(linker, "/export:CreateDXGIFactory2=CreateDXGIFactory2_ASM")
#endif

        // ============================================================================
        // SECTION 2: D3D10 DXGI INTEROP APIS (Internal & Interoperability)
        // ============================================================================
#ifdef PROXY_DXGI_D3D10_CREATE_DEVICE
#pragma comment(linker, "/export:DXGID3D10CreateDevice=DXGID3D10CreateDevice_")
        HRESULT WINAPI DXGID3D10CreateDevice_(
            HMODULE hModule,
            IDXGIFactory* pFactory,
            IDXGIAdapter* pAdapter,
            UINT Flags,
            void* pUnknown,
            void** ppDevice
        )
        {
            LOG_MSG("DXGID3D10CreateDevice called");
            auto fn = reinterpret_cast<DXGID3D10CreateDevice_t>(dll::proc_DXGID3D10CreateDevice);
            if (!fn) return E_FAIL;

            HRESULT result = fn(hModule, pFactory, pAdapter, Flags, pUnknown, ppDevice);
            if (SUCCEEDED(result) && ppDevice && *ppDevice) {
                // Wrap device if needed
            }
            return result;
        }
#else
#pragma comment(linker, "/export:DXGID3D10CreateDevice=DXGID3D10CreateDevice_ASM")
#endif

#ifdef PROXY_DXGI_D3D10_CREATE_LAYERED_DEVICE
#pragma comment(linker, "/export:DXGID3D10CreateLayeredDevice=DXGID3D10CreateLayeredDevice_")
        HRESULT WINAPI DXGID3D10CreateLayeredDevice_(
            void* p1, void* p2, void* p3, UINT p4, void* p5, void** p6
        )
        {
            LOG_MSG("DXGID3D10CreateLayeredDevice called");
            auto fn = reinterpret_cast<DXGID3D10CreateLayeredDevice_t>(dll::proc_DXGID3D10CreateLayeredDevice);
            if (!fn) return E_FAIL;
            return fn(p1, p2, p3, p4, p5, p6);
        }
#else
#pragma comment(linker, "/export:DXGID3D10CreateLayeredDevice=DXGID3D10CreateLayeredDevice_ASM")
#endif

#ifdef PROXY_DXGI_D3D10_GET_LAYERED_DEVICE_SIZE
#pragma comment(linker, "/export:DXGID3D10GetLayeredDeviceSize=DXGID3D10GetLayeredDeviceSize_")
        SIZE_T WINAPI DXGID3D10GetLayeredDeviceSize_(
            void* p1, UINT p2
        )
        {
            LOG_MSG("DXGID3D10GetLayeredDeviceSize called");
            auto fn = reinterpret_cast<DXGID3D10GetLayeredDeviceSize_t>(dll::proc_DXGID3D10GetLayeredDeviceSize);
            if (!fn) return 0;
            return fn(p1, p2);
        }
#else
#pragma comment(linker, "/export:DXGID3D10GetLayeredDeviceSize=DXGID3D10GetLayeredDeviceSize_ASM")
#endif

#ifdef PROXY_DXGI_D3D10_REGISTER_LAYERS
#pragma comment(linker, "/export:DXGID3D10RegisterLayers=DXGID3D10RegisterLayers_")
        HRESULT WINAPI DXGID3D10RegisterLayers_(
            void* p1, void* p2
        )
        {
            LOG_MSG("DXGID3D10RegisterLayers called");
            auto fn = reinterpret_cast<DXGID3D10RegisterLayers_t>(dll::proc_DXGID3D10RegisterLayers);
            if (!fn) return E_FAIL;
            return fn(p1, p2);
        }
#else
#pragma comment(linker, "/export:DXGID3D10RegisterLayers=DXGID3D10RegisterLayers_ASM")
#endif

        // ============================================================================
        // SECTION 3: DEBUG & DIAGNOSTICS APIS
        // ============================================================================
#ifdef PROXY_DXGI_GET_DEBUG_INTERFACE_1
#pragma comment(linker, "/export:DXGIGetDebugInterface1=DXGIGetDebugInterface1_")
        HRESULT WINAPI DXGIGetDebugInterface1_(
            UINT Flags,
            _In_ REFIID riid,
            _COM_Outptr_ void** pDebug
        )
        {
            LOG_MSG("DXGIGetDebugInterface1 called");
            auto fn = reinterpret_cast<DXGIGetDebugInterface1_t>(dll::proc_DXGIGetDebugInterface1);
            if (!fn) return E_FAIL;

            HRESULT result = fn(Flags, riid, pDebug);
            if (SUCCEEDED(result) && pDebug && *pDebug) {

            }
            return result;
        }
#else
#pragma comment(linker, "/export:DXGIGetDebugInterface1=DXGIGetDebugInterface1_ASM")
#endif

#ifdef PROXY_DXGI_DUMP_JOURNAL
#pragma comment(linker, "/export:DXGIDumpJournal=DXGIDumpJournal_")
        HRESULT WINAPI DXGIDumpJournal_()
        {
            LOG_MSG("DXGIDumpJournal called");
            auto fn = reinterpret_cast<DXGIDumpJournal_t>(dll::proc_DXGIDumpJournal);
            if (!fn) return E_FAIL;

            return fn();
        }
#else
#pragma comment(linker, "/export:DXGIDumpJournal=DXGIDumpJournal_ASM")
#endif


        // ============================================================================
        // SECTION 4: PIX CAPTURE & TOOLING APIS
        // ============================================================================
#ifdef PROXY_PIX_BEGIN_CAPTURE
#pragma comment(linker, "/export:PIXBeginCapture=PIXBeginCapture_")
        HRESULT WINAPI PIXBeginCapture_(
            REFGUID riid,
            void* pParameters
        )
        {
            LOG_MSG("PIXBeginCapture called");
            auto fn = reinterpret_cast<PIXBeginCapture_t>(dll::proc_PIXBeginCapture);
            if (!fn) return E_FAIL;

            return fn(riid, pParameters);
        }
#else
#pragma comment(linker, "/export:PIXBeginCapture=PIXBeginCapture_ASM")
#endif

#ifdef PROXY_PIX_END_CAPTURE
#pragma comment(linker, "/export:PIXEndCapture=PIXEndCapture_")
        HRESULT WINAPI PIXEndCapture_()
        {
            LOG_MSG("PIXEndCapture called");
            auto fn = reinterpret_cast<PIXEndCapture_t>(dll::proc_PIXEndCapture);
            if (!fn) return E_FAIL;

            return fn();
        }
#else
#pragma comment(linker, "/export:PIXEndCapture=PIXEndCapture_ASM")
#endif

#ifdef PROXY_PIX_GET_CAPTURE_STATE
#pragma comment(linker, "/export:PIXGetCaptureState=PIXGetCaptureState_")
        BOOL WINAPI PIXGetCaptureState_()
        {
            LOG_MSG("PIXGetCaptureState called");
            auto fn = reinterpret_cast<PIXGetCaptureState_t>(dll::proc_PIXGetCaptureState);
            if (!fn) return FALSE;

            return fn();
        }
#else
#pragma comment(linker, "/export:PIXGetCaptureState=PIXGetCaptureState_ASM")
#endif

        // ============================================================================
        // SECTION 5: COMPATIBILITY & SYSTEM QUIRKS APIS
        // ============================================================================
#ifdef PROXY_APPLY_COMPAT_RESOLUTION_QUIRKING
#pragma comment(linker, "/export:ApplyCompatResolutionQuirking=ApplyCompatResolutionQuirking_")
        HRESULT WINAPI ApplyCompatResolutionQuirking_(
            void* pUnknown
        )
        {
            LOG_MSG("ApplyCompatResolutionQuirking called");
            auto fn = reinterpret_cast<ApplyCompatResolutionQuirking_t>(dll::proc_ApplyCompatResolutionQuirking);
            if (!fn) return E_FAIL;
            return fn(pUnknown);
        }
#else
#pragma comment(linker, "/export:ApplyCompatResolutionQuirking=ApplyCompatResolutionQuirking_ASM")
#endif

#ifdef PROXY_COMPAT_STRING
#pragma comment(linker, "/export:CompatString=CompatString_")
        HRESULT WINAPI CompatString_(
            int tipo,
            char* str
        )
        {
            LOG_MSG("CompatString called");
            auto fn = reinterpret_cast<CompatString_t>(dll::proc_CompatString);
            if (!fn) return E_FAIL;
            return fn(tipo, str);
        }
#else
#pragma comment(linker, "/export:CompatString=CompatString_ASM")
#endif

#ifdef PROXY_COMPAT_VALUE
#pragma comment(linker, "/export:CompatValue=CompatValue_")
        HRESULT WINAPI CompatValue_(
            int tipo,
            UINT64* pValue
        )
        {
            LOG_MSG("CompatValue called");
            auto fn = reinterpret_cast<CompatValue_t>(dll::proc_CompatValue);
            if (!fn) return E_FAIL;
            return fn(tipo, pValue);
        }
#else
#pragma comment(linker, "/export:CompatValue=CompatValue_ASM")
#endif

#ifdef PROXY_SET_APP_COMPAT_STRING_POINTER
#pragma comment(linker, "/export:SetAppCompatStringPointer=SetAppCompatStringPointer_")
        void WINAPI SetAppCompatStringPointer_(
            int type,
            const char* str
        )
        {
            LOG_MSG("SetAppCompatStringPointer called");
            auto fn = reinterpret_cast<SetAppCompatStringPointer_t>(dll::proc_SetAppCompatStringPointer);
            if (fn) {
                fn(type, str);
            }
        }
#else
#pragma comment(linker, "/export:SetAppCompatStringPointer=SetAppCompatStringPointer_ASM")
#endif

#ifdef PROXY_UPDATE_HMD_EMULATION_STATUS
#pragma comment(linker, "/export:UpdateHMDEmulationStatus=UpdateHMDEmulationStatus_")
        BOOL WINAPI UpdateHMDEmulationStatus_(
            BOOL bEnabled
        )
        {
            LOG_MSG("UpdateHMDEmulationStatus called");
            auto fn = reinterpret_cast<UpdateHMDEmulationStatus_t>(dll::proc_UpdateHMDEmulationStatus);
            if (!fn) return FALSE;
            return fn(bEnabled);
        }
#else
#pragma comment(linker, "/export:UpdateHMDEmulationStatus=UpdateHMDEmulationStatus_ASM")
#endif

#ifdef PROXY_DXGI_DECLARE_ADAPTER_REMOVAL_SUPPORT
#pragma comment(linker, "/export:DXGIDeclareAdapterRemovalSupport=DXGIDeclareAdapterRemovalSupport_")
        HRESULT WINAPI DXGIDeclareAdapterRemovalSupport_()
        {
            LOG_MSG("DXGIDeclareAdapterRemovalSupport called");
            auto fn = reinterpret_cast<DXGIDeclareAdapterRemovalSupport_t>(dll::proc_DXGIDeclareAdapterRemovalSupport);
            if (!fn) return E_FAIL;
            return fn();
        }
#else
#pragma comment(linker, "/export:DXGIDeclareAdapterRemovalSupport=DXGIDeclareAdapterRemovalSupport_ASM")
#endif

#ifdef PROXY_DXGI_DISABLE_VBLANK_VIRTUALIZATION
#pragma comment(linker, "/export:DXGIDisableVBlankVirtualization=DXGIDisableVBlankVirtualization_")
        HRESULT WINAPI DXGIDisableVBlankVirtualization_()
        {
            LOG_MSG("DXGIDisableVBlankVirtualization called");
            auto fn = reinterpret_cast<DXGIDisableVBlankVirtualization_t>(dll::proc_DXGIDisableVBlankVirtualization);
            if (!fn) return E_FAIL;
            return fn();
        }
#else
#pragma comment(linker, "/export:DXGIDisableVBlankVirtualization=DXGIDisableVBlankVirtualization_ASM")
#endif

#ifdef PROXY_DXGI_REPORT_ADAPTER_CONFIGURATION
#pragma comment(linker, "/export:DXGIReportAdapterConfiguration=DXGIReportAdapterConfiguration_")
        HRESULT WINAPI DXGIReportAdapterConfiguration_()
        {
            LOG_MSG("DXGIReportAdapterConfiguration called");
            auto fn = reinterpret_cast<DXGIReportAdapterConfiguration_t>(dll::proc_DXGIReportAdapterConfiguration);
            if (!fn) return E_FAIL;
            return fn();
        }
#else
#pragma comment(linker, "/export:DXGIReportAdapterConfiguration=DXGIReportAdapterConfiguration_ASM")
#endif

    }

} // namespace dll