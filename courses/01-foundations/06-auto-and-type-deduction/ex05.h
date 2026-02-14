// Exercise 05: decltype for Expression Types
//
// PROBLEM:
//   decltype(expr) gives you the exact type of an expression without
//   evaluating it. This is useful when you need a variable whose type
//   matches another expression, especially in generic code.
//
//   Key rules:
//     decltype(variable)    → declared type of that variable
//     decltype(expression)  → type of the expression (with references)
//     decltype(auto)        → deduces using decltype rules (preserves refs)
//
// TODO:
//   Use decltype to declare variables or return types that match the
//   specified expressions.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

// Return a variable whose type matches the element type of the vector.
// Use decltype(v[0]) or decltype(v)::value_type to deduce the type.
// The function should return the sum of all elements.
inline int sum_with_decltype(const std::vector<int>& v) {
    TODO();
    // Hint: decltype(v)::value_type total = 0; then loop
}

// Return the size of the vector using a variable whose type is
// deduced via decltype to match v.size().
inline std::size_t deduced_size(const std::vector<std::string>& v) {
    TODO();
    // Hint: decltype(v.size()) n = v.size(); return n;
}

// Use decltype to declare a result variable that matches the type
// produced by (a * b). Return a * b + c.
inline double multiply_add(double a, double b, double c) {
    TODO();
    // Hint: decltype(a * b) result = a * b; return result + c;
}

// Use decltype to declare a string variable that matches another
// string's type. Return a copy of the input reversed.
inline std::string reversed(const std::string& s) {
    TODO();
    // Hint: decltype(s) is const std::string&, but you want a copy.
    // Use std::remove_cvref_t<decltype(s)> or just auto.
    // Reverse using std::string(s.rbegin(), s.rend())
}
