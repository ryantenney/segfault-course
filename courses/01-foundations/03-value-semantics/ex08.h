// Exercise 08: Dangling Reference
//
// PROBLEM:
//   The function `bad_max()` returns a reference to a local variable.
//   When the function returns, the local is destroyed and the reference
//   dangles — using it is undefined behavior.
//
// TODO:
//   1. Look at `bad_max()` — understand WHY it's broken.
//   2. Implement `safe_max()` which returns the larger value BY VALUE.
//   3. Implement `safe_max_ref()` which returns a CONST REFERENCE to
//      whichever parameter is larger. This is safe because the parameters
//      are references to the caller's objects, which outlive the call.
//
// WHY:
//   Dangling references are one of the most common sources of undefined
//   behavior in C++. The compiler rarely warns about them. You must
//   understand object lifetimes to avoid them.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

// BROKEN: returns a reference to a local variable.
// Uncomment to see the bug — but don't call it in real code!
// inline const std::string& bad_max(const std::string& a, const std::string& b) {
//     std::string result = (a.size() >= b.size()) ? a : b;  // local copy!
//     return result;  // DANGLING — result is destroyed here
// }

// SAFE version 1: return by value (copies the string).
inline std::string safe_max(const std::string& a, const std::string& b) {
    TODO();
}

// SAFE version 2: return a const reference to whichever parameter is longer.
// This is safe because a and b are references to the CALLER's objects.
// If there's a tie, return a.
inline const std::string& safe_max_ref(const std::string& a, const std::string& b) {
    TODO();
}

// EXERCISE: Given a vector element by const reference, this is safe —
// the vector outlives the function call.
// But what if someone passed a temporary? The reference would dangle.
// We prevent that by taking a const reference to a non-temporary.
inline const std::string& first_or_default(
    const std::vector<std::string>& v,
    const std::string& fallback)
{
    TODO();
}
