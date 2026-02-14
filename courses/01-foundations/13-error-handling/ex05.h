// Exercise 05: Convert Exceptions to Error Codes
//
// Some codebases prefer error codes over exceptions (embedded systems, game
// engines, libraries with C interfaces). A common pattern is to wrap a
// throwing function in a try/catch that translates exceptions into an
// error struct.
//
// TODO:
//   1. Implement open_file() — a "throwing" version that simulates opening
//      a file. It throws std::runtime_error for specific bad filenames.
//
//   2. Implement try_open_file() — wraps open_file() in try/catch and
//      returns a FileResult struct with a success flag and either the
//      file content or an error message.

#pragma once

#include <stdexcept>
#include <string>
#include <testkit/testkit.h>

struct FileResult {
    bool ok;
    std::string content;       // populated on success
    std::string error_message; // populated on failure
};

// Simulate opening a file and returning its content.
//   filename == ""           -> throw runtime_error("empty filename")
//   filename == "missing"    -> throw runtime_error("file not found")
//   filename == "locked"     -> throw runtime_error("permission denied")
//   anything else            -> return "content of <filename>"
inline std::string open_file(const std::string& filename) {
    TODO();
}

// Wrap open_file() in try/catch. Return a FileResult:
//   On success: { ok=true, content=<result>, error_message="" }
//   On failure: { ok=false, content="", error_message=<e.what()> }
inline FileResult try_open_file(const std::string& filename) {
    TODO();
}
