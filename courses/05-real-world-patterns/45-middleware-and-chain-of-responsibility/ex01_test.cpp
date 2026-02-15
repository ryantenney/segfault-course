// Exercise 01 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex01.h"

static testkit::TestRunner runner("05-45-ex01: Function Chain");

TEST(runner, "middleware receives the context") {
    std::string ctx = "hello";
    Middleware mw = [](std::string& c, std::function<void()> next) {
        c += " world";
        next();
    };
    run_middleware(mw, ctx, []() {});
    ASSERT_EQ(ctx, std::string("hello world"));
}

TEST(runner, "middleware calls next") {
    std::string ctx;
    bool next_called = false;
    Middleware mw = [](std::string& c, std::function<void()> next) {
        next();
    };
    run_middleware(mw, ctx, [&next_called]() { next_called = true; });
    ASSERT_TRUE(next_called);
}

TEST(runner, "middleware can modify context before and after next") {
    std::string ctx = "A";
    std::string order;
    Middleware mw = [&order](std::string& c, std::function<void()> next) {
        order += "before,";
        c += "B";
        next();
        order += "after";
    };
    run_middleware(mw, ctx, [&order]() { order += "next,"; });
    ASSERT_EQ(ctx, std::string("AB"));
    ASSERT_EQ(order, std::string("before,next,after"));
}

TEST(runner, "middleware that does not call next skips it") {
    std::string ctx;
    bool next_called = false;
    Middleware mw = [](std::string& c, std::function<void()>) {
        c = "short-circuited";
    };
    run_middleware(mw, ctx, [&next_called]() { next_called = true; });
    ASSERT_FALSE(next_called);
    ASSERT_EQ(ctx, std::string("short-circuited"));
}

TESTKIT_MAIN(runner)
