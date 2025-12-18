#include "../debug.hpp"

// POD struct (should be trivial)
struct PODPoint {
    int x, y;
};

// Non-POD struct with constructor (not trivial)
struct NonPODPoint {
    int x, y;
    NonPODPoint(int a, int b) : x(a), y(b) {}
};

// Non-POD with is_simple = true
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

    // Test containers - should show different formatting
    dbg(vec1);  // POD, no is_simple
    dbg(vec2);  // Non-POD, no is_simple
    dbg(vec3);  // Non-POD, with is_simple = true

    return 0;
}
