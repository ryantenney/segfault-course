// Exercise 01: Member Initializer List
//
// PROBLEM:
//   The Sensor class below initializes its members by assignment inside
//   the constructor body. This works, but it's inefficient and can't be
//   used for const members, references, or types without default constructors.
//
// TODO:
//   1. Rewrite the constructor to use a member initializer list instead of
//      assignment in the body. The constructor body should be empty (or
//      nearly empty).
//   2. Implement the getter methods.
//   3. Uncomment the const member `serial_number_` and initialize it in
//      the member initializer list (you cannot assign to a const in the body).
//
// WHY:
//   The member initializer list is where members are actually constructed.
//   Assignment in the body first default-constructs the member, then
//   assigns to it — two steps instead of one. For const members, references,
//   and types without default constructors, the initializer list is the
//   only option.

#pragma once

#include <testkit/testkit.h>
#include <string>

class Sensor {
private:
    std::string name_;
    double min_value_;
    double max_value_;
    double current_value_;
    // TODO: Uncomment this const member and initialize it in the
    // member initializer list:
    // const int serial_number_;

public:
    // TODO: Rewrite this constructor to use a member initializer list.
    // Add a serial_number parameter and initialize the const member.
    // The body should only contain the TODO() call until you implement it.
    Sensor(std::string name, double min_val, double max_val, int serial) {
        // Assignment in body — inefficient! Rewrite using initializer list.
        // name_ = std::move(name);
        // min_value_ = min_val;
        // max_value_ = max_val;
        // current_value_ = 0.0;
        TODO();
    }

    // Returns the sensor name.
    std::string name() const {
        TODO();
    }

    // Returns the minimum value.
    double min_value() const {
        TODO();
    }

    // Returns the maximum value.
    double max_value() const {
        TODO();
    }

    // Returns the current reading.
    double current_value() const {
        TODO();
    }

    // Returns the serial number.
    int serial_number() const {
        TODO();
    }

    // Records a new reading, clamped to [min_value_, max_value_].
    void record(double value) {
        TODO();
    }
};
