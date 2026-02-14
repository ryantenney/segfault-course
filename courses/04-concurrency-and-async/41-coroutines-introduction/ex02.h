// Exercise 02: Range-for with Generator
//
// PROBLEM:
//   Implement a range() generator that co_yields integers from start up to
//   (but not including) end. The Generator<T> class has been extended with
//   iterator support so you can use it in a range-for loop.
//
// TODO:
//   Remove the call to ex02_gate() and implement range(start, end).
//
// WHY:
//   Generators become truly useful when they integrate with C++ idioms like
//   range-for. By providing begin()/end() and an iterator type, a Generator<T>
//   can be used anywhere an iterable is expected. This is the same pattern
//   Python generators use — but with zero-overhead abstraction.

#pragma once
#include <testkit/testkit.h>
#include <coroutine>
#include <utility>

// ---------------------------------------------------------------------------
// Generator<T> with iterator support — provided infrastructure (do not modify)
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

    // Iterator for range-for support
    struct iterator {
        std::coroutine_handle<promise_type> handle;
        bool done;

        iterator() : handle(nullptr), done(true) {}
        explicit iterator(std::coroutine_handle<promise_type> h) : handle(h), done(false) {
            if (handle) {
                handle.resume();
                done = handle.done();
            }
        }

        T operator*() const { return handle.promise().current_value; }
        iterator& operator++() {
            handle.resume();
            done = handle.done();
            return *this;
        }
        bool operator!=(const iterator& other) const { return done != other.done; }
        bool operator==(const iterator& other) const { return done == other.done; }
    };

    iterator begin() { return iterator{handle_}; }
    iterator end() { return iterator{}; }

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
// Gate function — remove this call once you implement range()
// ---------------------------------------------------------------------------
inline void ex02_gate() { TODO(); }

// ---------------------------------------------------------------------------
// Student implements this coroutine
// ---------------------------------------------------------------------------
// Yields integers from start (inclusive) to end (exclusive).
// Example: range(1, 5) yields 1, 2, 3, 4
inline Generator<int> range(int start, int end) {
    ex02_gate();
    // Replace the above gate and this body with your implementation.
    // Hint: for (int i = start; i < end; ++i) co_yield i;
    co_return;
}
