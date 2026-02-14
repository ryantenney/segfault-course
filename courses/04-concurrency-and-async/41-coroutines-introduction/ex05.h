// Exercise 05: Lazy Evaluation
//
// PROBLEM:
//   Implement a generator that lazily produces the squares of integers
//   from 0 up to (but not including) n. Values are computed only when
//   requested — not all at once.
//
// TODO:
//   Remove the call to ex05_gate() and implement lazy_squares(n).
//
// WHY:
//   Lazy evaluation is a core benefit of generators. Instead of computing
//   all values upfront and storing them in a container, a generator computes
//   each value on demand. This saves memory and allows working with sequences
//   that would be expensive to materialize fully. Think of it like a pipeline:
//   each value flows through one at a time.

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

    bool next() {
        handle_.resume();
        return !handle_.done();
    }
    T value() const { return handle_.promise().current_value; }

private:
    std::coroutine_handle<promise_type> handle_;
};

// ---------------------------------------------------------------------------
// Gate function — remove this call once you implement lazy_squares()
// ---------------------------------------------------------------------------
inline void ex05_gate() { TODO(); }

// ---------------------------------------------------------------------------
// Student implements this coroutine
// ---------------------------------------------------------------------------
// Yields i*i for i from 0 to n-1.
// Example: lazy_squares(4) yields 0, 1, 4, 9
inline Generator<int> lazy_squares(int n) {
    ex05_gate();
    // Replace the above gate and this body with your implementation.
    // Hint: for (int i = 0; i < n; ++i) co_yield i * i;
    co_return;
}
