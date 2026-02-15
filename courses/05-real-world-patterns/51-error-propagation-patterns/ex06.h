// Exercise 06: Error Context
//
// When errors propagate up through layers, it helps to add context:
// "while parsing config: file not found". The context() method wraps
// the current error with an additional message, building a chain.
//
// We use ContextError to hold a message plus the original error.
// context(msg) returns Result<T, ContextError<E>>.
//
// TODO:
//   1. Implement context(msg) — if error, wrap it in ContextError
//      with the given message. If ok, pass through unchanged.

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

// ---------------------------------------------------------------------------
// ContextError — wraps an inner error with a descriptive message.
// ---------------------------------------------------------------------------

template <typename E>
struct ContextError {
    std::string message;
    E inner;

    ContextError(std::string msg, E err)
        : message(std::move(msg)), inner(std::move(err)) {}

    // Produce a human-readable description: "message: inner".
    // For nested ContextErrors, this naturally chains.
    std::string describe() const {
        return message + ": " + describe_inner(inner);
    }

private:
    // Base case: inner is a string.
    static std::string describe_inner(const std::string& e) {
        return e;
    }

    // Recursive case: inner is itself a ContextError.
    template <typename E2>
    static std::string describe_inner(const ContextError<E2>& e) {
        return e.describe();
    }
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

    // Wrap the error with additional context.
    // Returns Result<T, ContextError<E>>.
    auto context(std::string msg) const -> Result<T, ContextError<E>> {
        TODO();
    }
};
