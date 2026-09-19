#include "HookExporter.h"
#include "debug/debug_d3d11.h"
#include <algorithm>
#include <string>

namespace dll {

	HookExporter::HookExporter(const char* dllName, const ProxyMapping* proxyMap, size_t mapCount)
		: m_DllName(dllName ? dllName : "")
		, m_ProxyMap(proxyMap)
		, m_MappingCount(mapCount)
		, m_Chain(NULL)
	{
	}

	HookExporter::~HookExporter()
	{
		UnhookExports();
	}

	BOOL HookExporter::HookExports()
	{
		if (!m_ProxyMap || m_MappingCount == 0) {
			LOG_MSG("Error: Invalid proxy mapping configuration provided!");
			return FALSE;
		}

		char sysDir[MAX_PATH];

		// Resolve path to system32 directory
		if (GetSystemDirectoryA(sysDir, MAX_PATH) == 0) {
			LOG_MSG("Error: System32 directory could not be found!");
			return FALSE;
		}

		std::string path = std::string(sysDir) + "\\" + m_DllName;
		LOG_MSG("Original DLL target path:", path);

		// Load the actual original system DLL
		m_Chain = LoadLibraryA(path.c_str());

		if (!m_Chain)
		{
			LOG_MSG("Error: Original DLL could not be loaded! (", path.c_str(), ")");
			return FALSE;
		}

		if (!EnumerateExports()) {
			LOG_MSG("Error: Failed to enumerate exports from loaded DLL!");
			return FALSE;
		}

		// Cache and map all requested function pointers
		int found = MapFunctions();

		LOG_VARS(m_MappingCount, found);
		return (found > 0);
	}

	BOOL HookExporter::UnhookExports()
	{
		delete[] m_ExportCache;
		m_ExportCache = nullptr;
		m_ExportCount = 0;

		if (m_Chain)
		{
			BOOL result = FreeLibrary(m_Chain);
			if (result) {
				m_Chain = nullptr;
			}
			else {
				LOG_VARS(E_FAIL, m_Chain);
			}
			return result;
		}

		return TRUE;
	}

	bool HookExporter::EnumerateExports() {
		if (m_Chain == nullptr) return false;

		const auto image_base = reinterpret_cast<const BYTE*>(m_Chain);
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

		delete[] m_ExportCache;
		m_ExportCache = nullptr;
		m_ExportCount = export_dir->NumberOfNames;

		if (m_ExportCount == 0) return false;

		m_ExportCache = new ProxyExport[m_ExportCount];

		for (DWORD i = 0; i < m_ExportCount; ++i) {
			m_ExportCache[i].name = reinterpret_cast<const char*>(image_base + name_table[i]);

			const WORD func_index = ordinal_table[i];
			m_ExportCache[i].ordinal = static_cast<unsigned short>(export_dir->Base + func_index);
			m_ExportCache[i].address = const_cast<BYTE*>(image_base + func_table[func_index]);
		}

		return (m_ExportCache != nullptr);
	}

	int HookExporter::MapFunctions() {
		int found_count = 0;

		for (size_t i = 0; i < m_MappingCount; ++i) {
			const char* target_name = m_ProxyMap[i].name;
			FARPROC* target_ptr = m_ProxyMap[i].target;

			const ProxyExport* found_export = nullptr;

			for (size_t j = 0; j < m_ExportCount; ++j) {
				if (m_ExportCache[j].name != nullptr && strcmp(m_ExportCache[j].name, target_name) == 0) {
					found_export = &m_ExportCache[j];
					break;
				}
			}

			if (found_export != nullptr) {
				*target_ptr = reinterpret_cast<FARPROC>(found_export->address);
				LOG_MSG("Successfully mapped function: ", target_name, " at address: ", found_export->address);
				found_count++;
			}
			else {
				*target_ptr = nullptr;
				LOG_MSG("Warning: Function not found in original DLL: ", target_name);
			}
		}
		return found_count;
	}

} // namespace dll