#include <minwindef.h>

namespace dll {

    extern "C" {
        extern FARPROC proc_CreateDXGIFactory;
        extern FARPROC proc_CreateDXGIFactory1;
        extern FARPROC proc_CreateDXGIFactory2;
        extern FARPROC proc_DXGID3D10CreateDevice;
        extern FARPROC proc_DXGID3D10CreateLayeredDevice;
        extern FARPROC proc_DXGID3D10GetLayeredDeviceSize;
        extern FARPROC proc_DXGID3D10RegisterLayers;
        extern FARPROC proc_DXGIGetDebugInterface1;
        extern FARPROC proc_PIXBeginCapture;
        extern FARPROC proc_PIXEndCapture;
        extern FARPROC proc_PIXGetCaptureState;
        extern FARPROC proc_DXGIDumpJournal;
        extern FARPROC proc_ApplyCompatResolutionQuirking;
        extern FARPROC proc_CompatString;
        extern FARPROC proc_CompatValue;
        extern FARPROC proc_SetAppCompatStringPointer;
        extern FARPROC proc_UpdateHMDEmulationStatus;
        extern FARPROC proc_DXGIDeclareAdapterRemovalSupport;
        extern FARPROC proc_DXGIDisableVBlankVirtualization;
        extern FARPROC proc_DXGIReportAdapterConfiguration;
    }

} // namespace dxgi