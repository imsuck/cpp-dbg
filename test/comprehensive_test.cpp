#include "../debug.hpp"
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <stack>
#include <array>
#include <optional>
#include <tuple>
#include <string>
#include <memory>

int main() {
    // Test basic types
    int i = 42;
    bool b = false;
    char c = 'Z';
    double d = 2.71828;
    float f = 1.23f;
    std::string str = "Competitive Programming";

    dbg(i, b, c);
    dbg(d, f, str);

    // Test pointers
    int* ptr = &i;
    int* null_ptr = nullptr;
    const char* cstr = "C-style string";

    dbg(ptr, null_ptr, cstr);

    // Test smart pointers
    auto unique_ptr = std::make_unique<int>(123);
    auto shared_ptr = std::make_shared<std::string>("shared");
    std::weak_ptr<std::string> weak_ptr = shared_ptr;

    dbg(unique_ptr, shared_ptr, weak_ptr);

    // Test containers
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};
    std::array<int, 5> arr = {10, 20, 30, 40, 50};
    std::deque<int> deq = {100, 200, 300};

    dbg(vec);
    dbg(arr);
    dbg(deq);

    // Test sets and maps
    std::set<int> s = {5, 3, 8, 1, 9};
    std::multiset<int> ms = {1, 2, 2, 3, 3, 3};
    std::unordered_set<std::string> us = {"apple", "banana", "cherry"};
    std::unordered_multiset<std::string> ums = {"a", "b", "a", "c", "b", "a"};

    std::map<std::string, int> m = {{"one", 1}, {"two", 2}, {"three", 3}};
    std::multimap<std::string, int> mm = {{"a", 1}, {"b", 2}, {"a", 3}, {"c", 4}};
    std::unordered_map<int, std::string> um = {{1, "first"}, {2, "second"}};
    std::unordered_multimap<int, std::string> umm = {{1, "x"}, {2, "y"}, {1, "z"}};

    dbg(s, ms);
    dbg(us, ums);
    dbg(m, mm);
    dbg(um, umm);

    // Test queue/stack (these will show as empty since we can't iterate them)
    std::queue<int> q;
    q.push(1); q.push(2); q.push(3);
    std::stack<int> stk;
    stk.push(10); stk.push(20); stk.push(30);
    std::priority_queue<int> pq;
    pq.push(5); pq.push(15); pq.push(10);

    dbg(q, stk, pq);

    // Test tuple
    std::tuple<int, std::string, double, bool> complex_tuple = {42, "hello", 3.14159, true};
    dbg(complex_tuple);

    // Test optional
    std::optional<std::vector<int>> opt_vec = std::vector<int>{1, 2, 3};
    std::optional<std::string> opt_empty;
    dbg(opt_vec, opt_empty);

    // Test nested structures
    std::map<std::string, std::vector<int>> nested = {
        {"even", {2, 4, 6}},
        {"odd", {1, 3, 5}}
    };
    dbg(nested);

    // Test __int128 if available
    __int128_t big_int = (__int128_t)123456789LL * 1000000000LL + 123456789LL;
    dbg(big_int);

    return 0;
}
