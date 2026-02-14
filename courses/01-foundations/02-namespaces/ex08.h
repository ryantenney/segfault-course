// Exercise 08: ADL-Friendly Swap
//
// PROBLEM:
//   The standard idiom for swapping in generic code is:
//     using std::swap;
//     swap(a, b);
//
//   This two-step pattern lets ADL find a custom swap in the type's
//   namespace if one exists, while falling back to std::swap otherwise.
//
//   If you write `std::swap(a, b)` directly, you bypass ADL and always
//   get the generic version — which may be less efficient for types
//   that have a custom swap.
//
// TODO:
//   1. Implement Pair::swap() as a member function that swaps both
//      fields with the partner.
//   2. Implement the free function `swap(Pair&, Pair&)` in the
//      `container` namespace (it should call a.swap(b)).
//   3. Implement `generic_sort_pair()` using the two-step idiom:
//        using std::swap;
//        swap(a, b);
//      This lets ADL find container::swap for Pair objects.
//
// WHY:
//   This is one of the most important C++ idioms. The STL algorithms
//   use this pattern internally. If you write a custom type with an
//   efficient swap, following this convention means the STL can use it.

#pragma once

#include <testkit/testkit.h>
#include <algorithm>  // std::swap
#include <string>

namespace container {

struct Pair {
    int first;
    int second;

    // Member swap: exchange contents with another Pair
    void swap(Pair& other) {
        TODO();
    }
};

// Free-function swap found by ADL when swapping Pair objects
inline void swap(Pair& a, Pair& b) {
    TODO();
}

} // namespace container

// Uses the two-step swap idiom to sort a pair so that first <= second.
// TODO: Use `using std::swap; swap(p.first, p.second);` for ints,
// and the same idiom works for Pair objects via ADL.
inline void sort_pair(container::Pair& p) {
    TODO();
}

// Swaps two Pair objects using the two-step idiom.
// ADL will find container::swap.
inline void generic_swap_pairs(container::Pair& a, container::Pair& b) {
    TODO();
}
