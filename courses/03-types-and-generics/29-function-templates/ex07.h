// Exercise 07: Default Template Parameter
//
// PROBLEM:
//   Template parameters can have defaults, just like function parameters.
//   This lets you provide a "standard" behavior while allowing callers to
//   customize when needed.
//
//   A common pattern is a comparator or policy parameter:
//     template<typename T, typename Compare = std::less<T>>
//     T min_element(...)
//
// TODO:
//   1. Implement min_of: return the smaller value using the comparator.
//      The default comparator is std::less<T>.
//   2. Implement sort_pair: return a pair with the smaller value first,
//      using the comparator. The default comparator is std::less<T>.
//
// WHY:
//   Default template parameters reduce boilerplate for the common case
//   while keeping the door open for customization. The STL uses this
//   pattern extensively: std::set<T, Compare>, std::map<K, V, Compare>,
//   std::priority_queue<T, Container, Compare>.

#pragma once

#include <functional>
#include <utility>
#include <testkit/testkit.h>

// Return the smaller of a and b according to the comparator.
// Default comparator is std::less<T> (uses operator<).
template<typename T, typename Compare = std::less<T>>
T min_of(T a, T b, Compare comp = Compare{}) {
    TODO();
}

// Return a pair with the smaller value first and the larger second,
// according to the comparator.
template<typename T, typename Compare = std::less<T>>
std::pair<T, T> sort_pair(T a, T b, Compare comp = Compare{}) {
    TODO();
}
