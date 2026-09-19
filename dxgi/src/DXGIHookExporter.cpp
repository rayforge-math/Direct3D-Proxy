#include "DXGIHookExporter.h"

namespace dll {

    // Define function pointers inside extern "C"
    extern "C" {
        FARPROC proc_CreateDXGIFactory = nullptr;
        FARPROC proc_CreateDXGIFactory1 = nullptr;
        FARPROC proc_CreateDXGIFactory2 = nullptr;
        FARPROC proc_DXGID3D10CreateDevice = nullptr;
        FARPROC proc_DXGID3D10CreateLayeredDevice = nullptr;
        FARPROC proc_DXGID3D10GetLayeredDeviceSize = nullptr;
        FARPROC proc_DXGID3D10RegisterLayers = nullptr;
        FARPROC proc_DXGIGetDebugInterface1 = nullptr;
        FARPROC proc_PIXBeginCapture = nullptr;
        FARPROC proc_PIXEndCapture = nullptr;
        FARPROC proc_PIXGetCaptureState = nullptr;
        FARPROC proc_DXGIDumpJournal = nullptr;
        FARPROC proc_ApplyCompatResolutionQuirking = nullptr;
        FARPROC proc_CompatString = nullptr;
        FARPROC proc_CompatValue = nullptr;
        FARPROC proc_SetAppCompatStringPointer = nullptr;
        FARPROC proc_UpdateHMDEmulationStatus = nullptr;
        FARPROC proc_DXGIDeclareAdapterRemovalSupport = nullptr;
        FARPROC proc_DXGIDisableVBlankVirtualization = nullptr;
        FARPROC proc_DXGIReportAdapterConfiguration = nullptr;
    }

    // Define the proxy mapping table containing all DXGI exported functions
    static const dll::ProxyMapping s_DXGIProxyMap[] = {
        { "CreateDXGIFactory", &proc_CreateDXGIFactory },
        { "CreateDXGIFactory1", &proc_CreateDXGIFactory1 },
        { "CreateDXGIFactory2", &proc_CreateDXGIFactory2 },
        { "DXGID3D10CreateDevice", &proc_DXGID3D10CreateDevice },
        { "DXGID3D10CreateLayeredDevice", &proc_DXGID3D10CreateLayeredDevice },
        { "DXGID3D10GetLayeredDeviceSize", &proc_DXGID3D10GetLayeredDeviceSize },
        { "DXGID3D10RegisterLayers", &proc_DXGID3D10RegisterLayers },
        { "DXGIGetDebugInterface1", &proc_DXGIGetDebugInterface1 },
        { "PIXBeginCapture", &proc_PIXBeginCapture },
        { "PIXEndCapture", &proc_PIXEndCapture },
        { "PIXGetCaptureState", &proc_PIXGetCaptureState },
        { "DXGIDumpJournal", &proc_DXGIDumpJournal },
        { "ApplyCompatResolutionQuirking", &proc_ApplyCompatResolutionQuirking },
        { "CompatString", &proc_CompatString },
        { "CompatValue", &proc_CompatValue },
        { "SetAppCompatStringPointer", &proc_SetAppCompatStringPointer },
        { "UpdateHMDEmulationStatus", &proc_UpdateHMDEmulationStatus },
        { "DXGIDeclareAdapterRemovalSupport", &proc_DXGIDeclareAdapterRemovalSupport },
        { "DXGIDisableVBlankVirtualization", &proc_DXGIDisableVBlankVirtualization },
        { "DXGIReportAdapterConfiguration", &proc_DXGIReportAdapterConfiguration }
    };

    // Initialize the static HookExporter instance with "dxgi.dll" and the mapping configuration
    dll::HookExporter DXGIHookExporter::s_Exporter(
        "dxgi.dll",
        s_DXGIProxyMap,
        sizeof(s_DXGIProxyMap) / sizeof(dll::ProxyMapping)
    );

    BOOL DXGIHookExporter::HookExports() {
        return s_Exporter.HookExports();
    }

    BOOL DXGIHookExporter::UnhookExports() {
        return s_Exporter.UnhookExports();
    }

    HMODULE DXGIHookExporter::GetChainHandle() {
        return s_Exporter.GetChainHandle();
    }

} // namespace dxgi