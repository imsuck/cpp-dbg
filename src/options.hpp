#pragma once

#include <cstddef>

namespace dbg::options {
    struct Settings {
        static constexpr bool fixed_float = false;
        static constexpr int float_precision = 6;
        static constexpr bool trivial_string = true;
        static constexpr bool enable_colors = true;
        static constexpr size_t max_container_elements = 20;
        static constexpr bool show_multiplicity = true;
    };

    // Individual option templates that can be specialized separately
    template<typename = void> constexpr bool fixed_float = Settings::fixed_float;
    template<typename = void> constexpr int float_precision = Settings::float_precision;
    template<typename = void> constexpr bool trivial_string = Settings::trivial_string;
    template<typename = void> constexpr bool enable_colors = Settings::enable_colors;
    template<typename = void> constexpr size_t max_container_elements = Settings::max_container_elements;
    template<typename = void> constexpr bool show_multiplicity = Settings::show_multiplicity;

    // Convenience functions for accessing options
    constexpr bool fixed_float() { return fixed_float<>; }
    constexpr int float_precision() { return float_precision<>; }
    constexpr bool trivial_string() { return trivial_string<>; }
    constexpr bool enable_colors() { return enable_colors<>; }
    constexpr size_t max_container_elements() { return max_container_elements<>; }
    constexpr bool show_multiplicity() { return show_multiplicity<>; }
} // namespace dbg::options
