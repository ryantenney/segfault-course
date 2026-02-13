// Exercise 07: Anonymous Namespaces — Translation Unit A
//
// This file and ex07_b.cpp both define a helper function called
// `detail()`.  Normally, having two functions with the same name
// and external linkage in different TUs causes a linker error
// (multiple definitions of `detail`).
//
// The anonymous namespace gives `detail()` INTERNAL LINKAGE — it's
// only visible within this translation unit, so it can't conflict
// with the `detail()` in ex07_b.cpp.
//
// TODO: Implement `detail()` so that it returns 42.

#include "ex07.h"

#include <testkit/testkit.h>

namespace {

// Internal helper — only visible in this translation unit.
int detail() {
    TODO();
}

} // anonymous namespace

int compute_a() {
    return detail() + 10;
}
