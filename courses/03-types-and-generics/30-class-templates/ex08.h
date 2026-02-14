// Exercise 08: Dependent Type Names
//
// PROBLEM:
//   When you write a template that uses a nested type from a template
//   parameter (e.g., T::value_type), the compiler needs to know it's a
//   type.  In C++20, the compiler can figure this out in many positions
//   (like return types).  However, understanding dependent types is still
//   essential -- especially when declaring local variables or typedef/using
//   aliases inside template code.
//
// TODO:
//   1. Implement get_first() -- return the first element of a container.
//      Use container.front() or *container.begin().
//
//   2. Implement get_size() -- return container.size().
//
//   3. Implement get_begin() -- return container.begin() (as a const
//      iterator since the parameter is const).
//
//   4. Implement find_or_default() -- search the container for `target`.
//      If found, return it.  If not found, return a default-constructed
//      value of the container's value_type.
//      Hint: you'll need to declare a local variable of type
//      typename T::value_type (or use auto).
//
// WHY:
//   Dependent type names appear everywhere in template code.  Even though
//   C++20 relaxes many typename requirements, understanding the concept
//   helps you read and write generic code fluently.

#pragma once

#include <testkit/testkit.h>
#include <algorithm>

// Returns the first element of a container.
template<typename T>
typename T::value_type get_first(const T& container) {
    TODO();
}

// Returns the size of a container as its size_type.
template<typename T>
typename T::size_type get_size(const T& container) {
    TODO();
}

// Returns a const_iterator to the beginning of a container.
template<typename T>
typename T::const_iterator get_begin(const T& container) {
    TODO();
}

// Searches the container for target.  Returns target if found,
// or a default-constructed T::value_type if not found.
template<typename T>
typename T::value_type find_or_default(const T& container,
                                       const typename T::value_type& target) {
    TODO();
}
