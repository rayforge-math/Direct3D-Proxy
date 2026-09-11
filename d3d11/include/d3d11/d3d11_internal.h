#include <minwindef.h>

namespace d3d11 {

	extern "C" {
		extern FARPROC proc_CreateDirect3D11DeviceFromDXGIDevice;
		extern FARPROC proc_CreateDirect3D11SurfaceFromDXGISurface;
		extern FARPROC proc_D3D11CoreCreateDevice;
		extern FARPROC proc_D3D11CoreCreateLayeredDevice;
		extern FARPROC proc_D3D11CoreGetLayeredDeviceSize;
		extern FARPROC proc_D3D11CoreRegisterLayers;
		extern FARPROC proc_D3D11CreateDevice;
		extern FARPROC proc_D3D11CreateDeviceAndSwapChain;
		extern FARPROC proc_D3D11CreateDeviceForD3D12;
		extern FARPROC proc_D3D11On12CreateDevice;
		extern FARPROC proc_EnableFeatureLevelUpgrade;
		extern FARPROC proc_D3DKMTCloseAdapter;
		extern FARPROC proc_D3DKMTCreateAllocation;
		extern FARPROC proc_D3DKMTCreateContext;
		extern FARPROC proc_D3DKMTCreateDevice;
		extern FARPROC proc_D3DKMTCreateSynchronizationObject;
		extern FARPROC proc_D3DKMTDestroyAllocation;
		extern FARPROC proc_D3DKMTDestroyContext;
		extern FARPROC proc_D3DKMTDestroyDevice;
		extern FARPROC proc_D3DKMTDestroySynchronizationObject;
		extern FARPROC proc_D3DKMTEscape;
		extern FARPROC proc_D3DKMTGetContextSchedulingPriority;
		extern FARPROC proc_D3DKMTGetDeviceState;
		extern FARPROC proc_D3DKMTGetDisplayModeList;
		extern FARPROC proc_D3DKMTGetMultisampleMethodList;
		extern FARPROC proc_D3DKMTGetRuntimeData;
		extern FARPROC proc_D3DKMTGetSharedPrimaryHandle;
		extern FARPROC proc_D3DKMTLock;
		extern FARPROC proc_D3DKMTOpenAdapterFromHdc;
		extern FARPROC proc_D3DKMTOpenResource;
		extern FARPROC proc_D3DKMTPresent;
		extern FARPROC proc_D3DKMTQueryAdapterInfo;
		extern FARPROC proc_D3DKMTQueryAllocationResidency;
		extern FARPROC proc_D3DKMTQueryResourceInfo;
		extern FARPROC proc_D3DKMTRender;
		extern FARPROC proc_D3DKMTSetAllocationPriority;
		extern FARPROC proc_D3DKMTSetContextSchedulingPriority;
		extern FARPROC proc_D3DKMTSetDisplayMode;
		extern FARPROC proc_D3DKMTSetDisplayPrivateDriverFormat;
		extern FARPROC proc_D3DKMTSetGammaRamp;
		extern FARPROC proc_D3DKMTSetVidPnSourceOwner;
		extern FARPROC proc_D3DKMTSignalSynchronizationObject;
		extern FARPROC proc_D3DKMTUnlock;
		extern FARPROC proc_D3DKMTWaitForSynchronizationObject;
		extern FARPROC proc_D3DKMTWaitForVerticalBlankEvent;
		extern FARPROC proc_D3DPerformance_BeginEvent;
		extern FARPROC proc_D3DPerformance_EndEvent;
		extern FARPROC proc_D3DPerformance_GetStatus;
		extern FARPROC proc_D3DPerformance_SetMarker;
		extern FARPROC proc_OpenAdapter10;
		extern FARPROC proc_OpenAdapter10_2;
	}

} // namespace d3d11