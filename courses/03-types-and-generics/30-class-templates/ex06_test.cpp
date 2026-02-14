// Exercise 06 -- Tests (read-only)
//
// Verifies full specialization of Serializer<std::string>.

#include <testkit/testkit.h>
#include <string>
#include "ex06.h"

static testkit::TestRunner runner("03-30-ex06: Full Specialization");

TEST(runner, "primary template serializes int") {
    ASSERT_EQ(Serializer<int>::serialize(42), std::string("value:42"));
}

TEST(runner, "primary template describe returns generic") {
    ASSERT_EQ(Serializer<int>::describe(), std::string("generic"));
}

TEST(runner, "string specialization serializes short string") {
    // Gate: primary template must work first
    Serializer<int>::serialize(1);

    ASSERT_EQ(Serializer<std::string>::serialize("hello"),
              std::string("str:hello"));
}

TEST(runner, "string specialization truncates long string") {
    // Gate: primary template must work first
    Serializer<int>::serialize(1);

    ASSERT_EQ(Serializer<std::string>::serialize("abcdefghijklmnop"),
              std::string("str:abcdefghij"));
}

TEST(runner, "string specialization describe returns string") {
    // Gate: primary template must work first
    Serializer<int>::serialize(1);

    ASSERT_EQ(Serializer<std::string>::describe(), std::string("string"));
}

TEST(runner, "primary and specialization are distinct") {
    // Gate: primary template must work first
    Serializer<int>::serialize(1);

    ASSERT_NE(Serializer<int>::describe(), Serializer<std::string>::describe());
}

TEST(runner, "string specialization handles empty string") {
    // Gate: primary template must work first
    Serializer<int>::serialize(1);

    ASSERT_EQ(Serializer<std::string>::serialize(""), std::string("str:"));
}

TEST(runner, "string specialization handles exactly 10 chars") {
    // Gate: primary template must work first
    Serializer<int>::serialize(1);

    ASSERT_EQ(Serializer<std::string>::serialize("1234567890"),
              std::string("str:1234567890"));
}

TESTKIT_MAIN(runner)
