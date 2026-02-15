// Exercise 08: Pipeline with Results
//
// This exercise ties the whole lesson together. Build a data-processing
// pipeline that chains 4+ operations, any of which can fail. The
// pipeline processes a raw string input through parsing, validation,
// transformation, and formatting steps.
//
// The Result infrastructure is provided. You implement the pipeline
// functions.
//
// TODO:
//   1. Implement parse_int()    — parse string to int; error if invalid.
//   2. Implement validate_range() — error if value outside [min, max].
//   3. Implement double_value()  — multiply by 2, return Result.
//   4. Implement format_output() — format as "result: <value>".
//   5. Implement run_pipeline()  — chain all four in sequence.

#pragma once

#include <testkit/testkit.h>
#include <sstream>
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
};

// ---------------------------------------------------------------------------
// Pipeline steps — implement these.
// ---------------------------------------------------------------------------

// Parse a string as an integer. Return Err("parse error") if it fails.
// Hint: use std::stoi inside a try/catch.
inline Result<int, std::string> parse_int(const std::string& input) {
    TODO();
}

// Validate that value is in [min_val, max_val]. Return Err if out of range.
inline Result<int, std::string> validate_range(int value, int min_val, int max_val) {
    TODO();
}

// Multiply the value by 2. Always succeeds.
inline Result<int, std::string> double_value(int value) {
    TODO();
}

// Format the integer as "result: <value>".
inline Result<std::string, std::string> format_output(int value) {
    TODO();
}

// Run the full pipeline: parse -> validate [1, 100] -> double -> format.
inline Result<std::string, std::string> run_pipeline(const std::string& input) {
    TODO();
}
