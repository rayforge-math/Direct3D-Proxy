#pragma once

#include "d3d/COMRegistry.h"
#include "d3d/concepts.h"
#include "d3dcommon.h"
#include <concepts>

namespace d3d {

    template <IsCOMInterface T, typename TDerived>
    class ProxyD3D : public T {
    public:
        using InterfaceType = T;

    protected:
        InterfaceType* m_pReal;
        LONG m_RefCount;

        /**
         * Destructor is only called when m_RefCount reaches zero.
         * Ownership was taken in the constructor — this releases the one and only reference.
         */
        virtual ~ProxyD3D() noexcept {
            if (m_pReal) {
                COMRegistry<InterfaceType, TDerived>::Unregister(m_pReal);
                InterfaceType* pReal = m_pReal;
                m_pReal = nullptr;
                pReal->Release();
            }
        }

    public:
        /**
         * Constructor: Takes exclusive ownership of the provided pointer.
         * The caller must not call Release on it after this point.
         * No AddRef — we inherit the existing reference.
         */
        explicit ProxyD3D(InterfaceType* pReal) : m_pReal(pReal), m_RefCount(1)
        {
            COMRegistry<InterfaceType, TDerived>::Register(m_pReal, static_cast<TDerived*>(this));
        }

        // Non-copyable, non-movable (Rule of Five)
        ProxyD3D(const ProxyD3D&) = delete;
        ProxyD3D& operator=(const ProxyD3D&) = delete;
        ProxyD3D(ProxyD3D&&) = delete;
        ProxyD3D& operator=(ProxyD3D&&) = delete;

        // Accessor for the real underlying object (used for unwrapping in the context)
        InterfaceType* GetReal() const noexcept { return m_pReal; }

        // --- IUnknown ---

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override
        {
            if (!ppvObject) return E_POINTER;

            if (riid == __uuidof(InterfaceType) || riid == __uuidof(IUnknown)) {
                AddRef();
                *ppvObject = this;
                return S_OK;
            }

            // NOTE: Delegating here returns a raw pointer, bypassing the proxy.
            // If other interfaces need to be wrapped too, add a registry lookup here.
            return m_pReal->QueryInterface(riid, ppvObject);
        }

        virtual ULONG STDMETHODCALLTYPE AddRef() override
        {
            return static_cast<ULONG>(InterlockedIncrement(&m_RefCount));
        }

        virtual ULONG STDMETHODCALLTYPE Release() override
        {
            LONG count = InterlockedDecrement(&m_RefCount);
            if (count == 0) {
                delete this;
            }
            return static_cast<ULONG>(count);
        }
    };

    template <typename TProxy>
    concept IsProxy = requires {
        typename TProxy::InterfaceType;
    }&& std::derived_from<TProxy, ProxyD3D<typename TProxy::InterfaceType, TProxy>>;

    template <typename TProxy, typename TResource>
    concept IsProxyFor = IsProxy<TProxy>
        && std::same_as<typename TProxy::InterfaceType, TResource>;

} // namespace d3d