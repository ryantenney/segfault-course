// Exercise 05 -- Tests (read-only)
//
// Verifies partial specialization of Serializer for pointer types.

#include <testkit/testkit.h>
#include <string>
#include "ex05.h"

static testkit::TestRunner runner("03-30-ex05: Partial Specialization");

TEST(runner, "primary template serializes int") {
    ASSERT_EQ(Serializer<int>::serialize(42), std::string("value:42"));
}

TEST(runner, "primary template serializes double") {
    std::string result = Serializer<double>::serialize(3.14);
    // std::to_string(3.14) may produce "3.140000" -- just check the prefix
    ASSERT_TRUE(result.substr(0, 6) == "value:");
    ASSERT_TRUE(result.find("3.14") != std::string::npos);
}

TEST(runner, "pointer specialization serializes non-null int*") {
    // Gate: primary template must work first
    Serializer<int>::serialize(1);

    int x = 99;
    ASSERT_EQ(Serializer<int*>::serialize(&x), std::string("ptr:99"));
}

TEST(runner, "pointer specialization returns null for nullptr") {
    // Gate: primary template must work first
    Serializer<int>::serialize(1);

    ASSERT_EQ(Serializer<int*>::serialize(nullptr), std::string("null"));
}

TEST(runner, "pointer specialization works with double*") {
    // Gate: primary template must work first
    Serializer<int>::serialize(1);

    double d = 2.5;
    std::string result = Serializer<double*>::serialize(&d);
    ASSERT_TRUE(result.substr(0, 4) == "ptr:");
    ASSERT_TRUE(result.find("2.5") != std::string::npos);
}

TEST(runner, "pointer specialization with null double*") {
    // Gate: primary template must work first
    Serializer<int>::serialize(1);

    double* p = nullptr;
    ASSERT_EQ(Serializer<double*>::serialize(p), std::string("null"));
}

TESTKIT_MAIN(runner)
