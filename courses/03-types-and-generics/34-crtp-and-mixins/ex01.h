// Exercise 01: CRTP Counter
//
// The Curiously Recurring Template Pattern (CRTP) is a C++ idiom where a
// class derives from a template base class, passing itself as the template
// argument:
//
//   class Dog : public Counter<Dog> { ... };
//
// Each instantiation of Counter<T> has its own static data, so Counter<Dog>
// and Counter<Cat> track their instance counts independently.
//
// The Counter<Derived> base class below is fully implemented. It increments
// a static count in its constructor and decrements it in its destructor.
// The Dog and Cat classes are also provided -- they already derive from
// Counter<Dog> and Counter<Cat> respectively.
//
// TODO:
//   1. Implement Dog::name() -- return the stored name.
//   2. Implement Cat::name() -- return the stored name.
//   3. Implement make_dogs() -- create a vector<Dog> from the given names.
//   4. Implement total_animals() -- return the sum of Dog::count() and
//      Cat::count().
//
// WHY:
//   CRTP is the foundation of many C++ patterns. The instance-counter
//   example demonstrates how each CRTP instantiation gets its own static
//   state -- a property that catches many beginners off guard.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

// --- CRTP base (provided, do not modify) ---

template <typename Derived>
class Counter {
    static inline int count_ = 0;

public:
    Counter() { ++count_; }
    Counter(const Counter&) { ++count_; }
    Counter(Counter&&) noexcept { ++count_; }
    ~Counter() { --count_; }

    Counter& operator=(const Counter&) = default;
    Counter& operator=(Counter&&) noexcept = default;

    static int count() { return count_; }
};

// --- Dog and Cat structure (provided, do not modify structure) ---

class Dog : public Counter<Dog> {
    std::string name_;

public:
    explicit Dog(std::string name) : name_(std::move(name)) {}
    ~Dog() = default;

    // Return the dog's name.
    const std::string& name() const {
        TODO();
    }
};

class Cat : public Counter<Cat> {
    std::string name_;

public:
    explicit Cat(std::string name) : name_(std::move(name)) {}
    ~Cat() = default;

    // Return the cat's name.
    const std::string& name() const {
        TODO();
    }
};

// Create a vector of Dogs from the given names.
inline std::vector<Dog> make_dogs(const std::vector<std::string>& names) {
    TODO();
}

// Return the total number of live Dog + Cat instances.
inline int total_animals() {
    TODO();
}
