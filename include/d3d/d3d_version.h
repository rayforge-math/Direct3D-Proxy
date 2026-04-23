#pragma once
#include <sdkddkver.h>

// --- Direct3D 10 ---
#define DX_SDK_SUPPORTS_D3D10 1

// --- Direct3D 11 ---
#if defined(NTDDI_WIN8) && (NTDDI_VERSION >= NTDDI_WIN8)
	#define DX_SDK_SUPPORTS_D3D11_1 1
#endif

#if defined(NTDDI_WINBLUE) && (NTDDI_VERSION >= NTDDI_WINBLUE)
	#define DX_SDK_SUPPORTS_D3D11_2 1
#endif

#if defined(NTDDI_WIN10) && (NTDDI_VERSION >= NTDDI_WIN10)
	#define DX_SDK_SUPPORTS_D3D11_3 1
	#define DX_SDK_SUPPORTS_D3D11_4 1
#endif

// --- Direct3D 12 ---
#if defined(NTDDI_WIN10) && (NTDDI_VERSION >= NTDDI_WIN10)
	#define DX_SDK_SUPPORTS_D3D12 1
#endif

#if defined(NTDDI_WIN10_RS1) && (NTDDI_VERSION >= NTDDI_WIN10_RS1)
	#define DX_SDK_SUPPORTS_D3D12_1 1
#endif

#if defined(NTDDI_WIN10_RS5) && (NTDDI_VERSION >= NTDDI_WIN10_RS5)
	#define DX_SDK_SUPPORTS_D3D12_RAYTRACING 1
#endif

#if defined(NTDDI_WIN11_GE) && (NTDDI_VERSION >= NTDDI_WIN11_GE)
	#define DX_SDK_SUPPORTS_D3D12_ULTIMATE 1
#endif