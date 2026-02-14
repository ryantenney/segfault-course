// Exercise 06: Aggregate Initialization
//
// PROBLEM:
//   An aggregate is a class or struct with:
//   - No user-declared constructors (C++17) / no user-provided constructors (C++20)
//   - No private or protected non-static data members
//   - No virtual functions
//   - No virtual/private/protected base classes
//
//   Aggregates support brace initialization and designated initializers (C++20):
//     NetworkConfig cfg = {.host = "example.com", .port = 443, .use_tls = true};
//
// TODO:
//   1. Add in-class default values to the NetworkConfig members:
//      - host defaults to ""
//      - port defaults to 80
//      - use_tls defaults to false
//      - max_connections defaults to 10
//   2. Implement the free functions that create configs using various
//      initialization styles, including designated initializers.
//
// WHY:
//   Aggregates and designated initializers provide clean, readable
//   initialization without writing constructors. They're ideal for
//   configuration structs and plain data objects.

#pragma once

#include <testkit/testkit.h>
#include <string>

// TODO: Add in-class default values (NSDMIs) to these members.
// For example: std::string host = "";
struct NetworkConfig {
    std::string host;
    int port;
    bool use_tls;
    int max_connections;
};

// Returns a default-constructed NetworkConfig (all defaults apply).
inline NetworkConfig make_default_config() {
    TODO();
}

// Returns a config with only host and port set;
// use_tls and max_connections should use their defaults.
inline NetworkConfig make_config(std::string host, int port) {
    TODO();
}

// Returns a config using designated initializers (C++20):
// host = "secure.example.com", port = 443, use_tls = true, max_connections = 100
inline NetworkConfig make_secure_config() {
    TODO();
}

// Returns a config where only use_tls is set to true,
// all other fields use defaults. Use designated initializers.
inline NetworkConfig make_tls_only_config() {
    TODO();
}
