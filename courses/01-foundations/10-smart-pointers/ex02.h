// Exercise 02: Raw to unique_ptr
//
// Legacy C++ code is full of manual new/delete. Converting to unique_ptr
// eliminates leaks and makes ownership explicit. The key insight: every
// `new` should become `make_unique`, and every `delete` disappears.
//
// TODO:
//   Refactor each function to use std::make_unique instead of raw new/delete.
//   The behavior must remain identical, but no raw new or delete should appear.

#pragma once

#include <memory>
#include <string>
#include <testkit/testkit.h>

struct Sensor {
    std::string id;
    double reading;
    Sensor(std::string i, double r) : id(std::move(i)), reading(r) {}
};

// Create a Sensor with the given id and reading.
// Original (leaky) code used: Sensor* s = new Sensor(id, reading); return s;
// Refactor to return a unique_ptr<Sensor>.
inline std::unique_ptr<Sensor> create_sensor(const std::string& id, double reading) {
    TODO();
}

// Return the reading from a sensor, or -1.0 if the pointer is null.
inline double read_sensor(const std::unique_ptr<Sensor>& sensor) {
    TODO();
}

// Replace the sensor's reading with a new value.
// Precondition: sensor is not null.
inline void update_reading(const std::unique_ptr<Sensor>& sensor, double new_reading) {
    TODO();
}

// Release ownership from the unique_ptr and return the raw pointer.
// The caller is now responsible for deletion.
// (This simulates interfacing with legacy APIs that expect raw pointers.)
inline Sensor* release_sensor(std::unique_ptr<Sensor>& sensor) {
    TODO();
}
