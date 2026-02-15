// Exercise 06: Parse from String
//
// The reverse of stringify: given a JSON-like string, parse it into a Node
// tree. This is a simplified parser — no unicode escapes, no exponent
// notation for doubles, and no nested escaping in strings.
//
// Supported grammar (simplified):
//   value   = null | bool | number | string | array | object
//   null    = "null"
//   bool    = "true" | "false"
//   number  = optional '-', digits, optional ('.' digits)  -> int or double
//   string  = '"' chars '"'  (no escape sequences needed)
//   array   = '[' value (',' value)* ']' | '[]'
//   object  = '{' pair (',' pair)* '}' | '{}'
//   pair    = string ':' value
//
// Whitespace is skipped between tokens.
//
// TODO:
//   Implement parse() — parse a JSON-like string and return a NodePtr06.
//   Throw std::runtime_error on invalid input.

#pragma once

#include <testkit/testkit.h>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

struct Node06;
using NodePtr06 = std::shared_ptr<Node06>;
using Array06 = std::vector<NodePtr06>;
using Object06 = std::map<std::string, NodePtr06>;

struct Node06 {
    std::variant<std::monostate, std::string, int, double, bool, Array06, Object06> data;
};

// Helper factories (provided)
inline NodePtr06 pn_node(std::variant<std::monostate, std::string, int, double, bool, Array06, Object06> d) {
    return std::make_shared<Node06>(Node06{std::move(d)});
}

// Parse a JSON-like string into a Node tree.
// Throw std::runtime_error on malformed input.
inline NodePtr06 parse(const std::string& input) {
    TODO();
}
