// Exercise 08 — Tests (read-only)

#include <testkit/testkit.h>
#include <vector>
#include "ex08.h"

static testkit::TestRunner runner("05-45-ex08: Conditional Middleware");

TEST(runner, "path middleware applies tag when prefix matches") {
    auto mw = make_path_middleware("/api", "[api]");
    std::string ctx = "/api/users";
    mw(ctx, []() {});
    ASSERT_EQ(ctx, std::string("/api/users[api]"));
}

TEST(runner, "path middleware skips when prefix does not match") {
    auto mw = make_path_middleware("/api", "[api]");
    std::string ctx = "/home/page";
    mw(ctx, []() {});
    ASSERT_EQ(ctx, std::string("/home/page"));
}

TEST(runner, "path middleware always calls next") {
    auto mw = make_path_middleware("/api", "[api]");

    bool next1 = false;
    std::string ctx1 = "/api/data";
    mw(ctx1, [&next1]() { next1 = true; });
    ASSERT_TRUE(next1);

    bool next2 = false;
    std::string ctx2 = "/other";
    mw(ctx2, [&next2]() { next2 = true; });
    ASSERT_TRUE(next2);
}

TEST(runner, "multiple conditional middleware apply independently") {
    auto api_mw = make_path_middleware("/api", "[api]");
    auto admin_mw = make_path_middleware("/admin", "[admin]");

    std::string ctx1 = "/api/data";
    api_mw(ctx1, []() {});
    admin_mw(ctx1, []() {});
    ASSERT_EQ(ctx1, std::string("/api/data[api]"));

    std::string ctx2 = "/admin/settings";
    api_mw(ctx2, []() {});
    admin_mw(ctx2, []() {});
    ASSERT_EQ(ctx2, std::string("/admin/settings[admin]"));
}

TEST(runner, "path middleware matches exact prefix") {
    auto mw = make_path_middleware("/api", "[hit]");
    std::string ctx = "/apiary";
    mw(ctx, []() {});
    // "/apiary" starts with "/api", so it should match
    ASSERT_EQ(ctx, std::string("/apiary[hit]"));
}

TESTKIT_MAIN(runner)
