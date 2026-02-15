// Exercise 07 -- Tests (read-only)
//
// Verifies context/scope-based log prefixing.

#include <testkit/testkit.h>
#include <string>
#include "ex07.h"

static testkit::TestRunner runner("05-50-ex07: Log Context/Scope");

TEST(runner, "log without context is plain message") {
    ContextLogger logger;
    logger.log("hello");
    ASSERT_EQ(logger.messages()[0], std::string("hello"));
}

TEST(runner, "push adds context prefix") {
    ContextLogger logger;
    logger.push("request_id=abc");
    logger.log("started");
    ASSERT_EQ(logger.messages()[0], std::string("[request_id=abc] started"));
}

TEST(runner, "nested contexts stack") {
    ContextLogger logger;
    logger.push("req=1");
    logger.push("user=alice");
    logger.log("action");
    ASSERT_EQ(logger.messages()[0], std::string("[req=1] [user=alice] action"));
}

TEST(runner, "pop removes most recent context") {
    ContextLogger logger;
    logger.push("req=1");
    logger.push("user=alice");
    logger.pop();
    logger.log("after pop");
    ASSERT_EQ(logger.messages()[0], std::string("[req=1] after pop"));
}

TEST(runner, "LogScope pushes on construction and pops on destruction") {
    ContextLogger logger;
    logger.log("before");
    {
        LogScope scope(logger, "scoped=yes");
        logger.log("inside");
    }
    logger.log("after");
    ASSERT_EQ(logger.messages()[0], std::string("before"));
    ASSERT_EQ(logger.messages()[1], std::string("[scoped=yes] inside"));
    ASSERT_EQ(logger.messages()[2], std::string("after"));
}

TEST(runner, "nested LogScopes") {
    ContextLogger logger;
    {
        LogScope outer(logger, "outer");
        {
            LogScope inner(logger, "inner");
            logger.log("deep");
        }
        logger.log("shallow");
    }
    logger.log("none");
    ASSERT_EQ(logger.messages()[0], std::string("[outer] [inner] deep"));
    ASSERT_EQ(logger.messages()[1], std::string("[outer] shallow"));
    ASSERT_EQ(logger.messages()[2], std::string("none"));
}

TESTKIT_MAIN(runner)
