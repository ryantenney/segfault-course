// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("01-11-ex05: Moved-From State");

TEST(runner, "moved-from string is empty") {
    std::string s = "hello world";
    ASSERT_TRUE(move_and_check_empty(s));
}

TEST(runner, "moved-from string can be reassigned") {
    std::string s = "original";
    std::string result = move_and_reassign(s, "replacement");
    ASSERT_EQ(result, std::string("replacement"));
    ASSERT_EQ(s, std::string("replacement"));
}

TEST(runner, "drain_vector moves elements and clears source") {
    std::vector<std::string> v = {"a", "b", "c"};
    auto result = drain_vector(v);
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], std::string("a"));
    ASSERT_EQ(result[1], std::string("b"));
    ASSERT_EQ(result[2], std::string("c"));
    ASSERT_TRUE(v.empty());
}

TEST(runner, "size is safe to call on moved-from string") {
    std::string s = "test";
    std::size_t sz = move_and_get_size(s);
    // Moved-from string is typically empty, so size is 0
    ASSERT_EQ(sz, 0u);
}

TESTKIT_MAIN(runner)
