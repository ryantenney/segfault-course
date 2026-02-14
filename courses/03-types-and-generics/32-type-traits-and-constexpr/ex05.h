// Exercise 05: Type Manipulation
//
// Type traits don't just query types -- they can transform them.
//
//   std::remove_reference_t<int&>    => int
//   std::remove_const_t<const int>   => int
//   std::decay_t<const int&>         => int   (removes ref, const, and decays arrays/functions)
//   std::add_const_t<int>            => const int
//
// These are essential in template code where T might arrive as "int&",
// "const std::string&", or "int[5]" -- and you need the "plain" type.
//
// TODO:
//   1. Implement type_name_of<T>():
//      - If decay_t<T> is int, return "int".
//      - If decay_t<T> is double, return "double".
//      - If decay_t<T> is std::string, return "string".
//      - Otherwise, return "other".
//      (Use std::is_same_v with std::decay_t<T> to compare.)
//
//   2. Implement are_same_after_decay<T, U>():
//      Return true if T and U are the same type after applying std::decay_t.
//
//   3. Implement store_value<T>(T&& val):
//      Return a std::decay_t<T> copy of val. This strips references and const,
//      giving you a plain owned value.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <type_traits>

// Return a string naming the decayed type of T.
template <typename T>
std::string type_name_of() {
    TODO();
}

// Return true if T and U are the same type after decay.
template <typename T, typename U>
bool are_same_after_decay() {
    TODO();
}

// Return a decayed (owned) copy of val.
template <typename T>
auto store_value(T&& val) -> std::decay_t<T> {
    TODO();
}
