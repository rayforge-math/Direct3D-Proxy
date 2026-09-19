#include "dllmain.h"
#include "debug/debug_dxgi.h"
#include "globals.h"
#include "DXGIHookExporter.h"

namespace dll {

    namespace constants {
        static constexpr std::string_view dllmain_prefix = "DllMain Event (DXGI):";
        static constexpr std::string_view hook = "DLL_HOOK";
        static constexpr std::string_view unhook = "DLL_UNHOOK";
        static constexpr std::string_view proc_attach = "DLL_PROCESS_ATTACH";
        static constexpr std::string_view proc_detach = "DLL_PROCESS_DETACH";
        static constexpr std::string_view start = "START";
        static constexpr std::string_view success = "SUCCESS";
        static constexpr std::string_view error = "ERROR";
    }

    inline BOOL on_process_attach(HMODULE h_module, LPVOID lp_reserved);
    inline BOOL on_process_detach(HMODULE h_module, LPVOID lp_reserved);
    inline BOOL on_thread_attach(HMODULE h_module, LPVOID lp_reserved);
    inline BOOL on_thread_detach(HMODULE h_module, LPVOID lp_reserved);

    extern "C" BOOL APIENTRY DllMain(HMODULE h_module, DWORD ul_reason_for_call, LPVOID lp_reserved)
    {
        switch (ul_reason_for_call)
        {
        case DLL_PROCESS_ATTACH:
            return on_process_attach(h_module, lp_reserved);

        case DLL_THREAD_ATTACH:
            return on_thread_attach(h_module, lp_reserved);

        case DLL_THREAD_DETACH:
            return on_thread_detach(h_module, lp_reserved);

        case DLL_PROCESS_DETACH:
            return on_process_detach(h_module, lp_reserved);
        }
        return TRUE;
    }

    inline BOOL on_process_attach(HMODULE h_module, LPVOID lp_reserved)
    {
        LOG_MSG(constants::dllmain_prefix, constants::proc_attach, constants::start);
        DisableThreadLibraryCalls(h_module);

        if (auto res = dll::DXGIHookExporter::HookExports()) {
            LOG_MSG(constants::dllmain_prefix, constants::hook, constants::success);
        }
        else {
            LOG_MSG(constants::dllmain_prefix, constants::hook, constants::error, "(", res, ")");
            return res;
        }

        LOG_MSG(constants::dllmain_prefix, constants::proc_attach, constants::success);
        return TRUE;
    }

    inline BOOL on_process_detach(HMODULE h_module, LPVOID lp_reserved)
    {
        LOG_MSG(constants::dllmain_prefix, constants::proc_detach, constants::start);

        if (auto res = dll::DXGIHookExporter::UnhookExports()) {
            LOG_MSG(constants::dllmain_prefix, constants::unhook, constants::success);
        }
        else {
            LOG_MSG(constants::dllmain_prefix, constants::unhook, constants::error, "(", res, ")");
            return res;
        }

        LOG_MSG(constants::dllmain_prefix, constants::proc_detach, constants::success);
        return TRUE;
    }

    inline BOOL on_thread_attach(HMODULE h_module, LPVOID lp_reserved)
    {
        return TRUE;
    }

    inline BOOL on_thread_detach(HMODULE h_module, LPVOID lp_reserved)
    {
        return TRUE;
    }

} // namespace dll