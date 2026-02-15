// Exercise 05: Validation
//
// A config struct might hold values that individually look fine but
// together are invalid (e.g., TLS enabled but no cert path). A
// validate() function returns a list of all errors found.
//
// TODO:
//   Implement validate():
//   - If port < 1 or port > 65535, add "port out of range".
//   - If host is empty, add "host must not be empty".
//   - If max_connections < 1, add "max_connections must be positive".
//   - If max_connections > 10000, add "max_connections too large".
//   - Return the vector of error strings (empty means valid).

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

struct ServerConfig {
    int port = 8080;
    std::string host = "localhost";
    int max_connections = 100;
};

inline std::vector<std::string> validate(const ServerConfig& cfg) {
    TODO();
}
