// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex02.h"

static testkit::TestRunner runner("05-45-ex02: Request/Response Context");

TEST(runner, "request and response are empty by default") {
    Context ctx;
    ASSERT_EQ(ctx.request, std::string(""));
    ASSERT_EQ(ctx.response, std::string(""));
}

TEST(runner, "request and response can be set directly") {
    Context ctx;
    ctx.request = "GET /index";
    ctx.response = "200 OK";
    ASSERT_EQ(ctx.request, std::string("GET /index"));
    ASSERT_EQ(ctx.response, std::string("200 OK"));
}

TEST(runner, "set_metadata stores a value") {
    Context ctx;
    ctx.set_metadata("user", "alice");
    auto val = ctx.get_metadata("user");
    ASSERT_TRUE(val.has_value());
    ASSERT_EQ(val.value(), std::string("alice"));
}

TEST(runner, "get_metadata returns nullopt for missing key") {
    Context ctx;
    ctx.set_metadata("a", "1");  // gate: triggers TODO()
    auto val = ctx.get_metadata("nonexistent");
    ASSERT_FALSE(val.has_value());
}

TEST(runner, "set_metadata overwrites existing value") {
    Context ctx;
    ctx.set_metadata("key", "old");
    ctx.set_metadata("key", "new");
    auto val = ctx.get_metadata("key");
    ASSERT_TRUE(val.has_value());
    ASSERT_EQ(val.value(), std::string("new"));
}

TEST(runner, "multiple metadata keys are independent") {
    Context ctx;
    ctx.set_metadata("a", "1");
    ctx.set_metadata("b", "2");
    ctx.set_metadata("c", "3");
    auto va = ctx.get_metadata("a");
    auto vb = ctx.get_metadata("b");
    auto vc = ctx.get_metadata("c");
    ASSERT_EQ(va.value(), std::string("1"));
    ASSERT_EQ(vb.value(), std::string("2"));
    ASSERT_EQ(vc.value(), std::string("3"));
}

TESTKIT_MAIN(runner)
