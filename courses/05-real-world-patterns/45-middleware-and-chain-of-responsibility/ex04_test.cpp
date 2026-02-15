// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex04.h"

static testkit::TestRunner runner("05-45-ex04: Early Exit");

TEST(runner, "auth middleware passes when context starts with AUTH:") {
    auto auth = make_auth_middleware();
    std::string ctx = "AUTH:GET /secret";
    bool next_called = false;
    auth(ctx, [&next_called]() { next_called = true; });
    ASSERT_TRUE(next_called);
    ASSERT_EQ(ctx, std::string("GET /secret"));
}

TEST(runner, "auth middleware blocks when context lacks AUTH: prefix") {
    auto auth = make_auth_middleware();
    std::string ctx = "GET /secret";
    bool next_called = false;
    auth(ctx, [&next_called]() { next_called = true; });
    ASSERT_FALSE(next_called);
    ASSERT_EQ(ctx, std::string("401 Unauthorized"));
}

TEST(runner, "chain short-circuits on auth failure") {
    std::string ctx = "GET /secret";
    bool handler_called = false;
    std::vector<Middleware04> mws = {
        make_auth_middleware(),
        [](std::string& c, std::function<void()> next) {
            c += " processed";
            next();
        }
    };
    chain_with_early_exit(mws, ctx, [&handler_called]() { handler_called = true; });
    ASSERT_FALSE(handler_called);
    ASSERT_EQ(ctx, std::string("401 Unauthorized"));
}

TEST(runner, "chain proceeds when auth passes") {
    std::string ctx = "AUTH:GET /data";
    bool handler_called = false;
    std::vector<Middleware04> mws = {
        make_auth_middleware(),
        [](std::string& c, std::function<void()> next) {
            c += " processed";
            next();
        }
    };
    chain_with_early_exit(mws, ctx, [&handler_called]() { handler_called = true; });
    ASSERT_TRUE(handler_called);
    ASSERT_EQ(ctx, std::string("GET /data processed"));
}

TEST(runner, "auth middleware handles AUTH: with empty body") {
    auto auth = make_auth_middleware();
    std::string ctx = "AUTH:";
    bool next_called = false;
    auth(ctx, [&next_called]() { next_called = true; });
    ASSERT_TRUE(next_called);
    ASSERT_EQ(ctx, std::string(""));
}

TESTKIT_MAIN(runner)
