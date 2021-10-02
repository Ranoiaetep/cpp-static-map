# C++ Static Map

Header-only compile time key-value map written in C++20.

## Getting Started

Simply add the files in your source and `#include "@dir/Static_map.hpp"`, and replace `@dir` with the actual directory they are put in.

## Usage

### Creating a map

To generate a `Static_map` containing data: `{1,"One"},{2,"Two"},{3,"Three}`:

````c++
constexpr auto map = make_static_map(1, "One"sv, 2, "Two"sv, 3, "Three"sv);
````

To generate a `Static_map` where key and value are the same type, you can also do:

```c++
constexpr auto map = make_static_map({"1"sv, "One"sv}, {"2"sv, "Two"sv}, {"3"sv, "Three"sv});
```

-   Note: `sv` is the literal for `std::string_view`. Any type that can be constructed as `constexpr` should work.

Alternatively, you can first create an `std::array<std::pair<Key, Value>, N>` object manually, and it can be explicitly converted to `Static_map<Key, Value, N>`.

---

### Retrieving data

There are three methods to retrieve value from the map with a given key:

1.   `Static_map.at(KEY)` it returns the pointed value. If key was not found it will throws `std::out_of_range`.

2.   `Static_map[KEY]` it returns an `std::optional<VALUE>`. If key was not found it will return an `std::nullopt`.
3.   `Static_map.at_or_default(KEY, DEFAULT=VALUE{})` it returns the pointed value. If key was not found `DEFAULT` will be returned. If no default was given, the default constructed `VALUE` will be returned.

-   Note: The second option will always returns an `std::optional`, whereas the other two will attempt to return the `VALUE` type directly.
-   Note: The first method would fail in compile time if key was not found, as it requires exception handling.

---

### Duplicated Key

By default, `Static_map` will not check for duplicated keys. When retrieving data from a given key, only the first matched key will be considered.

Optionally, you can pass a custom flag `SM_NO_DUPLICATE`, it will throw `std::invalid_argument` if duplicate `KEY` were presented.

## Prerequisites

C++20 with range library support is required for now. C++14/17 support will be added later.
