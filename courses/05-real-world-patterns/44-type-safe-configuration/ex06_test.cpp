// Exercise 06 -- Tests (read-only)
//
// Verifies nested TlsConfig within ServerConfig.

#include <testkit/testkit.h>
#include "ex06.h"

static testkit::TestRunner runner("05-44-ex06: Nested Config");

TEST(runner, "default tls is disabled") {
    ServerConfig cfg;
    TlsConfig tls = cfg.get_tls();
    ASSERT_FALSE(tls.enabled);
    ASSERT_EQ(tls.cert_path, std::string(""));
    ASSERT_EQ(tls.key_path, std::string(""));
}

TEST(runner, "with_tls returns copy with new tls config") {
    ServerConfig cfg;
    TlsConfig tls;
    tls.enabled = true;
    tls.cert_path = "/etc/ssl/cert.pem";
    tls.key_path = "/etc/ssl/key.pem";

    ServerConfig modified = cfg.with_tls(tls);
    ASSERT_TRUE(modified.get_tls().enabled);
    ASSERT_EQ(modified.get_tls().cert_path, std::string("/etc/ssl/cert.pem"));
    ASSERT_EQ(modified.get_tls().key_path, std::string("/etc/ssl/key.pem"));
}

TEST(runner, "with_tls does not modify original") {
    ServerConfig cfg;
    TlsConfig tls;
    tls.enabled = true;
    tls.cert_path = "/cert";
    tls.key_path = "/key";

    ServerConfig modified = cfg.with_tls(tls);
    ASSERT_FALSE(cfg.get_tls().enabled);
    ASSERT_TRUE(modified.get_tls().enabled);
}

TEST(runner, "with_tls preserves other fields") {
    ServerConfig cfg;
    cfg.port = 443;
    cfg.host = "secure.local";

    TlsConfig tls;
    tls.enabled = true;
    tls.cert_path = "/cert";
    tls.key_path = "/key";

    ServerConfig modified = cfg.with_tls(tls);
    ASSERT_EQ(modified.port, 443);
    ASSERT_EQ(modified.host, std::string("secure.local"));
}

TEST(runner, "valid config with tls disabled") {
    ServerConfig cfg;
    auto errors = validate(cfg);
    ASSERT_TRUE(errors.empty());
}

TEST(runner, "valid config with tls fully configured") {
    ServerConfig cfg;
    TlsConfig tls;
    tls.enabled = true;
    tls.cert_path = "/cert.pem";
    tls.key_path = "/key.pem";
    cfg.tls = tls;
    auto errors = validate(cfg);
    ASSERT_TRUE(errors.empty());
}

TEST(runner, "tls enabled without cert_path") {
    ServerConfig cfg;
    cfg.tls.enabled = true;
    cfg.tls.key_path = "/key.pem";
    auto errors = validate(cfg);
    ASSERT_EQ(errors.size(), std::size_t(1));
    ASSERT_EQ(errors[0], std::string("tls: cert_path required when enabled"));
}

TEST(runner, "tls enabled without key_path") {
    ServerConfig cfg;
    cfg.tls.enabled = true;
    cfg.tls.cert_path = "/cert.pem";
    auto errors = validate(cfg);
    ASSERT_EQ(errors.size(), std::size_t(1));
    ASSERT_EQ(errors[0], std::string("tls: key_path required when enabled"));
}

TEST(runner, "tls enabled without both paths") {
    ServerConfig cfg;
    cfg.tls.enabled = true;
    auto errors = validate(cfg);
    ASSERT_EQ(errors.size(), std::size_t(2));
}

TEST(runner, "port error combined with tls error") {
    ServerConfig cfg;
    cfg.port = 0;
    cfg.tls.enabled = true;
    auto errors = validate(cfg);
    // At least port error + 2 tls errors
    ASSERT_TRUE(errors.size() >= std::size_t(3));
}

TESTKIT_MAIN(runner)
