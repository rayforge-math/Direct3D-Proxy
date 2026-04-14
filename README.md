# Direct3D Proxy

A collection of DirectX Proxy DLLs, currently only supports DirectX 11.

> **Note:** This project is heavily modified and continues to be actively developed, but is based on the original work by [SeanPesce/d3d11-wrapper](https://github.com/SeanPesce/d3d11-wrapper/tree/master). Credits and thanks go to the original author.

---

## How it Works

The proxy DLL sits in the game's executable directory. Because Windows prioritizes local DLLs over system DLLs ([DLL Search Order](https://learn.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-search-order)), the game loads this wrapper instead of the original system file. The wrapper then:

1. Loads the authentic system DLL from `C:\Windows\System32\`.
2. Redirects all function calls to the original library.
3. Provides a hook-point for logging or altering API behavior.

---

## Build Instructions

### Prerequisites

- Visual Studio 2022 (or newer)
- C++ Desktop Development workload
- Windows 10/11 SDK

### Compilation Steps

1. **Open the Solution:** Open the `.sln` file in Visual Studio.
2. **Configuration:**
   - Select **Release** for maximum performance and portability.
   - Select **x64** (required for most modern titles like Anno).
3. **Build:**
   - Go to `Build` → `Rebuild Solution`.
4. **Output:**
   - The clean output is located in: `.\Release\x64\`
   - Intermediate build files are isolated in the `build/` subdirectory.

---

## Installation & Usage

1. Copy the compiled `d3d11.dll` to the folder containing the game's `.exe`.
2. *(Optional)* Use a tool like **DebugView** to monitor `trace()` outputs if logging is enabled.
3. Start the game normally.
