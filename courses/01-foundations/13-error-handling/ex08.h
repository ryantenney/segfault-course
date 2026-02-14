// Exercise 08: Nested Exceptions
//
// When catching an exception and re-throwing a higher-level one, you lose
// the original error context. std::throw_with_nested wraps the current
// exception inside a new one, preserving the chain.
//
// To unpack the chain, use std::rethrow_if_nested inside a catch block.
//
// Example:
//   try {
//       try {
//           throw std::runtime_error("low-level I/O error");
//       } catch (...) {
//           std::throw_with_nested(std::runtime_error("failed to load config"));
//       }
//   } catch (const std::exception& e) {
//       // e.what() -> "failed to load config"
//       // rethrow_if_nested(e) re-throws the wrapped "low-level I/O error"
//   }
//
// TODO:
//   1. Implement read_sensor() — simulates reading a sensor value.
//      Throws std::runtime_error("sensor offline") if sensor_id is "broken".
//
//   2. Implement process_sensor() — calls read_sensor(), catches any error,
//      and re-throws with context using std::throw_with_nested.
//      The outer message should be "failed to process sensor: <sensor_id>".
//
//   3. Implement get_error_chain() — given a std::exception, build a vector
//      of all error messages by walking the nested exception chain.
//      The outermost message should be first, innermost last.

#pragma once

#include <exception>
#include <stdexcept>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Read a sensor value. Returns "value:<sensor_id>" on success.
// If sensor_id is "broken", throw std::runtime_error("sensor offline").
inline std::string read_sensor(const std::string& sensor_id) {
    TODO();
}

// Call read_sensor(sensor_id). If it throws, catch the exception and
// re-throw with nested context: "failed to process sensor: <sensor_id>".
// If it succeeds, return the result.
inline std::string process_sensor(const std::string& sensor_id) {
    TODO();
}

// Walk the nested exception chain and collect all what() messages
// into a vector. Outermost exception first, innermost last.
//
// Hint: use a loop or recursion. In each step:
//   1. Push e.what() into the vector.
//   2. Try std::rethrow_if_nested(e) inside a try/catch.
//   3. If it catches std::exception, repeat for that exception.
//   4. If rethrow_if_nested doesn't throw, the chain is done.
inline std::vector<std::string> get_error_chain(const std::exception& e) {
    TODO();
}
