#include "../debug.hpp"

// Custom struct without is_simple
struct Point2D {
    int x, y;
};

// Custom struct with is_simple = true
struct SimplePoint {
    int x, y;
    static constexpr bool is_simple = true;
};

// Custom struct with is_simple = false
struct ComplexPoint {
    int x, y;
    static constexpr bool is_simple = false;
};

DBG_FORMAT_STRUCT2(Point2D, x, y);
DBG_FORMAT_STRUCT2(SimplePoint, x, y);
DBG_FORMAT_STRUCT2(ComplexPoint, x, y);

int main() {
    Point2D p1{1, 2};
    SimplePoint p2{3, 4};
    ComplexPoint p3{5, 6};

    std::vector<Point2D> vec1 = {p1, {7, 8}, {9, 10}};
    std::vector<SimplePoint> vec2 = {p2, {11, 12}, {13, 14}};
    std::vector<ComplexPoint> vec3 = {p3, {15, 16}, {17, 18}};

    // Test individual structs
    dbg(p1);
    dbg(p2);
    dbg(p3);

    // Test containers - should show different formatting based on triviality
    dbg(vec1);
    dbg(vec2);
    dbg(vec3);

    return 0;
}
