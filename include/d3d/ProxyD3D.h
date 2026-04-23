#pragma once

#include "d3dcommon.h"
#include <concepts>

template <typename T>
concept IsCOMInterface = std::derived_from<T, IUnknown>;

template <IsCOMInterface T>
class ProxyD3D : public T {
protected:
    T* m_pReal;
    ULONG m_RefCount;

    virtual ~ProxyD3D() {
        if (m_pReal) {
            m_pReal->Release();
            m_pReal = nullptr;
        }
    }

public:
    ProxyD3D(T* pReal) : m_pReal(pReal), m_RefCount(1) {
        if (m_pReal) {
            m_pReal->AddRef();
        }
    }

    // Disable copying (Rule of Three/Five)
    ProxyD3D(const ProxyD3D&) = delete;
    ProxyD3D& operator=(const ProxyD3D&) = delete;

    // --- IUnknown Methods ---
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override {
        // Basic COM logic: if they ask for the interface T or IUnknown, return this proxy
        if (riid == __uuidof(T) || riid == __uuidof(IUnknown)) {
            AddRef();
            *ppvObject = this;
            return S_OK;
        }
        // Otherwise, delegate to the real object (e.g. for private data or other interfaces)
        return m_pReal->QueryInterface(riid, ppvObject);
    }

    virtual ULONG STDMETHODCALLTYPE AddRef() override {
        m_pReal->AddRef();
        return InterlockedIncrement(&m_RefCount);
    }

    virtual ULONG STDMETHODCALLTYPE Release() override {
        m_pReal->Release();
        ULONG count = InterlockedDecrement(&m_RefCount);
        if (count == 0) {
            delete this;
        }
        return count;
    }
};