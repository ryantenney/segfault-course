// Exercise 03: Parse from Key-Value Pairs
//
// Configuration often comes from external sources (files, environment
// variables) as string key-value pairs. Parsing them into a typed config
// struct catches errors early and provides a clean API to the rest of
// the code.
//
// TODO:
//   Implement parse_config():
//   - Accept a vector of (key, value) string pairs.
//   - Recognized keys: "port", "host", "max_connections".
//   - For "port" and "max_connections", convert the value string to int.
//     If conversion fails (stoi throws), return std::nullopt.
//   - Unknown keys are ignored.
//   - Start from defaults: port=8080, host="localhost", max_connections=100.
//   - Return the resulting ServerConfig wrapped in optional.

#pragma once

#include <testkit/testkit.h>
#include <optional>
#include <string>
#include <utility>
#include <vector>

struct ServerConfig {
    int port = 8080;
    std::string host = "localhost";
    int max_connections = 100;
};

inline std::optional<ServerConfig> parse_config(
    const std::vector<std::pair<std::string, std::string>>& pairs)
{
    TODO();
}
