// Exercise 04: Compare-and-Swap
//
// PROBLEM:
//   compare_exchange_weak (CAS) is the fundamental building block of lock-free
//   data structures. It atomically:
//     1. Compares the current value to an "expected" value.
//     2. If they match, replaces the current value with "desired" and returns true.
//     3. If they don't match, loads the current value into "expected" and
//        returns false.
//
//   A lock-free stack push looks like:
//     1. Read the current head.
//     2. Point the new node's next at the current head.
//     3. CAS the head from old to new. If it fails, retry from step 1.
//
// TODO:
//   1. Implement atomic_max(atom, value) -- atomically update atom to be
//      the maximum of its current value and the given value. Use a
//      compare_exchange_weak loop.
//   2. Implement atomic_push(stack, value) -- push a value onto the
//      AtomicStack. Uses CAS to update the head pointer.
//
// HINT:
//   For atomic_max:
//     - Load the current value.
//     - If value <= current, do nothing.
//     - Otherwise, try to CAS from current to value. If CAS fails,
//       current is updated automatically; loop and try again.

#pragma once

#include <atomic>
#include <memory>
#include <testkit/testkit.h>

// Atomically set atom to max(atom, value).
// Uses a compare_exchange_weak loop.
inline void atomic_max(std::atomic<int>& atom, int value) {
    TODO();
}

// A simple lock-free stack node.
struct StackNode {
    int value;
    StackNode* next;
};

// A lock-free stack using atomic head pointer.
struct AtomicStack {
    std::atomic<StackNode*> head{nullptr};
};

// Push a new value onto the stack using CAS.
// Allocates a new StackNode and links it to the front.
inline void atomic_push(AtomicStack& stack, int value) {
    TODO();
}

// Pop a value from the stack using CAS. Returns the value.
// Precondition: stack is non-empty.
// (Provided for testing; students don't implement this.)
inline int atomic_pop(AtomicStack& stack) {
    StackNode* old_head = stack.head.load();
    while (!stack.head.compare_exchange_weak(old_head, old_head->next)) {
        // old_head is updated by compare_exchange_weak on failure
    }
    int val = old_head->value;
    delete old_head;
    return val;
}
