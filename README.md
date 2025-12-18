# C++ Debug Library

A C++17 header-only debugging library for competitive programming.

See also: [philip82148/cpp-dump](https://github.com/philip82148/cpp-dump)

## Usage

```cpp
#include "debug.hpp"

int main() {
    int x = 42;
    std::vector<int> v = {1, 2, 3};
    std::map<std::string, int> m = {{"a", 1}, {"b", 2}};

    dbg(x);           // Single variable
    dbg(v);           // Container
    dbg(x, v, m);     // Multiple variables
}
```

## Features

- **Single argument**: `dbg(variable)`
- **Multiple arguments**: `dbg(var1, var2, var3)`
- **Output to stderr** with ANSI colors
- **Automatic formatting** for:
  - Built-in types (int, bool, char, float, pointers)
  - STL containers (vector, set, map, etc.)
  - Smart pointers and optional types
  - Tuples and custom types
- **Custom struct formatting**: `DBG_FORMAT_STRUCT` or through `operator<<`

## Customization

Modify the global configuration before using debug functions:

```cpp
#include "debug.hpp"

// Modify default options
dbg::config::fixed_float = true;        // Use fixed precision for floats
dbg::config::float_precision = 3;       // Float precision
dbg::config::enable_colors = false;     // Disable colors
dbg::config::max_container_elements = 10; // Max elements shown in containers

// Or using an immediately invoked lambda
namespace dbg::config {
    int _ = []() {
        fixed_float = true;
        float_precision = 3;
        enable_colors = false;
        max_container_elements = 10;
        return 0;
    }();
}
```

Available options in `dbg::config`:
- `fixed_float` - Use fixed precision for floating point numbers
- `float_precision` - Precision for floating point numbers
- `trivial_string` - Whether strings are considered trivial
- `enable_colors` - Enable/disable ANSI color output
- `max_container_elements` - Max elements shown before truncation (set to -1 for unlimited)
- `show_multiplicity` - Show multiplicity in multisets/maps

## Custom Struct Formatting

For custom structs without `operator<<`, use the formatting macros:

```cpp
struct Person {
    std::string name;
    int age;
    double height;
};

DBG_FORMAT_STRUCT(Person, name, age, height);

int main() {
    Person p{"Alice", 25, 5.6};
    dbg(p);  // Output: [main:11] p = Person{name=Alice, age=25, height=5.6}
}
```

## Custom Type Triviality

Types can control their "triviality" for container formatting by declaring:

```cpp
struct MyType {
    // ... members ...
    static constexpr bool is_simple = true;  // Forces single-line container formatting
};
```

Without `is_simple = true`, non-POD types format containers with newlines and indentation.
