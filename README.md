### Requires >=C++17
# How to use
Get a copy of [debug.hpp](https://github.com/imsuck/cpp-dbg/blob/main/debug.hpp).

In your source code:
```cpp
#ifdef LOCAL
#include "path/to/debug.hpp"
namespace dbg::options {
    // Customize stuff here
}
#else
#define dbg(...) (void(0))
#define mark_dbg() if (false)
#endif
```
Add `-DLOCAL` (or maybe `/DLOCAL`) to your compilation flags.

# Options
- Trivial string (disable new line for containers containing strings)
```cpp
namespace dbg::options {
    template<> constexpr bool trivial_string() {
        return true;
    }
}
```

# Bundling
Install [oj-bundle](https://github.com/online-judge-tools/verification-helper)

With `bundle.hpp`:
```cpp
#include "src/debug.hpp"
```
To bundle:
```sh
$ oj-bundle bundle.hpp > debug.hpp
```
