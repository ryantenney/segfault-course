// Exercise 04: Mixin for Logging
//
// A mixin adds reusable functionality to a class via CRTP. Unlike
// traditional inheritance (which models "is-a"), a mixin models
// "has this capability."
//
// The Loggable<Derived> mixin adds a log() method that produces a
// formatted log string. It calls into the derived class to get the
// string representation via to_string().
//
//   class Sensor : public Loggable<Sensor> {
//       std::string to_string() const { return "Sensor(42)"; }
//   };
//
//   Sensor s;
//   s.log("INFO");  // returns "[INFO] Sensor(42)"
//
// TODO:
//   1. Implement Event::to_string() -- return "Event(<name>)" where
//      <name> is the event's name.
//   2. Implement Metric::to_string() -- return "Metric(<name>=<value>)"
//      where <value> is formatted with default precision.
//   3. Implement format_log_entry() -- call obj.log(level) and return
//      the result.
//
// WHY:
//   Mixins are a composable alternative to deep inheritance hierarchies.
//   They let you bolt on cross-cutting concerns (logging, serialization,
//   comparison) without coupling unrelated classes together.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <sstream>

// --- CRTP mixin base (provided, do not modify) ---

template <typename Derived>
class Loggable {
public:
    // Produce a log string: "[<level>] <to_string()>"
    std::string log(const std::string& level) const {
        return "[" + level + "] "
             + static_cast<const Derived*>(this)->to_string();
    }
};

// --- Student implements below ---

class Event : public Loggable<Event> {
    std::string name_;

public:
    explicit Event(std::string name) : name_(std::move(name)) {}
    ~Event() = default;

    const std::string& name() const { return name_; }

    // Return "Event(<name>)", e.g. "Event(click)".
    std::string to_string() const {
        TODO();
    }
};

class Metric : public Loggable<Metric> {
    std::string name_;
    double value_;

public:
    Metric(std::string name, double value)
        : name_(std::move(name)), value_(value) {}
    ~Metric() = default;

    const std::string& name() const { return name_; }
    double value() const { return value_; }

    // Return "Metric(<name>=<value>)", e.g. "Metric(cpu=85.5)".
    // Use std::ostringstream to format the value.
    std::string to_string() const {
        TODO();
    }
};

// Call obj.log(level) and return the result.
// This demonstrates that the CRTP base's log() method works
// generically across all Loggable types.
template <typename Derived>
std::string format_log_entry(const Loggable<Derived>& obj,
                             const std::string& level) {
    TODO();
}
