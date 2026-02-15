// Exercise 07: Collect Results
//
// collect() takes a vector of Results and either returns a vector of
// all success values (if every element is ok) or the first error
// encountered. This is the "all or nothing" pattern for batched
// operations.
//
// TODO:
//   1. Implement collect() — iterate the vector. If all are ok, return
//      Ok(vector of values). If any is error, return the first error.

#pragma once

#include <testkit/testkit.h>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

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
};

// Collect a vector of Results into a single Result of a vector.
// Fails on the first error encountered.
template <typename T, typename E>
inline Result<std::vector<T>, E> collect(const std::vector<Result<T, E>>& results) {
    TODO();
}
