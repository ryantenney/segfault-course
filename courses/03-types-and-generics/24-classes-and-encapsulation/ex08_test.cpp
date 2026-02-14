// Exercise 08 — Tests (read-only)
//
// Verifies the friend operator<< for the Rect class.

#include <testkit/testkit.h>
#include <sstream>
#include <string>
#include "ex08.h"

static testkit::TestRunner runner("03-24-ex08: Friend Function");

TEST(runner, "width getter") {
    Rect r(10.0, 5.0);
    ASSERT_TRUE(r.width() == 10.0);
}

TEST(runner, "height getter") {
    Rect r(10.0, 5.0);
    ASSERT_TRUE(r.height() == 5.0);
}

TEST(runner, "area is width times height") {
    Rect r(10.0, 5.0);
    ASSERT_TRUE(r.area() == 50.0);
}

TEST(runner, "perimeter is 2*(w+h)") {
    Rect r(10.0, 5.0);
    ASSERT_TRUE(r.perimeter() == 30.0);
}

TEST(runner, "area of unit square") {
    Rect r(1.0, 1.0);
    ASSERT_TRUE(r.area() == 1.0);
}

TEST(runner, "operator<< outputs correct format") {
    Rect r(10, 5);
    std::ostringstream oss;
    oss << r;
    ASSERT_EQ(oss.str(), std::string("Rect(10 x 5)"));
}

TEST(runner, "operator<< with decimal values") {
    Rect r(3.5, 2.5);
    std::ostringstream oss;
    oss << r;
    ASSERT_EQ(oss.str(), std::string("Rect(3.5 x 2.5)"));
}

TEST(runner, "operator<< with zero dimensions") {
    Rect r(0, 0);
    std::ostringstream oss;
    oss << r;
    ASSERT_EQ(oss.str(), std::string("Rect(0 x 0)"));
}

TEST(runner, "operator<< can be chained") {
    Rect r1(1, 2);
    Rect r2(3, 4);
    std::ostringstream oss;
    oss << r1 << " and " << r2;
    ASSERT_EQ(oss.str(), std::string("Rect(1 x 2) and Rect(3 x 4)"));
}

TESTKIT_MAIN(runner)
