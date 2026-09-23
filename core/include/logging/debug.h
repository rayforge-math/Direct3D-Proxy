#pragma once

#include "logger.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <string>
#include <string_view>
#include <charconv>

namespace debug {

    template<typename... Args>
    inline void log_msg(const std::string_view tag, const char* func_name, Args... args) {
        logger::build_and_log<false>(tag, func_name, args...);
    }

    template<typename... Args>
    inline void log_params(const std::string_view tag, const char* func_name, Args... args) {
        logger::build_and_log<true>(tag, func_name, args...);
    }

    template<typename... Args>
    inline void log_result(const std::string_view tag, const char* func_name, HRESULT hr, Args... args) {
        char hexbuf[16];
        auto [ptr, ec] = std::to_chars(hexbuf, hexbuf + sizeof(hexbuf), (uint32_t)hr, 16);

        std::string_view status = SUCCEEDED(hr) ? " [OK]" : " [FAILED]";

        log_msg(tag, func_name, "Result: 0x", std::string_view(hexbuf, ptr - hexbuf), status, args...);
    }

}

#ifdef ENABLE_PROXY_LOGGING

#define EXPAND(x) x

#define FE_1(WHAT, X) WHAT(X)
#define FE_2(WHAT, X, ...) WHAT(X), EXPAND(FE_1(WHAT, __VA_ARGS__))
#define FE_3(WHAT, X, ...) WHAT(X), EXPAND(FE_2(WHAT, __VA_ARGS__))
#define FE_4(WHAT, X, ...) WHAT(X), EXPAND(FE_3(WHAT, __VA_ARGS__))
#define FE_5(WHAT, X, ...) WHAT(X), EXPAND(FE_4(WHAT, __VA_ARGS__))
#define FE_6(WHAT, X, ...) WHAT(X), EXPAND(FE_5(WHAT, __VA_ARGS__))
#define FE_7(WHAT, X, ...) WHAT(X), EXPAND(FE_6(WHAT, __VA_ARGS__))
#define FE_8(WHAT, X, ...) WHAT(X), EXPAND(FE_7(WHAT, __VA_ARGS__))
#define FE_9(WHAT, X, ...) WHAT(X), EXPAND(FE_8(WHAT, __VA_ARGS__))
#define FE_10(WHAT, X, ...) WHAT(X), EXPAND(FE_9(WHAT, __VA_ARGS__))

#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,NAME,...) NAME

#define FOR_EACH(action, ...) \
        EXPAND(GET_MACRO(__VA_ARGS__, FE_10, FE_9, FE_8, FE_7, FE_6, FE_5, FE_4, FE_3, FE_2, FE_1)(action, __VA_ARGS__))

#define EXPAND_PAIR(v) #v, v

#define LOG_VARS_INTERNAL(tag, ...) \
        EXPAND(debug::log_params(tag, __FUNCTION__, FOR_EACH(EXPAND_PAIR, __VA_ARGS__)))
#define LOG_RESULT_INTERNAL(tag, hr, ...)     debug::log_result(tag, __FUNCTION__, hr, __VA_ARGS__)
#define LOG_MSG_INTERNAL(tag, ...)            debug::log_msg(tag, __FUNCTION__, __VA_ARGS__)

#else

#define LOG_VARS_INTERNAL(tag, ...)
#define LOG_RESULT_INTERNAL(tag, hr, ...)
#define LOG_MSG_INTERNAL(tag, ...)

#endif // ENABLE_PROXY_LOGGING