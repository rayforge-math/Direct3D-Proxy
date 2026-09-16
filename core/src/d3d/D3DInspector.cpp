#include "d3d/D3DInspector.h"

namespace d3d {

    const char* D3DInspector::FeatureLevelToString(D3D_FEATURE_LEVEL level) {
#define D3D_LEVEL_STR(x) case x: return #x

        switch (level) {
            // Core & Generic (often used in specialized or emulated environments)
            D3D_LEVEL_STR(D3D_FEATURE_LEVEL_1_0_GENERIC);
            D3D_LEVEL_STR(D3D_FEATURE_LEVEL_1_0_CORE);

            // Legacy / Mobile Levels
            D3D_LEVEL_STR(D3D_FEATURE_LEVEL_9_1);
            D3D_LEVEL_STR(D3D_FEATURE_LEVEL_9_2);
            D3D_LEVEL_STR(D3D_FEATURE_LEVEL_9_3);

            // Direct3D 10
            D3D_LEVEL_STR(D3D_FEATURE_LEVEL_10_0);
            D3D_LEVEL_STR(D3D_FEATURE_LEVEL_10_1);

            // Direct3D 11
            D3D_LEVEL_STR(D3D_FEATURE_LEVEL_11_0);
#ifdef DX_SDK_SUPPORTS_D3D11_1
            D3D_LEVEL_STR(D3D_FEATURE_LEVEL_11_1);
#endif

            // Direct3D 12
#ifdef DX_SDK_SUPPORTS_D3D12
            D3D_LEVEL_STR(D3D_FEATURE_LEVEL_12_0);
            D3D_LEVEL_STR(D3D_FEATURE_LEVEL_12_1);
#endif
#ifdef DX_SDK_SUPPORTS_D3D12_ULTIMATE
            D3D_LEVEL_STR(D3D_FEATURE_LEVEL_12_2);
#endif

        default: return "D3D_FEATURE_LEVEL_UNKNOWN";
        }
#undef D3D_LEVEL_STR
    }

    const char* D3DInspector::DriverTypeToString(D3D_DRIVER_TYPE type) {
#define D3D_DRIVER_STR(x) case x: return #x
        switch (type) {
            D3D_DRIVER_STR(D3D_DRIVER_TYPE_UNKNOWN);
            D3D_DRIVER_STR(D3D_DRIVER_TYPE_HARDWARE);
            D3D_DRIVER_STR(D3D_DRIVER_TYPE_REFERENCE);
            D3D_DRIVER_STR(D3D_DRIVER_TYPE_NULL);
            D3D_DRIVER_STR(D3D_DRIVER_TYPE_SOFTWARE);
            D3D_DRIVER_STR(D3D_DRIVER_TYPE_WARP);
        default: return "D3D_DRIVER_TYPE_INVALID";
        }
#undef D3D_DRIVER_STR
    }

} // namespace d3d