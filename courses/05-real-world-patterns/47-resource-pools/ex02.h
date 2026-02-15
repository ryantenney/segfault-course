// Exercise 02: RAII Pool Handle
//
// PROBLEM:
//   Manually calling release() is error-prone. If an exception is thrown
//   or the caller forgets, the object leaks out of the pool. An RAII
//   handle solves this: when the handle goes out of scope, it automatically
//   returns the object to the pool.
//
// TODO:
//   Implement PoolHandle<T>:
//     1. Constructor: takes a T object and a pointer to the Pool<T> it
//        came from. Stores both.
//     2. Destructor: if the handle still owns an object, release it back
//        to the pool.
//     3. operator*() / operator->(): provide access to the held object.
//     4. Move constructor and move assignment: transfer ownership.
//        The moved-from handle must not return anything to the pool.
//     5. Delete copy constructor and copy assignment.
//
//   Use the Pool<T> from exercise 01 (included below for convenience).
//
// HINT:
//   - Use std::optional<T> or a bool flag to track whether the handle
//     still owns the object.
//   - The destructor must NOT throw. Don't use TODO() in it; instead,
//     leave a comment for the student to fill in.

#pragma once

#include <optional>
#include <stdexcept>
#include <vector>
#include <testkit/testkit.h>

// Minimal pool (same as ex01, provided here so ex02 is self-contained).
template <typename T>
class Pool02 {
    std::vector<T> objects_;

public:
    explicit Pool02(std::vector<T> initial) : objects_(std::move(initial)) {}

    T acquire() {
        if (objects_.empty()) throw std::runtime_error("pool exhausted");
        T obj = std::move(objects_.back());
        objects_.pop_back();
        return obj;
    }

    void release(T obj) { objects_.push_back(std::move(obj)); }
    std::size_t available() const { return objects_.size(); }
};

template <typename T>
class PoolHandle {
    std::optional<T> obj_;
    Pool02<T>* pool_;

public:
    // Construct a handle that owns `obj` and will return it to `pool`.
    PoolHandle(T obj, Pool02<T>* pool) : pool_(pool) {
        TODO();
    }

    // Destructor: return the object to the pool if still owned.
    // Do NOT use TODO() here — fill in the body directly.
    ~PoolHandle() {
        // TODO: if obj_.has_value(), call pool_->release(std::move(*obj_));
    }

    // Move constructor: transfer ownership from other.
    PoolHandle(PoolHandle&& other) noexcept
        : obj_(std::move(other.obj_)), pool_(other.pool_) {
        other.obj_.reset();
    }

    // Move assignment: release current if owned, then take from other.
    PoolHandle& operator=(PoolHandle&& other) noexcept {
        if (this != &other) {
            if (obj_.has_value()) {
                pool_->release(std::move(*obj_));
            }
            obj_ = std::move(other.obj_);
            pool_ = other.pool_;
            other.obj_.reset();
        }
        return *this;
    }

    // Non-copyable.
    PoolHandle(const PoolHandle&) = delete;
    PoolHandle& operator=(const PoolHandle&) = delete;

    // Access the held object.
    T& operator*() {
        TODO();
    }

    const T& operator*() const {
        TODO();
    }

    T* operator->() {
        TODO();
    }

    const T* operator->() const {
        TODO();
    }
};
