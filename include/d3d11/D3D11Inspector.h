/*
    Feature docs: https://learn.microsoft.com/en-us/windows/win32/api/_direct3d11/
*/

#pragma once

#include "d3d11/d3d11_version.h"
#include "dxgi/DXGIInspector.h"

namespace d3d11 {

    /**
     * @class D3D11Inspector
     * @brief Static utility class for extracting metadata from DirectX interfaces.
     * * This class operates in a read-only manner to observe and capture the state
     * and capabilities of graphics objects created by the application without
     * interfering with the rendering pipeline.
     */
    class D3D11Inspector {
    public:
        // data collection
        static dxgi::DeviceInfo CollectDeviceInfo(ID3D11Device* dev, IDXGIAdapter* pInAdapter, D3D_FEATURE_LEVEL* pInFLevel, UINT creationFlags);
        static dxgi::DeviceInfo CollectDeviceInfo(IDXGIDevice* dxgiDev);
        static dxgi::SurfaceInfo CollectSurfaceInfo(IDXGISurface* dxgiSurface);
        // string resolver

    };

} // namespace d3d11