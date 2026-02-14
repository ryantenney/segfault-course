// Exercise 03: Deleted Copy
//
// PROBLEM:
//   Some classes own resources that cannot be meaningfully duplicated --
//   a file handle, a network socket, a hardware device. For these types,
//   copying should be explicitly forbidden.
//
//   Declaring copy operations as `= delete` makes the compiler reject any
//   attempt to copy the object. This is clearer than the old C++03 trick
//   of making them private and unimplemented.
//
// TODO:
//   1. Delete the copy constructor and copy assignment operator.
//   2. Implement the constructor that opens the resource.
//   3. Implement is_open() and value().
//
// WHY:
//   Making a type non-copyable is a design decision that communicates
//   ownership semantics. If copying doesn't make sense, deleting the
//   operations catches bugs at compile time rather than at runtime.

#pragma once

#include <string>
#include <testkit/testkit.h>

class UniqueResource {
    std::string name_;
    int handle_;
    bool open_;

public:
    // Constructor: open a resource with the given name and handle.
    UniqueResource(std::string name, int handle) {
        TODO();
    }

    // Destructor: mark the resource as closed.
    ~UniqueResource() = default;

    // TODO: Delete the copy constructor.
    // UniqueResource(const UniqueResource&) = ???;

    // TODO: Delete the copy assignment operator.
    // UniqueResource& operator=(const UniqueResource&) = ???;

    const std::string& name() const { return name_; }
    int handle() const { return handle_; }

    bool is_open() const {
        TODO();
    }
};
