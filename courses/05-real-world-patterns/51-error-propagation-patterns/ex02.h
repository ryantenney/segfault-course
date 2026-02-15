// Exercise 02: Monadic Transform
//
// A transform (also called "map") applies a function to the success
// value inside a Result, leaving errors untouched. This lets you
// compose operations without manually checking for errors at each step.
//
// The full Result type from exercise 01 is provided here. You only
// need to implement the transform() method.
//
// TODO:
//   1. Implement transform(F) — if ok, apply F to the value and wrap
//      the return in a new Ok. If error, propagate the Err unchanged.

#pragma once

#include <testkit/testkit.h>
#include <stdexcept>
#include <string>
#include <variant>

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

template <typename T, typename E>
class Result {
    std::variant<Ok<T>, Err<E>> data_;

public:
    Result(Ok<T> ok) : data_(std::move(ok)) {}
    Result(Err<E> err) : data_(std::move(err)) {}

    bool is_ok() const { return data_.index() == 0; }
    bool is_error() const { return data_.index() == 1; }

    const T& value() const {
        if (is_error()) throw std::runtime_error("Result holds error");
        return std::get<Ok<T>>(data_).val;
    }

    const E& error() const {
        if (is_ok()) throw std::runtime_error("Result holds value");
        return std::get<Err<E>>(data_).val;
    }

    // Apply F to the success value.  F takes const T& and returns U.
    // Returns Result<U, E>.
    template <typename F>
    auto transform(F&& f) const -> Result<decltype(f(value())), E> {
        TODO();
    }
};
