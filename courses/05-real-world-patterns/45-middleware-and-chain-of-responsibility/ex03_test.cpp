// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex03.h"

static testkit::TestRunner runner("05-45-ex03: Next Function");

TEST(runner, "empty middleware list calls handler directly") {
    std::string ctx;
    bool handler_called = false;
    chain_execute({}, ctx, [&handler_called]() { handler_called = true; });
    ASSERT_TRUE(handler_called);
}

TEST(runner, "single middleware runs then calls handler") {
    std::string ctx;
    std::string order;
    std::vector<Middleware03> mws = {
        [&order](std::string& c, std::function<void()> next) {
            order += "mw1,";
            next();
        }
    };
    chain_execute(mws, ctx, [&order]() { order += "handler"; });
    ASSERT_EQ(order, std::string("mw1,handler"));
}

TEST(runner, "middleware runs in order") {
    std::string ctx;
    std::string order;
    std::vector<Middleware03> mws = {
        [&order](std::string& c, std::function<void()> next) {
            order += "A,";
            next();
        },
        [&order](std::string& c, std::function<void()> next) {
            order += "B,";
            next();
        },
        [&order](std::string& c, std::function<void()> next) {
            order += "C,";
            next();
        }
    };
    chain_execute(mws, ctx, [&order]() { order += "handler"; });
    ASSERT_EQ(order, std::string("A,B,C,handler"));
}

TEST(runner, "middleware can modify context along the chain") {
    std::string ctx = "start";
    std::vector<Middleware03> mws = {
        [](std::string& c, std::function<void()> next) {
            c += "->A";
            next();
        },
        [](std::string& c, std::function<void()> next) {
            c += "->B";
            next();
        }
    };
    chain_execute(mws, ctx, []() {});
    ASSERT_EQ(ctx, std::string("start->A->B"));
}

TEST(runner, "after-next code runs in reverse order") {
    std::string order;
    std::string ctx;
    std::vector<Middleware03> mws = {
        [&order](std::string& c, std::function<void()> next) {
            order += "A-before,";
            next();
            order += "A-after,";
        },
        [&order](std::string& c, std::function<void()> next) {
            order += "B-before,";
            next();
            order += "B-after,";
        }
    };
    chain_execute(mws, ctx, [&order]() { order += "handler,"; });
    ASSERT_EQ(order, std::string("A-before,B-before,handler,B-after,A-after,"));
}

TESTKIT_MAIN(runner)
