// Exercise 05: const_cast for Legacy APIs
//
// PROBLEM:
//   You have a legacy C-style API that takes a non-const pointer even
//   though it only reads from the buffer. Your modern C++ code correctly
//   passes const data. You need const_cast to bridge the gap.
//
// TODO:
//   Implement the wrapper functions using const_cast to call the legacy
//   API functions safely.
//
// WHY:
//   const_cast exists specifically for interfacing with APIs that lack
//   const-correctness. It should never be used to actually modify data
//   that was originally declared const — that is undefined behavior.

#pragma once
#include <cstring>
#include <string>
#include <testkit/testkit.h>

// ---- Legacy C API (pretend this is in a third-party library) ----

// Computes the length of a C string.
// The parameter SHOULD be const but isn't (legacy code).
inline int legacy_strlen(char* str) {
    int len = 0;
    while (str[len] != '\0') ++len;
    return len;
}

// Copies up to n characters from src into dest.
// src SHOULD be const but isn't (legacy code).
inline void legacy_copy(char* dest, char* src, int n) {
    for (int i = 0; i < n && src[i] != '\0'; ++i) {
        dest[i] = src[i];
    }
}

// ---- Modern C++ wrappers ----

// Return the length of a const C string by calling legacy_strlen.
// Use const_cast to remove const from the pointer.
inline int safe_strlen(const char* str) {
    TODO();
}

// Copy from a const source string into dest by calling legacy_copy.
// Use const_cast only on the source (which is read-only in practice).
inline void safe_copy(char* dest, const char* src, int n) {
    TODO();
}

// Return a std::string from a const C string by using safe_strlen
// and the const char* directly (std::string accepts const char*).
inline std::string to_string(const char* str) {
    TODO();
}
