// Exercise 02: Override Methods
//
// Instead of mutating a config in place, a functional approach returns
// a modified copy. Each with_*() method creates a new ServerConfig
// with one field changed, leaving the original untouched.
//
// TODO:
//   1. Implement with_port()           -- return copy with port changed.
//   2. Implement with_host()           -- return copy with host changed.
//   3. Implement with_max_connections() -- return copy with max_connections changed.

#pragma once

#include <testkit/testkit.h>
#include <string>

struct ServerConfig {
    int port = 8080;
    std::string host = "localhost";
    int max_connections = 100;

    ServerConfig with_port(int p) const {
        TODO();
    }

    ServerConfig with_host(const std::string& h) const {
        TODO();
    }

    ServerConfig with_max_connections(int mc) const {
        TODO();
    }
};
