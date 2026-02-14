// Exercise 07: Thread-local Storage
//
// PROBLEM:
//   thread_local variables have a separate instance per thread. Each
//   thread gets its own copy, initialized independently.
//
// TODO:
//   1. Remove the call to ex07_gate() in get_call_count().
//   2. Implement get_call_count() so that it uses a thread_local int
//      to count how many times it has been called within the current
//      thread. Each call should increment the count and return the
//      new value (first call returns 1, second returns 2, etc.).
//
// HINT:
//   thread_local int count = 0;
//   return ++count;
//
// WHY:
//   Thread-local storage lets you have per-thread state without
//   synchronization. It's useful for caches, counters, error codes,
//   and other data that doesn't need to be shared between threads.

#pragma once
#include <testkit/testkit.h>

inline void ex07_gate() { TODO(); }

// Returns the number of times this function has been called
// on the current thread. First call returns 1.
inline int get_call_count() {
    ex07_gate();  // Remove this line and implement
    return 0;
}
