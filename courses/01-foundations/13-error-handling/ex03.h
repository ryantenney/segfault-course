// Exercise 03: Multiple Catch Blocks
//
// When a function can throw different exception types, you use multiple catch
// blocks to handle each one. Catch blocks are tested in order — the first
// match wins. This means you must catch derived types BEFORE base types,
// or the base catch will swallow everything.
//
//   try { ... }
//   catch (const DerivedError& e) { ... }   // more specific — first
//   catch (const std::runtime_error& e) { ... }  // base — second
//   catch (const std::exception& e) { ... }      // most general — last
//
// TODO:
//   1. Define NetworkError (inherits from std::runtime_error).
//   2. Define TimeoutError (inherits from NetworkError).
//   3. Implement simulate_request() — throws different errors based on the
//      url parameter.
//   4. Implement classify_error() — call simulate_request() inside try/catch
//      with multiple catch blocks, and return a string identifying which
//      error type was caught.

#pragma once

#include <stdexcept>
#include <string>
#include <testkit/testkit.h>

// A general network error.
class NetworkError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// A timeout is a specific kind of network error.
class TimeoutError : public NetworkError {
public:
    using NetworkError::NetworkError;
};

// Simulate a network request.
//   url == "timeout"    -> throw TimeoutError("request timed out")
//   url == "disconnect" -> throw NetworkError("connection lost")
//   url == "unknown"    -> throw std::runtime_error("unknown error")
//   anything else       -> return "ok: <url>"
inline std::string simulate_request(const std::string& url) {
    TODO();
}

// Call simulate_request(url) and return:
//   "timeout"  if TimeoutError was caught
//   "network"  if NetworkError was caught
//   "runtime"  if std::runtime_error was caught
//   "success"  if no exception was thrown (return the result is also fine)
//
// IMPORTANT: order your catch blocks from most specific to least specific.
inline std::string classify_error(const std::string& url) {
    TODO();
}
