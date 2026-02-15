// Exercise 04: Monadic or_else
//
// or_else is the error-side counterpart of and_then. It lets you
// attempt recovery when a Result holds an error. If the Result is ok,
// it passes through unchanged; if it holds an error, it calls F with
// the error and returns whatever Result F produces.
//
// TODO:
//   1. Implement or_else(F) — if error, call F(error()) and return
//      its Result. If ok, pass through unchanged.

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

    template <typename F>
    auto and_then(F&& f) const -> decltype(f(value())) {
        using R = decltype(f(value()));
        if (is_ok()) return f(value());
        return R(Err<E>(E(error())));
    }

    // Attempt error recovery.  F takes const E& and returns Result<T, E>.
    // If ok, pass through unchanged.  If error, return F(error()).
    template <typename F>
    auto or_else(F&& f) const -> Result<T, E> {
        TODO();
    }
};
