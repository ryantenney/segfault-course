// Exercise 04: Setter with Validation
//
// PROBLEM:
//   A User class needs setters that enforce constraints. Without
//   validation, anyone can set an empty name or a negative age, putting
//   the object into an invalid state.
//
// TODO:
//   Implement the setter methods with validation:
//   1. set_name(name) — throw std::invalid_argument if name is empty
//   2. set_age(age)   — throw std::invalid_argument if age < 0 or age > 150
//   3. set_email(email) — throw std::invalid_argument if email doesn't
//      contain '@'
//
//   Also implement the getters: name(), age(), email().
//
// WHY:
//   Setters with validation are the most basic form of invariant
//   enforcement. The class guarantees that its state is always valid
//   — no consumer can break that promise.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <stdexcept>

class User {
private:
    std::string name_;
    int age_;
    std::string email_;

public:
    User(std::string name, int age, std::string email)
        : name_(std::move(name)), age_(age), email_(std::move(email)) {}

    // Returns the user's name.
    std::string name() const {
        TODO();
    }

    // Returns the user's age.
    int age() const {
        TODO();
    }

    // Returns the user's email.
    std::string email() const {
        TODO();
    }

    // Sets the user's name.
    // Throws std::invalid_argument if name is empty.
    void set_name(std::string name) {
        TODO();
    }

    // Sets the user's age.
    // Throws std::invalid_argument if age < 0 or age > 150.
    void set_age(int age) {
        TODO();
    }

    // Sets the user's email.
    // Throws std::invalid_argument if email does not contain '@'.
    void set_email(std::string email) {
        TODO();
    }
};
