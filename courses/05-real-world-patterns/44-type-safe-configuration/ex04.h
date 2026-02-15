// Exercise 04: Merge Two Configs
//
// When loading configuration from multiple sources (defaults, file,
// environment, command line), later sources override earlier ones.
// An "overlay" config only overrides fields that were explicitly set.
//
// We use std::optional for each field in the overlay to distinguish
// "not set" from "set to a value."
//
// TODO:
//   1. Implement merge_config():
//      - Start with the base config.
//      - For each field in the overlay, if it has a value, use it.
//      - Return the merged ServerConfig.

#pragma once

#include <testkit/testkit.h>
#include <optional>
#include <string>

struct ServerConfig {
    int port = 8080;
    std::string host = "localhost";
    int max_connections = 100;
};

struct ConfigOverlay {
    std::optional<int> port;
    std::optional<std::string> host;
    std::optional<int> max_connections;
};

inline ServerConfig merge_config(const ServerConfig& base, const ConfigOverlay& overlay) {
    TODO();
}
