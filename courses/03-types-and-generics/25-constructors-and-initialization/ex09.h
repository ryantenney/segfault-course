// Exercise 09: Most Vexing Parse
//
// PROBLEM:
//   C++ inherits an ambiguity from C: a declaration that looks like
//   object construction can be parsed as a function declaration.
//
//     Timer timer();       // Declares a FUNCTION returning Timer!
//     Timer timer;         // Default-constructs a Timer (no parens)
//     Timer timer{};       // Default-constructs a Timer (braces, C++11)
//
//   This is called the "most vexing parse" — it's valid C++ that
//   doesn't do what you expect.
//
// TODO:
//   Each function below demonstrates a scenario. Implement them to
//   return the correct values, showing you understand when the compiler
//   treats a declaration as a function vs an object.
//
// WHY:
//   The most vexing parse is a famous C++ gotcha. The fix is simple:
//   use brace initialization {} or remove the empty parentheses. But
//   you need to know the problem exists to recognize it in code reviews.

#pragma once

#include <testkit/testkit.h>
#include <string>

// A simple class for demonstration.
class Counter {
private:
    int count_;

public:
    Counter() : count_(0) {}
    explicit Counter(int start) : count_(start) {}

    int value() const { return count_; }
    void increment() { ++count_; }
};

// FIX the most vexing parse:
// The intention is to default-construct a Counter and return its value.
// But `Counter c();` declares a function, not an object!
// Fix it using either brace initialization or removing the parens.
inline int default_counter_value() {
    TODO();
    // Broken version (most vexing parse):
    //   Counter c();         // This declares a function named c!
    //   return c.value();    // Error: can't call .value() on a function
    //
    // Fix by using one of:
    //   Counter c;           // No parens
    //   Counter c{};         // Brace init
    //   auto c = Counter();  // Copy init
}

// Creates a Counter starting at 10, increments it 3 times,
// and returns the final value.
inline int incremented_counter() {
    TODO();
}

// FIX: This function intends to create a string from a char and count.
// std::string s(char, int) could be parsed ambiguously.
// Return a string of 5 'x' characters.
// Hint: std::string(5, 'x') or std::string s{...} with care.
inline std::string five_x_chars() {
    TODO();
    // The safe way: auto s = std::string(5, 'x');
}

// Returns the length of a default-constructed std::string.
// Demonstrate that you can default-construct without the vexing parse.
inline int empty_string_length() {
    TODO();
}
