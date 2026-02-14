// Exercise 06: Scoped Enum in Switch
//
// A switch over an enum class with no default case lets the compiler
// warn you about unhandled enumerators. This is a powerful safeguard:
// if someone adds a new value to the enum, the compiler flags every
// switch that needs updating.
//
// Adding `default:` suppresses this warning — so don't use it unless
// you truly want a catch-all.
//
// TODO:
//   Implement each function using a switch statement.
//   Do NOT add a default case.

#pragma once

#include <string_view>
#include <testkit/testkit.h>

enum class HttpMethod {
    Get,
    Post,
    Put,
    Delete
};

// Return the HTTP method as an uppercase string:
// "GET", "POST", "PUT", "DELETE"
inline std::string_view method_name(HttpMethod m) {
    TODO();
}

// Return true if the method is considered "safe" (does not modify state).
// Safe methods: Get
// Unsafe methods: Post, Put, Delete
inline bool is_safe(HttpMethod m) {
    TODO();
}

// Return true if the method is "idempotent" (repeating has same effect).
// Idempotent: Get, Put, Delete
// Not idempotent: Post
inline bool is_idempotent(HttpMethod m) {
    TODO();
}
