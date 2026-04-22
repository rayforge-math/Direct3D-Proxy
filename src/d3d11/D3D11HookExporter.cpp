#include "d3d11/D3D11HookExporter.h"
#include "debug.h"
#include <string>

namespace d3d11 {

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

	const ProxyMapping D3D11HookExporter::s_ProxyMap[] = {
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

	const size_t D3D11HookExporter::s_MappingCount = sizeof(s_ProxyMap) / sizeof(ProxyMapping);

	HMODULE D3D11HookExporter::s_Chain = NULL;
	std::vector<ProxyExport> D3D11HookExporter::s_ExportCache;

	BOOL D3D11HookExporter::HookExports()
	{
		char sysDir[MAX_PATH];

		// path to sys32
		if (GetSystemDirectoryA(sysDir, MAX_PATH) == 0) {
			LOG_MSG("Error: System32 could not be found!");
			return FALSE;
		}

		std::string path = std::string(sysDir) + "\\" + s_FileName;
		LOG_MSG("Original DLL found:");
		LOG_VARS(path);

		// load actual directx dll
		s_Chain = LoadLibraryA(path.c_str());

		if (!s_Chain)
		{
			LOG_MSG("Error: Original DLL could not be loaded! (", path.c_str(), ")");
			return FALSE;
		}

		if (!EnumerateExports()) {
			LOG_MSG("Error: Failed to enumerate exports!");
			return FALSE;
		}

		// cache all function pointers
		int found = MapFunctions();

		LOG_VARS(s_MappingCount, found);
		return (found > 0);
	}

	BOOL D3D11HookExporter::UnhookExports()
	{
		if (s_Chain)
		{
			BOOL result = FreeLibrary(s_Chain);
			if (result) {
				s_Chain = nullptr;
			}
			else {
				LOG_VARS(E_FAIL, s_Chain);
			}
			return result;
		}

		return TRUE;
	}

	bool D3D11HookExporter::EnumerateExports() {
		if (s_Chain == nullptr) return false;

		const auto image_base = reinterpret_cast<const BYTE*>(s_Chain);
		const auto dos_header = reinterpret_cast<const IMAGE_DOS_HEADER*>(image_base);

		if (dos_header->e_magic != IMAGE_DOS_SIGNATURE) return false;

		const auto nt_header = reinterpret_cast<const IMAGE_NT_HEADERS*>(image_base + dos_header->e_lfanew);

		if (nt_header->Signature != IMAGE_NT_SIGNATURE) return false;

		const auto& export_data_dir = nt_header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
		if (export_data_dir.Size == 0) return false;

		const auto export_dir = reinterpret_cast<const IMAGE_EXPORT_DIRECTORY*>(
			image_base + export_data_dir.VirtualAddress);

		const DWORD* func_table = reinterpret_cast<const DWORD*>(image_base + export_dir->AddressOfFunctions);
		const DWORD* name_table = reinterpret_cast<const DWORD*>(image_base + export_dir->AddressOfNames);
		const WORD* ordinal_table = reinterpret_cast<const WORD*>(image_base + export_dir->AddressOfNameOrdinals);

		s_ExportCache.clear();
		s_ExportCache.reserve(export_dir->NumberOfNames);

		for (DWORD i = 0; i < export_dir->NumberOfNames; ++i) {
			ProxyExport e;
			e.name = reinterpret_cast<const char*>(image_base + name_table[i]);

			const WORD func_index = ordinal_table[i];
			e.ordinal = static_cast<unsigned short>(export_dir->Base + func_index);
			e.address = const_cast<BYTE*>(image_base + func_table[func_index]);

			s_ExportCache.push_back(e);
		}

		return !s_ExportCache.empty();
	}

	int D3D11HookExporter::MapFunctions() {
		int found_count = 0;

		for (size_t i = 0; i < s_MappingCount; ++i) {
			const char* target_name = s_ProxyMap[i].name;
			FARPROC* target_ptr = s_ProxyMap[i].target;

			auto it = std::find_if(s_ExportCache.begin(), s_ExportCache.end(),
				[target_name](const ProxyExport& e) {
					return (e.name != nullptr && strcmp(e.name, target_name) == 0);
				});

			if (it != s_ExportCache.end()) {
				*target_ptr = reinterpret_cast<FARPROC>(it->address);
				LOG_MSG("Successfully mapped function: ", target_name, " at address: ", it->address);
				found_count++;
			}
			else {
				*target_ptr = nullptr;
				LOG_MSG("Warning: Function not found in original DLL: ", target_name);
			}
		}
		return found_count;
	}

} // namespace d3d11
