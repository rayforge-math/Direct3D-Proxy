#include "d3d11/d3d11_hook.h"
#include "debug.h"
#include <string>

namespace d3d11 {

	constexpr const char* filename = "d3d11.dll";

	const size_t func_count = 51; // func_count = 42 on Windows 7

    HMODULE chain = NULL;
    FARPROC functions[func_count];

	constexpr const char* func_names[func_count] = {
		"CreateDirect3D11DeviceFromDXGIDevice",
		"CreateDirect3D11SurfaceFromDXGISurface",
		"D3D11CoreCreateDevice",
		"D3D11CoreCreateLayeredDevice",
		"D3D11CoreGetLayeredDeviceSize",
		"D3D11CoreRegisterLayers",
		"D3D11CreateDevice",
		"D3D11CreateDeviceAndSwapChain",
		"D3D11CreateDeviceForD3D12",
		"D3D11On12CreateDevice",
		"D3DKMTCloseAdapter",
		"D3DKMTCreateAllocation",
		"D3DKMTCreateContext",
		"D3DKMTCreateDevice",
		"D3DKMTCreateSynchronizationObject",
		"D3DKMTDestroyAllocation",
		"D3DKMTDestroyContext",
		"D3DKMTDestroyDevice",
		"D3DKMTDestroySynchronizationObject",
		"D3DKMTEscape",
		"D3DKMTGetContextSchedulingPriority",
		"D3DKMTGetDeviceState",
		"D3DKMTGetDisplayModeList",
		"D3DKMTGetMultisampleMethodList",
		"D3DKMTGetRuntimeData",
		"D3DKMTGetSharedPrimaryHandle",
		"D3DKMTLock",
		"D3DKMTOpenAdapterFromHdc",
		"D3DKMTOpenResource",
		"D3DKMTPresent",
		"D3DKMTQueryAdapterInfo",
		"D3DKMTQueryAllocationResidency",
		"D3DKMTQueryResourceInfo",
		"D3DKMTRender",
		"D3DKMTSetAllocationPriority",
		"D3DKMTSetContextSchedulingPriority",
		"D3DKMTSetDisplayMode",
		"D3DKMTSetDisplayPrivateDriverFormat",
		"D3DKMTSetGammaRamp",
		"D3DKMTSetVidPnSourceOwner",
		"D3DKMTSignalSynchronizationObject",
		"D3DKMTUnlock",
		"D3DKMTWaitForSynchronizationObject",
		"D3DKMTWaitForVerticalBlankEvent",
		"D3DPerformance_BeginEvent",
		"D3DPerformance_EndEvent",
		"D3DPerformance_GetStatus",
		"D3DPerformance_SetMarker",
		"EnableFeatureLevelUpgrade",
		"OpenAdapter10",
		"OpenAdapter10_2"
	};

	BOOL hook_exports()
	{
		char sysDir[MAX_PATH];

		// path to sys32
		if (GetSystemDirectoryA(sysDir, MAX_PATH) == 0) {
			MessageBoxA(NULL, "System32 could not be found!", "Error", MB_ICONERROR);
			return FALSE;
		}

		std::string path = std::string(sysDir) + "\\" + filename;
		LOG_VARS(path);

		// load actual directx dll
		chain = LoadLibraryA(path.c_str());

		if (!chain)
		{
			std::string errorMsg = "Error loading original DLL: " + path;
			MessageBoxA(NULL, errorMsg.c_str(), "Proxy Error", MB_ICONERROR);
			exit(0);
		}

		// cache all function pointers
		int found = 0;
		for (int i = 0; i < func_count; i++)
		{
			FARPROC func = GetProcAddress(chain, func_names[i]);
			if (func)
			{
				found++;
			}
			else
			{
				LOG_VARS(E_FAIL, i, func_names[i]);
			}
			functions[i] = func;
		}

		LOG_VARS(func_count, found);

		return (found > 0);
	}

	BOOL unhook_exports()
	{
		if (chain)
		{
			BOOL result = FreeLibrary(chain);
			if (result) {
				chain = nullptr;
			}
			else {
				LOG_VARS(E_FAIL, chain);
			}
			return result;
		}

		return TRUE;
	}

	extern "C" inline FARPROC dx_func(func_index idx)
	{
		return functions[idx];
	}

} // namespace d3d11
