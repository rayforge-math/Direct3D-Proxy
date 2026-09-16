#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <string>
#include <string_view>
#include <type_traits>
#include <charconv>
#include <cstdio>
#include <cstdint>

namespace logger {

    namespace constants {
        static constexpr std::string_view null_ptr = "nullptr";
        static constexpr std::string_view bool_true = "true";
        static constexpr std::string_view bool_false = "false";
        static constexpr std::string_view fallback = "<?>";

        static constexpr size_t time_len = 12; // "HH:MM:SS.mmm"
        static constexpr std::string_view prefix_begin = "[";
        static constexpr std::string_view prefix_end = "]";
        static constexpr std::string_view separator = " ";
        static constexpr std::string_view param_open = "( ";
        static constexpr std::string_view param_close = " )\n";
        static constexpr std::string_view param_sep = "->";
        static constexpr std::string_view msg_end = "\n";
    }

    namespace max_len {
        static constexpr size_t null_ptr = constants::null_ptr.size();
        static constexpr size_t boolean = constants::bool_false.size();

        static constexpr size_t int8 = 4;       // "-128"
        static constexpr size_t uint8 = 3;      // "255"
        static constexpr size_t int16 = 6;      // "-32768"
        static constexpr size_t uint16 = 5;     // "65535"
        static constexpr size_t int32 = 11;     // "-2147483648"
        static constexpr size_t uint32 = 10;    // "4294967295"
        static constexpr size_t int64 = 21;     // "-9223372036854775808"
        static constexpr size_t uint64 = 20;    // "18446744073709551615"
        static constexpr size_t fp = 32;        // Float/Double (inkl. e+308)
        static constexpr size_t ptr = 18;       // "0x" + 16 hex chars
        static constexpr size_t fallback = constants::fallback.size();
    }

    template<typename T>
    constexpr size_t get_max_buffer_size(const T& arg) {
        using Type = std::remove_cvref_t<T>;

        if constexpr (std::is_same_v<Type, std::string> || std::is_same_v<Type, std::string_view>) {
            return arg.size();
        }
        else if constexpr (std::is_convertible_v<Type, const char*>) {
            if constexpr (std::is_pointer_v<Type>) {
                if (arg == nullptr) return max_len::null_ptr;
            }
            return std::char_traits<char>::length(arg);
        }

        else if constexpr (std::is_pointer_v<Type> || std::is_null_pointer_v<Type>) {
            if constexpr (std::is_null_pointer_v<Type>) return max_len::null_ptr;
            return max_len::ptr;
        }

        else if constexpr (std::is_integral_v<Type>) {
            if constexpr (std::is_same_v<Type, bool>) return max_len::boolean;

            constexpr bool is_signed = std::is_signed_v<Type>;

            if constexpr (sizeof(Type) == 1) return is_signed ? max_len::int8 : max_len::uint8;
            if constexpr (sizeof(Type) == 2) return is_signed ? max_len::int16 : max_len::uint16;
            if constexpr (sizeof(Type) == 4) return is_signed ? max_len::int32 : max_len::uint32;
            if constexpr (sizeof(Type) == 8) return is_signed ? max_len::int64 : max_len::uint64;

            return max_len::int32;
        }

        else if constexpr (std::is_floating_point_v<Type>) {
            return max_len::fp;
        }

        return max_len::fallback;
    }

    template<typename T>
    void append_arg(std::string& buf, const T& arg) {
        using Type = std::remove_cvref_t<T>;

        if constexpr (std::is_convertible_v<Type, std::string_view>) {
            buf.append(arg);
        }
        else if constexpr (std::is_pointer_v<Type> || std::is_null_pointer_v<Type>) {
            if (arg == nullptr) {
                buf.append(constants::null_ptr);
            }
            else {
                char pbuf[max_len::ptr];
                int len = snprintf(pbuf, sizeof(pbuf), "%p", (void*)arg);
                buf.append(pbuf, len);
            }
        }
        else if constexpr (std::is_integral_v<Type>) {
            if constexpr (std::is_same_v<Type, bool>) {
                buf.append(arg ? constants::bool_true : constants::bool_false);
            }
            else {
                char nbuf[max_len::int64];

                auto [ptr, ec] = std::to_chars(nbuf, nbuf + sizeof(nbuf), arg);
                if (ec == std::errc()) {
                    buf.append(nbuf, ptr - nbuf);
                }
            }
        }
        else if constexpr (std::is_floating_point_v<Type>) {
            char fbuf[max_len::fp];

            auto [ptr, ec] = std::to_chars(fbuf, fbuf + sizeof(fbuf), arg);
            if (ec == std::errc()) {
                buf.append(fbuf, ptr - fbuf);
            }
            else {
                buf.append(constants::fallback);
            }
        }
        else {
            buf.append(constants::fallback);
        }
    }

