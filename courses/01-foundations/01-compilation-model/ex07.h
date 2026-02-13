// Exercise 07 — Public interface (read-only)
//
// These functions are implemented in separate translation units
// (ex07_a.cpp and ex07_b.cpp).  Each uses an internal helper function
// named `detail()` — but because the helpers are in anonymous
// namespaces, they have internal linkage and don't conflict.
#pragma once

int compute_a();
int compute_b();
