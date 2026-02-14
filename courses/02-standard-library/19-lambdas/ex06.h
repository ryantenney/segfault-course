// Exercise 06: Lambda Returning Lambda
//
// A function can return a lambda. This is commonly used in the "factory"
// pattern: a function configures a lambda's captured state and returns it.
//
//   auto make_multiplier(int factor) {
//       return [factor](int x) { return x * factor; };
//   }
//   auto double_it = make_multiplier(2);
//   double_it(5);  // returns 10
//
// Since each call to the factory captures a different value, each
// returned lambda is independently configured.
//
// Note: when returning a lambda from a function, you can use auto as
// the return type, or std::function<> for type erasure.
//
// TODO:
//   1. Implement make_multiplier() -- return a lambda that multiplies
//      its argument by the captured factor.
//   2. Implement make_adder() -- return a lambda that adds a captured
//      offset to its argument.
//   3. Implement make_range_checker() -- return a lambda that returns
//      true if its argument is in the range [lo, hi] (inclusive).

#pragma once

#include <functional>
#include <testkit/testkit.h>

// Return a lambda that multiplies its int argument by `factor`.
inline std::function<int(int)> make_multiplier(int factor) {
    TODO();
}

// Return a lambda that adds `offset` to its int argument.
inline std::function<int(int)> make_adder(int offset) {
    TODO();
}

// Return a lambda that returns true if its int argument is
// in the range [lo, hi] (inclusive).
inline std::function<bool(int)> make_range_checker(int lo, int hi) {
    TODO();
}
