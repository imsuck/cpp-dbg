#include "../debug.hpp"

struct UnsupportedStruct {
    int x;
    double y;
};

struct SupportedStruct {
    int a;
    std::string b;
};

std::ostream& operator<<(std::ostream& os, const SupportedStruct& s) {
    return os << "SupportedStruct{a=" << s.a << ", b=" << s.b << "}";
}

int main() {
    UnsupportedStruct unsupported{42, 3.14};
    SupportedStruct supported{123, "hello"};

    dbg(unsupported);
    dbg(supported);

    return 0;
}
