#include "D3D11HookExporter.h"

namespace dll {

    // Define function pointers inside extern "C"
    extern "C" {
        FARPROC proc_CreateDirect3D11DeviceFromDXGIDevice = nullptr;
        FARPROC proc_CreateDirect3D11SurfaceFromDXGISurface = nullptr;
        FARPROC proc_D3D11CoreCreateDevice = nullptr;
        FARPROC proc_D3D11CoreCreateLayeredDevice = nullptr;
        FARPROC proc_D3D11CoreGetLayeredDeviceSize = nullptr;
        FARPROC proc_D3D11CoreRegisterLayers = nullptr;
        FARPROC proc_D3D11CreateDevice = nullptr;
        FARPROC proc_D3D11CreateDeviceAndSwapChain = nullptr;
        FARPROC proc_D3D11CreateDeviceForD3D12 = nullptr;
        FARPROC proc_D3D11On12CreateDevice = nullptr;
        FARPROC proc_EnableFeatureLevelUpgrade = nullptr;
        FARPROC proc_D3DKMTCloseAdapter = nullptr;
        FARPROC proc_D3DKMTCreateAllocation = nullptr;
        FARPROC proc_D3DKMTCreateContext = nullptr;
        FARPROC proc_D3DKMTCreateDevice = nullptr;
        FARPROC proc_D3DKMTCreateSynchronizationObject = nullptr;
        FARPROC proc_D3DKMTDestroyAllocation = nullptr;
        FARPROC proc_D3DKMTDestroyContext = nullptr;
        FARPROC proc_D3DKMTDestroyDevice = nullptr;
        FARPROC proc_D3DKMTDestroySynchronizationObject = nullptr;
        FARPROC proc_D3DKMTEscape = nullptr;
        FARPROC proc_D3DKMTGetContextSchedulingPriority = nullptr;
        FARPROC proc_D3DKMTGetDeviceState = nullptr;
        FARPROC proc_D3DKMTGetDisplayModeList = nullptr;
        FARPROC proc_D3DKMTGetMultisampleMethodList = nullptr;
        FARPROC proc_D3DKMTGetRuntimeData = nullptr;
        FARPROC proc_D3DKMTGetSharedPrimaryHandle = nullptr;
        FARPROC proc_D3DKMTLock = nullptr;
        FARPROC proc_D3DKMTOpenAdapterFromHdc = nullptr;
        FARPROC proc_D3DKMTOpenResource = nullptr;
        FARPROC proc_D3DKMTPresent = nullptr;
        FARPROC proc_D3DKMTQueryAdapterInfo = nullptr;
        FARPROC proc_D3DKMTQueryAllocationResidency = nullptr;
        FARPROC proc_D3DKMTQueryResourceInfo = nullptr;
        FARPROC proc_D3DKMTRender = nullptr;
        FARPROC proc_D3DKMTSetAllocationPriority = nullptr;
        FARPROC proc_D3DKMTSetContextSchedulingPriority = nullptr;
        FARPROC proc_D3DKMTSetDisplayMode = nullptr;
        FARPROC proc_D3DKMTSetDisplayPrivateDriverFormat = nullptr;
        FARPROC proc_D3DKMTSetGammaRamp = nullptr;
        FARPROC proc_D3DKMTSetVidPnSourceOwner = nullptr;
        FARPROC proc_D3DKMTSignalSynchronizationObject = nullptr;
        FARPROC proc_D3DKMTUnlock = nullptr;
        FARPROC proc_D3DKMTWaitForSynchronizationObject = nullptr;
        FARPROC proc_D3DKMTWaitForVerticalBlankEvent = nullptr;
        FARPROC proc_D3DPerformance_BeginEvent = nullptr;
        FARPROC proc_D3DPerformance_EndEvent = nullptr;
        FARPROC proc_D3DPerformance_GetStatus = nullptr;
        FARPROC proc_D3DPerformance_SetMarker = nullptr;
        FARPROC proc_OpenAdapter10 = nullptr;
        FARPROC proc_OpenAdapter10_2 = nullptr;
    }


