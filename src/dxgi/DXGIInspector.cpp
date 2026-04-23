#include "dxgi/DXGIInspector.h"

namespace dxgi {

    SwapChainInfo DXGIInspector::CollectSwapChainInfo(IDXGISwapChain* swChain) {
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

    InteropInfo DXGIInspector::CollectInteropInfo(const char* type, void* input, void* output) {
        InteropInfo info = {};
        info.BridgeType = (type) ? type : "Unknown";
        info.InputPointer = input;
        info.OutputPointer = output;
        info.IsValidChain = (input != nullptr && output != nullptr);

        return info;
    }

} // namespace dxgi