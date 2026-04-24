#pragma once

#include "d3dcommon.h"
#include <concepts>

namespace d3d {

    template <typename T>
    concept IsCOMInterface = std::derived_from<T, IUnknown>;

} // namespace d3d