// Exercise 07: IIFE for Initialization
//
// An Immediately Invoked Function Expression (IIFE, pronounced "iffy")
// is a lambda that is defined and called in the same expression. It is
// useful for initializing a `const` variable with complex logic:
//
//   const auto config = [&]() {
//       if (debug_mode) return Config{...};
//       else            return Config{...};
//   }();  // <-- note the () at the end -- calls the lambda immediately
//
// Without IIFE, you would either need a mutable variable or a separate
// helper function. IIFE keeps the initialization logic local and lets
// the result be const.
//
// TODO:
//   1. Implement classify_number() -- use an IIFE to initialize a const
//      string with "negative", "zero", or "positive" based on the input.
//   2. Implement build_greeting() -- use an IIFE to initialize a const
//      string. If `formal` is true, return "Dear <name>,"; otherwise
//      return "Hey <name>!".
//   3. Implement first_n_squares() -- use an IIFE to initialize a const
//      vector<int> containing the first `n` perfect squares (1, 4, 9, ...).

#pragma once

#include <string>
#include <vector>
#include <testkit/testkit.h>

// Use an IIFE to classify the number as "negative", "zero", or "positive".
// Return the classification string.
inline std::string classify_number(int n) {
    TODO();
}

// Use an IIFE to build a greeting string.
// If formal: "Dear <name>,"   Otherwise: "Hey <name>!"
inline std::string build_greeting(const std::string& name, bool formal) {
    TODO();
}

// Use an IIFE to initialize and return a const vector of the first n
// perfect squares: {1, 4, 9, 16, ...}.
inline std::vector<int> first_n_squares(int n) {
    TODO();
}
