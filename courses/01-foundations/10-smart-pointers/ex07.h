// Exercise 07: Break a Cycle with weak_ptr
//
// When two objects hold shared_ptrs to each other, a reference cycle forms:
// neither object's reference count can ever reach zero, so both leak.
//
// std::weak_ptr breaks cycles. It observes a shared object without
// incrementing the reference count. To access the object, call lock()
// which returns a shared_ptr (or nullptr if the object has been destroyed).
//
// TODO:
//   Fix the cycle below by changing one of the shared_ptr members to a
//   weak_ptr. Then implement the helper functions.

#pragma once

#include <memory>
#include <string>
#include <testkit/testkit.h>

struct Node; // forward declaration

struct Node {
    std::string name;
    // BUG: If both `next` and `prev` are shared_ptr, two nodes pointing to
    //      each other form a cycle and leak. Fix this by making `prev` a
    //      weak_ptr<Node>.
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev; // <-- change this to std::weak_ptr<Node>

    explicit Node(std::string n) : name(std::move(n)) {}
};

// Create a shared_ptr<Node> with the given name.
inline std::shared_ptr<Node> make_node(const std::string& name) {
    TODO();
}

// Link two nodes: a->next = b, b->prev = a.
// After fixing the cycle, b->prev should be a weak_ptr.
inline void link_nodes(std::shared_ptr<Node>& a, std::shared_ptr<Node>& b) {
    TODO();
}

// Return the name of the previous node by locking the weak_ptr.
// If the previous node has been destroyed, return "expired".
inline std::string get_prev_name(const std::shared_ptr<Node>& node) {
    TODO();
}
