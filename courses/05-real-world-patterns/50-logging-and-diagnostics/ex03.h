// Exercise 03: Source Location
//
// Good log messages include the file and line where they originated.
// C++20 provides std::source_location for this. If it is not available,
// the traditional __FILE__ and __LINE__ macros can be used instead.
//
// TODO:
//   1. Implement the SourceLocation struct's to_string() method.
//      Format: "filename:line" (just the base filename, not the full path).
//   2. Implement the MAKE_LOCATION() macro that captures __FILE__ and
//      __LINE__ at the call site and returns a SourceLocation.
//
// NOTE: We use a macro here because __FILE__ and __LINE__ must be
//       expanded at the call site, not inside a function.

#pragma once

#include <testkit/testkit.h>
#include <string>

struct SourceLocation {
    std::string file;
    int line;

    // Return "filename:line" where filename is just the base name
    // (e.g., "ex03_test.cpp:42", not "/full/path/ex03_test.cpp:42").
    std::string to_string() const {
        TODO();
    }
};

// Capture the current file (base name only) and line number.
// Usage: auto loc = MAKE_LOCATION();
#define MAKE_LOCATION() ::SourceLocation{__FILE__, __LINE__}
