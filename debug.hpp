#line 2 "src/debug.hpp"

#include <iostream>
#include <string>

namespace dbg {
    using namespace std;

    inline int indent_lvl = 0;
    inline string get_indent() { return string(2 * indent_lvl, ' '); }
} // namespace dbg

#line 2 "src/info.hpp"

#line 2 "src/containers.hpp"

#line 2 "src/info_fwd.hpp"

#line 4 "src/info_fwd.hpp"

namespace dbg {
    using namespace std;
    namespace _detail {
        template<typename T> string dbg_info(T &&);
    }
} // namespace dbg

#line 2 "src/iterator.hpp"

namespace dbg {
    namespace _detail {
        template<class T>
        inline auto _iter_begin(T &&x, int) -> decltype(x.begin()) {
            return x.begin();
        }
        template<class T>
        inline auto _iter_begin(T &&x, long) -> decltype(begin(x)) {
            return begin(x);
        }
        template<class T>
        inline auto iter_begin(T &&x) -> decltype(_iter_begin(x, 0)) {
            return _iter_begin(x, 0);
        }
    } // namespace _detail
} // namespace dbg
#line 2 "src/type_check.hpp"

#include <map>
#include <ostream>
#include <queue>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include <vector>

#line 2 "src/options.hpp"

namespace dbg {
    namespace options {
        template<typename = void> inline constexpr bool trivial_string() {
            return false;
        };
    }
}
#line 13 "src/type_check.hpp"

namespace dbg {
    using namespace std;
    namespace _detail {
        namespace utils {
            template<bool...> struct static_all_of;
            template<bool... tail>
            struct static_all_of<true, tail...> : static_all_of<tail...> {};
            template<bool... tail>
            struct static_all_of<false, tail...> : false_type {};
            template<> struct static_all_of<> : true_type {};

            template<bool...> struct static_any_of;
            template<bool... tail>
            struct static_any_of<true, tail...> : true_type {};
            template<bool... tail>
            struct static_any_of<false, tail...> : static_any_of<tail...> {};
            template<> struct static_any_of<> : false_type {};
        } // namespace utils

        template<typename T, typename... Ts> struct is_any_of {
            static constexpr bool value =
                utils::static_any_of<is_same_v<T, Ts>...>::value;
        };
        template<typename T, typename... Ts>
        inline constexpr bool is_any_of_v = is_any_of<T, Ts...>::value;

        template<typename T> struct remove_cvref {
            using type = remove_cv_t<remove_reference_t<T>>;
        };
        template<typename T>
        using remove_cvref_t = typename remove_cvref<T>::type;

        // Arithmetic ----------------------------------------------------------
        template<typename T> struct is_vec_bool_ref {
            template<typename TT>
            static auto
            test(int) -> enable_if_t<
                          is_same_v<decay_t<TT>, vector<bool>::const_reference>,
                          true_type>;
            template<typename> static auto test(...) -> false_type;

            static constexpr bool value = decltype(test<T>(0))::value;
        };
        template<typename T>
        inline constexpr bool is_arithmetic_v =
            std::is_arithmetic_v<remove_cvref_t<T>> ||
            is_vec_bool_ref<T>::value;
#ifdef __SIZEOF_INT128__
        template<
            typename T,
            enable_if_t<is_any_of_v<remove_cvref_t<T>, __int128_t, __uint128_t>,
                        int> = 1>
        inline constexpr bool is_arithmetic = true;
#endif

        // String --------------------------------------------------------------
        template<typename T>
        inline constexpr bool is_nullptr = is_null_pointer_v<remove_cvref_t<T>>;
        template<typename T>
        inline constexpr bool is_string =
            is_convertible_v<T, string_view> && !is_nullptr<T>;

        // Streamable ----------------------------------------------------------
        template<typename T> struct streamable {
            template<typename TT>
            static auto test(int) -> decltype(declval<ostream>()
                                                  << declval<TT>(),
                                              true_type());
            template<typename TT> static auto test(...) -> false_type;

            static constexpr bool value = decltype(test<T>(0))::value;
        };
        template<typename T>
        inline constexpr bool streamable_v =
            streamable<remove_cvref_t<T>>::value;

        // Pair/tuple ----------------------------------------------------------
        template<typename> struct is_pair : false_type {};
        template<typename T, typename U>
        struct is_pair<pair<T, U>> : true_type {};
        template<typename T>
        inline constexpr bool is_pair_v =
            is_pair<_detail::remove_cvref_t<T>>::value;

        template<typename> struct is_tuple : false_type {};
        template<typename... Args>
        struct is_pair<tuple<Args...>> : true_type {};
        template<typename T>
        inline constexpr bool is_tuple_v =
            is_tuple<_detail::remove_cvref_t<T>>::value;

