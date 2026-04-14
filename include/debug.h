#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace debug {

#ifdef ENABLE_PROXY_LOGGING

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
        char buffer[256];
        sprintf_s(buffer, "Result: 0x%08X [%s]\n",
            (unsigned int)hr, SUCCEEDED(hr) ? "OK" : "FAILED");
        trace_out(func_name, buffer);
    }

    template<typename... Args>
    inline void log_params(const char* func_name, HRESULT hr, Args... args) {
        std::stringstream ss;
        ss << "(";
        format_args(ss, args...);
        ss << " ) | Result: 0x" << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << (unsigned int)hr << "\n";
        trace_out(func_name, ss.str());
    }

#endif // ENABLE_PROXY_LOGGING

} // debug

#ifdef ENABLE_PROXY_LOGGING

    #define EXPAND(x) x

    #define V1(v1) #v1, v1
    #define V2(v1, v2) #v1, v1, #v2, v2
    #define V3(v1, v2, v3) #v1, v1, #v2, v2, #v3, v3
    #define V4(v1, v2, v3, v4) #v1, v1, #v2, v2, #v3, v3, #v4, v4
    #define V5(v1, v2, v3, v4, v5) #v1, v1, #v2, v2, #v3, v3, #v4, v4, #v5, v5
    #define V6(v1, v2, v3, v4, v5, v6) #v1, v1, #v2, v2, #v3, v3, #v4, v4, #v5, v5, #v6, v6
    #define V7(v1, v2, v3, v4, v5, v6, v7) #v1, v1, #v2, v2, #v3, v3, #v4, v4, #v5, v5, #v6, v6, #v7, v7
    #define V8(v1, v2, v3, v4, v5, v6, v7, v8) #v1, v1, #v2, v2, #v3, v3, #v4, v4, #v5, v5, #v6, v6, #v7, v7, #v8, v8
    #define V9(v1, v2, v3, v4, v5, v6, v7, v8, v9) #v1, v1, #v2, v2, #v3, v3, #v4, v4, #v5, v5, #v6, v6, #v7, v7, #v8, v8, #v9, v9
    #define V10(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) #v1, v1, #v2, v2, #v3, v3, #v4, v4, #v5, v5, #v6, v6, #v7, v7, #v8, v8, #v9, v9, #v10, v10

    #define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,NAME,...) NAME

    #define LOG_VARS(hr, ...) \
            EXPAND(debug::log_params(__FUNCTION__, hr, \
                EXPAND(GET_MACRO(__VA_ARGS__, V10, V9, V8, V7, V6, V5, V4, V3, V2, V1)(__VA_ARGS__))))

    #define LOG_RESULT(hr)  debug::log_api(__FUNCTION__, hr)
    #define LOG_MSG(...)    debug::log_msg(__FUNCTION__, __VA_ARGS__)

#else

    #define LOG_VARS(hr, ...)
    #define LOG_API(hr)
    #define LOG_MSG(...)

#endif // ENABLE_PROXY_LOGGING