#pragma once

#include "d3dcommon.h"
#include "d3d/d3d_version.h"

namespace d3d {

    /**
     * @class D3DInspector
     * @brief Static utility class for extracting metadata from DirectX interfaces.
     * * This class operates in a read-only manner to observe and capture the state
     * and capabilities of graphics objects created by the application without
     * interfering with the rendering pipeline.
     */
    class D3DInspector {
    public:
        // string resolver
        static const char* FeatureLevelToString(D3D_FEATURE_LEVEL level);
        static const char* DriverTypeToString(D3D_DRIVER_TYPE type);
    };

} // namespace d3d