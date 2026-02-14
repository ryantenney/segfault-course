// Exercise 05 — Tests (read-only)
//
// Verifies the Fraction class invariant: always normalized with
// positive denominator.

#include <testkit/testkit.h>
#include <stdexcept>
#include "ex05.h"

static testkit::TestRunner runner("03-24-ex05: Invariant Enforcement");

TEST(runner, "basic fraction construction") {
    Fraction f(3, 4);
    ASSERT_EQ(f.numerator(), 3);
    ASSERT_EQ(f.denominator(), 4);
}

TEST(runner, "fraction is auto-reduced") {
    Fraction f(6, 8);
    ASSERT_EQ(f.numerator(), 3);
    ASSERT_EQ(f.denominator(), 4);
}

TEST(runner, "negative denominator is flipped") {
    Fraction f(3, -4);
    ASSERT_EQ(f.numerator(), -3);
    ASSERT_EQ(f.denominator(), 4);
}

TEST(runner, "both negative simplifies to positive") {
    Fraction f(-6, -8);
    ASSERT_EQ(f.numerator(), 3);
    ASSERT_EQ(f.denominator(), 4);
}

TEST(runner, "zero numerator") {
    Fraction f(0, 5);
    ASSERT_EQ(f.numerator(), 0);
    ASSERT_EQ(f.denominator(), 1);
}

TEST(runner, "zero denominator throws") {
    ASSERT_THROWS(Fraction(1, 0), std::invalid_argument);
}

TEST(runner, "add two fractions") {
    Fraction a(1, 4);
    Fraction b(1, 4);
    Fraction result = a.add(b);
    ASSERT_EQ(result.numerator(), 1);
    ASSERT_EQ(result.denominator(), 2);
}

TEST(runner, "add different denominators") {
    Fraction a(1, 3);
    Fraction b(1, 6);
    Fraction result = a.add(b);
    ASSERT_EQ(result.numerator(), 1);
    ASSERT_EQ(result.denominator(), 2);
}

TEST(runner, "multiply two fractions") {
    Fraction a(2, 3);
    Fraction b(3, 4);
    Fraction result = a.multiply(b);
    ASSERT_EQ(result.numerator(), 1);
    ASSERT_EQ(result.denominator(), 2);
}

TEST(runner, "multiply by zero") {
    Fraction a(5, 7);
    Fraction b(0, 1);
    Fraction result = a.multiply(b);
    ASSERT_EQ(result.numerator(), 0);
    ASSERT_EQ(result.denominator(), 1);
}

TEST(runner, "equals for equivalent fractions") {
    Fraction a(1, 2);
    Fraction b(3, 6);
    ASSERT_TRUE(a.equals(b));
}

TEST(runner, "equals for non-equal fractions") {
    Fraction a(1, 2);
    Fraction b(1, 3);
    ASSERT_FALSE(a.equals(b));
}

TESTKIT_MAIN(runner)
