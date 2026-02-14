// Exercise 03: Transfer Ownership
//
// unique_ptr cannot be copied -- it models exclusive ownership. To transfer
// ownership you must use std::move, which converts the source to an rvalue
// reference. After the move, the source unique_ptr is null.
//
// TODO:
//   Implement the functions below. Pay attention to parameter types: a
//   function that takes unique_ptr by value *consumes* the pointer.

#pragma once

#include <memory>
#include <string>
#include <testkit/testkit.h>

struct Gadget {
    std::string label;
    explicit Gadget(std::string l) : label(std::move(l)) {}
};

// Create a Gadget wrapped in a unique_ptr.
inline std::unique_ptr<Gadget> make_gadget(const std::string& label) {
    TODO();
}

// Take ownership of a Gadget and return its label.
// After this call the caller's unique_ptr should be null.
inline std::string consume_gadget(std::unique_ptr<Gadget> gadget) {
    TODO();
}

// Transfer a gadget from `source` into `dest`.
// After the transfer, source must be null and dest must hold the gadget.
inline void transfer_gadget(std::unique_ptr<Gadget>& source,
                            std::unique_ptr<Gadget>& dest) {
    TODO();
}
