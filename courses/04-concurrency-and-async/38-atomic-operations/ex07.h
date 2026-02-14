// Exercise 07: Memory Order Awareness
//
// PROBLEM:
//   By default, all std::atomic operations use memory_order_seq_cst
//   (sequentially consistent), which is the strongest ordering guarantee.
//   It ensures that all threads see operations in the same total order.
//
//   This exercise asks you to use explicit memory orders to understand
//   what they mean:
//     - memory_order_seq_cst: total order visible to all threads.
//     - memory_order_relaxed: no ordering guarantees (only atomicity).
//     - memory_order_release: a store that "publishes" prior writes.
//     - memory_order_acquire: a load that "receives" published writes.
//
//   A release store paired with an acquire load creates a
//   "happens-before" relationship: everything written before the release
//   store is visible to code after the acquire load.
//
// TODO:
//   Implement the SequencedStore class:
//     1. publish(int payload) -- store the payload with release semantics,
//        then set a ready flag with release semantics.
//     2. consume() -- load the ready flag with acquire semantics. If true,
//        load and return the payload with acquire semantics. If false,
//        return -1.
//     3. payload_relaxed() -- load the payload with relaxed semantics.
//        (This is for demonstrating that relaxed loads don't synchronize.)
//
// HINT:
//   - Use store(value, std::memory_order_release) and
//     load(std::memory_order_acquire).
//   - The ready flag ensures consume() only reads payload after publish().

#pragma once

#include <atomic>
#include <testkit/testkit.h>

class SequencedStore {
    std::atomic<int> payload_{0};
    std::atomic<bool> ready_{false};

public:
    // Store the payload with release semantics, then set ready with release.
    void publish(int value) {
        TODO();
    }

    // If ready (acquire load), return the payload (acquire load).
    // Otherwise return -1.
    int consume() {
        TODO();
    }

    // Load the payload with relaxed memory order.
    int payload_relaxed() {
        TODO();
    }
};
