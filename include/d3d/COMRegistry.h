#pragma once

#define _DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR

#include "d3dcommon.h"
#include <unordered_map>
#include <mutex>

namespace d3d {

    template <typename TValue>
    class COMRegistry {
    private:
        static inline std::unordered_map<IUnknown*, TValue*> s_Map;
        static inline std::mutex s_Mutex;

    public:
        static void Register(IUnknown* pReal, TValue* pProxy) {
            if (!pReal || !pProxy) return;
            std::lock_guard<std::mutex> lock(s_Mutex);
            s_Map[pReal] = pProxy;
        }

        static void Unregister(IUnknown* pReal) {
            if (!pReal) return;
            std::lock_guard<std::mutex> lock(s_Mutex);
            s_Map.erase(pReal);
        }

        static TValue* Find(IUnknown* pReal) {
            if (!pReal) return nullptr;
            std::lock_guard<std::mutex> lock(s_Mutex);
            auto& map = s_Map;
            auto it = map.find(pReal);
            return (it != map.end()) ? it->second : nullptr;
        }
    };

} // namespace d3d