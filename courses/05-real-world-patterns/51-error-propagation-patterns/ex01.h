// Exercise 01: Result Type
//
// std::expected is not available on Apple Clang, so we build our own
// Result<T, E> type on top of std::variant. A Result holds either a
// success value of type T or an error value of type E.
//
// The variant stores an Ok<T> wrapper (index 0) for success and an
// Err<E> wrapper (index 1) for failure. The wrappers disambiguate
// when T and E are the same type.
//
// TODO:
//   1. Remove the TODO() from the Ok constructor body.
//   2. Remove the TODO() from the Err constructor body.
//   3. Implement is_ok()   — true when the variant holds Ok<T>.
//      Hint: check data_.index() or use std::holds_alternative.
//   4. Implement is_error() — true when the variant holds Err<E>.
//   5. Implement value()   — return the T inside Ok; throw if error.
//      Hint: use std::get<Ok<T>>(data_).val.
//   6. Implement error()   — return the E inside Err; throw if ok.

#pragma once

#include <testkit/testkit.h>
#include <stdexcept>
#include <string>
#include <variant>

// ---------------------------------------------------------------------------
// Tag wrappers — disambiguate T and E even when they are the same type.
// ---------------------------------------------------------------------------

template <typename T>
struct Ok {
    T val;
    explicit Ok(T v) : val(std::move(v)) {}
};

template <typename E>
struct Err {
    E val;
    explicit Err(E v) : val(std::move(v)) {}
};

// ---------------------------------------------------------------------------
// Result<T, E>
// ---------------------------------------------------------------------------

template <typename T, typename E>
class Result {
    std::variant<Ok<T>, Err<E>> data_;

public:
    // Construct a success result.  The initializer list stores the Ok
    // wrapper.  Remove the TODO() below once you understand the pattern.
    Result(Ok<T> ok) : data_(std::move(ok)) {
        TODO();
    }

    // Construct an error result.  The initializer list stores the Err
    // wrapper.  Remove the TODO() below once you understand the pattern.
    Result(Err<E> err) : data_(std::move(err)) {
        TODO();
    }

    // Returns true if the result holds a success value.
    bool is_ok() const {
        TODO();
    }

    // Returns true if the result holds an error value.
    bool is_error() const {
        TODO();
    }

    // Returns the success value. Throws std::runtime_error if error.
    const T& value() const {
        TODO();
    }

    // Returns the error value. Throws std::runtime_error if ok.
    const E& error() const {
        TODO();
    }
};
