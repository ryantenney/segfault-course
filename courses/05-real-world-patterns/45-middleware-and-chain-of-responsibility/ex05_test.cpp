// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex05.h"

static testkit::TestRunner runner("05-45-ex05: Middleware Composition");

TEST(runner, "empty pipeline calls handler directly") {
    Pipeline p;
    std::string ctx;
    bool called = false;
    p.execute(ctx, [&called]() { called = true; });
    ASSERT_TRUE(called);
}

TEST(runner, "pipeline with one middleware runs it then handler") {
    Pipeline p;
    std::string order;
    p.use([&order](std::string& c, std::function<void()> next) {
        order += "mw,";
        next();
    });
    std::string ctx;
    p.execute(ctx, [&order]() { order += "handler"; });
    ASSERT_EQ(order, std::string("mw,handler"));
}

TEST(runner, "pipeline runs middleware in insertion order") {
    Pipeline p;
    std::string order;
    p.use([&order](std::string& c, std::function<void()> next) {
        order += "1,";
        next();
    });
    p.use([&order](std::string& c, std::function<void()> next) {
        order += "2,";
        next();
    });
    p.use([&order](std::string& c, std::function<void()> next) {
        order += "3,";
        next();
    });
    std::string ctx;
    p.execute(ctx, [&order]() { order += "handler"; });
    ASSERT_EQ(order, std::string("1,2,3,handler"));
}

TEST(runner, "pipeline middleware can modify context") {
    Pipeline p;
    p.use([](std::string& c, std::function<void()> next) {
        c += "[logged]";
        next();
    });
    p.use([](std::string& c, std::function<void()> next) {
        c += "[compressed]";
        next();
    });
    std::string ctx = "data";
    p.execute(ctx, []() {});
    ASSERT_EQ(ctx, std::string("data[logged][compressed]"));
}

TEST(runner, "pipeline can be executed multiple times") {
    Pipeline p;
    int call_count = 0;
    p.use([&call_count](std::string& c, std::function<void()> next) {
        ++call_count;
        next();
    });
    std::string ctx1, ctx2;
    p.execute(ctx1, []() {});
    p.execute(ctx2, []() {});
    ASSERT_EQ(call_count, 2);
}

TESTKIT_MAIN(runner)
