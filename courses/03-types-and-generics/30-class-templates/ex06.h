// Exercise 06: Full Specialization
//
// PROBLEM:
//   While partial specialization handles families of types (e.g., all
//   pointers), full specialization handles one specific type.  Here,
//   you'll fully specialize Serializer for std::string.
//
//   The primary template uses std::to_string(), which doesn't work for
//   std::string (it's already a string!).  The full specialization
//   provides custom logic for string serialization.
//
// TODO:
//   1. Implement the primary Serializer<T>::serialize() method.
//      Return: "value:" + std::to_string(value)
//
//   2. Write a full specialization for std::string:
//        template<>
//        class Serializer<std::string> { ... };
//      Its serialize() method should:
//        - Return: "str:" + value.substr(0, 10)
//        (truncate to 10 characters for "preview" serialization)
//
//   3. Implement the describe() function for the primary template.
//      Return: "generic"
//
//   4. Implement the describe() function in the std::string specialization.
//      Return: "string"
//
// WHY:
//   Full specialization lets you provide a completely custom
//   implementation for one particular type.  The compiler will prefer
//   the most specialized match: full > partial > primary.

#pragma once

#include <testkit/testkit.h>
#include <string>

// Primary template
template<typename T>
class Serializer {
public:
    static std::string serialize(const T& value) {
        TODO();
    }

    static std::string describe() {
        TODO();
    }
};

// TODO: Add a full specialization of Serializer for std::string.
//
// template<>
// class Serializer<std::string> {
// public:
//     static std::string serialize(const std::string& value) {
//         return "str:" + value.substr(0, 10);
//     }
//
//     static std::string describe() {
//         return "string";
//     }
// };
