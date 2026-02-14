// Exercise 04: Virtual Destructor
//
// When you delete a derived object through a base pointer, the base class
// destructor runs. If the base destructor is NOT virtual, only the base
// part is destroyed — the derived part leaks.
//
// Rule: If a class has any virtual methods, it MUST have a virtual destructor.
// If in doubt, always make the destructor virtual.
//
// In this exercise, the Resource base class is missing a virtual destructor.
// When a DerivedResource is deleted through a Resource*, the DerivedResource
// destructor does not run, and cleanup_called remains false.
//
// TODO:
//   1. Fix the Resource class by adding: virtual ~Resource() = default;
//   2. Implement create_derived() to return a new DerivedResource.
//   3. Implement exercise_ready() to gate the tests.

#pragma once

#include <memory>
#include <string>
#include <testkit/testkit.h>

// Track whether cleanup was called (global for simplicity).
inline bool& cleanup_called() {
    static bool flag = false;
    return flag;
}

inline void reset_cleanup() {
    cleanup_called() = false;
}

class Resource {
    std::string name_;

public:
    explicit Resource(std::string name) : name_(std::move(name)) {}

    // BUG: This destructor is not virtual!
    // When deleting a DerivedResource through a Resource*, only this
    // destructor runs — the DerivedResource destructor is skipped.
    //
    // TODO: Change this to:
    //   virtual ~Resource() = default;
    ~Resource() = default;

    const std::string& name() const { return name_; }

    virtual std::string describe() const {
        return "Resource: " + name_;
    }
};

class DerivedResource : public Resource {
    int priority_;

public:
    DerivedResource(std::string name, int priority)
        : Resource(std::move(name)), priority_(priority) {}

    ~DerivedResource() {
        cleanup_called() = true;
    }

    int priority() const { return priority_; }

    std::string describe() const override {
        return "DerivedResource: " + name() + " (priority " +
               std::to_string(priority_) + ")";
    }
};

// Create a DerivedResource and return it as a unique_ptr<Resource>.
inline std::unique_ptr<Resource> create_derived(std::string name, int priority) {
    TODO();
}

// Gate function: implement this to signal that the exercise is ready.
inline bool exercise_ready() {
    TODO();
}
