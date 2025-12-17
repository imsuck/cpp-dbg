#pragma once

#include <algorithm>
#include <sstream>
#include <string>

#include "info_fwd.hpp"
#include "type_check.hpp"

namespace dbg {
    using namespace std;
    namespace _detail {
        template<
            typename T,
            enable_if_t<!is_floating_point_v<remove_cvref_t<T>>, int> = 1>
        inline string dbg_arithmetic(T n) {
            const bool neg = n < 0;
            _detail::make_unsigned_t<remove_cvref_t<T>> x = n;
            if (neg) x = -x;
            string output;
            while (x != 0) {
                output += char(x % 10 + '0');
                x /= 10;
            }
            if (neg) output += '-';
            reverse(output.begin(), output.end());
            if (output.empty()) output = "0";
            return output;
        }
        template<
            typename T,
            enable_if_t<is_floating_point_v<remove_cvref_t<T>>, int> = 1>
        inline string dbg_arithmetic(T x) {
            return to_string(x);
        }
        inline string dbg_bool(bool b) { return b ? "true" : "false"; }
        inline string dbg_char(char c) { return "'" + string(1, c) + "'"; }

        template<typename T, enable_if_t<is_string<T>, int> = 1>
        inline string dbg_string(T str) {
            return '"' + string(str) + '"';
        }

        template<typename T, typename U>
        inline string dbg_pair(const pair<T, U> &p) {
            return "(" + dbg_info(p.first) + ", " + dbg_info(p.second) + ")";
        }

        template<typename... Ts>
        inline string dbg_tuple(const tuple<Ts...> &t) {
            if constexpr (sizeof...(Ts) == 0) {
                return "()";
            } else {
                string result = "(";
                size_t i = 0;
                ((result += (i++ > 0 ? ", " : "") + dbg_info(get<Ts>(t))), ...);
                return result + ")";
            }
        }

        template<typename T> inline string dbg_streamable(T &&x) {
            stringstream ss;
            ss << x;
            return ss.str();
        }
    } // namespace _detail
} // namespace dbg
