// Exercise 07: Multiple Mixin Bases
//
// A class can derive from multiple CRTP bases simultaneously, composing
// several mixins into a single type:
//
//   class Widget : public Printable<Widget>,
//                  public Serializable<Widget> { ... };
//
// Each mixin adds independent functionality. The derived class must
// satisfy the requirements of all its mixin bases.
//
// In this exercise, two mixin bases are provided:
//
//   Printable<Derived>: adds a print() method that calls
//       static_cast<const Derived*>(this)->format() to get a string.
//
//   Cloneable<Derived>: adds a clone() method that returns a copy
//       using static_cast<const Derived*>(this)->clone_impl().
//
// TODO:
//   1. Implement Config::format() -- return "Config{<key>=<value>}".
//   2. Implement Config::clone_impl() -- return a copy of *this.
//   3. Implement Message::format() -- return "Message{<sender>: <text>}".
//   4. Implement Message::clone_impl() -- return a copy of *this.
//   5. Implement the free function print_and_clone() that calls
//      obj.print() and obj.clone(), returning a pair of the print
//      string and the cloned object.
//
// WHY:
//   Composing multiple mixins is the culmination of the CRTP pattern.
//   It gives you a form of multiple inheritance that is safe, efficient,
//   and composable -- each mixin is independent and adds no virtual
//   dispatch overhead.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <utility>

// --- CRTP mixin bases (provided, do not modify) ---

template <typename Derived>
class Printable {
public:
    // Returns the formatted string from the derived class.
    std::string print() const {
        return static_cast<const Derived*>(this)->format();
    }
};

template <typename Derived>
class Cloneable {
public:
    // Returns a copy of the derived object.
    Derived clone() const {
        return static_cast<const Derived*>(this)->clone_impl();
    }
};

// --- Student implements below ---

class Config : public Printable<Config>,
               public Cloneable<Config> {
    std::string key_;
    std::string value_;

public:
    Config(std::string key, std::string value)
        : key_(std::move(key)), value_(std::move(value)) {}
    ~Config() = default;

    const std::string& key() const { return key_; }
    const std::string& value() const { return value_; }

    // Return "Config{<key>=<value>}", e.g. "Config{port=8080}".
    std::string format() const {
        TODO();
    }

    // Return a copy of this Config.
    Config clone_impl() const {
        TODO();
    }
};

class Message : public Printable<Message>,
                public Cloneable<Message> {
    std::string sender_;
    std::string text_;

public:
    Message(std::string sender, std::string text)
        : sender_(std::move(sender)), text_(std::move(text)) {}
    ~Message() = default;

    const std::string& sender() const { return sender_; }
    const std::string& text() const { return text_; }

    // Return "Message{<sender>: <text>}", e.g. "Message{Alice: hello}".
    std::string format() const {
        TODO();
    }

    // Return a copy of this Message.
    Message clone_impl() const {
        TODO();
    }
};

// Call obj.print() and obj.clone(). Return a pair of the print string
// and the cloned object.
//
// The Derived type must inherit from both Printable and Cloneable.
template <typename Derived>
std::pair<std::string, Derived> print_and_clone(const Derived& obj) {
    TODO();
}
