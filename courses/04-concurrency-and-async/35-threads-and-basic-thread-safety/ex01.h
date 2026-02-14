// Exercise 01: Launch and Join
//
// PROBLEM:
//   Start a thread that runs a function and join() it to wait for
//   completion. After the thread finishes, read the result it produced.
//
// TODO:
//   Implement compute_answer() so that it sets `result` to 42.
//
// WHY:
//   std::thread is the fundamental building block of concurrency in C++.
//   Launching a thread runs a callable in a new OS thread. Calling join()
//   blocks until that thread finishes — and also ensures all writes made
//   by the thread are visible to the caller (happens-before relationship).

#pragma once
#include <testkit/testkit.h>

// Sets result to 42.
inline void compute_answer(int& result) {
    TODO();
}
