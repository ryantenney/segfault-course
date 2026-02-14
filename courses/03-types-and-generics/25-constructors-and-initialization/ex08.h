// Exercise 08: initializer_list Ambiguity
//
// PROBLEM:
//   When a class has both a regular constructor and one that takes
//   std::initializer_list, brace initialization STRONGLY prefers
//   the initializer_list constructor. This causes confusion:
//
//     std::vector<int> v1(10);     // 10 zeroes
//     std::vector<int> v1{10};     // one element: 10
//     std::vector<int> v2(10, 3);  // 10 threes
//     std::vector<int> v2{10, 3};  // two elements: 10, 3
//
// TODO:
//   Implement each function to return the correct value that
//   demonstrates your understanding of this ambiguity.
//   Read each function's comment carefully.
//
// WHY:
//   This is one of the most confusing corners of C++ initialization.
//   The rule is: if braces are used AND a viable initializer_list
//   constructor exists, it wins — even if another constructor would
//   be a better match. Knowing this prevents subtle bugs.

#pragma once

#include <testkit/testkit.h>
#include <vector>
#include <string>

// How many elements does std::vector<int>(10, 3) have?
// (Parentheses: calls the count+value constructor.)
inline int paren_count_value_size() {
    TODO();
}

// What is the first element of std::vector<int>(10, 3)?
inline int paren_count_value_first() {
    TODO();
}

// How many elements does std::vector<int>{10, 3} have?
// (Braces: prefers the initializer_list constructor.)
inline int brace_two_ints_size() {
    TODO();
}

// What is the first element of std::vector<int>{10, 3}?
inline int brace_two_ints_first() {
    TODO();
}

// What is the second element of std::vector<int>{10, 3}?
inline int brace_two_ints_second() {
    TODO();
}

// How many elements does std::vector<std::string>(3) have?
// (No initializer_list<string> from int, so calls the count constructor.)
inline int string_vec_paren_size() {
    TODO();
}

// How many elements does std::vector<std::string>{3} have?
// (int is not convertible to std::string, so initializer_list is not viable.
//  Falls back to the count constructor.)
// Wait — actually this won't compile because 3 is not a string.
// The correct answer: this is a trick! vector<string>(3) works,
// but vector<string>{3} does NOT compile. So instead:
//
// How many elements does std::vector<std::string>{"a", "b", "c"} have?
inline int string_vec_brace_size() {
    TODO();
}

// Returns a vector with exactly 5 elements, all with value 42.
// Hint: use the right initialization syntax to call the count+value ctor.
inline std::vector<int> make_filled_vector() {
    TODO();
}

// Returns a vector containing exactly {5, 42} (two elements).
// Hint: use the right initialization syntax for a literal list.
inline std::vector<int> make_literal_vector() {
    TODO();
}
