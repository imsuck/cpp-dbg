# How to use (for competitive programmers)
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
```sh
oj-bundle bundle.hpp > debug.hpp
```
