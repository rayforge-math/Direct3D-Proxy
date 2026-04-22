#pragma once

#include "sdk_version.h"

#include <dxgi.h>

#ifdef DX_SDK_SUPPORTS_D3D11_1
#include <dxgi1_2.h>
#endif

#ifdef DX_SDK_SUPPORTS_D3D11_2
#include <dxgi1_3.h>
#endif

#ifdef DX_SDK_SUPPORTS_D3D11_3
#endif

#ifdef DX_SDK_SUPPORTS_D3D11_4
#include <dxgi1_5.h>
#endif