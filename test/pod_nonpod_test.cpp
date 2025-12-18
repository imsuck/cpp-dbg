#include "../debug.hpp"

// POD struct (should be trivial by default)
struct PODPoint {
    int x, y;
};

// Non-POD struct with constructor (not trivial by default)
struct NonPODPoint {
    int x, y;
    NonPODPoint(int a, int b) : x(a), y(b) {}
};

// Non-POD struct with is_simple = true (forces trivial formatting)
struct NonPODSimple {
    int x, y;
    NonPODSimple(int a, int b) : x(a), y(b) {}
    static constexpr bool is_simple = true;
};

DBG_FORMAT_STRUCT2(PODPoint, x, y);
DBG_FORMAT_STRUCT2(NonPODPoint, x, y);
DBG_FORMAT_STRUCT2(NonPODSimple, x, y);

int main() {
    std::vector<PODPoint> vec1 = {{1, 2}, {3, 4}, {5, 6}};
    std::vector<NonPODPoint> vec2 = {{7, 8}, {9, 10}, {11, 12}};
    std::vector<NonPODSimple> vec3 = {{13, 14}, {15, 16}, {17, 18}};

    // Test containers - should show different formatting based on triviality
    dbg(vec1);  // POD, trivial by default
    dbg(vec2);  // Non-POD, not trivial by default
    dbg(vec3);  // Non-POD, but forced trivial with is_simple = true

    return 0;
}
