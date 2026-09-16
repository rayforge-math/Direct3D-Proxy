#pragma once

#include "d3dcommon.h"
#include <concepts>

namespace com {

    template <typename T>
    concept IsCOMInterface = std::derived_from<T, IUnknown>;

} // namespace com