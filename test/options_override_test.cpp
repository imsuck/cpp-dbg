#include "../debug.hpp"

namespace dbg::options {
    auto z = []() {
        trivial_string = false;
        enable_colors = false;
        float_precision = 2;
        return 0;
    }();
}; // namespace dbg::options

int main() {
    double pi = 3.141592653589793;
    std::vector<int> large_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<std::string> str_vec = {"hello", "world", "!"};

    // First show with unlimited container elements
    dbg::options::max_container_elements = -1;
    std::cout << "With unlimited max_container_elements (-1):" << std::endl;
    dbg(large_vec); // Should show all elements

    // Then show with limited container elements
    dbg::options::max_container_elements = 2;
    std::cout << "\nWith max_container_elements = 2:" << std::endl;
    dbg(large_vec); // Should truncate at 2 elements and show "..."

    // Other tests
    std::cout << "\nOther tests:" << std::endl;
    dbg(pi);      // Should show fixed precision with 2 decimal places
    dbg(str_vec); // Should have newlines to separate the strings

    return 0;
}
