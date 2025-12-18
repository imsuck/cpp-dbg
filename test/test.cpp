#include "../debug.hpp"
#include <vector>
#include <map>
#include <set>
#include <optional>
#include <tuple>

int main() {
    // Test basic types
    int x = 42;
    bool b = true;
    char c = 'A';
    double d = 3.14159;
    std::string s = "Hello World";

    dbg(x);
    dbg(b);
    dbg(c);
    dbg(d);
    dbg(s);

    // Test containers
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::set<int> st = {1, 2, 3, 4, 5};
    std::map<std::string, int> mp = {{"a", 1}, {"b", 2}, {"c", 3}};

    dbg(vec);
    dbg(st);
    dbg(mp);

    // Test optional
    std::optional<int> opt_some = 42;
    std::optional<int> opt_none;

    dbg(opt_some);
    dbg(opt_none);

    // Test tuple
    std::tuple<int, std::string, double> tup = {1, "hello", 3.14};
    dbg(tup);

    // Test multiple arguments
    int y = 10;
    std::string str = "test";
    dbg(x, y, str);

    return 0;
}
