// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex05.h"

static testkit::TestRunner runner("05-46-ex05: Serialize to String");

TEST(runner, "stringify null") {
    ASSERT_EQ(stringify(sn_null()), std::string("null"));
}

TEST(runner, "stringify string") {
    ASSERT_EQ(stringify(sn_string("hello")), std::string("\"hello\""));
}

TEST(runner, "stringify int") {
    ASSERT_EQ(stringify(sn_int(42)), std::string("42"));
}

TEST(runner, "stringify bool") {
    ASSERT_EQ(stringify(sn_bool(true)), std::string("true"));
    ASSERT_EQ(stringify(sn_bool(false)), std::string("false"));
}

TEST(runner, "stringify empty array") {
    ASSERT_EQ(stringify(sn_array({})), std::string("[]"));
}

TEST(runner, "stringify array with elements") {
    Array05 arr = {sn_int(1), sn_string("two"), sn_bool(true)};
    ASSERT_EQ(stringify(sn_array(std::move(arr))), std::string("[1, \"two\", true]"));
}

TEST(runner, "stringify empty object") {
    ASSERT_EQ(stringify(sn_object({})), std::string("{}"));
}

TEST(runner, "stringify object with entries") {
    Object05 obj = {{"age", sn_int(30)}, {"name", sn_string("Alice")}};
    // map is sorted by key, so "age" comes before "name"
    ASSERT_EQ(stringify(sn_object(std::move(obj))),
              std::string("{\"age\": 30, \"name\": \"Alice\"}"));
}

TEST(runner, "stringify nested structure") {
    Object05 obj = {
        {"items", sn_array({sn_int(1), sn_int(2)})}
    };
    ASSERT_EQ(stringify(sn_object(std::move(obj))),
              std::string("{\"items\": [1, 2]}"));
}

TESTKIT_MAIN(runner)
