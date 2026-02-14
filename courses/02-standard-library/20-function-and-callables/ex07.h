// Exercise 07: Higher-Order Function
//
// A higher-order function takes a callable as input and/or returns a new
// callable as output. This is a powerful pattern for composing behavior.
//
// Common examples:
//   - memoize(f): returns a version of f that caches results
//   - retry(f, n): returns a version of f that retries on exception
//   - compose(f, g): returns a function h where h(x) = f(g(x))
//
// In C++, you can return lambdas from functions. The returned lambda can
// capture the original callable and any additional state.
//
// Example:
//   auto make_adder(int n) {
//       return [n](int x) { return x + n; };
//   }
//   auto add5 = make_adder(5);
//   add5(10);  // returns 15
//
// TODO:
//   1. Implement make_multiplier() — return a lambda that multiplies its
//      argument by `factor`.
//   2. Implement compose() — return a callable that applies g then f:
//      compose(f, g)(x) == f(g(x)).
//   3. Implement call_n_times() — return a callable that calls f exactly
//      n times with the same argument, returning a vector of results.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <vector>

// Return a lambda that multiplies its int argument by `factor`.
inline std::function<int(int)> make_multiplier(int factor) {
    TODO();
}

// Return a callable that computes f(g(x)).
// compose(f, g)(x) should return f(g(x)).
inline std::function<int(int)> compose(
    std::function<int(int)> f,
    std::function<int(int)> g)
{
    TODO();
}

// Return a callable that invokes `f` exactly `n` times with the given
// argument, collecting the results into a vector.
// Example: call_n_times(f, 3)(x) returns {f(x), f(x), f(x)}.
inline std::function<std::vector<int>(int)> call_n_times(
    std::function<int(int)> f,
    int n)
{
    TODO();
}
