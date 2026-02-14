// Exercise 08: Identify the Right Cast
//
// PROBLEM:
//   Given different scenarios, you need to pick the correct C++ cast.
//   This is a conceptual exercise: each function describes a scenario,
//   and you implement it using the right cast.
//
// TODO:
//   Implement each function using the named cast specified in the
//   comments. Each function exercises a different cast for a
//   different reason.
//
// SUMMARY OF C++ CASTS:
//   static_cast    — Compile-time checked. Numeric conversions, upcasts,
//                    known-safe downcasts in non-polymorphic hierarchies.
//   dynamic_cast   — Runtime checked. Downcasts in polymorphic hierarchies.
//                    Requires virtual functions. Returns null/throws on failure.
//   const_cast     — Adds or removes const/volatile. Nothing else.
//   reinterpret_cast — Bit-level reinterpretation. Pointers to ints,
//                    between unrelated pointer types. Almost always unsafe.

#pragma once
#include <cstdint>
#include <string>
#include <testkit/testkit.h>

// Scenario 1: Numeric conversion (use static_cast)
// Convert an integer to a float.
inline float int_to_float(int value) {
    TODO();
}

// Scenario 2: Remove const to call legacy function (use const_cast)
// legacy_api_read takes char* but only reads from it.
inline int legacy_api_read(char* buf) {
    int sum = 0;
    while (*buf) { sum += *buf; ++buf; }
    return sum;
}

inline int call_legacy_read(const char* data) {
    TODO();
}

// Scenario 3: Check runtime type (use dynamic_cast)
class Printable {
public:
    virtual ~Printable() = default;
    virtual std::string text() const = 0;
};

class Label : public Printable {
    std::string text_;
public:
    explicit Label(std::string t) : text_(std::move(t)) {}
    std::string text() const override { return text_; }
    std::string decorated() const { return "[" + text_ + "]"; }
};

class PlainText : public Printable {
    std::string text_;
public:
    explicit PlainText(std::string t) : text_(std::move(t)) {}
    std::string text() const override { return text_; }
};

// If the Printable is a Label, return its decorated() text.
// Otherwise, return its plain text().
inline std::string smart_print(Printable* p) {
    TODO();
}

// Scenario 4: Pointer round-trip through integer (use reinterpret_cast)
// Store a pointer as a uintptr_t, then recover it.
inline double* round_trip_pointer(double* ptr) {
    TODO();
}
