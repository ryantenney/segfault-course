// Exercise 01: Basic Object Pool
//
// PROBLEM:
//   An object pool keeps a collection of reusable objects. Instead of
//   creating and destroying objects repeatedly, you acquire one from the
//   pool, use it, and release it back when you're done. This avoids
//   expensive allocation and construction costs.
//
//   The simplest pool is a stack of pre-built objects: acquire() pops one
//   off the top, release() pushes it back.
//
// TODO:
//   Implement Pool<T>:
//     1. Constructor: takes a vector<T> of initial objects to stock the pool.
//     2. acquire() -- remove and return the next available object.
//        Throw std::runtime_error("pool exhausted") if the pool is empty.
//     3. release(T obj) -- return an object to the pool for reuse.
//     4. available() -- return the number of objects currently in the pool.
//
// HINT:
//   - Use a std::vector<T> as internal storage. push_back / pop_back
//     give you stack semantics.
//   - acquire() should move the object out when returning it.

#pragma once

#include <stdexcept>
#include <vector>
#include <testkit/testkit.h>

template <typename T>
class Pool {
    std::vector<T> objects_;

public:
    // Stock the pool with the given initial objects.
    explicit Pool(std::vector<T> initial) {
        TODO();
    }

    // Remove and return the next available object.
    // Throws std::runtime_error("pool exhausted") if empty.
    T acquire() {
        TODO();
    }

    // Return an object to the pool.
    void release(T obj) {
        TODO();
    }

    // Return the number of objects currently available.
    std::size_t available() const {
        TODO();
    }
};
