#pragma once

#include "options.hpp"
#include "type_traits.hpp"
#include <type_traits>

namespace dbg {

    // Forward declaration
    template<typename T> struct is_trivial;

    namespace detail {

        // Helper to check if a type is trivial
        template<typename _T, typename T = detail::remove_cvref_t<_T>>
        struct is_trivial_impl {
            static bool value() {
                return (std::is_trivial_v<T> && std::is_standard_layout_v<T> &&
                        !std::is_array_v<T>) ||
                       (detail::is_string<T>::value &&
                        options::trivial_string) ||
                       detail::is_vec_bool_ref<T>::value ||
                       detail::is_simple<T>::value;
            }
        };

    } // namespace detail

    template<typename T> struct is_trivial : detail::is_trivial_impl<T> {};

    // Specialization for tuples - trivial if all element types are trivial
    template<typename... Ts> struct is_trivial<std::tuple<Ts...>> {
        static bool value() { return (is_trivial<Ts>::value() && ...); }
    };

    template<typename T> inline bool is_trivial_v(const T &) {
        return is_trivial<T>::value();
    }

    // For backward compatibility - type-based check
    template<typename T> inline bool is_trivial_type_v() {
        return is_trivial<T>::value();
    }

} // namespace dbg
