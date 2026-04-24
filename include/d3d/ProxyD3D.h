#pragma once

#include "d3d/COMRegistry.h"
#include "d3d/concepts.h"
#include "d3dcommon.h"
#include <concepts>

namespace d3d {

    template <IsCOMInterface T>
    class ProxyD3D : public T {
    public:
        using InterfaceType = T;

    protected:
        InterfaceType* m_pReal;
        ULONG m_RefCount;

        /**
         * Destructor is only called when our local m_RefCount reaches zero.
         * This is the final point where we release the underlying real object.
         */
        virtual ~ProxyD3D() {
            if (m_pReal) {
                COMRegistry<ProxyD3D<InterfaceType>>::Unregister(m_pReal);
                m_pReal->Release();
                m_pReal = nullptr;
            }
        }

    public:
        /**
         * Constructor: Ownership Strategy.
         * We increment the real object's count once to ensure it lives as long as this proxy.
         */
        ProxyD3D(InterfaceType* pReal) : m_pReal(pReal), m_RefCount(1)
        {
            if (m_pReal) {
                COMRegistry<ProxyD3D<InterfaceType>>::Register(m_pReal, this);
            }
        }

        // Accessor for the real object (needed for unwrapping in the Context)
        InterfaceType* GetReal() const { return m_pReal; }

        // Disable copying (Rule of Three/Five)
        ProxyD3D(const ProxyD3D&) = delete;
        ProxyD3D& operator=(const ProxyD3D&) = delete;

        // --- IUnknown Methods ---
        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override {
            if (!ppvObject) return E_POINTER;
            // Basic COM logic: if they ask for the interface InterfaceType or IUnknown, return this proxy
            if (riid == __uuidof(InterfaceType) || riid == __uuidof(IUnknown)) {
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
            if (count == 0) {
                delete this;
            }
            return count;
        }
    };

    template<typename TProxy, typename TResource>
    concept IsProxyFor = std::derived_from<TProxy, ProxyD3D<TResource>>;

} // namespace d3d