        // Vector/array --------------------------------------------------------
        template<typename> struct is_vector : false_type {};
        template<typename T, typename... Args>
        struct is_vector<vector<T, Args...>> : true_type {};
        template<typename T>
        inline constexpr bool is_vector_v =
            is_vector<_detail::remove_cvref_t<T>>::value;

        template<typename> struct is_array : false_type {};
        template<typename T, size_t N>
        struct is_array<array<T, N>> : true_type {};
        template<typename T>
        inline constexpr bool is_array_v =
            _detail::is_array<remove_cvref_t<T>>::value;

        // Map -----------------------------------------------------------------
        template<typename> inline constexpr bool _is_map = false;
        template<typename... Args>
        inline constexpr bool _is_map<map<Args...>> = true;
        template<typename... Args>
        inline constexpr bool _is_map<unordered_map<Args...>> = true;

        template<typename T>
        inline constexpr bool is_map = _is_map<remove_cvref_t<T>>;

        // Stack/queue ---------------------------------------------------------
        template<typename> struct is_stack : false_type {};
        template<typename... Args>
        struct is_stack<stack<Args...>> : true_type {};
        template<typename... Args>
        struct is_stack<priority_queue<Args...>> : true_type {}; // for top()
        template<typename T>
        inline constexpr bool is_stack_v = is_stack<remove_cvref_t<T>>::value;

        template<typename> struct is_queue : false_type {};
        template<typename... Args>
        struct is_queue<queue<Args...>> : true_type {};
        template<typename T>
        inline constexpr bool is_queue_v = is_queue<remove_cvref_t<T>>::value;

        // Iterable ------------------------------------------------------------
        template<typename T> struct iterable {
            template<typename TT>
            static auto test(int) -> decltype(iter_begin(declval<TT>()),
                                              true_type());
            template<typename TT> static auto test(...) -> false_type;

            static constexpr bool value = decltype(test<T>(0))::value;
        };
        template<typename T>
        inline constexpr bool iterable_v = iterable<remove_cvref_t<T>>::value;

        // Multiline utility stuff
        template<typename _T, typename T = _detail::remove_cvref_t<_T>>
        struct is_trivial {
            static constexpr bool value =
                (std::is_trivial_v<T> && is_standard_layout_v<T> &&
                 !is_array_v<T>) ||
                (is_string<T> && dbg::options::trivial_string());
        };
        template<typename T, typename U> struct is_trivial<pair<T, U>> {
            static constexpr bool value =
                _detail::is_trivial<T>::value && _detail::is_trivial<U>::value;
        };
        template<typename... Ts> struct is_trivial<tuple<Ts...>> {
            static constexpr bool value =
                utils::static_all_of<_detail::is_trivial<Ts>::value...>::value;
        };
        template<typename T>
        inline constexpr bool is_trivial_v =
            _detail::is_trivial<_detail::remove_cvref_t<T>>::value;
    } // namespace _detail
} // namespace dbg
#line 6 "src/containers.hpp"

namespace dbg {
    using namespace std;

    extern int indent_lvl;
    extern string get_indent();

    namespace _detail {
        template<typename T>
        inline string dbg_iterable(T &&a, string open, string close) {
            indent_lvl++;
            const bool trivial_value =
                _detail::is_trivial_v<decltype(*iter_begin(a))>;
            const string sep = trivial_value ? ", " : ",\n" + get_indent();

            vector<string> vals;
            for (auto &&elem : a) vals.push_back(dbg_info(elem));

            string output = open + (trivial_value ? "" : "\n" + get_indent());
            bool first_elem = true;
            for (string &val : vals) {
                if (first_elem) {
                    output += val;
                    first_elem = false;
                } else {
                    output += sep + val;
                }
            }
            indent_lvl--;
            output += (trivial_value ? "" : "\n" + get_indent()) + close;
            return output;
        }

        template<typename T> inline string dbg_map(T &&mp) {
            indent_lvl++;
            const string sep = "\n" + get_indent();
            vector<string> vals;
            for (auto &&[key, val] : mp)
                vals.push_back(dbg_info(key) + " -> " + dbg_info(val));

            string output = "{\n" + get_indent();
            bool first_elem = true;
            for (string &val : vals) {
                if (first_elem) {
                    output += val;
                    first_elem = false;
                } else {
                    output += sep + val;
                }
            }
            indent_lvl--;
            output += "\n" + get_indent() + "}";
            return output;
        }

        template<typename T>
        inline string dbg_stack(T st) { // works with priority_queue too
            vector<typename T::value_type> v;
            while (!st.empty()) v.push_back(st.top()), st.pop();
            return dbg_iterable(v, "{", "}");
        }
        template<typename T, typename... Args>
        inline string dbg_queue(queue<T, Args...> q) {
            vector<T> v;
            while (!q.empty()) v.push_back(q.front()), q.pop();
            return dbg_iterable(v, "{", "}");
        }
    } // namespace _detail
} // namespace dbg
#line 2 "src/other.hpp"

