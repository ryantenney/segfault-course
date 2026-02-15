// Exercise 07: Config Diffing
//
// When debugging or auditing config changes, it's useful to see which
// fields differ between two configs. A diff function compares two
// ServerConfig instances and returns the names of differing fields.
//
// TODO:
//   Implement config_diff():
//   - Compare each field of lhs and rhs.
//   - If port differs, add "port" to the result.
//   - If host differs, add "host" to the result.
//   - If max_connections differs, add "max_connections" to the result.
//   - Return the vector of differing field names.
//   - The order must be: port, host, max_connections (if each differs).

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

struct ServerConfig {
    int port = 8080;
    std::string host = "localhost";
    int max_connections = 100;
};

inline std::vector<std::string> config_diff(const ServerConfig& lhs, const ServerConfig& rhs) {
    TODO();
}
