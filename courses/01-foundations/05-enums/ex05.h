// Exercise 05: Enum as Bitflags
//
// A common pattern is to use an enum class as a set of combinable flags.
// Each enumerator is a power of two, and you combine them with bitwise OR.
//
// Since enum class does NOT allow implicit conversion to int, the bitwise
// operators must be overloaded explicitly. This is a feature, not a bug —
// it prevents accidental mixing of flag types.
//
// TODO:
//   1. Set the correct values for each Permission enumerator (powers of two).
//   2. Implement operator| and operator& for Permission.
//   3. Implement the helper functions.

#pragma once

#include <cstdint>
#include <testkit/testkit.h>

// TODO: Set the correct power-of-two values for each enumerator.
//   None    = 0
//   Read    = 1       (bit 0)
//   Write   = 2       (bit 1)
//   Execute = 4       (bit 2)
enum class Permission : uint8_t {
    None    = 0,
    Read    = 0,    // TODO: fix this value
    Write   = 0,    // TODO: fix this value
    Execute = 0     // TODO: fix this value
};

// TODO: Implement operator| to combine two Permissions.
// Cast both operands to uint8_t, OR them together, cast back to Permission.
inline Permission operator|(Permission a, Permission b) {
    TODO();
}

// TODO: Implement operator& to test if a flag is set.
// Same pattern as operator| but with bitwise AND.
inline Permission operator&(Permission a, Permission b) {
    TODO();
}

// Return true if `perms` has the `flag` set.
// Hint: (perms & flag) != Permission::None
inline bool has_permission(Permission perms, Permission flag) {
    TODO();
}

// Combine Read and Write into a single Permission value.
inline Permission read_write() {
    TODO();
}

// Return a Permission with all three flags set (Read | Write | Execute).
inline Permission all_permissions() {
    TODO();
}
