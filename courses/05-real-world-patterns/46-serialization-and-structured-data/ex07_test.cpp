// Exercise 07 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex07.h"

static testkit::TestRunner runner("05-46-ex07: Pretty Print");

TEST(runner, "pretty print null") {
    ASSERT_EQ(pretty_print(pp_null(), 2), std::string("null"));
}

TEST(runner, "pretty print string") {
    ASSERT_EQ(pretty_print(pp_string("hello"), 2), std::string("\"hello\""));
}

TEST(runner, "pretty print int") {
    ASSERT_EQ(pretty_print(pp_int(42), 2), std::string("42"));
}

TEST(runner, "pretty print bool") {
    ASSERT_EQ(pretty_print(pp_bool(true), 2), std::string("true"));
}

TEST(runner, "pretty print empty array") {
    ASSERT_EQ(pretty_print(pp_array({}), 2), std::string("[]"));
}

TEST(runner, "pretty print array with elements") {
    Array07 arr = {pp_int(1), pp_int(2), pp_int(3)};
    std::string expected = "[\n  1,\n  2,\n  3\n]";
    ASSERT_EQ(pretty_print(pp_array(std::move(arr)), 2), expected);
}

TEST(runner, "pretty print empty object") {
    ASSERT_EQ(pretty_print(pp_object({}), 2), std::string("{}"));
}

TEST(runner, "pretty print object with entries") {
    Object07 obj = {{"age", pp_int(30)}, {"name", pp_string("Alice")}};
    // map is sorted: "age" before "name"
    std::string expected = "{\n  \"age\": 30,\n  \"name\": \"Alice\"\n}";
    ASSERT_EQ(pretty_print(pp_object(std::move(obj)), 2), expected);
}

TEST(runner, "pretty print nested structure") {
    Object07 obj = {
        {"items", pp_array({pp_int(1), pp_int(2)})}
    };
    std::string expected =
        "{\n"
        "  \"items\": [\n"
        "    1,\n"
        "    2\n"
        "  ]\n"
        "}";
    ASSERT_EQ(pretty_print(pp_object(std::move(obj)), 2), expected);
}

TEST(runner, "pretty print with indent width 4") {
    Array07 arr = {pp_int(1), pp_int(2)};
    std::string expected = "[\n    1,\n    2\n]";
    ASSERT_EQ(pretty_print(pp_array(std::move(arr)), 4), expected);
}

TESTKIT_MAIN(runner)
