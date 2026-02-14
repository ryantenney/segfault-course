// Exercise 01: Wrap in a Namespace
//
// CONTEXT:
//   In C++, free functions at global scope risk name collisions with
//   other libraries. Wrapping them in a namespace (like `math::add`)
//   prevents this.
//
// WHAT YOU SEE:
//   The functions below are already inside `namespace math`. The test
//   file calls them as `math::add(2, 3)`.
//
// TODO:
//   Implement all three function bodies.
//
// THINK ABOUT:
//   Without the namespace, two libraries that both define `add()` would
//   cause a linker error. With namespaces, `math::add` and `audio::add`
//   can coexist.

#pragma once

#include <testkit/testkit.h>

namespace math {

// Returns the sum of a and b
inline int add(int a, int b) {
    TODO();
}

// Returns a minus b
inline int subtract(int a, int b) {
    TODO();
}

// Returns a times b
inline int multiply(int a, int b) {
    TODO();
}

} // namespace math
