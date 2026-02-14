// Exercise 08: Thread-safe Wrapper
//
// PROBLEM:
//   Implement a generic Synchronized<T> wrapper that protects any
//   value with a mutex. Access is only possible through an apply()
//   method that takes a callable — the callable receives a reference
//   to the wrapped value while the mutex is held.
//
// TODO:
//   1. Implement apply() — lock the mutex, call the function with
//      a reference to value_, and return whatever the function returns.
//   2. Implement apply() const — same, but with a shared reference.
//
// HINT:
//   template <typename F>
//   auto apply(F&& f) -> decltype(f(value_)) {
//       std::lock_guard<std::mutex> lock(mtx_);
//       return f(value_);
//   }
//
// WHY:
//   This pattern makes it impossible to access the protected data
//   without holding the lock. Unlike exposing getters/setters, the
//   apply() approach guarantees the lock is held for the entire
//   operation, preventing "check-then-act" races.

#pragma once
#include <testkit/testkit.h>
#include <mutex>
#include <utility>

template <typename T>
class Synchronized {
    T value_;
    mutable std::mutex mtx_;

public:
    explicit Synchronized(T initial) : value_(std::move(initial)) {}

    // Locks the mutex and calls f(value_). Returns whatever f returns.
    template <typename F>
    auto apply(F&& f) -> decltype(f(value_)) {
        TODO();
    }

    // Locks the mutex and calls f(value_) const. Returns whatever f returns.
    template <typename F>
    auto apply(F&& f) const -> decltype(f(std::declval<const T&>())) {
        TODO();
    }
};
