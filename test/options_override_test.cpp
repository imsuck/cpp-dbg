#include <bits/stdc++.h>

#include "../debug.hpp"

// Configure only the options we want to override
namespace dbg::options {
    template<> constexpr bool trivial_string<> = false;
    template<> constexpr bool enable_colors<> = false;
    template<> constexpr int float_precision<> = 2;
    template<> constexpr size_t max_container_elements<> = 2;
} // namespace dbg::options

int main() {
    double pi = 3.141592653589793;
    std::vector<int> large_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // These should use the overridden options
    dbg(pi);        // Should show fixed precision with 2 decimal places
    dbg(large_vec); // Should truncate at 2 elements and show "..."

    return 0;
}
