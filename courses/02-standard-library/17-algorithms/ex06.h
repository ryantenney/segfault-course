// Exercise 06: Accumulate and Reduce
//
// std::accumulate (from <numeric>) is the classic "fold" operation. It
// takes an initial value and combines each element into it:
//
//   int sum = std::accumulate(v.begin(), v.end(), 0);
//   // equivalent to: init + v[0] + v[1] + ... + v[n-1]
//
// You can pass a custom binary operation as the fourth argument:
//
//   int product = std::accumulate(v.begin(), v.end(), 1,
//       [](int acc, int x) { return acc * x; });
//
// Note: use the correct initial value! 0 for sums, 1 for products,
// empty string for string concatenation, etc.
//
// TODO:
//   1. Implement sum_all() — compute the sum using std::accumulate.
//   2. Implement product_all() — compute the product using std::accumulate
//      with a custom binary operation.
//   3. Implement concat_strings() — concatenate all strings using
//      std::accumulate with a custom binary operation.
//   4. Implement dot_product() — compute the dot product of two vectors
//      using std::inner_product (from <numeric>).

#pragma once

#include <numeric>
#include <string>
#include <vector>
#include <testkit/testkit.h>

// Return the sum of all elements.
inline int sum_all(const std::vector<int>& vec) {
    TODO();
}

// Return the product of all elements.
// Use std::accumulate with a custom binary operation.
// Return 1 for an empty vector (the multiplicative identity).
inline long long product_all(const std::vector<int>& vec) {
    TODO();
}

// Concatenate all strings with a separator between them.
// Example: {"a", "b", "c"} with sep="-" -> "a-b-c"
// Empty vector returns "".
inline std::string concat_strings(const std::vector<std::string>& vec,
                                  const std::string& sep) {
    TODO();
}

// Compute the dot product of two vectors: a[0]*b[0] + a[1]*b[1] + ...
// Use std::inner_product from <numeric>.
// Precondition: a.size() == b.size().
inline int dot_product(const std::vector<int>& a, const std::vector<int>& b) {
    TODO();
}
