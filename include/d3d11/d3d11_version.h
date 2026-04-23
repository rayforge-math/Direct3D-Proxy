#pragma once

#include "d3d/d3d_version.h"

#include <d3d11.h>

#ifdef DX_SDK_SUPPORTS_D3D11_1
#include <d3d11_1.h>
#endif

#ifdef DX_SDK_SUPPORTS_D3D11_2
#include <d3d11_2.h>
#endif

#ifdef DX_SDK_SUPPORTS_D3D11_3
#include <d3d11_3.h>
#endif

#ifdef DX_SDK_SUPPORTS_D3D11_4
#include <d3d11_4.h>
#endif