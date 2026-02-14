// Exercise 05: Identify a Data Race
//
// PROBLEM:
//   When two threads increment a plain int concurrently, the result is
//   undefined behavior — a data race. The fix is to use std::atomic,
//   which provides thread-safe operations.
//
// TODO:
//   Implement safe_increment() so that it atomically increments counter
//   by 1. Use counter.fetch_add(1) or the ++ operator on atomic.
//
// WHY:
//   A data race occurs when two threads access the same memory location
//   concurrently, at least one access is a write, and there's no
//   synchronization. In C++, data races are undefined behavior — not
//   just "you might get the wrong answer," but "literally anything can
//   happen." std::atomic eliminates data races for individual variables.

#pragma once
#include <testkit/testkit.h>
#include <atomic>

// Atomically increments counter by 1.
inline void safe_increment(std::atomic<int>& counter) {
    TODO();
}
