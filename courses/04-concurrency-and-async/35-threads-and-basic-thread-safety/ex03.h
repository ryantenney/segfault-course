// Exercise 03: jthread Basics
//
// PROBLEM:
//   std::jthread (C++20) is a safer alternative to std::thread. It
//   automatically joins in its destructor, so you can't accidentally
//   forget to join (which would call std::terminate).
//
// TODO:
//   Implement fill_vector() so it pushes back the integers 0 through
//   count-1 into the vector v.
//
// WHY:
//   Forgetting to join a std::thread is undefined behavior in C++ —
//   the destructor calls std::terminate. jthread removes this footgun
//   by joining automatically. It also supports cooperative cancellation
//   via stop_token (see the next exercise).

#pragma once
#include <testkit/testkit.h>
#include <vector>

// Pushes integers 0, 1, ..., count-1 into v.
inline void fill_vector(std::vector<int>& v, int count) {
    TODO();
}
