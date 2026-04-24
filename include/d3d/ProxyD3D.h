#pragma once

#include "d3dcommon.h"
#include <concepts>

namespace d3d {

    template <typename T>
    concept IsCOMInterface = std::derived_from<T, IUnknown>;

    template <IsCOMInterface T>
    class ProxyD3D : public T {
    protected:
        T* m_pReal;
        ULONG m_RefCount;

        /**
         * Destructor is only called when our local m_RefCount reaches zero.
         * This is the final point where we release the underlying real object.
         */
        virtual ~ProxyD3D() {
            if (m_pReal) {
                m_pReal->Release();
                m_pReal = nullptr;
            }
        }

    public:
        /**
         * Constructor: Ownership Strategy.
         * We increment the real object's count once to ensure it lives as long as this proxy.
         */
        ProxyD3D(T* pReal) : m_pReal(pReal), m_RefCount(1) {
            if (m_pReal) {
                m_pReal->AddRef();
            }
        }

        // Accessor for the real object (needed for unwrapping in the Context)
        T* GetReal() const { return m_pReal; }

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
            // We only increment our local proxy counter.
            return InterlockedIncrement(&m_RefCount);
        }

        virtual ULONG STDMETHODCALLTYPE Release() override {
            // We only decrement our local proxy counter.
            ULONG count = InterlockedDecrement(&m_RefCount);

            // This triggers the virtual destructor chain:
            // ~ProxyD3D11Buffer() -> ~ProxyD3D11Resource() -> ~ProxyD3D() -> ~<T>()
            if (count == 0) {
                delete this;
            }

            return count;
        }
    };

} // namespace d3d