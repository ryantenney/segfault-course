// Exercise 05: Partial Specialization
//
// PROBLEM:
//   Sometimes you need a class template to behave differently for a
//   family of types (e.g., all pointer types) while keeping the same
//   interface.  Partial specialization lets you specialize a template
//   for a pattern of types rather than one specific type.
//
// TODO:
//   1. Implement the primary Serializer<T> template's serialize() method.
//      It should return: "value:" + std::to_string(value)
//
//   2. Write a partial specialization of Serializer for pointer types:
//        template<typename T>
//        class Serializer<T*> { ... };
//      Its serialize() method should:
//        - If ptr is nullptr, return "null"
//        - Otherwise, return "ptr:" + std::to_string(*ptr)
//
// WHY:
//   Partial specialization is a powerful technique for customizing
//   template behavior for families of types.  A common use case is
//   handling pointers differently from values -- dereferencing them,
//   checking for null, etc.

#pragma once

#include <testkit/testkit.h>
#include <string>

// Primary template: serializes a value type.
template<typename T>
class Serializer {
public:
    // Return "value:" + std::to_string(value)
    static std::string serialize(const T& value) {
        TODO();
    }
};

// TODO: Add a partial specialization of Serializer for pointer types T*.
//
// template<typename T>
// class Serializer<T*> {
// public:
//     static std::string serialize(T* ptr) {
//         // If ptr is nullptr, return "null"
//         // Otherwise, return "ptr:" + std::to_string(*ptr)
//     }
// };
