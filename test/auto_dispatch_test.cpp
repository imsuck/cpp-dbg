#include "../debug.hpp"

struct Test1 { int a; };
struct Test2 { int a, b; };
struct Test3 { int a, b, c; };
struct Test6 { int a, b, c, d, e, f; };

DBG_FORMAT_STRUCT(Test1, a);
DBG_FORMAT_STRUCT(Test2, a, b);
DBG_FORMAT_STRUCT(Test3, a, b, c);
DBG_FORMAT_STRUCT(Test6, a, b, c, d, e, f);

int main() {
    Test1 t1{1};
    Test2 t2{1, 2};
    Test3 t3{1, 2, 3};
    Test6 t6{1, 2, 3, 4, 5, 6};

    dbg(t1);
    dbg(t2);
    dbg(t3);
    dbg(t6);

    return 0;
}
