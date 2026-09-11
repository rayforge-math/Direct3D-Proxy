#pragma once

#define _DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR

#include "d3d/concepts.h"
#include "d3dcommon.h"
#include <unordered_map>
#include <mutex>

namespace d3d {

    template <IsCOMInterface TInterface, typename TProxy>
    class COMRegistry {
    private:
        static inline std::unordered_map<TInterface*, TProxy*> s_Map;
        static inline std::mutex s_Mutex;

    public:
        static void Register(TInterface* pReal, TProxy* pProxy) {
            if (!pReal || !pProxy) return;
            std::lock_guard<std::mutex> lock(s_Mutex);
            s_Map[pReal] = pProxy;
        }

        static void Unregister(TInterface* pReal) {
            if (!pReal) return;
            std::lock_guard<std::mutex> lock(s_Mutex);
            s_Map.erase(pReal);
        }

        static TProxy* Find(TInterface* pReal) {
            if (!pReal) return nullptr;
            std::lock_guard<std::mutex> lock(s_Mutex);
            auto it = s_Map.find(pReal);
            return (it != s_Map.end()) ? it->second : nullptr;
        }
    };

} // namespace d3d