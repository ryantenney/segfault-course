// Exercise 05: Serialize to String
//
// Given a Node tree (from ex03/ex04), produce a JSON-like string
// representation. This is the "stringify" direction of serialization.
//
// Output format:
//   null       -> "null"
//   string     -> "\"hello\""  (quoted with double quotes)
//   int        -> "42"
//   double     -> uses std::ostringstream default formatting
//   bool       -> "true" or "false"
//   array      -> "[1, \"a\", true]"  (comma+space separated)
//   object     -> "{\"key\": value, ...}"  (sorted by key, comma+space separated)
//
// TODO:
//   Implement stringify() — convert a Node tree to a JSON-like string.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

struct Node05;
using NodePtr05 = std::shared_ptr<Node05>;
using Array05 = std::vector<NodePtr05>;
using Object05 = std::map<std::string, NodePtr05>;

struct Node05 {
    std::variant<std::monostate, std::string, int, double, bool, Array05, Object05> data;
};

// Helper factories (provided)
inline NodePtr05 sn_null() { return std::make_shared<Node05>(Node05{std::monostate{}}); }
inline NodePtr05 sn_string(const std::string& s) { return std::make_shared<Node05>(Node05{s}); }
inline NodePtr05 sn_int(int i) { return std::make_shared<Node05>(Node05{i}); }
inline NodePtr05 sn_double(double d) { return std::make_shared<Node05>(Node05{d}); }
inline NodePtr05 sn_bool(bool b) { return std::make_shared<Node05>(Node05{b}); }
inline NodePtr05 sn_array(Array05 arr) { return std::make_shared<Node05>(Node05{std::move(arr)}); }
inline NodePtr05 sn_object(Object05 obj) { return std::make_shared<Node05>(Node05{std::move(obj)}); }

// Convert a Node tree into a JSON-like string.
inline std::string stringify(const NodePtr05& node) {
    TODO();
}
