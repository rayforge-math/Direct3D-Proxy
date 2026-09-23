#include "dxgi/ProxyDXGIAdapter.h"
//#include "dxgi/ProxyDXGIOutput.h"
#include "dxgi/ProxyDXGIFactory.h"
#include "d3d/ProxyWrapper.h"
#include "logging/debug_dxgi.h"

namespace dxgi {

    ProxyDXGIAdapter::ProxyDXGIAdapter(IDXGIAdapter3* pReal)
        : ProxyD3D<IDXGIAdapter3, ProxyDXGIAdapter>(pReal)
    {
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::QueryInterface(REFIID riid, void** ppvObject)
    {
        if (!ppvObject)
            return E_POINTER;

        *ppvObject = nullptr;

        if (riid == __uuidof(IDXGIObject))
        {
            *ppvObject = static_cast<IDXGIObject*>(this);
            AddRef();
            return S_OK;
        }

        if (riid == __uuidof(IDXGIAdapter) ||
            riid == __uuidof(IDXGIAdapter1) ||
            riid == __uuidof(IDXGIAdapter2) ||
            riid == __uuidof(IDXGIAdapter3))
        {
            *ppvObject = static_cast<IDXGIAdapter3*>(this);
            AddRef();
            return S_OK;
        }

        return d3d::ProxyD3D<IDXGIAdapter3, ProxyDXGIAdapter>::QueryInterface(riid, ppvObject);
    }

    // --- IDXGIObject Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::SetPrivateData(REFGUID Name, UINT DataSize, const void* pData) {
        LOG_MSG("ProxyDXGIAdapter::SetPrivateData called");
        return m_pReal->SetPrivateData(Name, DataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::SetPrivateDataInterface(REFGUID Name, const IUnknown* pUnknown) {
        LOG_MSG("ProxyDXGIAdapter::SetPrivateDataInterface called");
        return m_pReal->SetPrivateDataInterface(Name, pUnknown);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::GetPrivateData(REFGUID Name, UINT* pDataSize, void* pData) {
        LOG_MSG("ProxyDXGIAdapter::GetPrivateData called");
        return m_pReal->GetPrivateData(Name, pDataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::GetParent(REFIID riid, void** ppParent) {
        LOG_MSG("ProxyDXGIAdapter::GetParent called");
        HRESULT hr = m_pReal->GetParent(riid, ppParent);
        if (SUCCEEDED(hr) && ppParent && *ppParent) {
            d3d::ProxyWrapper::Wrap<ProxyDXGIFactory>(reinterpret_cast<ProxyDXGIFactory::InterfaceType**>(ppParent));
        }
        return hr;
    }

    // --- IDXGIAdapter Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::EnumOutputs(UINT Output, IDXGIOutput** ppOutput) {
        LOG_MSG("ProxyDXGIAdapter::EnumOutputs called");
        HRESULT hr = m_pReal->EnumOutputs(Output, ppOutput);
        if (SUCCEEDED(hr) && ppOutput && *ppOutput) {
            // d3d::ProxyWrapper::Wrap<ProxyDXGIOutput>(ppOutput);
        }
        return hr;
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::GetDesc(DXGI_ADAPTER_DESC* pDesc) {
        LOG_MSG("ProxyDXGIAdapter::GetDesc called");
        return m_pReal->GetDesc(pDesc);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::CheckInterfaceSupport(REFGUID InterfaceName, LARGE_INTEGER* pUMDVersion) {
        LOG_MSG("ProxyDXGIAdapter::CheckInterfaceSupport called");
        return m_pReal->CheckInterfaceSupport(InterfaceName, pUMDVersion);
    }

    // --- IDXGIAdapter1 Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::GetDesc1(DXGI_ADAPTER_DESC1* pDesc) {
        LOG_MSG("ProxyDXGIAdapter::GetDesc1 called");
        return m_pReal->GetDesc1(pDesc);
    }

    // --- IDXGIAdapter2 Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::GetDesc2(DXGI_ADAPTER_DESC2* pDesc) {
        LOG_MSG("ProxyDXGIAdapter::GetDesc2 called");
        return m_pReal->GetDesc2(pDesc);
    }

    // --- IDXGIAdapter3 Methods ---

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::RegisterHardwareContentProtectionTeardownStatusEvent(HANDLE hEvent, DWORD* pdwCookie) {
        LOG_MSG("ProxyDXGIAdapter::RegisterHardwareContentProtectionTeardownStatusEvent called");
        return m_pReal->RegisterHardwareContentProtectionTeardownStatusEvent(hEvent, pdwCookie);
    }

    void STDMETHODCALLTYPE ProxyDXGIAdapter::UnregisterHardwareContentProtectionTeardownStatus(DWORD dwCookie) {
        LOG_MSG("ProxyDXGIAdapter::UnregisterHardwareContentProtectionTeardownStatus called");
        m_pReal->UnregisterHardwareContentProtectionTeardownStatus(dwCookie);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::QueryVideoMemoryInfo(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, DXGI_QUERY_VIDEO_MEMORY_INFO* pVideoMemoryInfo) {
        LOG_MSG("ProxyDXGIAdapter::QueryVideoMemoryInfo called");
        return m_pReal->QueryVideoMemoryInfo(NodeIndex, MemorySegmentGroup, pVideoMemoryInfo);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::SetVideoMemoryReservation(UINT NodeIndex, DXGI_MEMORY_SEGMENT_GROUP MemorySegmentGroup, UINT64 Reservation) {
        LOG_MSG("ProxyDXGIAdapter::SetVideoMemoryReservation called");
        return m_pReal->SetVideoMemoryReservation(NodeIndex, MemorySegmentGroup, Reservation);
    }

    HRESULT STDMETHODCALLTYPE ProxyDXGIAdapter::RegisterVideoMemoryBudgetChangeNotificationEvent(HANDLE hEvent, DWORD* pdwCookie) {
        LOG_MSG("ProxyDXGIAdapter::RegisterVideoMemoryBudgetChangeNotificationEvent called");
        return m_pReal->RegisterVideoMemoryBudgetChangeNotificationEvent(hEvent, pdwCookie);
    }

    void STDMETHODCALLTYPE ProxyDXGIAdapter::UnregisterVideoMemoryBudgetChangeNotification(DWORD dwCookie) {
        LOG_MSG("ProxyDXGIAdapter::UnregisterVideoMemoryBudgetChangeNotification called");
        m_pReal->UnregisterVideoMemoryBudgetChangeNotification(dwCookie);
    }

} // namespace dxgi