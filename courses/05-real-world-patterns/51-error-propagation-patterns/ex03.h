// Exercise 03: Monadic and_then
//
// and_then (also called "flat_map" or "bind") chains operations that
// themselves return Result. Unlike transform, the function F returns
// a Result<U, E> rather than a plain U. This avoids nested Results.
//
// TODO:
//   1. Implement and_then(F) — if ok, call F(value()) and return its
//      Result directly. If error, propagate the Err unchanged.

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

    template <typename F>
    auto transform(F&& f) const -> Result<decltype(f(value())), E> {
        using U = decltype(f(value()));
        if (is_ok()) return Ok<U>(f(value()));
        return Err<E>(E(error()));
    }

    // Chain a failable operation.  F takes const T& and returns Result<U, E>.
    // Returns the Result<U, E> from F if ok, or propagates the current error.
    template <typename F>
    auto and_then(F&& f) const -> decltype(f(value())) {
        TODO();
    }
};
