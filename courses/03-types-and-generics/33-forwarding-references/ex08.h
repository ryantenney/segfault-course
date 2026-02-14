// Exercise 08: decltype(auto) Return
//
// When writing a forwarding wrapper, the return type matters just as much
// as the argument types. If the wrapped function returns a reference, your
// wrapper should return a reference too -- not a copy.
//
// `decltype(auto)` deduces the return type exactly, preserving references:
//   - If the expression is an lvalue, decltype(auto) deduces a reference.
//   - If the expression is a prvalue, decltype(auto) deduces a value.
//
// Compare with plain `auto`, which ALWAYS strips references and const.
//
// TODO:
//   1. Implement forward_result(f, args...): call f with perfectly forwarded
//      args and return the result using decltype(auto) to preserve the exact
//      return type (including references).
//
//   2. Implement get_or_default(ptr, default_val): if ptr is not null, return
//      *ptr (a reference to the pointed-to value). If null, return default_val.
//      Use decltype(auto) for the return type.
//      NOTE: Be careful -- both branches must return the same value category.
//      Return *ptr when non-null, and default_val (which is a reference param)
//      when null.

#pragma once

#include <testkit/testkit.h>
#include <utility>
#include <string>

// Forward the call to f and preserve the exact return type.
// The trailing return type deduces the exact type from the call expression.
template <typename F, typename... Args>
auto forward_result(F&& f, Args&&... args)
    -> decltype(std::forward<F>(f)(std::forward<Args>(args)...))
{
    TODO();
    // Hint: return std::forward<F>(f)(std::forward<Args>(args)...);
}

// If ptr is non-null, return a reference to *ptr.
// If ptr is null, return a reference to default_val.
template <typename T>
const T& get_or_default(const T* ptr, const T& default_val) {
    TODO();
    // Hint: return ptr ? *ptr : default_val;
}
