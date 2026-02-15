// Exercise 06 — Tests (read-only)

#include <testkit/testkit.h>
#include <stdexcept>
#include "ex06.h"

static testkit::TestRunner runner("05-45-ex06: Error-handling Middleware");

TEST(runner, "error handler passes through when no exception") {
    auto eh = make_error_handler();
    std::string ctx = "ok";
    eh(ctx, []() {});
    ASSERT_EQ(ctx, std::string("ok"));
}

TEST(runner, "error handler catches exception and sets error response") {
    auto eh = make_error_handler();
    std::string ctx;
    eh(ctx, []() { throw std::runtime_error("something broke"); });
    ASSERT_EQ(ctx, std::string("500: something broke"));
}

TEST(runner, "error handler in a chain catches downstream exceptions") {
    std::string ctx;
    std::vector<Middleware06> mws = {
        make_error_handler(),
        [](std::string& c, std::function<void()> next) {
            throw std::runtime_error("handler failed");
        }
    };
    execute_with_error_handling(mws, ctx, []() {});
    ASSERT_EQ(ctx, std::string("500: handler failed"));
}

TEST(runner, "error handler catches exception from final handler") {
    std::string ctx;
    std::vector<Middleware06> mws = {
        make_error_handler()
    };
    execute_with_error_handling(mws, ctx, []() {
        throw std::runtime_error("final handler error");
    });
    ASSERT_EQ(ctx, std::string("500: final handler error"));
}

TEST(runner, "without error handler, exception propagates") {
    std::string ctx;
    std::vector<Middleware06> mws = {
        [](std::string& c, std::function<void()> next) {
            next();
        }
    };
    bool caught = false;
    try {
        execute_with_error_handling(mws, ctx, []() {
            throw std::runtime_error("boom");
        });
    } catch (const testkit::not_implemented&) {
        throw;
    } catch (const std::runtime_error&) {
        caught = true;
    }
    ASSERT_TRUE(caught);
}

TESTKIT_MAIN(runner)
