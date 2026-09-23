#pragma once

#include "COMRegistry.h"
#include "d3dcommon.h"
#include <unknwn.h>
#include "logging/debug_core.h"
#include "IProxy.h"

namespace d3d {

    template <typename T>
    concept IsCOMObject = std::is_base_of_v<IUnknown, T>;

    template <typename TDerived, IsCOMObject T, IsCOMObject... TAdditional>
    class ProxyD3D : public T, public TAdditional..., public IProxy {
    public:
        using InterfaceType = T;
        using ProxyBase = ProxyD3D<TDerived, T, TAdditional...>;

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
        IUnknown* GetRealUnknown() const noexcept { return m_pReal; }

        // --- IUnknown ---

        virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override {
            if (!ppvObject) return E_POINTER;

            if (riid == __uuidof(IUnknown)) {
                AddRef();
                *ppvObject = static_cast<IUnknown*>(static_cast<InterfaceType*>(this));
                return S_OK;
            }

            if (riid == __uuidof(InterfaceType)) {
                AddRef();
                *ppvObject = static_cast<InterfaceType*>(this);
                return S_OK;
            }

            if (riid == __uuidof(IProxy)) {
                AddRef();
                *ppvObject = dynamic_cast<IProxy*>(this);
                return S_OK;
            }

            char iidString[39]{};
            std::snprintf(
                iidString, sizeof(iidString),
                "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
                static_cast<unsigned int>(riid.Data1),
                static_cast<unsigned int>(riid.Data2),
                static_cast<unsigned int>(riid.Data3),
                static_cast<unsigned int>(riid.Data4[0]),
                static_cast<unsigned int>(riid.Data4[1]),
                static_cast<unsigned int>(riid.Data4[2]),
                static_cast<unsigned int>(riid.Data4[3]),
                static_cast<unsigned int>(riid.Data4[4]),
                static_cast<unsigned int>(riid.Data4[5]),
                static_cast<unsigned int>(riid.Data4[6]),
                static_cast<unsigned int>(riid.Data4[7])
            );

            auto hr = m_pReal->QueryInterface(riid, ppvObject);
            if (SUCCEEDED(hr)) {
                LOG_MSG("QueryInterface called with unknown IID, returning real pointer (IID: ", iidString, ")");
            }
            else {
                LOG_MSG("QueryInterface called with unknown IID, returning E_NOINTERFACE (IID: ", iidString, ")");
            }

            return hr;
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
        typename TProxy::ProxyBase;
    }&& std::derived_from<TProxy, typename TProxy::ProxyBase>;

    template <typename TProxy, typename TResource>
    concept IsProxyFor =
        IsProxy<TProxy> &&
        std::same_as<typename TProxy::InterfaceType, TResource>;

} // namespace d3d