    // Define the proxy mapping table containing all D3D11 exported functions
    static const ProxyMapping s_D3D11ProxyMap[] = {
        { "CreateDirect3D11DeviceFromDXGIDevice", &proc_CreateDirect3D11DeviceFromDXGIDevice },
        { "CreateDirect3D11SurfaceFromDXGISurface", &proc_CreateDirect3D11SurfaceFromDXGISurface },
        { "D3D11CoreCreateDevice", &proc_D3D11CoreCreateDevice },
        { "D3D11CoreCreateLayeredDevice", &proc_D3D11CoreCreateLayeredDevice },
        { "D3D11CoreGetLayeredDeviceSize", &proc_D3D11CoreGetLayeredDeviceSize },
        { "D3D11CoreRegisterLayers", &proc_D3D11CoreRegisterLayers },
        { "D3D11CreateDevice", &proc_D3D11CreateDevice },
        { "D3D11CreateDeviceAndSwapChain", &proc_D3D11CreateDeviceAndSwapChain },
        { "D3D11CreateDeviceForD3D12", &proc_D3D11CreateDeviceForD3D12 },
        { "D3D11On12CreateDevice", &proc_D3D11On12CreateDevice },
        { "D3DKMTCloseAdapter", &proc_D3DKMTCloseAdapter },
        { "D3DKMTCreateAllocation", &proc_D3DKMTCreateAllocation },
        { "D3DKMTCreateContext", &proc_D3DKMTCreateContext },
        { "D3DKMTCreateDevice", &proc_D3DKMTCreateDevice },
        { "D3DKMTCreateSynchronizationObject", &proc_D3DKMTCreateSynchronizationObject },
        { "D3DKMTDestroyAllocation", &proc_D3DKMTDestroyAllocation },
        { "D3DKMTDestroyContext", &proc_D3DKMTDestroyContext },
        { "D3DKMTDestroyDevice", &proc_D3DKMTDestroyDevice },
        { "D3DKMTDestroySynchronizationObject", &proc_D3DKMTDestroySynchronizationObject },
        { "D3DKMTEscape", &proc_D3DKMTEscape },
        { "D3DKMTGetContextSchedulingPriority", &proc_D3DKMTGetContextSchedulingPriority },
        { "D3DKMTGetDeviceState", &proc_D3DKMTGetDeviceState },
        { "D3DKMTGetDisplayModeList", &proc_D3DKMTGetDisplayModeList },
        { "D3DKMTGetMultisampleMethodList", &proc_D3DKMTGetMultisampleMethodList },
        { "D3DKMTGetRuntimeData", &proc_D3DKMTGetRuntimeData },
        { "D3DKMTGetSharedPrimaryHandle", &proc_D3DKMTGetSharedPrimaryHandle },
        { "D3DKMTLock", &proc_D3DKMTLock },
        { "D3DKMTOpenAdapterFromHdc", &proc_D3DKMTOpenAdapterFromHdc },
        { "D3DKMTOpenResource", &proc_D3DKMTOpenResource },
        { "D3DKMTPresent", &proc_D3DKMTPresent },
        { "D3DKMTQueryAdapterInfo", &proc_D3DKMTQueryAdapterInfo },
        { "D3DKMTQueryAllocationResidency", &proc_D3DKMTQueryAllocationResidency },
        { "D3DKMTQueryResourceInfo", &proc_D3DKMTQueryResourceInfo },
        { "D3DKMTRender", &proc_D3DKMTRender },
        { "D3DKMTSetAllocationPriority", &proc_D3DKMTSetAllocationPriority },
        { "D3DKMTSetContextSchedulingPriority", &proc_D3DKMTSetContextSchedulingPriority },
        { "D3DKMTSetDisplayMode", &proc_D3DKMTSetDisplayMode },
        { "D3DKMTSetDisplayPrivateDriverFormat", &proc_D3DKMTSetDisplayPrivateDriverFormat },
        { "D3DKMTSetGammaRamp", &proc_D3DKMTSetGammaRamp },
        { "D3DKMTSetVidPnSourceOwner", &proc_D3DKMTSetVidPnSourceOwner },
        { "D3DKMTSignalSynchronizationObject", &proc_D3DKMTSignalSynchronizationObject },
        { "D3DKMTUnlock", &proc_D3DKMTUnlock },
        { "D3DKMTWaitForSynchronizationObject", &proc_D3DKMTWaitForSynchronizationObject },
        { "D3DKMTWaitForVerticalBlankEvent", &proc_D3DKMTWaitForVerticalBlankEvent },
        { "D3DPerformance_BeginEvent", &proc_D3DPerformance_BeginEvent },
        { "D3DPerformance_EndEvent", &proc_D3DPerformance_EndEvent },
        { "D3DPerformance_GetStatus", &proc_D3DPerformance_GetStatus },
        { "D3DPerformance_SetMarker", &proc_D3DPerformance_SetMarker },
        { "EnableFeatureLevelUpgrade", &proc_EnableFeatureLevelUpgrade },
        { "OpenAdapter10", &proc_OpenAdapter10 },
        { "OpenAdapter10_2", &proc_OpenAdapter10_2 }
    };

    // Initialize the static HookExporter instance with "d3d11.dll" and the mapping configuration
    HookExporter D3D11HookExporter::s_Exporter(
        "d3d11.dll",
        s_D3D11ProxyMap,
        sizeof(s_D3D11ProxyMap) / sizeof(dll::ProxyMapping)
    );

    BOOL D3D11HookExporter::HookExports() {
        return s_Exporter.HookExports();
    }

    BOOL D3D11HookExporter::UnhookExports() {
        return s_Exporter.UnhookExports();
    }

    HMODULE D3D11HookExporter::GetChainHandle() {
        return s_Exporter.GetChainHandle();
    }

} // namespace d3d11