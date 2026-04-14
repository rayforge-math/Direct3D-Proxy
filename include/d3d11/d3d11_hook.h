#pragma once

#include "D3D11.h"

namespace d3d11 {

	enum func_index {
		CreateDirect3D11DeviceFromDXGIDevice_i,
		CreateDirect3D11SurfaceFromDXGISurface_i,
		D3D11CoreCreateDevice_i,
		D3D11CoreCreateLayeredDevice_i,
		D3D11CoreGetLayeredDeviceSize_i,
		D3D11CoreRegisterLayers_i,
		D3D11CreateDevice_i,
		D3D11CreateDeviceAndSwapChain_i,
		D3D11CreateDeviceForD3D12_i,
		D3D11On12CreateDevice_i,
		D3DKMTCloseAdapter_i,
		D3DKMTCreateAllocation_i,
		D3DKMTCreateContext_i,
		D3DKMTCreateDevice_i,
		D3DKMTCreateSynchronizationObject_i,
		D3DKMTDestroyAllocation_i,
		D3DKMTDestroyContext_i,
		D3DKMTDestroyDevice_i,
		D3DKMTDestroySynchronizationObject_i,
		D3DKMTEscape_i,
		D3DKMTGetContextSchedulingPriority_i,
		D3DKMTGetDeviceState_i,
		D3DKMTGetDisplayModeList_i,
		D3DKMTGetMultisampleMethodList_i,
		D3DKMTGetRuntimeData_i,
		D3DKMTGetSharedPrimaryHandle_i,
		D3DKMTLock_i,
		D3DKMTOpenAdapterFromHdc_i,
		D3DKMTOpenResource_i,
		D3DKMTPresent_i,
		D3DKMTQueryAdapterInfo_i,
		D3DKMTQueryAllocationResidency_i,
		D3DKMTQueryResourceInfo_i,
		D3DKMTRender_i,
		D3DKMTSetAllocationPriority_i,
		D3DKMTSetContextSchedulingPriority_i,
		D3DKMTSetDisplayMode_i,
		D3DKMTSetDisplayPrivateDriverFormat_i,
		D3DKMTSetGammaRamp_i,
		D3DKMTSetVidPnSourceOwner_i,
		D3DKMTSignalSynchronizationObject_i,
		D3DKMTUnlock_i,
		D3DKMTWaitForSynchronizationObject_i,
		D3DKMTWaitForVerticalBlankEvent_i,
		D3DPerformance_BeginEvent_i,
		D3DPerformance_EndEvent_i,
		D3DPerformance_GetStatus_i,
		D3DPerformance_SetMarker_i,
		EnableFeatureLevelUpgrade_i,
		OpenAdapter10_i,
		OpenAdapter10_2_i
	};

	BOOL hook_exports();
	BOOL unhook_exports();

	FARPROC dx_func(func_index idx);

} // namespace d3d11