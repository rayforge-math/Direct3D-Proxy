#pragma once

#include "d3d/concepts.h"
#include "d3d/ProxyD3D.h"
#include "d3dcommon.h"
#include <unordered_map>
#include <mutex>

namespace d3d {

    template <IsCOMInterface TResource, IsProxyFor<TResource> TProxy>
    class ProxyRegistry {
    private:
        // One map per resource/proxy pair
        static inline std::unordered_map<TResource*, TProxy*> m_Map;
        static inline std::mutex m_Mutex;

    public:
        // Registers a proxy-resource pair
        static void Register(TResource* pReal, TProxy* pProxy) {
            std::lock_guard<std::mutex> lock(m_Mutex);
            m_Map[pReal] = pProxy;
        }

        // Removes the pair (call this in the Proxy destructor)
        static void Unregister(TResource* pReal) {
            std::lock_guard<std::mutex> lock(m_Mutex);
            m_Map.erase(pReal);
        }

        // Finds an existing proxy for a real resource pointer
        static TProxy* Find(TResource* pReal) {
            std::lock_guard<std::mutex> lock(m_Mutex);
            auto it = m_Map.find(pReal);
            return (it != m_Map.end()) ? it->second : nullptr;
        }

        // Access for the Inspector UI
        static const auto& GetMap() { return m_Map; }
    };

} // namespace d3d