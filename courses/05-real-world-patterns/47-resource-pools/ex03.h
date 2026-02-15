// Exercise 03: Pool with Factory
//
// PROBLEM:
//   A fixed-size pool runs out quickly. A factory pool creates new objects
//   on demand when the pool is empty, up to a maximum capacity. Once the
//   max is reached, acquire() throws instead of creating more objects.
//
// TODO:
//   Implement FactoryPool<T>:
//     1. Constructor: takes a factory function (std::function<T()>) and
//        a max_size. The pool starts empty.
//     2. acquire() -- if an idle object is available, return it.
//        Otherwise, if total_created < max_size, call the factory to
//        create a new one. If at capacity, throw
//        std::runtime_error("pool at capacity").
//     3. release(T obj) -- return an object to the idle pool.
//     4. idle_count() -- number of objects sitting idle in the pool.
//     5. total_created() -- total number of objects ever created by
//        the factory.
//
// HINT:
//   - Keep a vector<T> for idle objects and a size_t counter for
//     total objects ever created by the factory.

#pragma once

#include <functional>
#include <stdexcept>
#include <vector>
#include <testkit/testkit.h>

template <typename T>
class FactoryPool {
    std::function<T()> factory_;
    std::size_t max_size_;
    std::vector<T> idle_;
    std::size_t created_ = 0;

public:
    // Create a pool that uses `factory` to make new objects,
    // up to `max_size` total.
    FactoryPool(std::function<T()> factory, std::size_t max_size)
        : factory_(std::move(factory)), max_size_(max_size) {}

    // Acquire an object: reuse idle, or create via factory, or throw.
    T acquire() {
        TODO();
    }

    // Return an object to the idle pool.
    void release(T obj) {
        TODO();
    }

    // Number of idle objects available for reuse.
    std::size_t idle_count() const {
        TODO();
    }

    // Total number of objects ever created by the factory.
    std::size_t total_created() const {
        TODO();
    }
};
