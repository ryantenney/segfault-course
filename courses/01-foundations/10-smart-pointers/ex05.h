// Exercise 05: Shared Ownership
//
// std::shared_ptr uses reference counting to allow multiple owners of the
// same object. The object is destroyed when the last shared_ptr to it is
// destroyed or reset. use_count() tells you how many shared_ptrs share
// ownership of the managed object.
//
// TODO:
//   Implement the functions below using std::make_shared and shared_ptr
//   operations: use_count(), reset(), copy construction.

#pragma once

#include <memory>
#include <string>
#include <testkit/testkit.h>

struct Connection {
    std::string endpoint;
    explicit Connection(std::string ep) : endpoint(std::move(ep)) {}
};

// Create a shared_ptr<Connection> with the given endpoint.
inline std::shared_ptr<Connection> open_connection(const std::string& endpoint) {
    TODO();
}

// Return the current reference count for the shared_ptr.
inline long get_ref_count(const std::shared_ptr<Connection>& conn) {
    TODO();
}

// Create and return a copy of the shared_ptr (increasing the reference count).
inline std::shared_ptr<Connection> share_connection(const std::shared_ptr<Connection>& conn) {
    TODO();
}

// Reset the given shared_ptr to null. This decrements the reference count.
// Return the reference count of the *original* object after the reset.
// Hint: you'll need another shared_ptr that still points to the object
//       to observe the count after the reset.
inline long close_and_report(std::shared_ptr<Connection>& conn,
                             const std::shared_ptr<Connection>& observer) {
    TODO();
}
