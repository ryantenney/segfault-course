// Exercise 05: Pool with Health Check
//
// PROBLEM:
//   Objects in a pool can become stale or invalid (e.g., a database
//   connection that was closed by the server). Before handing an object
//   to a caller, the pool should validate it. If the check fails, the
//   pool discards that object and tries the next one. If there are no
//   healthy objects, the pool creates a new one via the factory.
//
// TODO:
//   Implement HealthCheckPool<T>:
//     1. Constructor: takes a factory, a health_check predicate, and
//        max_size.
//     2. acquire() -- pop idle objects, run the health check on each.
//        Discard unhealthy ones (do not count them toward the limit
//        any more). Return the first healthy one. If no healthy idle
//        objects remain, create a new one via the factory (if under
//        max_size), otherwise throw std::runtime_error("pool at capacity").
//     3. release(T obj) -- push the object back to idle (no check here).
//     4. idle_count() / total_created() / discarded() -- statistics.
//
// HINT:
//   - Keep a discard counter. When an unhealthy object is discarded,
//     increment it and decrement the alive count (so the pool can
//     create replacements).

#pragma once

#include <functional>
#include <stdexcept>
#include <vector>
#include <testkit/testkit.h>

template <typename T>
class HealthCheckPool {
    std::function<T()> factory_;
    std::function<bool(const T&)> health_check_;
    std::size_t max_size_;
    std::vector<T> idle_;
    std::size_t alive_ = 0;     // objects currently alive (idle + in-use)
    std::size_t created_ = 0;   // total ever created
    std::size_t discarded_ = 0; // total discarded by health check

public:
    HealthCheckPool(std::function<T()> factory,
                    std::function<bool(const T&)> health_check,
                    std::size_t max_size)
        : factory_(std::move(factory)),
          health_check_(std::move(health_check)),
          max_size_(max_size) {}

    // Acquire a healthy object from the pool.
    T acquire() {
        TODO();
    }

    // Return an object to the idle pool.
    void release(T obj) {
        TODO();
    }

    std::size_t idle_count() const { return idle_.size(); }
    std::size_t total_created() const { return created_; }
    std::size_t discarded() const { return discarded_; }
};
