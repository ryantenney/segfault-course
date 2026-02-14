// Exercise 05: Atomic Accumulation
//
// PROBLEM:
//   std::atomic<int> provides fetch_add() and fetch_sub() which atomically
//   add/subtract a value and return the PREVIOUS value. These are more
//   efficient than a CAS loop for simple arithmetic.
//
//     std::atomic<int> x{10};
//     int old = x.fetch_add(3);  // old == 10, x is now 13
//     old = x.fetch_sub(5);      // old == 13, x is now 8
//
// TODO:
//   Implement the StatsCounter class:
//     1. add(int n) -- atomically add n to the counter. Return the
//        value BEFORE the addition.
//     2. subtract(int n) -- atomically subtract n. Return the value
//        BEFORE the subtraction.
//     3. get() -- return the current value.
//
// HINT:
//   - fetch_add returns the old value, which is what add() should return.
//   - fetch_sub returns the old value, which is what subtract() should return.

#pragma once

#include <atomic>
#include <testkit/testkit.h>

class StatsCounter {
    std::atomic<int> value_{0};

public:
    // Atomically add n to the counter. Return the value BEFORE the add.
    int add(int n) {
        TODO();
    }

    // Atomically subtract n from the counter. Return the value BEFORE the sub.
    int subtract(int n) {
        TODO();
    }

    // Return the current value.
    int get() {
        TODO();
    }
};
