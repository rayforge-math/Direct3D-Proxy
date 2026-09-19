; ============================================================================
; DXGI PROXY - ASM JUMP TABLE (x64)
; ============================================================================

.code

; --- EXTERNAL FUNCTION POINTERS ---
extern proc_CreateDXGIFactory : qword
extern proc_CreateDXGIFactory1 : qword
extern proc_CreateDXGIFactory2 : qword
extern proc_DXGID3D10CreateDevice : qword
extern proc_DXGID3D10CreateLayeredDevice : qword
extern proc_DXGID3D10GetLayeredDeviceSize : qword
extern proc_DXGID3D10RegisterLayers : qword
extern proc_DXGIGetDebugInterface1 : qword
extern proc_PIXBeginCapture : qword
extern proc_PIXEndCapture : qword
extern proc_PIXGetCaptureState : qword
extern proc_DXGIDumpJournal : qword
extern proc_ApplyCompatResolutionQuirking : qword
extern proc_CompatString : qword
extern proc_CompatValue : qword
extern proc_SetAppCompatStringPointer : qword
extern proc_UpdateHMDEmulationStatus : qword
extern proc_DXGIDeclareAdapterRemovalSupport : qword
extern proc_DXGIDisableVBlankVirtualization : qword
extern proc_DXGIReportAdapterConfiguration : qword


; --- IMPLEMENTATION STUBS ---

CreateDXGIFactory_ASM proc
    jmp qword ptr [proc_CreateDXGIFactory]
CreateDXGIFactory_ASM endp

CreateDXGIFactory1_ASM proc
    jmp qword ptr [proc_CreateDXGIFactory1]
CreateDXGIFactory1_ASM endp

CreateDXGIFactory2_ASM proc
    jmp qword ptr [proc_CreateDXGIFactory2]
CreateDXGIFactory2_ASM endp

DXGID3D10CreateDevice_ASM proc
    jmp qword ptr [proc_DXGID3D10CreateDevice]
DXGID3D10CreateDevice_ASM endp

DXGID3D10CreateLayeredDevice_ASM proc
    jmp qword ptr [proc_DXGID3D10CreateLayeredDevice]
DXGID3D10CreateLayeredDevice_ASM endp

DXGID3D10GetLayeredDeviceSize_ASM proc
    jmp qword ptr [proc_DXGID3D10GetLayeredDeviceSize]
DXGID3D10GetLayeredDeviceSize_ASM endp

DXGID3D10RegisterLayers_ASM proc
    jmp qword ptr [proc_DXGID3D10RegisterLayers]
DXGID3D10RegisterLayers_ASM endp

DXGIGetDebugInterface1_ASM proc
    jmp qword ptr [proc_DXGIGetDebugInterface1]
DXGIGetDebugInterface1_ASM endp

PIXBeginCapture_ASM proc
    jmp qword ptr [proc_PIXBeginCapture]
PIXBeginCapture_ASM endp

PIXEndCapture_ASM proc
    jmp qword ptr [proc_PIXEndCapture]
PIXEndCapture_ASM endp

PIXGetCaptureState_ASM proc
    jmp qword ptr [proc_PIXGetCaptureState]
PIXGetCaptureState_ASM endp

DXGIDumpJournal_ASM proc
    jmp qword ptr [proc_DXGIDumpJournal]
DXGIDumpJournal_ASM endp

ApplyCompatResolutionQuirking_ASM proc
    jmp qword ptr [proc_ApplyCompatResolutionQuirking]
ApplyCompatResolutionQuirking_ASM endp

CompatString_ASM proc
    jmp qword ptr [proc_CompatString]
CompatString_ASM endp

CompatValue_ASM proc
    jmp qword ptr [proc_CompatValue]
CompatValue_ASM endp

SetAppCompatStringPointer_ASM proc
    jmp qword ptr [proc_SetAppCompatStringPointer]
SetAppCompatStringPointer_ASM endp

UpdateHMDEmulationStatus_ASM proc
    jmp qword ptr [proc_UpdateHMDEmulationStatus]
UpdateHMDEmulationStatus_ASM endp

DXGIDeclareAdapterRemovalSupport_ASM proc
    jmp qword ptr [proc_DXGIDeclareAdapterRemovalSupport]
DXGIDeclareAdapterRemovalSupport_ASM endp

DXGIDisableVBlankVirtualization_ASM proc
    jmp qword ptr [proc_DXGIDisableVBlankVirtualization]
DXGIDisableVBlankVirtualization_ASM endp

DXGIReportAdapterConfiguration_ASM proc
    jmp qword ptr [proc_DXGIReportAdapterConfiguration]
DXGIReportAdapterConfiguration_ASM endp

end