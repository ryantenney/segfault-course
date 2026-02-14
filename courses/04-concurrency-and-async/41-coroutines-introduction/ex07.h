// Exercise 07: Exception in Coroutine
//
// PROBLEM:
//   Implement a generator that may throw an exception during execution.
//   The exception should propagate to the caller when they resume the
//   coroutine.
//
// TODO:
//   Remove the call to ex07_gate() and implement:
//   1. validated_range(start, end) — a generator that yields integers from
//      start to end-1, but throws std::invalid_argument if start > end.
//
// WHY:
//   Coroutines need to handle errors just like regular functions. When a
//   coroutine throws, the exception is captured by the promise's
//   unhandled_exception() handler. Our ThrowingGenerator propagates the
//   exception on the next resume, so the caller sees it at the call site.
//   This makes error handling in coroutines feel natural.

#pragma once
#include <testkit/testkit.h>
#include <coroutine>
#include <utility>
#include <stdexcept>
#include <exception>

// ---------------------------------------------------------------------------
// ThrowingGenerator<T> — like Generator but propagates exceptions
// ---------------------------------------------------------------------------
template<typename T>
class ThrowingGenerator {
public:
    struct promise_type {
        T current_value{};
        std::exception_ptr exception;

        ThrowingGenerator get_return_object() {
            return ThrowingGenerator{
                std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }
        void return_void() {}
        void unhandled_exception() { exception = std::current_exception(); }
    };

    explicit ThrowingGenerator(std::coroutine_handle<promise_type> h)
        : handle_(h) {}
    ~ThrowingGenerator() { if (handle_) handle_.destroy(); }

    ThrowingGenerator(ThrowingGenerator&& other) noexcept
        : handle_(other.handle_) {
        other.handle_ = nullptr;
    }
    ThrowingGenerator& operator=(ThrowingGenerator&& other) noexcept {
        if (this != &other) {
            if (handle_) handle_.destroy();
            handle_ = other.handle_;
            other.handle_ = nullptr;
        }
        return *this;
    }
    ThrowingGenerator(const ThrowingGenerator&) = delete;
    ThrowingGenerator& operator=(const ThrowingGenerator&) = delete;

    // Resumes the coroutine. If it threw an exception, rethrows it here.
    bool next() {
        handle_.resume();
        if (handle_.promise().exception) {
            std::rethrow_exception(handle_.promise().exception);
        }
        return !handle_.done();
    }
    T value() const { return handle_.promise().current_value; }

private:
    std::coroutine_handle<promise_type> handle_;
};

// ---------------------------------------------------------------------------
// Gate function — remove this call once you implement validated_range()
// ---------------------------------------------------------------------------
inline void ex07_gate() { TODO(); }

// ---------------------------------------------------------------------------
// Student implements this coroutine
// ---------------------------------------------------------------------------
// Yields integers from start to end-1.
// Throws std::invalid_argument("start must not exceed end") if start > end.
inline ThrowingGenerator<int> validated_range(int start, int end) {
    ex07_gate();
    // Replace the above gate and this body with your implementation.
    // Hint:
    //   if (start > end) throw std::invalid_argument("start must not exceed end");
    //   for (int i = start; i < end; ++i) co_yield i;
    co_return;
}
