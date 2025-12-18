#include "../debug.hpp"

struct BigStruct {
    int f1, f2, f3, f4, f5, f6, f7, f8, f9, f10;
};

DBG_FORMAT_STRUCT10(BigStruct, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10);

int main() {
    BigStruct bs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    dbg(bs);
    return 0;
}
