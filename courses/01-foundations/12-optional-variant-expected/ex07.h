// Exercise 07: Error Handling with Expected
//
// std::expected<T, E> (C++23) represents either a success value (T) or an
// error (E). It's like a Result type in Rust or an Either in Haskell.
//
// Since this project targets C++20, we define a simplified Expected<T, E>
// template below using std::variant internally. You'll implement its methods.
//
// TODO:
//   1. Implement the Expected<T, E> methods:
//      - value() — return the success value, or throw the error
//      - error() — return the error value, or throw std::logic_error
//      - has_value() — return true if this holds a success value
//      - value_or(default) — return the value if present, else the default
//
//   2. Implement parse_int() — parse a string to an int, returning
//      Expected<int, std::string>. Return an error message string if
//      the input is empty or not a valid integer.

#pragma once

#include <stdexcept>
#include <string>
#include <variant>
#include <testkit/testkit.h>

// Tag types to disambiguate construction.
struct success_tag {};
struct error_tag {};

// A simplified Expected<T, E> using variant<T, E> internally.
// The first alternative (index 0) is the success type T.
// The second alternative (index 1) is the error type E.
template<typename T, typename E>
class Expected {
    std::variant<T, E> data_;

public:
    // Construct a success value.
    Expected(success_tag, const T& value) : data_(value) {}
    Expected(success_tag, T&& value) : data_(std::move(value)) {}

    // Construct an error value.
    Expected(error_tag, const E& err)
        : data_(std::in_place_index<1>, err) {}
    Expected(error_tag, E&& err)
        : data_(std::in_place_index<1>, std::move(err)) {}

    // Returns true if this Expected holds a success value.
    bool has_value() const {
        TODO();
    }

    // Returns the success value. Throws the error (as std::runtime_error
    // with the error converted to string) if this holds an error.
    const T& value() const {
        TODO();
    }

    // Returns the error. Throws std::logic_error if this holds a success value.
    const E& error() const {
        TODO();
    }

    // Returns the success value if present, otherwise returns default_val.
    T value_or(const T& default_val) const {
        TODO();
    }
};

// Convenience factory functions.
template<typename T, typename E>
Expected<T, E> make_success(T value) {
    return Expected<T, E>(success_tag{}, std::move(value));
}

template<typename T, typename E>
Expected<T, E> make_error(E err) {
    return Expected<T, E>(error_tag{}, std::move(err));
}

// Parse a string as an integer.
// On success, return the parsed integer.
// On error, return a descriptive error message:
//   - Empty input: "empty input"
//   - Invalid format: "invalid integer: <input>"
//
// Hint: use std::stoi() inside a try/catch, or iterate the characters.
inline Expected<int, std::string> parse_int(const std::string& input) {
    TODO();
}
