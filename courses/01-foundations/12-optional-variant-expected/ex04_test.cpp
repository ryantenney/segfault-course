// Exercise 04 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex04.h"

static testkit::TestRunner runner("01-12-ex04: Variant Basics");

TEST(runner, "make_int_setting creates a variant holding an int") {
    Setting s = make_int_setting(42);
    ASSERT_TRUE(std::holds_alternative<int>(s));
    ASSERT_EQ(std::get<int>(s), 42);
}

TEST(runner, "make_string_setting creates a variant holding a string") {
    Setting s = make_string_setting("hello");
    ASSERT_TRUE(std::holds_alternative<std::string>(s));
    ASSERT_EQ(std::get<std::string>(s), std::string("hello"));
}

TEST(runner, "make_bool_setting creates a variant holding a bool") {
    Setting s = make_bool_setting(true);
    ASSERT_TRUE(std::holds_alternative<bool>(s));
    ASSERT_EQ(std::get<bool>(s), true);
}

TEST(runner, "setting_type_name returns the correct type name") {
    ASSERT_EQ(setting_type_name(make_int_setting(1)), std::string("int"));
    ASSERT_EQ(setting_type_name(make_string_setting("x")), std::string("string"));
    ASSERT_EQ(setting_type_name(make_bool_setting(false)), std::string("bool"));
}

TEST(runner, "get_int_or returns the int when present") {
    Setting s = make_int_setting(99);
    ASSERT_EQ(get_int_or(s, 0), 99);
}

TEST(runner, "get_int_or returns the default when not an int") {
    Setting s = make_string_setting("not an int");
    ASSERT_EQ(get_int_or(s, -1), -1);

    Setting b = make_bool_setting(true);
    ASSERT_EQ(get_int_or(b, 42), 42);
}

TEST(runner, "std::get throws on wrong type access") {
    Setting s = make_string_setting("oops");
    ASSERT_THROWS(std::get<int>(s), std::bad_variant_access);
}

TESTKIT_MAIN(runner)
