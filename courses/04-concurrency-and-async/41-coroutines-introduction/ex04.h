// Exercise 04: Chained Coroutines
//
// PROBLEM:
//   Implement two coroutines where one co_awaits the other. The inner
//   coroutine computes a value, and the outer coroutine transforms it.
//
// TODO:
//   Remove the call to ex04_gate() and implement:
//   1. double_value(n) — co_returns n * 2
//   2. double_and_add(n, m) — co_awaits double_value(n), then co_returns
//      that result plus m
//
// WHY:
//   Chaining coroutines is how you compose async operations. One coroutine
//   can co_await another, suspending until the inner coroutine completes.
//   This creates readable, sequential-looking code for what are logically
//   dependent operations.

#pragma once
#include <testkit/testkit.h>
#include <coroutine>
#include <utility>
#include <optional>

// ---------------------------------------------------------------------------
// Task<T> with co_await support — provided infrastructure (do not modify)
// ---------------------------------------------------------------------------
template<typename T>
class Task {
public:
    struct promise_type {
        std::optional<T> result;

        Task get_return_object() {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_value(T value) { result = value; }
        void unhandled_exception() { std::terminate(); }
    };

    // Awaiter — allows one Task to co_await another Task
    bool await_ready() const { return handle_.done(); }
    void await_suspend(std::coroutine_handle<>) {}
    T await_resume() { return handle_.promise().result.value(); }

    explicit Task(std::coroutine_handle<promise_type> h) : handle_(h) {}
    ~Task() { if (handle_) handle_.destroy(); }

    Task(Task&& other) noexcept : handle_(other.handle_) {
        other.handle_ = nullptr;
    }
    Task& operator=(Task&& other) noexcept {
        if (this != &other) {
            if (handle_) handle_.destroy();
            handle_ = other.handle_;
            other.handle_ = nullptr;
        }
        return *this;
    }
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    T result() const { return handle_.promise().result.value(); }
    bool done() const { return handle_.done(); }

private:
    std::coroutine_handle<promise_type> handle_;
};

// ---------------------------------------------------------------------------
// Gate function — remove this call once you implement the coroutines
// ---------------------------------------------------------------------------
inline void ex04_gate() { TODO(); }

// ---------------------------------------------------------------------------
// Student implements these coroutines
// ---------------------------------------------------------------------------

// Returns n * 2 via co_return.
inline Task<int> double_value(int n) {
    ex04_gate();
    co_return 0;
}

// co_awaits double_value(n), then adds m to the result.
inline Task<int> double_and_add(int n, int m) {
    ex04_gate();
    co_return 0;
}
