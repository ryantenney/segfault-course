// Exercise 02 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex02.h"

static testkit::TestRunner runner("05-46-ex02: Dynamic Value Type");

TEST(runner, "default value is null") {
    Value v;
    v.is_null();  // gate: triggers TODO()
    ASSERT_TRUE(v.is_null());
    ASSERT_FALSE(v.is_string());
    ASSERT_FALSE(v.is_int());
    ASSERT_FALSE(v.is_double());
    ASSERT_FALSE(v.is_bool());
}

TEST(runner, "string value") {
    Value v(std::string("hello"));
    ASSERT_TRUE(v.is_string());
    ASSERT_FALSE(v.is_int());
    ASSERT_FALSE(v.is_null());
}

TEST(runner, "int value") {
    Value v(42);
    ASSERT_TRUE(v.is_int());
    ASSERT_FALSE(v.is_double());
    ASSERT_FALSE(v.is_string());
}

TEST(runner, "double value") {
    Value v(3.14);
    ASSERT_TRUE(v.is_double());
    ASSERT_FALSE(v.is_int());
}

TEST(runner, "bool value") {
    Value v(true);
    ASSERT_TRUE(v.is_bool());
    ASSERT_FALSE(v.is_int());
}

TEST(runner, "type_name returns correct names") {
    ASSERT_EQ(Value().type_name(), std::string("null"));
    ASSERT_EQ(Value(std::string("hi")).type_name(), std::string("string"));
    ASSERT_EQ(Value(1).type_name(), std::string("int"));
    ASSERT_EQ(Value(1.0).type_name(), std::string("double"));
    ASSERT_EQ(Value(false).type_name(), std::string("bool"));
}

TESTKIT_MAIN(runner)
