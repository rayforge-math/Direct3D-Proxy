#include "d3d11/D3D11Inspector.h"

namespace d3d11 {

    DeviceInfo D3D11Inspector::CollectDeviceInfo(ID3D11Device* dev, IDXGIAdapter* pInAdapter, D3D_FEATURE_LEVEL* pInFLevel, UINT creationFlags) {
        DeviceInfo info = {};
        info.CreationFlags = creationFlags;
        if (pInFLevel) info.SelectedFeatureLevel = *pInFLevel;

        // --- 1. Identify Adapter ---
        IDXGIAdapter* targetAdapter = pInAdapter;
        IDXGIDevice* pDXGIDevice = nullptr;

        if (!targetAdapter && SUCCEEDED(dev->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice))) {
            pDXGIDevice->GetAdapter(&targetAdapter);
        }

        if (targetAdapter) {
            IDXGIAdapter1* adapter1 = nullptr;
            if (SUCCEEDED(targetAdapter->QueryInterface(__uuidof(IDXGIAdapter1), (void**)&adapter1))) {
                adapter1->GetDesc1(&info.AdapterDesc);
                adapter1->Release();
            }
            else {
                DXGI_ADAPTER_DESC legacyDesc = {};
                if (SUCCEEDED(targetAdapter->GetDesc(&legacyDesc))) {
                    memcpy(info.AdapterDesc.Description, legacyDesc.Description, sizeof(legacyDesc.Description));
                    info.AdapterDesc.VendorId = legacyDesc.VendorId;
                    info.AdapterDesc.DeviceId = legacyDesc.DeviceId;
                    info.AdapterDesc.SubSysId = legacyDesc.SubSysId;
                    info.AdapterDesc.Revision = legacyDesc.Revision;
                    info.AdapterDesc.DedicatedVideoMemory = legacyDesc.DedicatedVideoMemory;
                    info.AdapterDesc.DedicatedSystemMemory = legacyDesc.DedicatedSystemMemory;
                    info.AdapterDesc.SharedSystemMemory = legacyDesc.SharedSystemMemory;
                    info.AdapterDesc.AdapterLuid = legacyDesc.AdapterLuid;
                    info.AdapterDesc.Flags = DXGI_ADAPTER_FLAG_NONE;
                }
            }
            if (!pInAdapter) targetAdapter->Release();
        }
        if (pDXGIDevice) pDXGIDevice->Release();

        // --- 2. Feature Support Queries ---

        // Multithreading
        D3D11_FEATURE_DATA_THREADING threadCaps = { 0 };
        if (SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_THREADING, &threadCaps, sizeof(threadCaps)))) {
            info.DriverConcurrentCreates = threadCaps.DriverConcurrentCreates;
            info.DriverCommandLists = threadCaps.DriverCommandLists;
        }

        // Architecture (Tile-based)
#ifdef DX_SDK_SUPPORTS_D3D11_2
        D3D11_FEATURE_DATA_ARCHITECTURE_INFO arch = { 0 };
        if (SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_ARCHITECTURE_INFO, &arch, sizeof(arch)))) {
            info.Architecture.IsTileBased = arch.TileBasedDeferredRenderer;
        }
#endif

        // Shader Cache (DX11.3+)
#ifdef DX_SDK_SUPPORTS_D3D11_3
        D3D11_FEATURE_DATA_SHADER_CACHE scache = { 0 };
        if (SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_SHADER_CACHE, &scache, sizeof(scache)))) {
            info.Architecture.SupportsShaderCache = (scache.SupportFlags & D3D11_SHADER_CACHE_SUPPORT_AUTOMATIC_DISK_CACHE) != 0;
        }
#endif

        // Feature Options (Logic Ops & Constant Buffers)
#ifdef DX_SDK_SUPPORTS_D3D11_1
        D3D11_FEATURE_DATA_D3D11_OPTIONS opt1 = { 0 };
        if (SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS, &opt1, sizeof(opt1)))) {
            info.Features.OutputMergerLogicOp = opt1.OutputMergerLogicOp;
            info.Architecture.SupportsConstantBufferOffsetting = opt1.ConstantBufferOffsetting;
        }
#endif

        // Double Precision (FP64)
        D3D11_FEATURE_DATA_DOUBLES doubles = { 0 };
        if (SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_DOUBLES, &doubles, sizeof(doubles)))) {
            info.Features.DoublePrecision = doubles.DoublePrecisionFloatShaderOps;
        }

