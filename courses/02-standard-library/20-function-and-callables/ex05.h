// Exercise 05: Template Parameter vs Type Erasure
//
// std::function uses "type erasure" — it can hold *any* callable with a
// matching signature, but this flexibility has a cost: a virtual call on
// every invocation and possible heap allocation to store the callable.
//
// A template parameter avoids these costs entirely. The compiler knows
// the exact callable type and can inline the call. The tradeoff is that
// template functions generate separate code for each callable type and
// cannot be stored in containers (since each instantiation is a different type).
//
// When to use which:
//   - std::function: storing callbacks, runtime polymorphism, containers
//   - Template parameter: algorithms, hot loops, when you don't need to store
//
// Example with std::function (type-erased):
//   int apply_erased(std::function<int(int)> f, int x) { return f(x); }
//
// Example with template (zero-overhead):
//   template<typename F>
//   int apply_template(F&& f, int x) { return f(x); }
//
// TODO:
//   1. Implement apply_erased() — takes a std::function<int(int)> and a value,
//      returns the result of calling the function.
//   2. Implement apply_template() — same behavior but using a template parameter
//      for the callable. Use a forwarding reference (F&&).
//   3. Implement transform_all_erased() — apply a std::function<int(int)> to
//      every element of a vector, returning a new vector.
//   4. Implement transform_all_template() — same as above but with a template
//      parameter for the callable.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <vector>

// Type-erased version: accepts any callable via std::function.
inline int apply_erased(std::function<int(int)> f, int x) {
    TODO();
}

// Template version: accepts any callable via template parameter.
// The compiler knows the exact type of `f` and can inline the call.
template<typename F>
inline int apply_template(F&& f, int x) {
    TODO();
}

// Apply a type-erased function to every element, returning a new vector.
inline std::vector<int> transform_all_erased(
    const std::vector<int>& input,
    std::function<int(int)> f)
{
    TODO();
}

// Apply a templated callable to every element, returning a new vector.
template<typename F>
inline std::vector<int> transform_all_template(
    const std::vector<int>& input,
    F&& f)
{
    TODO();
}
