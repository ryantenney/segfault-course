// Exercise 08: Visitor Pattern
//
// Instead of using if/else chains with std::holds_alternative, the visitor
// pattern lets you define typed callbacks that are dispatched based on the
// actual type held by the variant. This is cleaner and ensures every type
// is handled.
//
// For a Node tree, a visitor traverses all nodes depth-first, calling the
// appropriate callback for each one.
//
// TODO:
//   Implement visit_value() — traverse the Node tree depth-first and call
//   the appropriate callback from the Visitor struct for each node.
//   For arrays: call on_array_start, visit each element, call on_array_end.
//   For objects: call on_object_start, visit each entry (key then value),
//   call on_object_end.

#pragma once

#include <testkit/testkit.h>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

struct Node08;
using NodePtr08 = std::shared_ptr<Node08>;
using Array08 = std::vector<NodePtr08>;
using Object08 = std::map<std::string, NodePtr08>;

struct Node08 {
    std::variant<std::monostate, std::string, int, double, bool, Array08, Object08> data;
};

// Helper factories (provided)
inline NodePtr08 vn_null() { return std::make_shared<Node08>(Node08{std::monostate{}}); }
inline NodePtr08 vn_string(const std::string& s) { return std::make_shared<Node08>(Node08{s}); }
inline NodePtr08 vn_int(int i) { return std::make_shared<Node08>(Node08{i}); }
inline NodePtr08 vn_bool(bool b) { return std::make_shared<Node08>(Node08{b}); }
inline NodePtr08 vn_array(Array08 arr) { return std::make_shared<Node08>(Node08{std::move(arr)}); }
inline NodePtr08 vn_object(Object08 obj) { return std::make_shared<Node08>(Node08{std::move(obj)}); }

struct Visitor {
    std::function<void()> on_null = []() {};
    std::function<void(const std::string&)> on_string = [](const std::string&) {};
    std::function<void(int)> on_int = [](int) {};
    std::function<void(double)> on_double = [](double) {};
    std::function<void(bool)> on_bool = [](bool) {};
    std::function<void()> on_array_start = []() {};
    std::function<void()> on_array_end = []() {};
    std::function<void()> on_object_start = []() {};
    std::function<void(const std::string&)> on_object_key = [](const std::string&) {};
    std::function<void()> on_object_end = []() {};
};

// Traverse the Node tree depth-first, calling the appropriate Visitor callbacks.
// Scalars: call on_null/on_string/on_int/on_double/on_bool.
// Arrays: call on_array_start, visit each element, call on_array_end.
// Objects: call on_object_start, then for each entry call on_object_key
//          followed by visiting the value, then call on_object_end.
inline void visit_value(const NodePtr08& node, const Visitor& v) {
    TODO();
}
