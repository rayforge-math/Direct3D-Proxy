#pragma once
#include <sdkddkver.h>

#if defined(NTDDI_WIN10) && (NTDDI_VERSION >= NTDDI_WIN10)
#define DX_SDK_SUPPORTS_D3D11_4 1
#define DX_SDK_SUPPORTS_D3D11_3 1
#endif

#if defined(NTDDI_WINBLUE) && (NTDDI_VERSION >= NTDDI_WINBLUE)
#define DX_SDK_SUPPORTS_D3D11_2 1
#endif

#if defined(NTDDI_WIN8) && (NTDDI_VERSION >= NTDDI_WIN8)
#define DX_SDK_SUPPORTS_D3D11_1 1
#endif