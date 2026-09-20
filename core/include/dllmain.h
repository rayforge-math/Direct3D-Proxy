#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <string_view>

namespace dll::constants {
    static constexpr std::string_view dllmain_prefix = "DllMain Event:";
    static constexpr std::string_view hook = "DLL_HOOK";
    static constexpr std::string_view unhook = "DLL_UNHOOK";
    static constexpr std::string_view proc_attach = "DLL_PROCESS_ATTACH";
    static constexpr std::string_view proc_detach = "DLL_PROCESS_DETACH";
    static constexpr std::string_view start = "START";
    static constexpr std::string_view success = "SUCCESS";
    static constexpr std::string_view error = "ERROR";
}