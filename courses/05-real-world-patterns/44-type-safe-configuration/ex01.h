// Exercise 01: Config Struct with Defaults
//
// A configuration struct with in-class member initializers provides
// sensible defaults. Callers can create a config and only override
// the fields they care about.
//
// TODO:
//   1. Set default values for the ServerConfig fields:
//      - port: 8080
//      - host: "localhost"
//      - max_connections: 100
//   2. Implement get_port(), get_host(), get_max_connections().

#pragma once

#include <testkit/testkit.h>
#include <string>

struct ServerConfig {
    int port = 0;               // TODO: default to 8080
    std::string host;           // TODO: default to "localhost"
    int max_connections = 0;    // TODO: default to 100

    int get_port() const {
        TODO();
    }

    std::string get_host() const {
        TODO();
    }

    int get_max_connections() const {
        TODO();
    }
};
