#include "../debug.hpp"
#include <map>
#include <string>
#include <utility>
#include <vector>

int main() {
    // Basic pair
    std::pair<int, int> p1{42, 100};
    dbg(p1);

    // Pair with string
    std::pair<std::string, int> p2{"answer", 42};
    dbg(p2);

    // Nested pair
    std::pair<std::pair<int, int>, std::string> p3{
        {1, 2},
        "nested"
    };
    dbg(p3);

    // Pair in vector
    std::vector<std::pair<std::string, int>> vec{
        {  "Alice", 25},
        {    "Bob", 30},
        {"Charlie", 35}
    };
    dbg(vec);

    // Map (which internally uses pairs)
    std::map<std::string, int> m{
        {  "one", 1},
        {  "two", 2},
        {"three", 3}
    };
    dbg(m);

    // Multiple pairs
    std::pair<double, double> p4{3.14, 2.71};
    std::pair<char, bool> p5{'A', true};
    dbg(p4, p5);

    return 0;
}
