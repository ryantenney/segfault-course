// Exercise 08: Expected Chaining
//
// When you have multiple operations that each return Expected, you want to
// chain them so that the first error short-circuits the rest. This is the
// "railway pattern" — values flow along the happy path, and any error
// diverts to the error track.
//
// Since our Expected doesn't have monadic methods (.and_then), you'll
// implement a free function and_then() that chains two Expected-returning
// operations manually.
//
// TODO:
//   1. Implement and_then() — if the Expected holds a success value, apply
//      the given function to it and return the result. If it holds an error,
//      propagate the error without calling the function.
//
//   2. Implement validate_and_double() — chain parse_int (from ex07.h) with
//      validate_positive, then double_value. Use and_then for each step.
//
// The pipeline is: string -> parse_int -> validate_positive -> double_value

#pragma once

#include <functional>
#include <string>
#include <testkit/testkit.h>

#include "ex07.h"  // Expected, parse_int, make_success, make_error

// If `result` holds a value, apply `fn` to it and return the new Expected.
// If `result` holds an error, propagate the error unchanged.
template<typename T, typename E, typename Fn>
auto and_then(const Expected<T, E>& result, Fn fn) -> decltype(fn(result.value())) {
    TODO();
}

// Validate that a number is positive (> 0).
// Returns the number on success, or an error message on failure.
inline Expected<int, std::string> validate_positive(int n) {
    TODO();
    // On error: "not positive: <n>"
}

// Double a number. Always succeeds.
inline Expected<int, std::string> double_value(int n) {
    TODO();
}

// Chain the full pipeline: parse -> validate positive -> double.
// Uses and_then to compose each step.
inline Expected<int, std::string> validate_and_double(const std::string& input) {
    TODO();
}
