// Exercise 07: ADL Basics
//
// PROBLEM:
//   Argument-Dependent Lookup (ADL) means that when you call an
//   unqualified function, the compiler also searches the namespaces
//   of the argument types. This is why `std::cout << x` works without
//   writing `std::operator<<(std::cout, x)`.
//
//   But ADL can also cause surprises. In this exercise, both the
//   `geometry` namespace and global scope define a `describe()` function.
//   You need to understand which one gets called and why.
//
// TODO:
//   1. Implement geometry::describe(const Circle&) to return
//      "circle(r=<radius>)" using std::to_string.
//   2. Implement describe_shape() which takes a geometry::Circle and
//      should call geometry::describe (not the global one).
//      Think about how ADL helps here.
//   3. Implement describe_number() which takes an int and must call
//      the global describe (since int has no associated namespace).
//
// WHY:
//   Understanding ADL is essential because it's why operators and
//   friend functions "just work" with custom types. It also explains
//   some surprising overload resolution behavior.

#pragma once

#include <testkit/testkit.h>
#include <string>

namespace geometry {

struct Circle {
    double radius;
};

// ADL will find this when called with a Circle argument
inline std::string describe(const Circle& c) {
    TODO();
}

} // namespace geometry

// A global describe for plain integers
inline std::string describe(int value) {
    return "int(" + std::to_string(value) + ")";
}

// TODO: Call describe() with the circle argument.
// ADL will find geometry::describe because Circle is in the geometry namespace.
inline std::string describe_shape(const geometry::Circle& c) {
    TODO();
}

// TODO: Call describe() with the integer argument.
// No ADL here — int has no associated namespace, so only the global
// describe is found by normal unqualified lookup.
inline std::string describe_number(int n) {
    TODO();
}
