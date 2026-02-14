// Exercise 01: Manual Iteration
//
// Iterators are the glue between containers and algorithms in C++. Every
// standard container provides begin() and end() iterators that let you
// traverse its elements. For a std::list (doubly-linked list), you cannot
// use [] indexing -- you must use iterators.
//
// An iterator acts like a pointer:
//   *it      — dereference to get the element
//   ++it     — advance to the next element
//   it != end — check if there are more elements
//
// TODO:
//   1. Implement sum_list() — iterate through a std::list<int> and return
//      the sum of all elements.
//   2. Implement double_elements() — iterate through a std::list<int> and
//      multiply each element by 2 (modify in place).
//   3. Implement find_in_list() — iterate through a std::list<std::string>
//      and return an iterator to the first element matching `target`, or
//      end() if not found.

#pragma once

#include <list>
#include <string>
#include <testkit/testkit.h>

// Return the sum of all elements in the list.
inline int sum_list(const std::list<int>& lst) {
    TODO();
}

// Multiply every element in the list by 2.
inline void double_elements(std::list<int>& lst) {
    TODO();
}

// Return an iterator to the first element equal to `target`, or lst.end().
inline std::list<std::string>::const_iterator
find_in_list(const std::list<std::string>& lst, const std::string& target) {
    TODO();
}
