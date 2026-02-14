// Exercise 07: Object Slicing
//
// When you assign a derived object to a base object BY VALUE, the derived
// part is "sliced off." Only the base part is copied. This is called
// object slicing.
//
//   Derived d;
//   Base b = d;  // SLICED: b is only a Base, the Derived part is lost
//
// After slicing, calling a virtual method on `b` calls the BASE version,
// not the derived override — because `b` IS a Base, not a Derived.
//
// To preserve polymorphism, always use pointers or references:
//   Base& ref = d;      // no slicing — ref still refers to the Derived
//   Base* ptr = &d;     // no slicing — ptr points to the full Derived
//
// TODO:
//   1. Implement Instrument::play() — return "..." (the base sound).
//   2. Implement Guitar::play() — return "Twang!".
//   3. Implement Drum::play() — return "Boom!".
//   4. Implement play_by_value(Base b) — demonstrates slicing.
//   5. Implement play_by_reference(const Base& b) — preserves polymorphism.

#pragma once

#include <string>
#include <testkit/testkit.h>

class Instrument {
public:
    virtual ~Instrument() = default;

    // Return "..." — the default sound.
    virtual std::string play() const {
        TODO();
    }
};

class Guitar : public Instrument {
public:
    // Return "Twang!".
    std::string play() const override {
        TODO();
    }
};

class Drum : public Instrument {
public:
    // Return "Boom!".
    std::string play() const override {
        TODO();
    }
};

// Takes an Instrument BY VALUE — this slices off the derived part.
// The returned string will always be the base Instrument::play() result.
inline std::string play_by_value(Instrument inst) {
    TODO();
}

// Takes an Instrument BY CONST REFERENCE — preserves polymorphism.
// The returned string will be from the actual derived type's play().
inline std::string play_by_reference(const Instrument& inst) {
    TODO();
}
