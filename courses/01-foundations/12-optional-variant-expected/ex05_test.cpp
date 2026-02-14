// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("01-12-ex05: std::visit");

TEST(runner, "setting_to_string converts int to string") {
    Setting s = 42;
    ASSERT_EQ(setting_to_string(s), std::string("42"));

    Setting neg = -7;
    ASSERT_EQ(setting_to_string(neg), std::string("-7"));
}

TEST(runner, "setting_to_string converts string to itself") {
    Setting s = std::string("hello");
    ASSERT_EQ(setting_to_string(s), std::string("hello"));
}

TEST(runner, "setting_to_string converts bool to true/false") {
    Setting t = true;
    ASSERT_EQ(setting_to_string(t), std::string("true"));

    Setting f = false;
    ASSERT_EQ(setting_to_string(f), std::string("false"));
}

TEST(runner, "double_setting doubles an int") {
    Setting s = 21;
    Setting result = double_setting(s);
    ASSERT_TRUE(std::holds_alternative<int>(result));
    ASSERT_EQ(std::get<int>(result), 42);
}

TEST(runner, "double_setting concatenates a string") {
    Setting s = std::string("ab");
    Setting result = double_setting(s);
    ASSERT_TRUE(std::holds_alternative<std::string>(result));
    ASSERT_EQ(std::get<std::string>(result), std::string("abab"));
}

TEST(runner, "double_setting negates a bool") {
    Setting s = true;
    Setting result = double_setting(s);
    ASSERT_TRUE(std::holds_alternative<bool>(result));
    ASSERT_EQ(std::get<bool>(result), false);

    Setting f = false;
    Setting result2 = double_setting(f);
    ASSERT_EQ(std::get<bool>(result2), true);
}

TESTKIT_MAIN(runner)
