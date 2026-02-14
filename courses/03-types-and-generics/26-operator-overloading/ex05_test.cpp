// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>
#include <sstream>
#include <string>

#include "ex05.h"

static testkit::TestRunner runner("03-26-ex05: Stream Insertion");

TEST(runner, "Timestamp formats with leading zeros") {
    Timestamp ts{9, 5, 2};
    std::ostringstream oss;
    oss << ts;
    ASSERT_EQ(oss.str(), std::string("09:05:02"));
}

TEST(runner, "Timestamp formats midnight correctly") {
    Timestamp ts{0, 0, 0};
    std::ostringstream oss;
    oss << ts;
    ASSERT_EQ(oss.str(), std::string("00:00:00"));
}

TEST(runner, "Timestamp formats double-digit values") {
    Timestamp ts{14, 30, 59};
    std::ostringstream oss;
    oss << ts;
    ASSERT_EQ(oss.str(), std::string("14:30:59"));
}

TEST(runner, "Timestamp supports chaining") {
    Timestamp a{10, 0, 0};
    Timestamp b{12, 30, 0};
    std::ostringstream oss;
    oss << a << " - " << b;
    ASSERT_EQ(oss.str(), std::string("10:00:00 - 12:30:00"));
}

TEST(runner, "Coordinate formats with parentheses") {
    Coordinate c{40.7128, -74.006};
    std::ostringstream oss;
    oss << c;
    std::string result = oss.str();
    // Check the format: starts with '(' and ends with ')'
    ASSERT_TRUE(result.front() == '(');
    ASSERT_TRUE(result.back() == ')');
    // Should contain both numbers separated by ", "
    ASSERT_TRUE(result.find("40.7128") != std::string::npos);
    ASSERT_TRUE(result.find("-74.006") != std::string::npos);
}

TEST(runner, "Coordinate at origin") {
    Coordinate c{0, 0};
    std::ostringstream oss;
    oss << c;
    ASSERT_EQ(oss.str(), std::string("(0, 0)"));
}

TEST(runner, "Coordinate supports chaining") {
    Coordinate a{1.0, 2.0};
    Coordinate b{3.0, 4.0};
    std::ostringstream oss;
    oss << a << " -> " << b;
    std::string result = oss.str();
    ASSERT_TRUE(result.find("(1, 2)") != std::string::npos);
    ASSERT_TRUE(result.find(" -> ") != std::string::npos);
    ASSERT_TRUE(result.find("(3, 4)") != std::string::npos);
}

TESTKIT_MAIN(runner)
