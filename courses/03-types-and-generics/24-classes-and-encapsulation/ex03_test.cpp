// Exercise 03 — Tests (read-only)
//
// Verifies const getter methods on the Color class.

#include <testkit/testkit.h>
#include <cmath>
#include "ex03.h"

static testkit::TestRunner runner("03-24-ex03: Getter Methods");

TEST(runner, "red getter returns red component") {
    Color c(100, 150, 200);
    ASSERT_EQ(c.red(), 100);
}

TEST(runner, "green getter returns green component") {
    Color c(100, 150, 200);
    ASSERT_EQ(c.green(), 150);
}

TEST(runner, "blue getter returns blue component") {
    Color c(100, 150, 200);
    ASSERT_EQ(c.blue(), 200);
}

TEST(runner, "getters work on const Color") {
    const Color c(10, 20, 30);
    ASSERT_EQ(c.red(), 10);
    ASSERT_EQ(c.green(), 20);
    ASSERT_EQ(c.blue(), 30);
}

TEST(runner, "luminance computes weighted brightness") {
    Color c(255, 255, 255);
    // 0.2126*255 + 0.7152*255 + 0.0722*255 = 255.0
    ASSERT_TRUE(std::abs(c.luminance() - 255.0) < 0.01);
}

TEST(runner, "luminance for black is zero") {
    Color c(0, 0, 0);
    ASSERT_TRUE(std::abs(c.luminance()) < 0.01);
}

TEST(runner, "luminance for pure red") {
    Color c(255, 0, 0);
    // 0.2126 * 255 = 54.213
    ASSERT_TRUE(std::abs(c.luminance() - 54.213) < 0.01);
}

TEST(runner, "is_grayscale true for equal components") {
    Color c(128, 128, 128);
    ASSERT_TRUE(c.is_grayscale());
}

TEST(runner, "is_grayscale false for different components") {
    Color c(128, 128, 129);
    ASSERT_FALSE(c.is_grayscale());
}

TEST(runner, "is_bright for white") {
    Color white(255, 255, 255);
    ASSERT_TRUE(is_bright(white));
}

TEST(runner, "is_bright for black") {
    Color black(0, 0, 0);
    ASSERT_FALSE(is_bright(black));
}

TESTKIT_MAIN(runner)
