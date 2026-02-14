// Exercise 07: Multi-return function (Capstone)
//
// PROBLEM:
//   A common pattern is returning multiple values from a function.
//   Before structured bindings, you might use output parameters or
//   return a pair/tuple with meaningless .first/.second names.
//
//   The modern approach is:
//   1. Define a struct with named fields
//   2. Return the struct
//   3. Decompose with structured bindings at the call site
//
//   This gives you named fields AND clean call-site syntax.
//
// TODO:
//   1. Define the Result struct (described below).
//   2. Implement analyze_text() to return a Result.
//   3. The tests decompose the result with structured bindings.

#pragma once

#include <testkit/testkit.h>
#include <string>

// TODO: Define a struct called TextStats with these fields (in order):
//   - int word_count       (number of space-separated words)
//   - int char_count       (total characters including spaces)
//   - int longest_word_len (length of the longest word)
//   - char first_char      (first character, or '\0' if empty)
struct TextStats {
    int word_count = 0;
    int char_count = 0;
    int longest_word_len = 0;
    char first_char = '\0';
};

// Analyze the given text and return a TextStats.
// Words are separated by spaces (no leading/trailing/double spaces).
// For empty string, return {0, 0, 0, '\0'}.
inline TextStats analyze_text(const std::string& text) {
    TODO();
}

// Return a formatted summary: "N words, M chars, longest: L"
// Use structured bindings to unpack the TextStats.
inline std::string text_summary(const std::string& text) {
    TODO();
    // Hint: auto [words, chars, longest, first] = analyze_text(text);
    //       then build the string using std::to_string
}
