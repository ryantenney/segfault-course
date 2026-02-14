// Exercise 07: Strong Typedef
//
// In C++, type aliases (typedef / using) create interchangeable types:
//
//   using UserId = int;
//   using OrderId = int;
//   void process(UserId u, OrderId o);
//   process(order_id, user_id);  // compiles — but arguments are swapped!
//
// A "strong typedef" wraps the underlying type in a struct so the compiler
// treats them as distinct types. Swapping arguments becomes a compile error.
//
// TODO:
//   1. Add an explicit constructor to each wrapper struct.
//   2. Implement the helper functions.
//
// Each wrapper should:
//   - Store the value in a public member named `value`
//   - Have an explicit constructor taking the underlying type
//   - Support operator== and operator!= for comparison

#pragma once

#include <testkit/testkit.h>

// TODO: Add an explicit constructor: explicit UserId(int v) : value(v) {}
struct UserId {
    int value = 0;

    bool operator==(const UserId&) const = default;
    bool operator!=(const UserId&) const = default;
};

// TODO: Add an explicit constructor: explicit OrderId(int v) : value(v) {}
struct OrderId {
    int value = 0;

    bool operator==(const OrderId&) const = default;
    bool operator!=(const OrderId&) const = default;
};

// Create a UserId from a raw integer.
inline UserId make_user_id(int id) {
    TODO();
}

// Create an OrderId from a raw integer.
inline OrderId make_order_id(int id) {
    TODO();
}

// Return the raw integer value from a UserId.
inline int user_id_value(UserId id) {
    TODO();
}

// Return the raw integer value from an OrderId.
inline int order_id_value(OrderId id) {
    TODO();
}
