#pragma once

#define _DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR

#include "d3dcommon.h"
#include <unordered_map>
#include <mutex>

namespace com {

    template <typename TProxy>
    class COMRegistry {
    private:
        static inline std::unordered_map<IUnknown*, TProxy*> s_Map;
        static inline std::mutex s_Mutex;

    public:
        static void Register(IUnknown* pReal, TProxy* pProxy) {
            if (!pReal || !pProxy) return;
            std::lock_guard<std::mutex> lock(s_Mutex);
            s_Map[pReal] = pProxy;
        }

        static void Unregister(IUnknown* pReal) {
            if (!pReal) return;
            std::lock_guard<std::mutex> lock(s_Mutex);
            s_Map.erase(pReal);
        }

        static TProxy* Find(IUnknown* pReal) {
            if (!pReal) return nullptr;
            std::lock_guard<std::mutex> lock(s_Mutex);
            auto it = s_Map.find(pReal);
            return (it != s_Map.end()) ? it->second : nullptr;
        }
    };

} // namespace com