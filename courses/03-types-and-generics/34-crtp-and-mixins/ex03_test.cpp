// Exercise 03 -- Tests (read-only)
//
// Verifies CRTP-based operator generation.

#include <testkit/testkit.h>
#include "ex03.h"

static testkit::TestRunner runner("03-34-ex03: CRTP Operator Generation");

// --- Token tests ---

TEST(runner, "Token: equal tokens compare equal") {
    Token a("keyword", "if");
    Token b("keyword", "if");
    ASSERT_TRUE(a == b);
}

TEST(runner, "Token: different type means not equal") {
    Token a("keyword", "if");
    Token b("identifier", "if");
    ASSERT_FALSE(a == b);
}

TEST(runner, "Token: different value means not equal") {
    Token a("keyword", "if");
    Token b("keyword", "else");
    ASSERT_FALSE(a == b);
}

TEST(runner, "Token: operator!= generated from CRTP base") {
    Token a("keyword", "if");
    Token b("keyword", "else");
    ASSERT_TRUE(a != b);
    ASSERT_FALSE(a != a);
}

// --- Coordinate tests ---

TEST(runner, "Coordinate: equal coordinates compare equal") {
    Coordinate a(1, 2, 3);
    Coordinate b(1, 2, 3);
    ASSERT_TRUE(a == b);
}

TEST(runner, "Coordinate: different coordinates are not equal") {
    Coordinate a(1, 2, 3);
    Coordinate b(1, 2, 4);
    ASSERT_FALSE(a == b);
}

TEST(runner, "Coordinate: operator!= from CRTP base") {
    Coordinate a(1, 2, 3);
    Coordinate b(4, 5, 6);
    ASSERT_TRUE(a != b);
}

TEST(runner, "Coordinate: operator< uses lexicographic ordering") {
    ASSERT_TRUE(Coordinate(1, 2, 3) < Coordinate(2, 0, 0));
    ASSERT_TRUE(Coordinate(1, 2, 3) < Coordinate(1, 3, 0));
    ASSERT_TRUE(Coordinate(1, 2, 3) < Coordinate(1, 2, 4));
    ASSERT_FALSE(Coordinate(1, 2, 3) < Coordinate(1, 2, 3));
    ASSERT_FALSE(Coordinate(2, 0, 0) < Coordinate(1, 9, 9));
}

TEST(runner, "Coordinate: operator> from CRTP base") {
    ASSERT_TRUE(Coordinate(2, 0, 0) > Coordinate(1, 9, 9));
    ASSERT_FALSE(Coordinate(1, 2, 3) > Coordinate(1, 2, 3));
}

TEST(runner, "Coordinate: operator<= from CRTP base") {
    ASSERT_TRUE(Coordinate(1, 2, 3) <= Coordinate(1, 2, 3));
    ASSERT_TRUE(Coordinate(1, 2, 3) <= Coordinate(1, 2, 4));
    ASSERT_FALSE(Coordinate(1, 2, 4) <= Coordinate(1, 2, 3));
}

TEST(runner, "Coordinate: operator>= from CRTP base") {
    ASSERT_TRUE(Coordinate(1, 2, 3) >= Coordinate(1, 2, 3));
    ASSERT_TRUE(Coordinate(1, 2, 4) >= Coordinate(1, 2, 3));
    ASSERT_FALSE(Coordinate(1, 2, 3) >= Coordinate(1, 2, 4));
}

TESTKIT_MAIN(runner)
