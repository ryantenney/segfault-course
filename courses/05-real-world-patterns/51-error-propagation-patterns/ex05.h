// Exercise 05: Map Error
//
// map_error transforms the error type, leaving success values alone.
// This is useful when composing functions that use different error types
// — you can normalize them to a common error type before chaining.
//
// TODO:
//   1. Implement map_error(F) — if error, apply F to the error and
//      wrap the return in Err. If ok, pass through unchanged.

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

    // Transform the error type.  F takes const E& and returns E2.
    // Returns Result<T, E2>.
    template <typename F>
    auto map_error(F&& f) const -> Result<T, decltype(f(error()))> {
        TODO();
    }
};
