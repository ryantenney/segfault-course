// Exercise 01: Basic Inheritance
//
// Inheritance lets a derived class reuse and extend the interface and
// implementation of a base class. The derived class inherits all public
// and protected members of the base.
//
// Syntax:
//   class Derived : public Base { ... };
//
// Public inheritance means "Derived IS-A Base." A Student IS-A Person.
// The derived class inherits all public members of the base and can
// access them directly.
//
// TODO:
//   1. Implement Student::describe() — return a string combining
//      the inherited name(), age(), and major.
//      Format: "Name, age Age, Major" (e.g., "Alice, age 20, Computer Science")
//      Hint: use std::to_string(age()) to convert the int.
//   2. Implement create_student() to construct a Student.

#pragma once

#include <string>
#include <testkit/testkit.h>

class Person {
    std::string name_;
    int age_;

public:
    Person(std::string name, int age)
        : name_(std::move(name)), age_(age) {}

    const std::string& name() const { return name_; }
    int age() const { return age_; }
};

// Student inherits from Person via public inheritance.
// It adds a "major" field on top of the inherited name and age.
class Student : public Person {
    std::string major_;

public:
    Student(std::string name, int age, std::string major)
        : Person(std::move(name), age), major_(std::move(major)) {}

    const std::string& major() const { return major_; }

    // Return "Name, age Age, Major" (e.g., "Alice, age 20, Computer Science").
    // Hint: name() + ", age " + std::to_string(age()) + ", " + major_
    std::string describe() const {
        TODO();
    }
};

// Create and return a Student with the given name, age, and major.
inline Student create_student(std::string name, int age, std::string major) {
    TODO();
}