#ifdef DX_SDK_SUPPORTS_D3D11_1
        D3D11_FEATURE_DATA_SHADER_MIN_PRECISION_SUPPORT mprec = { 0 };
        if (SUCCEEDED(dev->CheckFeatureSupport(D3D11_FEATURE_SHADER_MIN_PRECISION_SUPPORT, &mprec, sizeof(mprec)))) {
            info.Features.MinPrecision = (mprec.PixelShaderMinPrecision & D3D11_SHADER_MIN_PRECISION_16_BIT) != 0;
        }
#endif

        return info;
    }

    DeviceInfo D3D11Inspector::CollectDeviceInfo(IDXGIDevice* dxgiDev) {
        DeviceInfo info = {};
        if (!dxgiDev) return info;

        // In D3D11, the DXGI Device is an interface implemented by the same object
        ID3D11Device* d3d11Dev = nullptr;
        if (SUCCEEDED(dxgiDev->QueryInterface(__uuidof(ID3D11Device), (void**)&d3d11Dev))) {

            // We use GetAdapter from the IDXGIDevice interface
            IDXGIAdapter* pAdapter = nullptr;
            if (FAILED(dxgiDev->GetAdapter(&pAdapter))) {
                pAdapter = nullptr;
            }

            // Since we don't have a pInFLevel pointer, we ask the device directly
            D3D_FEATURE_LEVEL actualFLevel = d3d11Dev->GetFeatureLevel();

            info = CollectDeviceInfo(d3d11Dev, pAdapter, &actualFLevel, 0);

            // Cleanup
            if (pAdapter) pAdapter->Release();
            d3d11Dev->Release();
        }

        return info;
    }

    SwapChainInfo D3D11Inspector::CollectSwapChainInfo(IDXGISwapChain* swChain) {
        SwapChainInfo info = {};
        if (!swChain) return info;

        // Legacy Desc
        if (FAILED(swChain->GetDesc(&info.Desc))) {
            return info;
        }
        info.OutputWindow = info.Desc.OutputWindow;

        // Extended Desc (DXGI 1.2+)
        IDXGISwapChain1* swChain1 = nullptr;
        if (SUCCEEDED(swChain->QueryInterface(__uuidof(IDXGISwapChain1), (void**)&swChain1))) {
            if (SUCCEEDED(swChain1->GetDesc1(&info.Desc1))) {
                info.IsModernFlipModel = (info.Desc1.SwapEffect == DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL ||
                    info.Desc1.SwapEffect == DXGI_SWAP_EFFECT_FLIP_DISCARD);
            }
            swChain1->Release();
        }

        // Calculate actual refresh rate
        if (info.Desc.BufferDesc.RefreshRate.Denominator > 0) {
            info.EffectiveRefreshRate = static_cast<float>(info.Desc.BufferDesc.RefreshRate.Numerator) /
                static_cast<float>(info.Desc.BufferDesc.RefreshRate.Denominator);
        }
        else {
            info.EffectiveRefreshRate = 0.0f;
        }

        return info;
    }

    InteropInfo D3D11Inspector::CollectInteropInfo(const char* type, void* input, void* output) {
        InteropInfo info = {};
        info.BridgeType = (type) ? type : "Unknown";
        info.InputPointer = input;
        info.OutputPointer = output;
        info.IsValidChain = (input != nullptr && output != nullptr);

        return info;
    }

    SurfaceInfo D3D11Inspector::CollectSurfaceInfo(IDXGISurface* dxgiSurface) {
        SurfaceInfo info = {};
        if (!dxgiSurface) return info;

        // Provides resolution and pixel format
        if (FAILED(dxgiSurface->GetDesc(&info.Desc))) {
            return info;
        }

        // Query the underlying resource to check for MSAA and sharing flags
        ID3D11Resource* res = nullptr;
        if (SUCCEEDED(dxgiSurface->QueryInterface(__uuidof(ID3D11Resource), (void**)&res))) {
            D3D11_RESOURCE_DIMENSION dim;
            res->GetType(&dim);

            // We specifically look for 2D Textures as they carry SampleDescs
            if (dim == D3D11_RESOURCE_DIMENSION_TEXTURE2D) {
                ID3D11Texture2D* tex = nullptr;
                if (SUCCEEDED(res->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&tex))) {
                    D3D11_TEXTURE2D_DESC texDesc;
                    tex->GetDesc(&texDesc);

                    info.MultisampleCount = texDesc.SampleDesc.Count;
                    info.MultisampleQuality = texDesc.SampleDesc.Quality;
                    info.IsSharedResource = (texDesc.MiscFlags & D3D11_RESOURCE_MISC_SHARED) != 0;

                    tex->Release();
                }
            }
            res->Release();
        }

        return info;
    }

} // namespace d3d11