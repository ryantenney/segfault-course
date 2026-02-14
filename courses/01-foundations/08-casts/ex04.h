// Exercise 04: Safe Downcasting (Reference)
//
// PROBLEM:
//   When you use dynamic_cast with references instead of pointers, a
//   failed cast throws std::bad_cast instead of returning nullptr.
//   This makes sense: a reference can't be null, so the only way to
//   signal failure is an exception.
//
// TODO:
//   Implement get_speak() to dynamic_cast the Animal& to a Dog& or Cat&.
//   Catch std::bad_cast if the cast fails and return "unknown".
//
// WHY:
//   Reference-based dynamic_cast is useful when null isn't a valid
//   result — you either get the derived type or handle the error.

#pragma once
#include <stdexcept>
#include <string>
#include <testkit/testkit.h>

class Animal {
public:
    virtual ~Animal() = default;
    virtual std::string type() const = 0;
};

class Dog : public Animal {
public:
    std::string type() const override { return "Dog"; }
    std::string speak() const { return "Woof"; }
};

class Cat : public Animal {
public:
    std::string type() const override { return "Cat"; }
    std::string speak() const { return "Meow"; }
};

class Fish : public Animal {
public:
    std::string type() const override { return "Fish"; }
};

// Attempt to dynamic_cast the animal reference to Dog&.
// If it succeeds, return dog.speak().
// If it throws std::bad_cast, return "unknown".
inline std::string try_dog_speak(Animal& animal) {
    TODO();
}

// Attempt to dynamic_cast the animal reference to Cat&.
// If it succeeds, return cat.speak().
// If it throws std::bad_cast, return "unknown".
inline std::string try_cat_speak(Animal& animal) {
    TODO();
}
