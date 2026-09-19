#pragma once

#include "HookExporter.h"

namespace dll {

    class DXGIHookExporter {
    public:
        /**
         * @brief Hooks all DXGI exports by loading the original system dxgi.dll.
         * @return BOOL TRUE on success, FALSE otherwise.
         */
        static BOOL HookExports();

        /**
         * @brief Unhooks and unloads the original dxgi.dll.
         * @return BOOL TRUE on success, FALSE otherwise.
         */
        static BOOL UnhookExports();

        /**
         * @brief Gets the module handle of the chained original DLL.
         * @return HMODULE Handle to the loaded system DLL.
         */
        static HMODULE GetChainHandle();

    private:
        // Static instance of the generic HookExporter configured for dxgi.dll
        static dll::HookExporter s_Exporter;
    };

} // namespace dll