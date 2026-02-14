// Exercise 03: Key-Value Pair
//
// PROBLEM:
//   Implement a generic Pair<K, V> class template that holds a key and
//   a value.  This is similar to std::pair but simpler -- it demonstrates
//   class templates with multiple type parameters.
//
// TODO:
//   1. Implement key() and value() accessors.
//   2. Implement operator== and operator!= as free functions.
//      Two pairs are equal if both their keys and values are equal.
//   3. Implement operator< as a free function.
//      Compare by key first; if keys are equal, compare by value.
//
// WHY:
//   Class templates can have multiple type parameters.  This exercise
//   also practices defining comparison operators as non-member functions
//   (the idiomatic C++ approach for symmetric operators).

#pragma once

#include <testkit/testkit.h>

template<typename K, typename V>
class Pair {
    K key_;
    V value_;

public:
    // Constructor: already implemented for you.
    Pair(const K& key, const V& value) : key_(key), value_(value) {}

    // Return a const reference to the key.
    const K& key() const {
        TODO();
    }

    // Return a const reference to the value.
    const V& value() const {
        TODO();
    }
};

// Equality: two pairs are equal if their keys and values are both equal.
template<typename K, typename V>
bool operator==(const Pair<K, V>& lhs, const Pair<K, V>& rhs) {
    TODO();
}

// Inequality.
template<typename K, typename V>
bool operator!=(const Pair<K, V>& lhs, const Pair<K, V>& rhs) {
    TODO();
}

// Less-than: compare by key first; if keys are equal, compare by value.
template<typename K, typename V>
bool operator<(const Pair<K, V>& lhs, const Pair<K, V>& rhs) {
    TODO();
}
