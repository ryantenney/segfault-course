// Exercise 07: Variadic Forwarding
//
// Variadic templates + perfect forwarding let you write functions that
// accept any number of arguments of any types, preserving the value
// category of each one.
//
// The pack expansion `std::forward<Args>(args)...` applies std::forward
// to each argument independently. An lvalue stays an lvalue, an rvalue
// stays an rvalue.
//
// TODO:
//   1. Implement apply_to_each(f, args...): call f once for each argument,
//      perfectly forwarding each one individually.
//
//   2. Implement forward_to(target, args...): call
//      target(std::forward<Args>(args)...) -- forwarding all args at once
//      to a single function call.
//
//   3. Implement count_args(args...): return the number of arguments
//      (sizeof...(args)).

#pragma once

#include <testkit/testkit.h>
#include <utility>
#include <string>

// Call f(arg) for each argument, perfectly forwarding each one.
template <typename F, typename... Args>
void apply_to_each(F&& f, Args&&... args) {
    TODO();
    // Hint: Use a fold expression:
    //   (f(std::forward<Args>(args)), ...);
    // Or use an initializer list trick.
}

// Forward all arguments to target in a single call.
template <typename F, typename... Args>
auto forward_to(F&& target, Args&&... args)
    -> decltype(std::forward<F>(target)(std::forward<Args>(args)...))
{
    TODO();
    // Hint: return std::forward<F>(target)(std::forward<Args>(args)...);
}

// Return the number of arguments in the pack.
template <typename... Args>
std::size_t count_args(Args&&...) {
    TODO();
    // Hint: return sizeof...(Args);
}
