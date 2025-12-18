#include <map>
#include <string>
#include <vector>

#include "debug.hpp"

int main() {
    std::vector a{2, 3, 47, 83};
    std::map<int, std::string> mp{
        { 7,        "seven"},
        {83, "eighty three"}
    };
    std::tuple tup{7, 3.4, true, 'h', "test"};
    std::vector vec_of_tups{tup, tup, tup};
    dbg(a), dbg(mp), dbg(tup), dbg(vec_of_tups);
    dbg(a, mp), dbg("hi");
    dbg(4, a, mp, tup);
}
