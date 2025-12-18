#include "../debug.hpp"

struct Person {
    std::string name;
    int age;
    double height;
};

DBG_FORMAT_STRUCT3(Person, name, age, height);

struct Point {
    int x, y;
};

DBG_FORMAT_STRUCT2(Point, x, y);

int main() {
    Person p{"Alice", 25, 5.6};
    Point pt{10, 20};

    dbg(p);
    dbg(pt);

    return 0;
}
