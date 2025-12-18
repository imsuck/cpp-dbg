#include "../debug.hpp"

struct Struct1 { int a; };
struct Struct2 { int a, b; };
struct Struct3 { int a, b, c; };
struct Struct6 { int a, b, c, d, e, f; };
struct Struct10 { int a, b, c, d, e, f, g, h, i, j; };

// DBG_FORMAT_STRUCT1(Struct1, a);
// DBG_FORMAT_STRUCT2(Struct2, a, b);
// DBG_FORMAT_STRUCT3(Struct3, a, b, c);
// DBG_FORMAT_STRUCT6(Struct6, a, b, c, d, e, f);
// DBG_FORMAT_STRUCT10(Struct10, a, b, c, d, e, f, g, h, i, j);
DBG_FORMAT_STRUCT(Struct1, a);
DBG_FORMAT_STRUCT(Struct2, a, b);
DBG_FORMAT_STRUCT(Struct3, a, b, c);
DBG_FORMAT_STRUCT(Struct6, a, b, c, d, e, f);
DBG_FORMAT_STRUCT(Struct10, a, b, c, d, e, f, g, h, i, j);

int main() {
    Struct1 s1{1};
    Struct2 s2{1, 2};
    Struct3 s3{1, 2, 3};
    Struct6 s6{1, 2, 3, 4, 5, 6};
    Struct10 s10{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    dbg(s1);
    dbg(s2);
    dbg(s3);
    dbg(s6);
    dbg(s10);

    return 0;
}