    constexpr size_t size_time(std::string_view open, std::string_view close, std::string_view sep) {
        return open.size() + constants::time_len + close.size() + sep.size();
    }

    inline void append_time(std::string& buf, std::string_view open, std::string_view close, std::string_view sep) {
        SYSTEMTIME st;
        GetLocalTime(&st);
        char tbuf[16];
        int len = snprintf(tbuf, sizeof(tbuf), "%02d:%02d:%02d.%03d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        buf.append(open);
        buf.append(tbuf, len);
        buf.append(close);
        buf.append(sep);
    }

    constexpr size_t size_wrapped(std::string_view content, std::string_view open, std::string_view close, std::string_view sep) {
        return open.size() + content.size() + close.size() + sep.size();
    }

    inline void append_wrapped(std::string& buf, std::string_view open, std::string_view content, std::string_view close, std::string_view sep) {
        buf.append(open);
        buf.append(content);
        buf.append(close);
        buf.append(sep);
    }

    constexpr size_t size_header(std::string_view prefix, const char* func_name, std::string_view open, std::string_view close, std::string_view sep) {
        size_t s = 0;
        s += size_wrapped(prefix, open, close, sep);
        s += size_time(open, close, sep);
        s += size_wrapped(func_name ? func_name : "", open, close, sep);
        return s;
    }

    inline void append_header(std::string& buf, std::string_view prefix, const char* func_name,
        std::string_view open, std::string_view close, std::string_view sep) {
        append_wrapped(buf, open, prefix, close, sep);
        append_time(buf, open, close, sep);
        append_wrapped(buf, open, func_name ? func_name : "", close, sep);
    }

    template<typename... Args>
    constexpr size_t size_params_block(std::string_view open, std::string_view close, std::string_view p_sep, std::string_view g_sep, Args... args) {
        size_t s = open.size() + close.size();
        if constexpr (sizeof...(args) > 0) {
            s += (sizeof...(args) / 2) * p_sep.size();
            s += ((sizeof...(args) - 1) / 2) * g_sep.size();
        }
        return s;
    }

    template<typename... Args>
    void append_params_block(std::string& buf, std::string_view open, std::string_view close, std::string_view p_sep, std::string_view g_sep, Args... args) {
        buf.append(open);
        size_t i = 0;
        ((
            append_arg(buf, args),
            i++,
            buf.append(i < sizeof...(args) ? (i % 2 == 0 ? g_sep : p_sep) : "")
            ), ...);
        buf.append(close);
    }

    template<typename... Args>
    constexpr size_t size_messages_block(std::string_view sep, std::string_view end, Args... args) {
        size_t s = end.size();
        if constexpr (sizeof...(args) > 0) {
            s += (sizeof...(args) - 1) * sep.size();
        }
        return s;
    }

    template<typename... Args>
    void append_messages_block(std::string& buf, std::string_view sep, std::string_view end, Args... args) {
        size_t i = 0;
        ((
            append_arg(buf, args),
            buf.append(++i < sizeof...(args) ? sep : "")
            ), ...);
        buf.append(end);
    }

    template<bool IsParams, typename... Args>
    void build_and_log(const std::string_view prefix, const char* func_name, Args... args) {
        using namespace constants;

        size_t payload_size = (get_max_buffer_size(args) + ...);

        size_t header_size = size_header(prefix, func_name, prefix_begin, prefix_end, separator);

        size_t struct_size = 0;
        if constexpr (IsParams) {
            struct_size = size_params_block(param_open, param_close, param_sep, separator, args...);
        }
        else {
            struct_size = size_messages_block(separator, msg_end, args...);
        }

        static thread_local std::string buf;
        buf.clear();
        buf.reserve(header_size + payload_size + struct_size + 1);

        append_header(buf, prefix, func_name, prefix_begin, prefix_end, separator);

        if constexpr (IsParams) {
            append_params_block(buf, param_open, param_close, param_sep, separator, args...);
        }
        else {
            append_messages_block(buf, separator, msg_end, args...);
        }

        OutputDebugStringA(buf.c_str());
    }

} // logger