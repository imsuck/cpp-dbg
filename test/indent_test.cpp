#include "../debug.hpp"
#include <vector>
#include <map>
#include <string>

int main() {
    // Create nested structures to test indentation levels
    std::map<std::string, std::vector<std::map<std::string, int>>> nested = {
        {"level1", {
            {{"a", 1}, {"b", 2}},
            {{"c", 3}, {"d", 4}}
        }},
        {"level2", {
            {{"x", 10}, {"y", 20}},
            {{"z", 30}}
        }}
    };

    dbg(nested);

    // Another example with tuple containing map
    std::tuple<std::string, std::map<std::string, std::vector<int>>> complex_tuple = {
        "tuple_with_map",
        {
            {"vec1", {1, 2, 3}},
            {"vec2", {4, 5, 6, 7, 8}}
        }
    };

    dbg(complex_tuple);

    return 0;
}
