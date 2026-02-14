// Exercise 03: Perfect Forwarding Wrapper
//
// Perfect forwarding preserves the value category (lvalue/rvalue) of
// arguments as they pass through a wrapper function. Without it, all
// arguments become lvalues inside the wrapper (because named parameters
// are always lvalues), which prevents move semantics.
//
// The pattern:
//   template <typename... Args>
//   auto wrapper(Args&&... args) {
//       return f(std::forward<Args>(args)...);
//   }
//
// std::forward<T>(arg) casts arg back to T&&. If T is an lvalue reference,
// arg stays an lvalue. If T is a non-reference, arg becomes an rvalue.
//
// TODO:
//   Implement log_and_call(f, args...):
//   1. Set the global `call_count` to call_count + 1.
//   2. Perfectly forward all args to f and return the result.

#pragma once

#include <testkit/testkit.h>
#include <utility>
#include <string>

// Global counter incremented by the wrapper.
inline int call_count = 0;

// A wrapper that logs (increments call_count) and forwards all arguments
// to the callable f, preserving their value categories.
//
// The trailing return type uses decltype to deduce the return type from
// the actual call expression. Your implementation should use decltype(auto)
// or this same pattern. The stub uses TODO() which throws before returning.
template <typename F, typename... Args>
auto log_and_call(F&& f, Args&&... args)
    -> decltype(std::forward<F>(f)(std::forward<Args>(args)...))
{
    TODO();
    // Hint:
    //   ++call_count;
    //   return std::forward<F>(f)(std::forward<Args>(args)...);
}
