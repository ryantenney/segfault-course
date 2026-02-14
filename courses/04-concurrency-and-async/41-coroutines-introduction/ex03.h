// Exercise 03: Simple Coroutine Task
//
// PROBLEM:
//   Implement a coroutine that uses co_return to produce a result.
//   A Task<T> coroutine computes a value and returns it, unlike a Generator
//   which yields a sequence.
//
// TODO:
//   Remove the call to ex03_gate() and implement compute_task(n) so that
//   it co_returns n * n.
//
// WHY:
//   While generators produce sequences of values with co_yield, tasks produce
//   a single result with co_return. This is the foundation for async tasks —
//   a coroutine that does some work and returns a result. The Task<T>
//   infrastructure handles the promise_type plumbing for you.

#pragma once
#include <testkit/testkit.h>
#include <coroutine>
#include <utility>
#include <optional>

// ---------------------------------------------------------------------------
// Task<T> — provided infrastructure (do not modify)
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

    // Get the result. The task runs eagerly (initial_suspend is suspend_never),
    // so the result is available immediately after construction.
    T result() const { return handle_.promise().result.value(); }

    bool done() const { return handle_.done(); }

private:
    std::coroutine_handle<promise_type> handle_;
};

// ---------------------------------------------------------------------------
// Gate function — remove this call once you implement compute_task()
// ---------------------------------------------------------------------------
inline void ex03_gate() { TODO(); }

// ---------------------------------------------------------------------------
// Student implements this coroutine
// ---------------------------------------------------------------------------
// Returns n squared via co_return.
inline Task<int> compute_task(int n) {
    ex03_gate();
    // Replace the above gate and this body with your implementation.
    // Hint: co_return n * n;
    co_return 0;
}
