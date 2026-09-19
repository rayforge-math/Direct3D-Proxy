#pragma once

#include "COMRegistry.h"
#include "d3dcommon.h"
#include <unknwn.h>

namespace d3d {

    template <typename T>
    concept IsCOMObject = std::is_base_of_v<IUnknown, T>;

    template <IsCOMObject T, typename TDerived>
    class ProxyD3D : public T {
    public:
        using InterfaceType = T;

    protected:
        InterfaceType* m_pReal;
        LONG m_RefCount;

        /**
         * @brief Destructor called when m_RefCount reaches zero.
         */
        virtual ~ProxyD3D() noexcept {
            if (m_pReal) {
                dll::COMRegistry::Unregister(m_pReal);

                InterfaceType* pReal = m_pReal;
                m_pReal = nullptr;
                pReal->Release();
            }
        }

    public:
        /**
         * @brief Constructor: Takes ownership of the provided pointer.
         */
        explicit ProxyD3D(InterfaceType* pReal) : m_pReal(pReal), m_RefCount(1) {
            dll::COMRegistry::Register(m_pReal, static_cast<TDerived*>(this));
        }

        // Non-copyable, non-movable (Rule of Five)
        ProxyD3D(const ProxyD3D&) = delete;
        ProxyD3D& operator=(const ProxyD3D&) = delete;
        ProxyD3D(ProxyD3D&&) = delete;
        ProxyD3D& operator=(ProxyD3D&&) = delete;

        // Accessor for the real underlying object
        InterfaceType* GetReal() const noexcept { return m_pReal; }

        // --- IUnknown ---

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override {
            if (!ppvObject) return E_POINTER;

            if (riid == __uuidof(InterfaceType) || riid == __uuidof(IUnknown)) {
                AddRef();
                *ppvObject = this;
                return S_OK;
            }

            return m_pReal->QueryInterface(riid, ppvObject);
        }

        virtual ULONG STDMETHODCALLTYPE AddRef() override {
            return static_cast<ULONG>(InterlockedIncrement(&m_RefCount));
        }

        virtual ULONG STDMETHODCALLTYPE Release() override {
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