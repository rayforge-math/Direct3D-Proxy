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
        static constexpr std::string_view separator = " ";
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

    namespace constants {
        static constexpr size_t time_len = 12; // "HH:MM:SS.mmm"
        static constexpr std::string_view prefix_begin = "[";
        static constexpr std::string_view prefix_end = "]";
    }

    inline void append_time(std::string& buf) {
        SYSTEMTIME st;
        GetLocalTime(&st);
        char tbuf[16];
        int len = snprintf(tbuf, sizeof(tbuf), "%02d:%02d:%02d.%03d",
            st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        buf.append(tbuf, len);
    }

    template<bool IsParams, typename... Args>
    void build_and_log(const std::string_view prefix, const char* func_name, Args... args) {
        // size
        size_t msg_size = (get_max_buffer_size(args) + ...);
        // Header: [D3D11_PROXY] [HH:MM:SS.mmm] [func_name]
        size_t header_size = (constants::prefix_begin.size() * 3) +
            (constants::prefix_end.size() * 3) +
            prefix.size() +
            constants::time_len +
            strlen(func_name) +
            (constants::separator.size() * 2);

        std::string buf;
        buf.reserve(header_size + msg_size + 16); // +16 buffer/newline

        // header
        auto wrap = [&](std::string_view content) {
            buf.append(constants::prefix_begin);
            buf.append(content);
            buf.append(constants::prefix_end);
            buf.append(constants::separator);
            };

        wrap(prefix);

        // time
        buf.append(constants::prefix_begin);
        append_time(buf);
        buf.append(constants::prefix_end);
        buf.append(constants::separator);

        wrap(func_name);

        // content
        if constexpr (IsParams) {
            buf.append("( ");
            size_t i = 0;
            auto append_pair = [&](const auto& arg) {
                append_arg(buf, arg);
                if (++i < sizeof...(args)) {
                    buf.append((i % 2 == 0) ? constants::separator : "->");
                }
                };
            (append_pair(args), ...);
            buf.append(" )\n");
        }
        else {
            // regular msg
            size_t i = 0;
            auto append_with_sep = [&](const auto& arg) {
                append_arg(buf, arg);
                if (++i < sizeof...(args)) buf.append(constants::separator);
                };
            (append_with_sep(args), ...);
            buf.append("\n");
        }

        // output
        OutputDebugStringA(buf.c_str());
    }

} // logger