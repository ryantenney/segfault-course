// Exercise 04: Callback to Coroutine
//
// PROBLEM:
//   Create an awaitable that wraps a callback-based API so it can be
//   used with co_await. The awaitable stores the callback result and
//   makes it available to the coroutine.
//
// TODO:
//   Remove the call to ex04_gate() and implement:
//   1. ReadAwaitable — an awaitable type that wraps async_read_cb.
//   2. coroutine_read() — a coroutine that co_awaits the ReadAwaitable
//      and co_returns the result.
//
// WHY:
//   The real power of coroutines comes from co_await. By wrapping callback
//   APIs into awaitables, you can write async code that looks synchronous.
//   This is exactly how modern async frameworks (like Asio with C++20
//   coroutines) work under the hood: callback-based operations are wrapped
//   in awaitables so coroutines can co_await them.

#pragma once
#include <testkit/testkit.h>
#include <coroutine>
#include <functional>
#include <string>
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

    T result() const { return handle_.promise().result.value(); }
    bool done() const { return handle_.done(); }

private:
    std::coroutine_handle<promise_type> handle_;
};

// ---------------------------------------------------------------------------
// Callback-based API (provided — do not modify)
// ---------------------------------------------------------------------------
inline void async_read_cb(std::function<void(const std::string&)> callback) {
    callback("awaited data");
}

// ---------------------------------------------------------------------------
// Gate function — remove this call once you implement the awaitable
// ---------------------------------------------------------------------------
inline void ex04_gate() { TODO(); }

// ---------------------------------------------------------------------------
// Student implements the awaitable and coroutine
// ---------------------------------------------------------------------------

// An awaitable that wraps async_read_cb.
// When co_awaited, it calls async_read_cb and captures the result.
//
// An awaitable must provide three methods:
//   bool await_ready()      — return true if result is already available
//   void await_suspend(h)   — called if await_ready() returned false
//   T await_resume()        — return the result when the coroutine resumes
//
// Since our callback is synchronous, you can call it in await_suspend
// (or even in the constructor) and store the result. Then await_resume
// returns it.
struct ReadAwaitable {
    std::string data;

    bool await_ready() {
        // Call async_read_cb here and store in data, then return true.
        // Since the callback is synchronous, the result is immediately ready.
        TODO();
        return false;
    }
    void await_suspend(std::coroutine_handle<>) {}
    std::string await_resume() { return data; }
};

// A coroutine that co_awaits ReadAwaitable and returns the result.
inline Task<std::string> coroutine_read() {
    ex04_gate();
    co_return "";
    // Replace the gate and body above with:
    //   co_return co_await ReadAwaitable{};
}
