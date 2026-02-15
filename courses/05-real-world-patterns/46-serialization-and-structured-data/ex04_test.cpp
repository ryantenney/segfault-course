// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex04.h"

static testkit::TestRunner runner("05-46-ex04: Type-safe Accessors");

TEST(runner, "as_string returns value for string node") {
    auto n = mk_string("hello");
    auto v = as_string(n);
    ASSERT_TRUE(v.has_value());
    ASSERT_EQ(v.value(), std::string("hello"));
}

TEST(runner, "as_string returns nullopt for non-string node") {
    auto n = mk_int(42);
    auto s = as_string(n);
    // gate: call as_string on a string first to trigger TODO()
    as_string(mk_string("gate"));
    ASSERT_FALSE(s.has_value());
}

TEST(runner, "as_int returns value for int node") {
    auto n = mk_int(99);
    auto v = as_int(n);
    ASSERT_TRUE(v.has_value());
    ASSERT_EQ(v.value(), 99);
}

TEST(runner, "as_int returns nullopt for string node") {
    auto n = mk_string("not an int");
    auto v = as_int(n);
    ASSERT_FALSE(v.has_value());
}

TEST(runner, "as_double returns value for double node") {
    auto n = mk_double(2.718);
    auto v = as_double(n);
    ASSERT_TRUE(v.has_value());
}

TEST(runner, "as_bool returns value for bool node") {
    auto n = mk_bool(true);
    auto v = as_bool(n);
    ASSERT_TRUE(v.has_value());
    ASSERT_EQ(v.value(), true);
}

TEST(runner, "as_bool returns nullopt for null node") {
    auto n = mk_null();
    auto v = as_bool(n);
    ASSERT_FALSE(v.has_value());
}

TEST(runner, "as_array returns array for array node") {
    Array04 items = {mk_int(1), mk_int(2)};
    auto n = mk_array(items);
    auto v = as_array(n);
    ASSERT_TRUE(v.has_value());
    ASSERT_EQ(v.value().size(), std::size_t(2));
}

TEST(runner, "as_object returns object for object node") {
    Object04 fields = {{"key", mk_string("val")}};
    auto n = mk_object(fields);
    auto v = as_object(n);
    ASSERT_TRUE(v.has_value());
    ASSERT_EQ(v.value().size(), std::size_t(1));
}

TESTKIT_MAIN(runner)
