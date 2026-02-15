// Exercise 06 — Tests (read-only)

#include <testkit/testkit.h>
#include <stdexcept>
#include "ex06.h"

static testkit::TestRunner runner("05-46-ex06: Parse from String");

TEST(runner, "parse null") {
    auto n = parse("null");
    ASSERT_TRUE(std::holds_alternative<std::monostate>(n->data));
}

TEST(runner, "parse true") {
    auto n = parse("true");
    ASSERT_TRUE(std::holds_alternative<bool>(n->data));
    ASSERT_EQ(std::get<bool>(n->data), true);
}

TEST(runner, "parse false") {
    auto n = parse("false");
    ASSERT_TRUE(std::holds_alternative<bool>(n->data));
    ASSERT_EQ(std::get<bool>(n->data), false);
}

TEST(runner, "parse integer") {
    auto n = parse("42");
    ASSERT_TRUE(std::holds_alternative<int>(n->data));
    ASSERT_EQ(std::get<int>(n->data), 42);
}

TEST(runner, "parse negative integer") {
    auto n = parse("-7");
    ASSERT_TRUE(std::holds_alternative<int>(n->data));
    ASSERT_EQ(std::get<int>(n->data), -7);
}

TEST(runner, "parse double") {
    auto n = parse("3.14");
    ASSERT_TRUE(std::holds_alternative<double>(n->data));
}

TEST(runner, "parse string") {
    auto n = parse("\"hello world\"");
    ASSERT_TRUE(std::holds_alternative<std::string>(n->data));
    ASSERT_EQ(std::get<std::string>(n->data), std::string("hello world"));
}

TEST(runner, "parse empty array") {
    auto n = parse("[]");
    ASSERT_TRUE(std::holds_alternative<Array06>(n->data));
    ASSERT_EQ(std::get<Array06>(n->data).size(), std::size_t(0));
}

TEST(runner, "parse array with elements") {
    auto n = parse("[1, 2, 3]");
    ASSERT_TRUE(std::holds_alternative<Array06>(n->data));
    auto& arr = std::get<Array06>(n->data);
    ASSERT_EQ(arr.size(), std::size_t(3));
    ASSERT_EQ(std::get<int>(arr[0]->data), 1);
    ASSERT_EQ(std::get<int>(arr[2]->data), 3);
}

TEST(runner, "parse empty object") {
    auto n = parse("{}");
    ASSERT_TRUE(std::holds_alternative<Object06>(n->data));
    ASSERT_EQ(std::get<Object06>(n->data).size(), std::size_t(0));
}

TEST(runner, "parse object with entries") {
    auto n = parse("{\"name\": \"Alice\", \"age\": 30}");
    ASSERT_TRUE(std::holds_alternative<Object06>(n->data));
    auto& obj = std::get<Object06>(n->data);
    ASSERT_EQ(obj.size(), std::size_t(2));
    ASSERT_EQ(std::get<std::string>(obj.at("name")->data), std::string("Alice"));
    ASSERT_EQ(std::get<int>(obj.at("age")->data), 30);
}

TEST(runner, "parse with whitespace") {
    auto n = parse("  { \"a\" : 1 }  ");
    ASSERT_TRUE(std::holds_alternative<Object06>(n->data));
}

TESTKIT_MAIN(runner)
