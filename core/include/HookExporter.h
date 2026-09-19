#pragma once
#include <windows.h>
#include <cstddef>
#include "coreapi.h"

namespace dll {

	struct ProxyMapping {
		const char* name;
		FARPROC* target;
	};

	struct ProxyExport {
		void* address;
		const char* name;
		unsigned short ordinal;
	};

	class CORE_API HookExporter {
	public:
		/**
		 * @brief Constructs a HookExporter instance for a specific target DLL and mapping table.
		 * @param dllName  [in] The file name of the system DLL to chain (e.g., "d3d11.dll").
		 * @param proxyMap [in] Pointer to an array of ProxyMapping structures.
		 * @param mapCount [in] Number of elements in the proxyMap array.
		 */
		HookExporter(const char* dllName, const ProxyMapping* proxyMap, size_t mapCount);

		~HookExporter();

		// Delete copy operations to prevent multiple frees of the same HMODULE
		HookExporter(const HookExporter&) = delete;
		HookExporter& operator=(const HookExporter&) = delete;

		// Allow move operations if needed
		HookExporter(HookExporter&&) noexcept = default;
		HookExporter& operator=(HookExporter&&) noexcept = default;

		/**
		 * @brief Loads the target system DLL, enumerates its exports, and maps the function pointers.
		 * @return BOOL TRUE on success (at least one function mapped), FALSE otherwise.
		 */
		BOOL HookExports();

		/**
		 * @brief Frees the loaded chain DLL handle.
		 * @return BOOL TRUE on success, FALSE otherwise.
		 */
		BOOL UnhookExports();

		// Getters for internal states
		HMODULE GetChainHandle() const { return m_Chain; }
		const ProxyExport* GetExportCache() const { return m_ExportCache; }
		size_t GetExportCount() const { return m_ExportCount; }

	private:
		bool EnumerateExports();
		int MapFunctions();

		// Instance members
		const char* m_DllName;
		const ProxyMapping* m_ProxyMap;
		size_t m_MappingCount;

		HMODULE m_Chain;
		ProxyExport* m_ExportCache;
		size_t m_ExportCount;
	};

} // namespace dll