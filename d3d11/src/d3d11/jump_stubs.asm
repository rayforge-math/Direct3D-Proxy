; ============================================================================
; D3D11 PROXY - ASM JUMP TABLE (x64)
; ============================================================================

.code

; --- [1] PUBLIC SDK APIs ---
extern proc_D3D11CreateDevice : qword
extern proc_D3D11CreateDeviceAndSwapChain : qword
extern proc_D3D11On12CreateDevice : qword
extern proc_CreateDirect3D11DeviceFromDXGIDevice : qword
extern proc_CreateDirect3D11SurfaceFromDXGISurface : qword

; --- [2] CORE & INTERNAL ---
extern proc_D3D11CoreCreateDevice : qword
extern proc_D3D11CoreRegisterLayers : qword
extern proc_D3D11CoreCreateLayeredDevice : qword
extern proc_D3D11CoreGetLayeredDeviceSize : qword
extern proc_D3D11CreateDeviceForD3D12 : qword
extern proc_EnableFeatureLevelUpgrade : qword

; --- [3] UMD ---
extern proc_OpenAdapter10 : qword
extern proc_OpenAdapter10_2 : qword

; --- [4] PERF ---
extern proc_D3DPerformance_BeginEvent : qword
extern proc_D3DPerformance_EndEvent : qword
extern proc_D3DPerformance_SetMarker : qword
extern proc_D3DPerformance_GetStatus : qword

; --- [5] KMT (D3DKMT) ---
extern proc_D3DKMTOpenAdapterFromHdc : qword
extern proc_D3DKMTQueryAdapterInfo : qword
extern proc_D3DKMTCloseAdapter : qword
extern proc_D3DKMTCreateDevice : qword
extern proc_D3DKMTGetDeviceState : qword
extern proc_D3DKMTDestroyDevice : qword
extern proc_D3DKMTCreateContext : qword
extern proc_D3DKMTGetContextSchedulingPriority : qword
extern proc_D3DKMTSetContextSchedulingPriority : qword
extern proc_D3DKMTDestroyContext : qword
extern proc_D3DKMTCreateAllocation : qword
extern proc_D3DKMTQueryResourceInfo : qword
extern proc_D3DKMTOpenResource : qword
extern proc_D3DKMTGetSharedPrimaryHandle : qword
extern proc_D3DKMTLock : qword
extern proc_D3DKMTUnlock : qword
extern proc_D3DKMTQueryAllocationResidency : qword
extern proc_D3DKMTSetAllocationPriority : qword
extern proc_D3DKMTDestroyAllocation : qword
extern proc_D3DKMTSetVidPnSourceOwner : qword
extern proc_D3DKMTSetDisplayMode : qword
extern proc_D3DKMTGetDisplayModeList : qword
extern proc_D3DKMTSetDisplayPrivateDriverFormat : qword
extern proc_D3DKMTSetGammaRamp : qword
extern proc_D3DKMTGetMultisampleMethodList : qword
extern proc_D3DKMTWaitForVerticalBlankEvent : qword
extern proc_D3DKMTRender : qword
extern proc_D3DKMTPresent : qword
extern proc_D3DKMTCreateSynchronizationObject : qword
extern proc_D3DKMTSignalSynchronizationObject : qword
extern proc_D3DKMTWaitForSynchronizationObject : qword
extern proc_D3DKMTDestroySynchronizationObject : qword
extern proc_D3DKMTEscape : qword
extern proc_D3DKMTGetRuntimeData : qword

; --- IMPLEMENTATION STUBS ---

; --- [1] PUBLIC SDK APIs ---

D3D11CreateDevice_ASM proc
    jmp qword ptr [proc_D3D11CreateDevice]
D3D11CreateDevice_ASM endp

D3D11CreateDeviceAndSwapChain_ASM proc
    jmp qword ptr [proc_D3D11CreateDeviceAndSwapChain]
D3D11CreateDeviceAndSwapChain_ASM endp

D3D11On12CreateDevice_ASM proc
    jmp qword ptr [proc_D3D11On12CreateDevice]
D3D11On12CreateDevice_ASM endp

CreateDirect3D11DeviceFromDXGIDevice_ASM proc
    jmp qword ptr [proc_CreateDirect3D11DeviceFromDXGIDevice]
CreateDirect3D11DeviceFromDXGIDevice_ASM endp

