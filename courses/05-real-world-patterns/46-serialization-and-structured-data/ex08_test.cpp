// Exercise 08 — Tests (read-only)

#include <testkit/testkit.h>
#include <string>
#include <vector>
#include "ex08.h"

static testkit::TestRunner runner("05-46-ex08: Visitor Pattern");

TEST(runner, "visitor sees null") {
    bool saw_null = false;
    Visitor v;
    v.on_null = [&saw_null]() { saw_null = true; };
    visit_value(vn_null(), v);
    ASSERT_TRUE(saw_null);
}

TEST(runner, "visitor sees string") {
    std::string seen;
    Visitor v;
    v.on_string = [&seen](const std::string& s) { seen = s; };
    visit_value(vn_string("hello"), v);
    ASSERT_EQ(seen, std::string("hello"));
}

TEST(runner, "visitor sees int") {
    int seen = 0;
    Visitor v;
    v.on_int = [&seen](int i) { seen = i; };
    visit_value(vn_int(42), v);
    ASSERT_EQ(seen, 42);
}

TEST(runner, "visitor sees bool") {
    bool seen = false;
    Visitor v;
    v.on_bool = [&seen](bool b) { seen = b; };
    visit_value(vn_bool(true), v);
    ASSERT_TRUE(seen);
}

TEST(runner, "visitor traverses array elements") {
    std::vector<int> ints;
    Visitor v;
    v.on_int = [&ints](int i) { ints.push_back(i); };
    bool arr_start = false, arr_end = false;
    v.on_array_start = [&arr_start]() { arr_start = true; };
    v.on_array_end = [&arr_end]() { arr_end = true; };
    visit_value(vn_array({vn_int(1), vn_int(2), vn_int(3)}), v);
    ASSERT_TRUE(arr_start);
    ASSERT_TRUE(arr_end);
    ASSERT_EQ(ints.size(), std::size_t(3));
    ASSERT_EQ(ints[0], 1);
    ASSERT_EQ(ints[2], 3);
}

TEST(runner, "visitor traverses object keys and values") {
    std::vector<std::string> keys;
    std::vector<std::string> values;
    Visitor v;
    v.on_object_key = [&keys](const std::string& k) { keys.push_back(k); };
    v.on_string = [&values](const std::string& s) { values.push_back(s); };
    bool obj_start = false, obj_end = false;
    v.on_object_start = [&obj_start]() { obj_start = true; };
    v.on_object_end = [&obj_end]() { obj_end = true; };

    Object08 obj = {{"a", vn_string("x")}, {"b", vn_string("y")}};
    visit_value(vn_object(std::move(obj)), v);
    ASSERT_TRUE(obj_start);
    ASSERT_TRUE(obj_end);
    ASSERT_EQ(keys.size(), std::size_t(2));
    ASSERT_EQ(keys[0], std::string("a"));
    ASSERT_EQ(keys[1], std::string("b"));
    ASSERT_EQ(values.size(), std::size_t(2));
}

TEST(runner, "visitor traverses nested structure") {
    std::vector<std::string> events;
    Visitor v;
    v.on_object_start = [&events]() { events.push_back("obj_start"); };
    v.on_object_end = [&events]() { events.push_back("obj_end"); };
    v.on_object_key = [&events](const std::string& k) { events.push_back("key:" + k); };
    v.on_array_start = [&events]() { events.push_back("arr_start"); };
    v.on_array_end = [&events]() { events.push_back("arr_end"); };
    v.on_int = [&events](int i) { events.push_back("int:" + std::to_string(i)); };

    Object08 obj = {
        {"nums", vn_array({vn_int(1), vn_int(2)})}
    };
    visit_value(vn_object(std::move(obj)), v);

    // Expected order: obj_start, key:nums, arr_start, int:1, int:2, arr_end, obj_end
    ASSERT_EQ(events.size(), std::size_t(7));
    ASSERT_EQ(events[0], std::string("obj_start"));
    ASSERT_EQ(events[1], std::string("key:nums"));
    ASSERT_EQ(events[2], std::string("arr_start"));
    ASSERT_EQ(events[3], std::string("int:1"));
    ASSERT_EQ(events[4], std::string("int:2"));
    ASSERT_EQ(events[5], std::string("arr_end"));
    ASSERT_EQ(events[6], std::string("obj_end"));
}

TESTKIT_MAIN(runner)
