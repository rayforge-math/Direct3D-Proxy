#pragma once

#include "coreapi.h"
#include "d3d/ProxyD3D.h"
#include "dxgi_version.h"

namespace dxgi {

    /**
     * @class ProxyDXGIAdapter3
     * @brief A virtualization wrapper for the IDXGIAdapter3 interface, covering DXGI 1.4 adapter features.
     *
     * @details
     * Inheriting from `IDXGIAdapter3` ensures backward compatibility with all older adapter versions
     * (IDXGIAdapter, IDXGIAdapter1, IDXGIAdapter2) while providing access to advanced features
     * such as memory budget tracking and query methods.
     */
    class CORE_API ProxyDXGIAdapter : public d3d::ProxyD3D<IDXGIAdapter3, ProxyDXGIAdapter> {
    public:
        explicit ProxyDXGIAdapter(IDXGIAdapter3* pReal);

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override;

        // --- IDXGIObject Methods ---
        virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID Name, UINT DataSize, const void* pData) override;
        virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown) override;
        virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData) override;
        virtual HRESULT STDMETHODCALLTYPE GetParent(REFIID riid, void** ppParent) override;

        // --- IDXGIAdapter Methods ---
        virtual HRESULT STDMETHODCALLTYPE EnumOutputs(UINT Output, IDXGIOutput** ppOutput) override;
        virtual HRESULT STDMETHODCALLTYPE GetDesc(DXGI_ADAPTER_DESC* pDesc) override;
        virtual HRESULT STDMETHODCALLTYPE CheckInterfaceSupport(REFGUID InterfaceName, LARGE_INTEGER* pUMDVersion) override;

        // --- IDXGIAdapter1 Methods ---
        virtual HRESULT STDMETHODCALLTYPE GetDesc1(DXGI_ADAPTER_DESC1* pDesc) override;

        // --- IDXGIAdapter2 Methods ---
        virtual HRESULT STDMETHODCALLTYPE GetDesc2(DXGI_ADAPTER_DESC2* pDesc) override;

        // --- IDXGIAdapter3 Methods ---
        virtual HRESULT STDMETHODCALLTYPE RegisterHardwareContentProtectionTeardownStatusEvent(HANDLE hEvent, DWORD* pdwCookie) override;
        virtual void STDMETHODCALLTYPE UnregisterHardwareContentProtectionTeardownStatus(DWORD dwCookie) override;
        virtual HRESULT STDMETHODCALLTYPE QueryVideoMemoryInfo(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, DXGI_QUERY_VIDEO_MEMORY_INFO* pVideoMemoryInfo) override;
        virtual HRESULT STDMETHODCALLTYPE SetVideoMemoryReservation(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, UINT64 Reservation) override;
        virtual HRESULT STDMETHODCALLTYPE RegisterVideoMemoryBudgetChangeNotificationEvent(HANDLE hEvent, DWORD* pdwCookie) override;
        virtual void STDMETHODCALLTYPE UnregisterVideoMemoryBudgetChangeNotification(DWORD dwCookie) override;
    };

} // namespace dxgi