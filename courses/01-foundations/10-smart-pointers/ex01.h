// Exercise 01: Create a unique_ptr
//
// std::unique_ptr is the go-to smart pointer for single ownership. It wraps a
// raw pointer and automatically deletes the managed object when the unique_ptr
// goes out of scope. std::make_unique is the preferred way to create one.
//
// TODO:
//   Implement the functions below using std::make_unique and unique_ptr
//   member functions: get(), operator*, operator->, operator bool, reset().

#pragma once

#include <memory>
#include <string>
#include <testkit/testkit.h>

struct Widget {
    std::string name;
    explicit Widget(std::string n) : name(std::move(n)) {}
};

// Create and return a unique_ptr<Widget> with the given name.
inline std::unique_ptr<Widget> create_widget(const std::string& name) {
    TODO();
}

// Return the name of the widget pointed to by the unique_ptr.
// Precondition: ptr is not null.
inline std::string get_widget_name(const std::unique_ptr<Widget>& ptr) {
    TODO();
}

// Return true if the unique_ptr is non-null.
inline bool is_valid(const std::unique_ptr<Widget>& ptr) {
    TODO();
}

// Reset the unique_ptr to null and return the name that the widget had
// before being destroyed.
inline std::string reset_widget(std::unique_ptr<Widget>& ptr) {
    TODO();
}
