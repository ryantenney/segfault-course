// Exercise 02: Enum with Explicit Underlying Type
//
// By default, the compiler chooses the underlying integer type for an enum
// (typically int). You can specify it explicitly:
//
//   enum class Status : uint8_t { Ok = 0, Error = 1 };
//
// This is useful when:
//   - You need a specific size (e.g., for serialization or network protocols)
//   - You want to limit the range of values
//   - You need to match a binary format or hardware register
//
// TODO:
//   1. Change the underlying type of Severity from int (default) to uint8_t.
//   2. Assign the correct values to each enumerator.
//   3. Implement the helper functions.

#pragma once

#include <cstdint>
#include <testkit/testkit.h>

// TODO:
//   1. Add `: uint8_t` after `Severity` to set the underlying type.
//   2. Assign the correct numeric values:
//      Trace=0, Debug=1, Info=2, Warning=3, Error=4, Fatal=5
enum class Severity {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Fatal
};

// Return true if the severity is Warning or higher (Warning, Error, Fatal).
inline bool is_warning_or_above(Severity s) {
    TODO();
}

// Return the severity as its underlying uint8_t value.
// Hint: use static_cast<uint8_t>(s).
inline uint8_t severity_value(Severity s) {
    TODO();
}

// Return true if severity `a` is more severe than `b`.
// Higher numeric value = more severe.
inline bool more_severe(Severity a, Severity b) {
    TODO();
}
