// Exercise 03 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex03.h"

static testkit::TestRunner runner("05-46-ex03: Array and Object Values");

TEST(runner, "make_null creates a null node") {
    auto n = make_null();
    ASSERT_TRUE(std::holds_alternative<std::monostate>(n->data));
}

TEST(runner, "make_string creates a string node") {
    auto n = make_string("hello");
    ASSERT_TRUE(std::holds_alternative<std::string>(n->data));
    ASSERT_EQ(std::get<std::string>(n->data), std::string("hello"));
}

TEST(runner, "make_int creates an int node") {
    auto n = make_int(42);
    ASSERT_TRUE(std::holds_alternative<int>(n->data));
    ASSERT_EQ(std::get<int>(n->data), 42);
}

TEST(runner, "make_double creates a double node") {
    auto n = make_double(3.14);
    ASSERT_TRUE(std::holds_alternative<double>(n->data));
}

TEST(runner, "make_bool creates a bool node") {
    auto n = make_bool(true);
    ASSERT_TRUE(std::holds_alternative<bool>(n->data));
    ASSERT_EQ(std::get<bool>(n->data), true);
}

TEST(runner, "make_array creates an empty array") {
    auto n = make_array();
    ASSERT_TRUE(std::holds_alternative<Array>(n->data));
    ASSERT_EQ(std::get<Array>(n->data).size(), std::size_t(0));
}

TEST(runner, "array_push adds elements") {
    auto arr = make_array();
    array_push(arr, make_int(1));
    array_push(arr, make_int(2));
    auto& vec = std::get<Array>(arr->data);
    ASSERT_EQ(vec.size(), std::size_t(2));
    ASSERT_EQ(std::get<int>(vec[0]->data), 1);
    ASSERT_EQ(std::get<int>(vec[1]->data), 2);
}

TEST(runner, "make_object creates an empty object") {
    auto n = make_object();
    ASSERT_TRUE(std::holds_alternative<Object>(n->data));
    ASSERT_EQ(std::get<Object>(n->data).size(), std::size_t(0));
}

TEST(runner, "object_set adds key-value pairs") {
    auto obj = make_object();
    object_set(obj, "name", make_string("Alice"));
    object_set(obj, "age", make_int(30));
    auto& m = std::get<Object>(obj->data);
    ASSERT_EQ(m.size(), std::size_t(2));
    ASSERT_EQ(std::get<std::string>(m.at("name")->data), std::string("Alice"));
    ASSERT_EQ(std::get<int>(m.at("age")->data), 30);
}

TEST(runner, "nested structures work") {
    auto root = make_object();
    auto items = make_array();
    array_push(items, make_string("a"));
    array_push(items, make_string("b"));
    object_set(root, "items", items);

    auto& obj = std::get<Object>(root->data);
    auto& arr = std::get<Array>(obj.at("items")->data);
    ASSERT_EQ(arr.size(), std::size_t(2));
    ASSERT_EQ(std::get<std::string>(arr[0]->data), std::string("a"));
}

TESTKIT_MAIN(runner)
