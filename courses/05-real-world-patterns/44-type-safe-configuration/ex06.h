// Exercise 06: Nested Config
//
// Real-world configs are hierarchical. A ServerConfig might contain a
// TlsConfig sub-config for TLS/SSL settings. The nested config has its
// own defaults and validation.
//
// TODO:
//   1. Implement TlsConfig with defaults:
//      - enabled: false
//      - cert_path: "" (empty)
//      - key_path: "" (empty)
//   2. Implement get_tls() to return the TlsConfig.
//   3. Implement with_tls() to return a copy of ServerConfig with a
//      new TlsConfig.
//   4. Implement validate():
//      - All ServerConfig rules from ex05 still apply.
//      - If tls.enabled is true and cert_path is empty,
//        add "tls: cert_path required when enabled".
//      - If tls.enabled is true and key_path is empty,
//        add "tls: key_path required when enabled".

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

struct TlsConfig {
    bool enabled = false;
    std::string cert_path;
    std::string key_path;
};

struct ServerConfig {
    int port = 8080;
    std::string host = "localhost";
    int max_connections = 100;
    TlsConfig tls;

    TlsConfig get_tls() const {
        TODO();
    }

    ServerConfig with_tls(const TlsConfig& t) const {
        TODO();
    }
};

inline std::vector<std::string> validate(const ServerConfig& cfg) {
    TODO();
}
