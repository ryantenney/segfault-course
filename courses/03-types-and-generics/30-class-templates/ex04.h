// Exercise 04: CTAD (Class Template Argument Deduction) Guide
//
// PROBLEM:
//   C++17 introduced Class Template Argument Deduction (CTAD), which
//   allows the compiler to deduce template arguments from constructor
//   arguments.  Sometimes the compiler can't figure out the types on
//   its own, and you need to provide a "deduction guide."
//
//   For example, given:
//     Pair{1, "hello"}
//   Without a guide, the compiler deduces Pair<int, const char*>.
//   A deduction guide can tell the compiler to deduce
//   Pair<int, std::string> instead.
//
// TODO:
//   1. Implement the make_pair function below.
//   2. Add a deduction guide for Pair so that:
//        Pair{1, "hello"}
//      deduces Pair<int, std::string>, not Pair<int, const char*>.
//
//      Syntax:
//        Pair(K, const char*) -> Pair<K, std::string>;
//
// WHY:
//   CTAD reduces verbosity -- you don't have to write Pair<int, std::string>
//   every time.  Deduction guides let you control what types are deduced
//   when the default deduction would be wrong or undesirable.

#pragma once

#include <testkit/testkit.h>
#include <string>

template<typename K, typename V>
class Pair {
    K key_;
    V value_;

public:
    // Note: parameters taken by value so that array types decay to pointers
    // during template argument deduction (e.g., "hello" -> const char*).
    Pair(K key, V value) : key_(std::move(key)), value_(std::move(value)) {}

    const K& key() const { return key_; }
    const V& value() const { return value_; }
};

// TODO: Add a deduction guide here so that Pair{k, "string literal"}
// deduces the value type as std::string, not const char*.
//
// Syntax:  Pair(K, const char*) -> Pair<K, std::string>;

// A helper function that creates a Pair using explicit template arguments.
// This function is just for gating tests -- implement it to return a Pair.
template<typename K, typename V>
Pair<K, V> create_pair(const K& key, const V& value) {
    TODO();
}
