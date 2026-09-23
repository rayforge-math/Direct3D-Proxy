#pragma once

#include "debug.h"
#include "globals.h"

#define LOG_VARS(...)			LOG_VARS_INTERNAL(globals::name_d3d11_proxy, __VA_ARGS__)
#define LOG_RESULT(hr, ...)     LOG_RESULT_INTERNAL(globals::name_d3d11_proxy, hr, __VA_ARGS__)
#define LOG_MSG(...)			LOG_MSG_INTERNAL(globals::name_d3d11_proxy, __VA_ARGS__)