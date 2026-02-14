// Exercise 02: Callback with Error Handling
//
// PROBLEM:
//   Implement async read functions that report success or failure through
//   a callback. The callback takes an error code and a result string.
//   An error code of 0 means success; non-zero means failure.
//
// TODO:
//   1. Implement async_read_success(callback) — calls callback with (0, "data ok").
//   2. Implement async_read_failure(callback) — calls callback with (1, "").
//
// WHY:
//   Real async APIs need to report errors. The callback pattern uses an
//   error-first convention (popularized by Node.js): the first parameter
//   is an error code, and the second is the result. The caller checks the
//   error code before using the result. This pattern is simple but leads
//   to deeply nested code ("callback hell") when operations are chained.

#pragma once
#include <testkit/testkit.h>
#include <functional>
#include <string>

// Simulates a successful async read.
// Calls callback with error_code=0 and result="data ok".
inline void async_read_success(
    std::function<void(int error_code, const std::string& result)> callback)
{
    TODO();
    // Hint: callback(0, "data ok");
}

// Simulates a failed async read.
// Calls callback with error_code=1 and result="" (empty string).
inline void async_read_failure(
    std::function<void(int error_code, const std::string& result)> callback)
{
    TODO();
    // Hint: callback(1, "");
}
