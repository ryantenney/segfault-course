// Exercise 06: Pool Statistics
//
// PROBLEM:
//   For monitoring and debugging, pools should expose usage statistics:
//   how many objects are currently checked out (active), how many are
//   sitting idle, and how many have been created in total.
//
// TODO:
//   Implement StatsPool<T>:
//     1. Constructor: takes a vector<T> of initial objects.
//     2. acquire() -- pop an idle object, increment active count.
//        Throw std::runtime_error("pool exhausted") if empty.
//     3. release(T obj) -- push back, decrement active count.
//     4. active_count() -- objects currently checked out.
//     5. idle_count() -- objects currently available in the pool.
//     6. total_created() -- total objects that have ever entered the pool
//        (initial + any added later, but for this exercise just the
//        initial set size).
//
// HINT:
//   - active_count = total_created - idle_count at any consistent point,
//     but tracking it explicitly is clearer and avoids races if you later
//     add thread safety.

#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <testkit/testkit.h>

template <typename T>
class StatsPool {
    std::vector<T> idle_;
    std::size_t active_ = 0;
    std::size_t total_created_ = 0;

public:
    // Stock the pool with initial objects.
    explicit StatsPool(std::vector<T> initial) {
        TODO();
    }

    // Acquire an idle object; throws if none available.
    T acquire() {
        TODO();
    }

    // Return an object to the pool.
    void release(T obj) {
        TODO();
    }

    // Number of objects currently checked out.
    std::size_t active_count() const {
        TODO();
    }

    // Number of objects currently idle in the pool.
    std::size_t idle_count() const {
        TODO();
    }

    // Total objects ever added to the pool.
    std::size_t total_created() const {
        TODO();
    }
};
