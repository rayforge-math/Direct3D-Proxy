/*
    Undocumented function prototypes were determined using IDA Pro and the following references:
        
*/

#include "DXGIImpl.h"
#include "DXGIJumpStubs.h"
//#include "dxgi/DXGIInspector.h"
#include "d3d/ProxyWrapper.h"
#include "dxgi/ProxyDXGISwapChain.h"
#include "dxgi/ProxyDXGIFactory.h"
#include "debug/debug_dxgi.h"

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

    }

} // namespace dll