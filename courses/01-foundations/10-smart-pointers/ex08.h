// Exercise 08: Custom Deleter
//
// By default, unique_ptr calls `delete` on the managed pointer. But
// sometimes you need a different cleanup action -- for example, when
// wrapping a C library resource that must be freed with a specific
// function (free(), fclose(), custom_destroy(), etc.).
//
// You can provide a custom deleter as a second template argument:
//
//   auto ptr = std::unique_ptr<Type, decltype(&deleter_fn)>(raw, deleter_fn);
//
// Or use a lambda / function object as the deleter.
//
// TODO:
//   Implement the functions below using unique_ptr with custom deleters.

#pragma once

#include <cstdlib>
#include <cstring>
#include <functional>
#include <memory>
#include <string>
#include <testkit/testkit.h>

// A counter that tracks how many times our custom deleter is called.
// Tests use this to verify that the correct deleter runs.
inline int& deleter_call_count() {
    static int count = 0;
    return count;
}

// Allocate a C-string copy of `text` using malloc, wrapped in a unique_ptr
// that frees it with std::free.
// Hint: use std::unique_ptr<char, decltype(&std::free)> or a lambda.
inline std::unique_ptr<char, decltype(&std::free)> make_c_string(const std::string& text) {
    TODO();
}

struct Resource {
    int id;
};

// A custom deleter function for Resource that increments deleter_call_count.
inline void destroy_resource(Resource* r) {
    ++deleter_call_count();
    delete r;
}

// Create a unique_ptr<Resource> that uses destroy_resource as its deleter.
inline std::unique_ptr<Resource, decltype(&destroy_resource)> create_resource(int id) {
    TODO();
}

// Using a lambda deleter: create a unique_ptr<int[]> that was allocated with
// new int[size] and uses a lambda deleter that calls delete[] and increments
// deleter_call_count.
inline auto make_int_array(std::size_t size)
    -> std::unique_ptr<int[], std::function<void(int*)>> {
    TODO();
}
