// Exercise 07: Anonymous Namespaces — Translation Unit B
//
// Same name (`detail`), different translation unit.  Without the
// anonymous namespace this would clash with ex07_a.cpp's `detail()`.
//
// TODO: Implement `detail()` so that it returns 7.

#include "ex07.h"

#include <testkit/testkit.h>

namespace {

// Internal helper — only visible in this translation unit.
int detail() {
    TODO();
}

} // anonymous namespace

int compute_b() {
    return detail() * 3;
}
