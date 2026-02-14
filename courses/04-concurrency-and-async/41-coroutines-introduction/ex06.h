// Exercise 06: Infinite Sequence
//
// PROBLEM:
//   Implement an infinite generator and a function that consumes a finite
//   number of values from it.
//
// TODO:
//   Remove the call to ex06_gate() and implement:
//   1. naturals() — an infinite generator yielding 0, 1, 2, 3, ...
//   2. take(gen, n) — pulls exactly n values from the generator and returns
//      them in a vector.
//
// WHY:
//   Infinite sequences are a powerful abstraction that generators make
//   practical. Since values are computed lazily, an infinite generator uses
//   constant memory — it only produces a value when asked. The take()
//   function demonstrates how to safely consume a finite prefix of an
//   infinite sequence.

#pragma once
#include <testkit/testkit.h>
#include <coroutine>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Generator<T> — provided infrastructure (do not modify)
// ---------------------------------------------------------------------------
template<typename T>
class Generator {
public:
    struct promise_type {
        T current_value{};

        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    explicit Generator(std::coroutine_handle<promise_type> h) : handle_(h) {}
    ~Generator() { if (handle_) handle_.destroy(); }

    Generator(Generator&& other) noexcept : handle_(other.handle_) {
        other.handle_ = nullptr;
    }
    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (handle_) handle_.destroy();
            handle_ = other.handle_;
            other.handle_ = nullptr;
        }
        return *this;
    }
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;

    bool next() {
        handle_.resume();
        return !handle_.done();
    }
    T value() const { return handle_.promise().current_value; }

private:
    std::coroutine_handle<promise_type> handle_;
};

// ---------------------------------------------------------------------------
// Gate function — remove this call once you implement the functions
// ---------------------------------------------------------------------------
inline void ex06_gate() { TODO(); }

// ---------------------------------------------------------------------------
// Student implements these
// ---------------------------------------------------------------------------

// Infinite generator yielding 0, 1, 2, 3, ...
inline Generator<int> naturals() {
    ex06_gate();
    // Replace the above gate and this body with your implementation.
    // Hint: for (int i = 0; ; ++i) co_yield i;
    co_return;
}

// Pulls exactly n values from the generator and returns them in a vector.
inline std::vector<int> take(Generator<int>& gen, int n) {
    TODO();
    // Hint: call gen.next() n times and collect gen.value()
}
