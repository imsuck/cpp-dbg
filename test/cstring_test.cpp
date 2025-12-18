#include "../debug.hpp"

int main() {
    const char* cstr = "Hello C-string";
    char* mutable_cstr = const_cast<char*>("Mutable C-string");
    const char* null_cstr = nullptr;
    std::string std_str = "Hello std::string";

    dbg(cstr);
    dbg(mutable_cstr);
    dbg(null_cstr);
    dbg(std_str);

    return 0;
}
