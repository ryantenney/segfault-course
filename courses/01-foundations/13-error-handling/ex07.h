// Exercise 07: Exception vs Error Code
//
// This exercise implements the same operation two ways so you can compare:
//   1. An exception-based version (throws on failure)
//   2. An error-code-based version (returns a struct with success/failure)
//
// The operation: look up a user by ID and return their name.
//
// Trade-offs:
//   Exceptions:  cleaner happy path, but try/catch at the call site
//   Error codes: explicit checking, no hidden control flow
//
// TODO:
//   1. Implement lookup_user_throwing() — throw if not found.
//   2. Implement lookup_user_result() — return a LookupResult.
//   3. Implement greet_user_with_exceptions() — use the throwing version,
//      catch the error, and return a greeting or error message.
//   4. Implement greet_user_with_result() — use the result version,
//      check the flag, and return a greeting or error message.
//
//   User table:
//     1 -> "Alice", 2 -> "Bob", 3 -> "Charlie"

#pragma once

#include <stdexcept>
#include <string>
#include <testkit/testkit.h>

struct LookupResult {
    bool found;
    std::string name;          // populated when found == true
    std::string error_message; // populated when found == false
};

// Look up user by ID. Throw std::runtime_error("user not found: <id>") if
// the ID doesn't exist in the table.
inline std::string lookup_user_throwing(int id) {
    TODO();
}

// Look up user by ID. Return a LookupResult:
//   found: { found=true, name=<name>, error_message="" }
//   not found: { found=false, name="", error_message="user not found: <id>" }
inline LookupResult lookup_user_result(int id) {
    TODO();
}

// Use lookup_user_throwing() to greet a user.
// On success: return "Hello, <name>!"
// On failure (catch runtime_error): return "Error: <e.what()>"
inline std::string greet_user_with_exceptions(int id) {
    TODO();
}

// Use lookup_user_result() to greet a user.
// On success: return "Hello, <name>!"
// On failure: return "Error: <error_message>"
inline std::string greet_user_with_result(int id) {
    TODO();
}
