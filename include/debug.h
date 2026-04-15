#pragma once

#include "logger.h"
#include "globals.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <string>
#include <string_view>
#include <charconv>

namespace debug {

#ifdef ENABLE_PROXY_LOGGING

    template<typename... Args>
    inline void log_msg(const char* func_name, Args... args) {
        logger::build_and_log<false>(globals::name, func_name, args...);
    }

    template<typename... Args>
    inline void log_params(const char* func_name, Args... args) {
        logger::build_and_log<true>(globals::name, func_name, args...);
    }

    template<typename... Args>
    inline void log_result(const char* func_name, HRESULT hr, Args... args) {
        char hexbuf[16];
        auto [ptr, ec] = std::to_chars(hexbuf, hexbuf + sizeof(hexbuf), (uint32_t)hr, 16);

        std::string_view status = SUCCEEDED(hr) ? " [OK]" : " [FAILED]";

        log_msg(func_name, "Result: 0x", std::string_view(hexbuf, ptr - hexbuf), status, args...);
    }

    /*
    inline std::string get_time() {
        SYSTEMTIME st;
        GetLocalTime(&st);
        char buf[16];
        sprintf_s(buf, "%02d:%02d:%02d.%03d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        return std::string(buf);
    }

    inline void trace_out(const char* func_name, const std::string& msg) {
        std::stringstream ss;
        ss << "[D3D11_PROXY] [" << get_time() << "] [" << func_name << "] " << msg;
        OutputDebugStringA(ss.str().c_str());
    }

    inline void format_args(std::ostream& os) {
        // do nothing
    }

    template<typename T>
    inline void format_args(std::ostream& os, T value) {
        os << " | " << value;
    }

    template<typename T, typename... Args>
    inline void format_args(std::ostream& os, const char* name, T value, Args... args) {
        os << " " << name << "->" << value;
        format_args(os, args...);
    }

    inline void format_msg(std::ostream& os) {}

    template<typename T, typename... Args>
    inline void format_msg(std::ostream& os, T value, Args... args) {
        os << " " << value;
        format_msg(os, args...);
    }

    template<typename... Args>
    inline void log_msg(const char* func_name, Args... args) {
        std::stringstream ss;
        format_msg(ss, args...);
        ss << "\n";
        trace_out(func_name, ss.str());
    }

    inline void log_api(const char* func_name, HRESULT hr) {
        std::stringstream ss;
        ss << "Result: 0x"
            << std::hex << std::uppercase << std::setw(8) << std::setfill('0')
            << (unsigned int)hr
            << " [" << (SUCCEEDED(hr) ? "OK" : "FAILED") << "]\n";
        trace_out(func_name, ss.str());
    }

    template<typename... Args>
    inline void log_params(const char* func_name, Args... args) {
        std::stringstream ss;
        ss << "(";
        format_args(ss, args...);
        ss << " )\n";
        trace_out(func_name, ss.str());
    }
    */

#endif // ENABLE_PROXY_LOGGING
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

#define LOG_VARS(...) \
        EXPAND(debug::log_params(__FUNCTION__, FOR_EACH(EXPAND_PAIR, __VA_ARGS__)))

#define LOG_RESULT(hr, ...)     debug::log_result(__FUNCTION__, hr, __VA_ARGS__)
#define LOG_MSG(...)            debug::log_msg(__FUNCTION__, __VA_ARGS__)

#else

#define LOG_VARS(hr, ...)
#define LOG_API(hr)
#define LOG_MSG(...)

#endif // ENABLE_PROXY_LOGGING