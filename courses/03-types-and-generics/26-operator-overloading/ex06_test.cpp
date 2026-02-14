// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>
#include <sstream>

#include "ex06.h"

static testkit::TestRunner runner("03-26-ex06: Stream Extraction");

TEST(runner, "Dimensions parses WxH format") {
    std::istringstream iss("1920x1080");
    Dimensions dim{};
    iss >> dim;
    ASSERT_EQ(dim.width, 1920);
    ASSERT_EQ(dim.height, 1080);
}

TEST(runner, "Dimensions parses small values") {
    std::istringstream iss("4x3");
    Dimensions dim{};
    iss >> dim;
    ASSERT_EQ(dim.width, 4);
    ASSERT_EQ(dim.height, 3);
}

TEST(runner, "Dimensions supports chaining") {
    std::istringstream iss("800x600 1024x768");
    Dimensions a{}, b{};
    iss >> a >> b;
    ASSERT_EQ(a.width, 800);
    ASSERT_EQ(a.height, 600);
    ASSERT_EQ(b.width, 1024);
    ASSERT_EQ(b.height, 768);
}

TEST(runner, "DateParts parses YYYY-MM-DD format") {
    std::istringstream iss("2024-03-15");
    DateParts date{};
    iss >> date;
    ASSERT_EQ(date.year, 2024);
    ASSERT_EQ(date.month, 3);
    ASSERT_EQ(date.day, 15);
}

TEST(runner, "DateParts parses start of year") {
    std::istringstream iss("2000-01-01");
    DateParts date{};
    iss >> date;
    ASSERT_EQ(date.year, 2000);
    ASSERT_EQ(date.month, 1);
    ASSERT_EQ(date.day, 1);
}

TEST(runner, "DateParts parses end of year") {
    std::istringstream iss("1999-12-31");
    DateParts date{};
    iss >> date;
    ASSERT_EQ(date.year, 1999);
    ASSERT_EQ(date.month, 12);
    ASSERT_EQ(date.day, 31);
}

TEST(runner, "DateParts supports chaining") {
    std::istringstream iss("2024-01-01 2024-12-31");
    DateParts start{}, end{};
    iss >> start >> end;
    ASSERT_EQ(start.year, 2024);
    ASSERT_EQ(start.month, 1);
    ASSERT_EQ(end.year, 2024);
    ASSERT_EQ(end.month, 12);
}

TESTKIT_MAIN(runner)
