#pragma once

#include <windows.h>

namespace dll {

    typedef BOOL(entry_point_t)(HMODULE, LPVOID);

} // namespace dll