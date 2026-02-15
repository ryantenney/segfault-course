// Exercise 03: Array and Object Values
//
// JSON-like data is recursive: an array contains values, and an object maps
// strings to values. Since variant cannot directly hold a vector of itself
// (incomplete type), we use std::shared_ptr to break the recursion.
//
// This exercise defines a Node type that can be a scalar (string, int, double,
// bool, null), an array (vector of shared_ptr<Node>), or an object
// (map of string to shared_ptr<Node>).
//
// TODO:
//   1. Implement make_null(), make_string(), make_int(), make_double(),
//      make_bool() — factory functions returning shared_ptr<Node>.
//   2. Implement make_array() — returns a shared_ptr<Node> holding an
//      empty Array.
//   3. Implement make_object() — returns a shared_ptr<Node> holding an
//      empty Object.
//   4. Implement array_push() — append a child to an Array node.
//   5. Implement object_set() — set a key in an Object node.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

struct Node;
using NodePtr = std::shared_ptr<Node>;
using Array = std::vector<NodePtr>;
using Object = std::map<std::string, NodePtr>;

struct Node {
    std::variant<std::monostate, std::string, int, double, bool, Array, Object> data;
};

// Factory functions
inline NodePtr make_null() { TODO(); }
inline NodePtr make_string(const std::string& s) { TODO(); }
inline NodePtr make_int(int i) { TODO(); }
inline NodePtr make_double(double d) { TODO(); }
inline NodePtr make_bool(bool b) { TODO(); }
inline NodePtr make_array() { TODO(); }
inline NodePtr make_object() { TODO(); }

// Append `child` to the Array held by `node`.
// Assumes `node` holds an Array.
inline void array_push(NodePtr node, NodePtr child) {
    TODO();
}

// Set `key` to `child` in the Object held by `node`.
// Assumes `node` holds an Object.
inline void object_set(NodePtr node, const std::string& key, NodePtr child) {
    TODO();
}
