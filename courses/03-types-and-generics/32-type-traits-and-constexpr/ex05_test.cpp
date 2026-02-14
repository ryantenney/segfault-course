// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("03-32-ex05: Type Manipulation");

TEST(runner, "type_name_of<int> returns int") {
    ASSERT_EQ(type_name_of<int>(), std::string("int"));
}

TEST(runner, "type_name_of<const int&> returns int (decays)") {
    ASSERT_EQ(type_name_of<const int&>(), std::string("int"));
}

TEST(runner, "type_name_of<double> returns double") {
    ASSERT_EQ(type_name_of<double>(), std::string("double"));
}

TEST(runner, "type_name_of<const double&&> returns double") {
    ASSERT_EQ(type_name_of<const double&&>(), std::string("double"));
}

TEST(runner, "type_name_of<std::string> returns string") {
    ASSERT_EQ(type_name_of<std::string>(), std::string("string"));
}

TEST(runner, "type_name_of<const std::string&> returns string") {
    ASSERT_EQ(type_name_of<const std::string&>(), std::string("string"));
}

TEST(runner, "type_name_of<char> returns other") {
    ASSERT_EQ(type_name_of<char>(), std::string("other"));
}

TEST(runner, "are_same_after_decay: int and const int& are same") {
    ASSERT_TRUE((are_same_after_decay<int, const int&>()));
}

TEST(runner, "are_same_after_decay: int and double are not same") {
    ASSERT_FALSE((are_same_after_decay<int, double>()));
}

TEST(runner, "store_value produces a decayed copy from lvalue ref") {
    const std::string s = "hello";
    auto result = store_value(s);
    ASSERT_EQ(result, std::string("hello"));
    // result is a std::string, not a reference
    ASSERT_TRUE((std::is_same_v<decltype(result), std::string>));
}

TEST(runner, "store_value produces a decayed copy from rvalue") {
    auto result = store_value(42);
    ASSERT_EQ(result, 42);
    ASSERT_TRUE((std::is_same_v<decltype(result), int>));
}

TESTKIT_MAIN(runner)
