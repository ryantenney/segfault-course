// Exercise 02: Virtual Method Dispatch
//
// A virtual method allows derived classes to provide their own implementation
// of a base class method. When you call a virtual method through a base
// pointer or reference, the program dispatches to the correct override at
// runtime — this is called "dynamic dispatch" or "polymorphism."
//
// Without `virtual`, the call is resolved at compile time based on the
// static type of the pointer, not the actual object type.
//
// Key rules:
//   - Mark the base method `virtual`
//   - Mark the derived override with `override`
//   - Always give the base class a virtual destructor
//
// TODO:
//   1. Implement Dog::speak() — return "Woof"
//   2. Implement Cat::speak() — return "Meow"
//   3. Implement Dog::type() — return "Dog"
//   4. Implement Cat::type() — return "Cat"

#pragma once

#include <memory>
#include <string>
#include <testkit/testkit.h>

class Animal {
public:
    virtual ~Animal() = default;

    // Return the sound this animal makes.
    virtual std::string speak() const = 0;

    // Return the type name of this animal.
    virtual std::string type() const = 0;
};

class Dog : public Animal {
public:
    // Return "Woof".
    std::string speak() const override {
        TODO();
    }

    // Return "Dog".
    std::string type() const override {
        TODO();
    }
};

class Cat : public Animal {
public:
    // Return "Meow".
    std::string speak() const override {
        TODO();
    }

    // Return "Cat".
    std::string type() const override {
        TODO();
    }
};

// Create a Dog and return it as a unique_ptr<Animal>.
inline std::unique_ptr<Animal> make_dog() {
    TODO();
}

// Create a Cat and return it as a unique_ptr<Animal>.
inline std::unique_ptr<Animal> make_cat() {
    TODO();
}
