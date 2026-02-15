// Exercise 01: To/From Map
//
// The simplest form of serialization is converting a struct to and from a
// flat key-value map. This is a common pattern for configuration, form data,
// and simple persistence layers.
//
// TODO:
//   1. Implement to_map() — convert a Person to a map<string, string>.
//      Keys: "name", "age", "email". Convert age to string.
//   2. Implement from_map() — construct a Person from a map<string, string>.
//      Parse age from string using std::stoi. If "age" key is missing, default
//      to 0. If "name" or "email" keys are missing, default to "".

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <string>

struct Person {
    std::string name;
    int age = 0;
    std::string email;
};

// Convert a Person to a flat map.
// Keys: "name", "age", "email"
inline std::map<std::string, std::string> to_map(const Person& p) {
    TODO();
}

// Construct a Person from a flat map.
// Missing keys default: name="", age=0, email=""
inline Person from_map(const std::map<std::string, std::string>& m) {
    TODO();
}
