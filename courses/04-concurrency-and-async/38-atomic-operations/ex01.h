// Exercise 01: Atomic Counter
//
// PROBLEM:
//   Without synchronization, incrementing a shared integer from multiple
//   threads is a data race (undefined behavior). std::atomic<int> provides
//   lock-free, thread-safe operations on integers.
//
//   The simplest atomic operations are ++ (pre/post increment) and load():
//     std::atomic<int> counter{0};
//     counter++;           // atomic increment
//     int val = counter;   // atomic load (implicit conversion)
//
// TODO:
//   Implement the AtomicCounter class:
//     1. increment() -- atomically increment the internal counter.
//     2. get() -- return the current value of the counter.
//     3. reset() -- set the counter back to zero.
//
// HINT:
//   - std::atomic<int> supports ++, load(), and store().
//   - The default memory order (seq_cst) is fine for all operations.

#pragma once

#include <atomic>
#include <testkit/testkit.h>

class AtomicCounter {
    std::atomic<int> count_{0};

public:
    // Atomically increment the counter by 1.
    void increment() {
        TODO();
    }

    // Return the current value of the counter.
    int get() {
        TODO();
    }

    // Reset the counter to zero.
    void reset() {
        TODO();
    }
};
