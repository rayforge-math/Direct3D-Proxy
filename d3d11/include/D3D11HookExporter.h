#pragma once

#include "HookExporter.h"

namespace dll {

    class D3D11HookExporter {
    public:
        /**
         * @brief Hooks all D3D11 exports by loading the original system d3d11.dll.
         * @return BOOL TRUE on success, FALSE otherwise.
         */
        static BOOL HookExports();

        /**
         * @brief Unhooks and unloads the original d3d11.dll.
         * @return BOOL TRUE on success, FALSE otherwise.
         */
        static BOOL UnhookExports();

        /**
         * @brief Gets the module handle of the chained original DLL.
         * @return HMODULE Handle to the loaded system DLL.
         */
        static HMODULE GetChainHandle();

    private:
        // Static instance of the generic HookExporter configured for d3d11.dll
        static dll::HookExporter s_Exporter;
    };
} // namespace dll