CreateDirect3D11SurfaceFromDXGISurface_ASM proc
    jmp qword ptr [proc_CreateDirect3D11SurfaceFromDXGISurface]
CreateDirect3D11SurfaceFromDXGISurface_ASM endp

; --- [2] CORE & INTERNAL ---

D3D11CoreCreateDevice_ASM proc
    jmp qword ptr [proc_D3D11CoreCreateDevice]
D3D11CoreCreateDevice_ASM endp

D3D11CoreRegisterLayers_ASM proc
    jmp qword ptr [proc_D3D11CoreRegisterLayers]
D3D11CoreRegisterLayers_ASM endp

D3D11CoreCreateLayeredDevice_ASM proc
    jmp qword ptr [proc_D3D11CoreCreateLayeredDevice]
D3D11CoreCreateLayeredDevice_ASM endp

D3D11CoreGetLayeredDeviceSize_ASM proc
    jmp qword ptr [proc_D3D11CoreGetLayeredDeviceSize]
D3D11CoreGetLayeredDeviceSize_ASM endp

D3D11CreateDeviceForD3D12_ASM proc
    jmp qword ptr [proc_D3D11CreateDeviceForD3D12]
D3D11CreateDeviceForD3D12_ASM endp

EnableFeatureLevelUpgrade_ASM proc
    jmp qword ptr [proc_D3D11CreateDeviceForD3D12]
EnableFeatureLevelUpgrade_ASM endp

; --- [3] UMD ---

OpenAdapter10_ASM proc
    jmp qword ptr [proc_OpenAdapter10]
OpenAdapter10_ASM endp

OpenAdapter10_2_ASM proc
    jmp qword ptr [proc_OpenAdapter10_2]
OpenAdapter10_2_ASM endp

; --- [4] PERF ---

D3DPerformance_BeginEvent_ASM proc
    jmp qword ptr [proc_D3DPerformance_BeginEvent]
D3DPerformance_BeginEvent_ASM endp

D3DPerformance_EndEvent_ASM proc
    jmp qword ptr [proc_D3DPerformance_EndEvent]
D3DPerformance_EndEvent_ASM endp

D3DPerformance_SetMarker_ASM proc
    jmp qword ptr [proc_D3DPerformance_SetMarker]
D3DPerformance_SetMarker_ASM endp

D3DPerformance_GetStatus_ASM proc
    jmp qword ptr [proc_D3DPerformance_GetStatus]
D3DPerformance_GetStatus_ASM endp

; --- [5] KMT (D3DKMT) ---

D3DKMTOpenAdapterFromHdc_ASM proc
    jmp qword ptr [proc_D3DKMTOpenAdapterFromHdc]
D3DKMTOpenAdapterFromHdc_ASM endp

D3DKMTQueryAdapterInfo_ASM proc
    jmp qword ptr [proc_D3DKMTQueryAdapterInfo]
D3DKMTQueryAdapterInfo_ASM endp

D3DKMTCloseAdapter_ASM proc
    jmp qword ptr [proc_D3DKMTCloseAdapter]
D3DKMTCloseAdapter_ASM endp

D3DKMTCreateDevice_ASM proc
    jmp qword ptr [proc_D3DKMTCreateDevice]
D3DKMTCreateDevice_ASM endp

D3DKMTGetDeviceState_ASM proc
    jmp qword ptr [proc_D3DKMTGetDeviceState]
D3DKMTGetDeviceState_ASM endp

D3DKMTDestroyDevice_ASM proc
    jmp qword ptr [proc_D3DKMTDestroyDevice]
D3DKMTDestroyDevice_ASM endp

D3DKMTCreateContext_ASM proc
    jmp qword ptr [proc_D3DKMTCreateContext]
D3DKMTCreateContext_ASM endp

D3DKMTGetContextSchedulingPriority_ASM proc
    jmp qword ptr [proc_D3DKMTGetContextSchedulingPriority]
D3DKMTGetContextSchedulingPriority_ASM endp

D3DKMTSetContextSchedulingPriority_ASM proc
    jmp qword ptr [proc_D3DKMTSetContextSchedulingPriority]
D3DKMTSetContextSchedulingPriority_ASM endp

D3DKMTDestroyContext_ASM proc
    jmp qword ptr [proc_D3DKMTDestroyContext]
D3DKMTDestroyContext_ASM endp

