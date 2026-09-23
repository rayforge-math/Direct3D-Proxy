#pragma once

#include <unknwn.h>
#include <type_traits>
#include "coreapi.h"

namespace d3d {
    
    class __declspec(uuid("2885e949-41bb-4274-bf11-ddfb09a8e1f9")) CORE_API IProxy {
    public:
        virtual ~IProxy() = default;
        virtual IUnknown* GetRealUnknown() const noexcept = 0;
    };
}