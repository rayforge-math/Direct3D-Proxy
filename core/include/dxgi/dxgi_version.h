#pragma once

#include "d3d/d3d_version.h"

#include <dxgi.h>

#ifdef DX_SDK_SUPPORTS_D3D11_1
#include <dxgi1_2.h>
#endif

#ifdef DX_SDK_SUPPORTS_D3D11_2
#include <dxgi1_3.h>
#endif

#ifdef DX_SDK_SUPPORTS_D3D11_3
#include <dxgi1_4.h>
#endif

#ifdef DX_SDK_SUPPORTS_D3D11_4
#include <dxgi1_5.h>
#endif


#if defined(__has_include)
#if __has_include(<dxgi1_6.h>)
#include <dxgi1_6.h>

#ifndef DX_SDK_SUPPORTS_DXGI_1_6
#define DX_SDK_SUPPORTS_DXGI_1_6 1
#endif

#endif
#endif