D3DKMTCreateAllocation_ASM proc
    jmp qword ptr [proc_D3DKMTCreateAllocation]
D3DKMTCreateAllocation_ASM endp

D3DKMTQueryResourceInfo_ASM proc
    jmp qword ptr [proc_D3DKMTQueryResourceInfo]
D3DKMTQueryResourceInfo_ASM endp

D3DKMTOpenResource_ASM proc
    jmp qword ptr [proc_D3DKMTOpenResource]
D3DKMTOpenResource_ASM endp

D3DKMTGetSharedPrimaryHandle_ASM proc
    jmp qword ptr [proc_D3DKMTGetSharedPrimaryHandle]
D3DKMTGetSharedPrimaryHandle_ASM endp

D3DKMTLock_ASM proc
    jmp qword ptr [proc_D3DKMTLock]
D3DKMTLock_ASM endp

D3DKMTUnlock_ASM proc
    jmp qword ptr [proc_D3DKMTUnlock]
D3DKMTUnlock_ASM endp

D3DKMTQueryAllocationResidency_ASM proc
    jmp qword ptr [proc_D3DKMTQueryAllocationResidency]
D3DKMTQueryAllocationResidency_ASM endp

D3DKMTSetAllocationPriority_ASM proc
    jmp qword ptr [proc_D3DKMTSetAllocationPriority]
D3DKMTSetAllocationPriority_ASM endp

D3DKMTDestroyAllocation_ASM proc
    jmp qword ptr [proc_D3DKMTDestroyAllocation]
D3DKMTDestroyAllocation_ASM endp

D3DKMTSetVidPnSourceOwner_ASM proc
    jmp qword ptr [proc_D3DKMTSetVidPnSourceOwner]
D3DKMTSetVidPnSourceOwner_ASM endp

D3DKMTSetDisplayMode_ASM proc
    jmp qword ptr [proc_D3DKMTSetDisplayMode]
D3DKMTSetDisplayMode_ASM endp

D3DKMTGetDisplayModeList_ASM proc
    jmp qword ptr [proc_D3DKMTGetDisplayModeList]
D3DKMTGetDisplayModeList_ASM endp

D3DKMTSetDisplayPrivateDriverFormat_ASM proc
    jmp qword ptr [proc_D3DKMTSetDisplayPrivateDriverFormat]
D3DKMTSetDisplayPrivateDriverFormat_ASM endp

D3DKMTSetGammaRamp_ASM proc
    jmp qword ptr [proc_D3DKMTSetGammaRamp]
D3DKMTSetGammaRamp_ASM endp

D3DKMTGetMultisampleMethodList_ASM proc
    jmp qword ptr [proc_D3DKMTGetMultisampleMethodList]
D3DKMTGetMultisampleMethodList_ASM endp

D3DKMTWaitForVerticalBlankEvent_ASM proc
    jmp qword ptr [proc_D3DKMTWaitForVerticalBlankEvent]
D3DKMTWaitForVerticalBlankEvent_ASM endp

D3DKMTRender_ASM proc
    jmp qword ptr [proc_D3DKMTRender]
D3DKMTRender_ASM endp

D3DKMTPresent_ASM proc
    jmp qword ptr [proc_D3DKMTPresent]
D3DKMTPresent_ASM endp

D3DKMTCreateSynchronizationObject_ASM proc
    jmp qword ptr [proc_D3DKMTCreateSynchronizationObject]
D3DKMTCreateSynchronizationObject_ASM endp

D3DKMTSignalSynchronizationObject_ASM proc
    jmp qword ptr [proc_D3DKMTSignalSynchronizationObject]
D3DKMTSignalSynchronizationObject_ASM endp

D3DKMTWaitForSynchronizationObject_ASM proc
    jmp qword ptr [proc_D3DKMTWaitForSynchronizationObject]
D3DKMTWaitForSynchronizationObject_ASM endp

D3DKMTDestroySynchronizationObject_ASM proc
    jmp qword ptr [proc_D3DKMTDestroySynchronizationObject]
D3DKMTDestroySynchronizationObject_ASM endp

D3DKMTEscape_ASM proc
    jmp qword ptr [proc_D3DKMTEscape]
D3DKMTEscape_ASM endp

D3DKMTGetRuntimeData_ASM proc
    jmp qword ptr [proc_D3DKMTGetRuntimeData]
D3DKMTGetRuntimeData_ASM endp

end 
;