#line 4 "src/other.hpp"
#include <string_view>

namespace dbg {
    using namespace std;
    namespace _detail {
        template<typename T> constexpr auto func_name() {
            return __PRETTY_FUNCTION__;
        }
        template<typename T> constexpr auto _type_of_impl() {
            constexpr string_view fn_name = func_name<T>();
#if defined(__GNUC__) && !defined(__llvm__)
            return string_view{fn_name.data() + 51, fn_name.size() - 52};
#elif defined(__llvm__)
            return string_view{fn_name.data() + 36, fn_name.size() - 37};
#endif
        }
        template<typename T> constexpr auto type_of(T &&x) {
            return _type_of_impl<decltype(x)>();
        }
        template<typename T> constexpr auto type_of() {
            return _type_of_impl<T>();
        }

        template<typename T> string unsupported_type() {
            return "\e[31m[" + string(type_of<T>()) + "]\e[0m";
        }
    } // namespace _detail
} // namespace dbg
#line 2 "src/trivial.hpp"

#line 5 "src/trivial.hpp"
#include <algorithm>
#include <sstream>
#line 8 "src/trivial.hpp"

namespace dbg {
    using namespace std;
    namespace _detail {
        template<typename T,
                 enable_if_t<!is_floating_point_v<remove_cvref_t<T>>, int> = 1>
        inline string dbg_arithmetic(T n) {
            const bool neg = n < 0;
            make_unsigned_t<remove_cvref_t<T>> x = n;
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
        template<typename T,
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

        template<typename... Ts, size_t idx = 0>
        inline string dbg_tuple_helper(const tuple<Ts...> &t) {
            return "";
        }
        template<typename... Ts>
        inline string dbg_tuple(const tuple<Ts...> &t) {
            return "(" + dbg_tuple_helper<Ts...>(t) + ")";
        }

        template<typename T> inline string dbg_streamable(T &&x) {
            stringstream ss;
            ss << x;
            return ss.str();
        }
    } // namespace _detail
} // namespace dbg
#line 8 "src/info.hpp"

namespace dbg {
    namespace _detail {
        template<typename T> string dbg_info(T &&x) {
            if constexpr (is_same_v<remove_cvref_t<T>, bool>) {
                return dbg_bool(x);
            } else if constexpr (is_same_v<remove_cvref_t<T>, char>) {
                return dbg_char(x);
            } else if constexpr (_detail::is_arithmetic_v<T>) {
                return dbg_arithmetic(x);
            } else if constexpr (is_string<T>) {
                return dbg_string(x);
            } else if constexpr (is_pair_v<T>) {
                return dbg_pair(x);
            } else if constexpr (is_tuple_v<T>) {
                return dbg_tuple(x);
            } else if constexpr (is_vector_v<T> || _detail::is_array_v<T>) {
                return dbg_iterable(x, "[", "]");
            } else if constexpr(is_map<T>) {
                return dbg_map(x);
            } else if constexpr (is_stack_v<T>) {
                return dbg_stack(x);
            } else if constexpr (is_queue_v<T>) {
                return dbg_queue(x);
            } else if constexpr (streamable_v<T>) {
                return dbg_streamable(x);
            } else if constexpr (iterable_v<T>) {
                return dbg_iterable(x, "{", "}");
            } else {
                return unsupported_type<T>();
            }
        }
    } // namespace _detail
} // namespace dbg
#line 14 "src/debug.hpp"

namespace dbg {
    namespace _detail {
        struct src_loc {
            string file_name;
            int line;
            string func_name;
        };

        template<typename...> string fmt() { return ""; }
        template<typename T, typename... Args>
        string fmt(T &&x, Args &&...args) {
            return dbg_info(x) + (sizeof...(args) ? ", " + fmt(args...) : "");
        }
    }; // namespace _detail

    template<typename... Args>
    void dbg_impl(_detail::src_loc loc, string args_str, Args &&...args) {
        const bool multi_arg = sizeof...(args) > 1;
        const string label =
            "[\e[33m" + loc.func_name + "\e[0m:" + to_string(loc.line) + "]";

        string vals = _detail::fmt(args...);

        if (multi_arg) {
            args_str = "[" + args_str + "]";
            vals = "[" + vals + "]";
        }

        const string output = label + " " + args_str + " = " + vals;
        cerr << output << "\n";
    }
} // namespace dbg

#define dbg(a...) dbg::dbg_impl({__FILE__, __LINE__, __func__}, #a, a)
#define mark_dbg()
#line 2 "debug.hpp"
