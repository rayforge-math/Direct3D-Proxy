#pragma once

#define _DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR
#include <unordered_map>
#include <mutex>
#include <unknwn.h>

namespace dll {

    class COMRegistry {
    public:
        // Registers any proxy instance associated with a real COM object
        static void Register(IUnknown* pReal, IUnknown* pProxy) {
            if (!pReal || !pProxy) return;

            IUnknown* pCanonicalKey = GetCanonicalUnknown(pReal);
            if (!pCanonicalKey) return;

            std::lock_guard<std::mutex> lock(s_Mutex);
            s_Map[pCanonicalKey] = pProxy;

            pCanonicalKey->Release();
        }

        // Unregisters the proxy when it gets destroyed
        static void Unregister(IUnknown* pReal) {
            if (!pReal) return;

            IUnknown* pCanonicalKey = GetCanonicalUnknown(pReal);
            if (!pCanonicalKey) return;

            std::lock_guard<std::mutex> lock(s_Mutex);
            s_Map.erase(pCanonicalKey);

            pCanonicalKey->Release();
        }

        template <typename TProxy>
        static TProxy* Find(IUnknown* pReal) {
            if (!pReal) return nullptr;

            IUnknown* pCanonicalKey = GetCanonicalUnknown(pReal);
            if (!pCanonicalKey) return nullptr;

            std::lock_guard<std::mutex> lock(s_Mutex);

            TProxy* pFound = nullptr;
            auto it = s_Map.find(pCanonicalKey);
            if (it != s_Map.end()) {
                pFound = static_cast<TProxy*>(it->second);
            }

            pCanonicalKey->Release();
            return pFound;
        }

    private:
        static IUnknown* GetCanonicalUnknown(IUnknown* pObj) {
            IUnknown* pUnknown = nullptr;
            HRESULT hr = pObj->QueryInterface(__uuidof(IUnknown), reinterpret_cast<void**>(&pUnknown));
            if (FAILED(hr)) return nullptr;
            return pUnknown;
        }

        inline static std::unordered_map<IUnknown*, IUnknown*> s_Map;
        inline static std::mutex s_Mutex;
    };

} // namespace dll