// Exercise 07: Pretty Print
//
// Compact JSON is hard to read. A pretty printer adds newlines and
// indentation to make the structure clear. This exercise produces
// multi-line output with configurable indentation.
//
// Output format (indent = 2):
//   {
//     "name": "Alice",
//     "items": [
//       1,
//       2
//     ]
//   }
//
// Rules:
//   - Scalars: same as stringify (inline, no newlines).
//   - Empty array/object: "[]" / "{}" (no newlines).
//   - Non-empty array: "[" newline, each element indented, "," after each
//     except last, newline, closing "]" at parent indent.
//   - Non-empty object: same pattern with "{" / "}".
//
// TODO:
//   Implement pretty_print() — return a formatted string with the given
//   indent_width (number of spaces per level).

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

struct Node07;
using NodePtr07 = std::shared_ptr<Node07>;
using Array07 = std::vector<NodePtr07>;
using Object07 = std::map<std::string, NodePtr07>;

struct Node07 {
    std::variant<std::monostate, std::string, int, double, bool, Array07, Object07> data;
};

// Helper factories (provided)
inline NodePtr07 pp_null() { return std::make_shared<Node07>(Node07{std::monostate{}}); }
inline NodePtr07 pp_string(const std::string& s) { return std::make_shared<Node07>(Node07{s}); }
inline NodePtr07 pp_int(int i) { return std::make_shared<Node07>(Node07{i}); }
inline NodePtr07 pp_bool(bool b) { return std::make_shared<Node07>(Node07{b}); }
inline NodePtr07 pp_array(Array07 arr) { return std::make_shared<Node07>(Node07{std::move(arr)}); }
inline NodePtr07 pp_object(Object07 obj) { return std::make_shared<Node07>(Node07{std::move(obj)}); }

// Pretty-print a Node tree with the given indentation width (spaces per level).
// `indent_width` is the number of spaces per nesting level.
inline std::string pretty_print(const NodePtr07& node, int indent_width) {
    TODO();
}
