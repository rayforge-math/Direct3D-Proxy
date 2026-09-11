#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

namespace dll {

    typedef BOOL(entry_point_t)(HMODULE, LPVOID);

} // namespace dll