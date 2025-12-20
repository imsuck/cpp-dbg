#include "../debug.hpp"
#include <map>
#include <string>
#include <utility>
#include <vector>

int main() {
    // Test 1: Basic pairs
    std::cout << "\n1. Basic pairs:" << std::endl;
    std::pair<int, int> coordinates{10, 20};
    dbg(coordinates);

    // Test 2: Pair with string
    std::pair<std::string, double> item{"Pi", 3.14159};
    dbg(item);

    // Test 3: Nested pairs
    std::pair<std::pair<int, int>, std::pair<int, int>> nested{
        {1, 2},
        {3, 4}
    };
    dbg(nested);

    // Test 4: Pair in containers
    std::cout << "\n2. Pairs in containers:" << std::endl;
    std::vector<std::pair<std::string, int>> scores{
        {  "Alice", 95},
        {    "Bob", 87},
        {"Charlie", 92}
    };
    dbg(scores);

    // Test 5: Non-trivial pairs (should format multi-line)
    std::cout << "\n3. Non-trivial pairs:" << std::endl;
    std::pair<std::vector<int>, std::vector<int>> vec_pair{
        {1, 2, 3},
        {4, 5, 6}
    };
    dbg(vec_pair);

    // Test 6: Mixed trivial/non-trivial
    std::pair<int, std::vector<std::string>> mixed{
        42,
        {"hello", "world"}
    };
    dbg(mixed);

    // Test 7: Map iteration (uses pairs internally)
    std::cout << "\n4. Map with pairs:" << std::endl;
    std::map<std::string, std::pair<int, int>> positions{
        {"player1", {100, 200}},
        {"player2", {150, 250}},
        {"player3", {200, 300}}
    };
    dbg(positions);

    return 0;
}
