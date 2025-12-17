#pragma once

#include <iostream>
#include <string>

namespace dbg {
    using namespace std;

    inline int indent_lvl = 0;
    inline string get_indent() { return string(2 * indent_lvl, ' '); }
} // namespace dbg

#include "info.hpp"

namespace dbg {
    namespace _detail {
        struct src_loc {
            string file_name;
            int line;
            string func_name;
        };

        template<typename... Args>
        string fmt(Args &&...args) {
            if constexpr (sizeof...(Args) == 0) {
                return "";
            } else {
                vector<string> parts = {dbg_info(args)...};
                string result;
                for (size_t i = 0; i < parts.size(); ++i) {
                    if (i > 0) result += ", ";
                    result += parts[i];
                }
                return result;
            }
        }
    }; // namespace _detail

    template<typename... Args>
    void dbg_impl(_detail::src_loc loc, string args_str, Args &&...args) {
        const string label =
            "[\e[33m" + loc.func_name + "\e[0m:" + to_string(loc.line) + "]";

        string vals = _detail::fmt(args...);

        const string output = label + " " +
            (sizeof...(args) > 1 ? "[" + args_str + "]" : args_str) + " = " +
            (sizeof...(args) > 1 ? "[" + vals + "]" : vals);

        cerr << output << "\n";
    }
} // namespace dbg

#define dbg(a...) dbg::dbg_impl({__FILE__, __LINE__, __func__}, #a, a)
#define debug()
