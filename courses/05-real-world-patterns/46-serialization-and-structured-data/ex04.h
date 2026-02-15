// Exercise 04: Type-safe Accessors
//
// Raw std::get<T> on a variant throws std::bad_variant_access if the type
// is wrong. For user-facing APIs, it's better to return std::optional<T>
// so callers can handle the "wrong type" case gracefully.
//
// This exercise adds type-safe accessor functions to the Node type from ex03.
//
// TODO:
//   1. Implement as_string() — return optional<string> if the node holds a
//      string, std::nullopt otherwise.
//   2. Implement as_int() — same pattern for int.
//   3. Implement as_double() — same pattern for double.
//   4. Implement as_bool() — same pattern for bool.
//   5. Implement as_array() — return optional<Array> (the vector).
//   6. Implement as_object() — return optional<Object> (the map).

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

struct Node04;
using NodePtr04 = std::shared_ptr<Node04>;
using Array04 = std::vector<NodePtr04>;
using Object04 = std::map<std::string, NodePtr04>;

struct Node04 {
    std::variant<std::monostate, std::string, int, double, bool, Array04, Object04> data;
};

// Accessor: return the string if the node holds one, else nullopt.
inline std::optional<std::string> as_string(const NodePtr04& node) { TODO(); }

// Accessor: return the int if the node holds one, else nullopt.
inline std::optional<int> as_int(const NodePtr04& node) { TODO(); }

// Accessor: return the double if the node holds one, else nullopt.
inline std::optional<double> as_double(const NodePtr04& node) { TODO(); }

// Accessor: return the bool if the node holds one, else nullopt.
inline std::optional<bool> as_bool(const NodePtr04& node) { TODO(); }

// Accessor: return the array if the node holds one, else nullopt.
inline std::optional<Array04> as_array(const NodePtr04& node) { TODO(); }

// Accessor: return the object if the node holds one, else nullopt.
inline std::optional<Object04> as_object(const NodePtr04& node) { TODO(); }

// Helper factories (provided, not TODO)
inline NodePtr04 mk_string(const std::string& s) {
    return std::make_shared<Node04>(Node04{s});
}
inline NodePtr04 mk_int(int i) {
    return std::make_shared<Node04>(Node04{i});
}
inline NodePtr04 mk_double(double d) {
    return std::make_shared<Node04>(Node04{d});
}
inline NodePtr04 mk_bool(bool b) {
    return std::make_shared<Node04>(Node04{b});
}
inline NodePtr04 mk_null() {
    return std::make_shared<Node04>(Node04{std::monostate{}});
}
inline NodePtr04 mk_array(Array04 arr = {}) {
    return std::make_shared<Node04>(Node04{std::move(arr)});
}
inline NodePtr04 mk_object(Object04 obj = {}) {
    return std::make_shared<Node04>(Node04{std::move(obj)});
}
