// Exercise 01: Generator Basics
//
// PROBLEM:
//   Implement a Fibonacci sequence generator using C++20 coroutines.
//   The generator should co_yield successive Fibonacci numbers: 0, 1, 1, 2, 3, 5, 8, ...
//
// TODO:
//   Remove the call to ex01_gate() and implement fibonacci() so that it
//   co_yields Fibonacci numbers starting from 0.
//
// WHY:
//   Generators are the simplest coroutine pattern. A generator suspends after
//   each co_yield, allowing the caller to pull values one at a time. This is
//   lazy evaluation: values are computed on demand, not all at once. The
//   Generator<T> infrastructure (promise_type, handle management) is provided
//   for you — focus on the coroutine body.

#pragma once
#include <testkit/testkit.h>
#include <coroutine>
#include <utility>

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

    // Advance to the next value. Returns false if the coroutine is done.
    bool next() {
        handle_.resume();
        return !handle_.done();
    }

    // Get the current yielded value.
    T value() const { return handle_.promise().current_value; }

private:
    std::coroutine_handle<promise_type> handle_;
};

// ---------------------------------------------------------------------------
// Gate function — remove this call once you implement fibonacci()
// ---------------------------------------------------------------------------
inline void ex01_gate() { TODO(); }

// ---------------------------------------------------------------------------
// Student implements this coroutine
// ---------------------------------------------------------------------------
// Yields Fibonacci numbers: 0, 1, 1, 2, 3, 5, 8, 13, ...
inline Generator<int> fibonacci() {
    ex01_gate();
    // Replace the above gate and this body with your implementation.
    // Hint: co_yield 0; co_yield 1; then loop adding the previous two.
    co_return;
}
