#pragma once

#include "Windows.h"
#include <vector>

namespace d3d11 {

	struct ProxyMapping {
		const char* name;
		FARPROC* target;
	};

	struct ProxyExport {
		void* address;
		const char* name;
		unsigned short ordinal;
	};

	class D3D11HookExporter {
	public:
		static BOOL HookExports();
		static BOOL UnhookExports();

	private:
		static HMODULE s_Chain;
		static std::vector<ProxyExport> s_ExportCache;

		static bool EnumerateExports();
		static int MapFunctions();

		static constexpr const char* s_FileName = "d3d11.dll";
		//static constexpr size_t s_FuncCount = 51; // func_count = 42 on Windows 7

		static const ProxyMapping s_ProxyMap[];
		static const size_t s_MappingCount;
	};

} // namespace d3d11