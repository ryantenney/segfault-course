// Exercise 07 -- Tests (read-only)
//
// Verifies subsumption ordering: the compiler picks the most constrained match.

#include <testkit/testkit.h>
#include <string>
#include "ex07.h"

// Ordered only (has < but no .name())
struct Weight {
    double kg;
    bool operator<(const Weight& other) const { return kg < other.kg; }
};

// Both Ordered and Named
struct Player {
    std::string name_;
    int score;

    bool operator<(const Player& other) const { return score < other.score; }
    std::string name() const { return name_; }
};

// Named only (has .name() but no <)
struct Tag {
    std::string label;
    std::string name() const { return label; }
};

static testkit::TestRunner runner("03-31-ex07: Subsumption Ordering");

TEST(runner, "identify selects Ordered for Weight") {
    Weight w{75.0};
    ASSERT_EQ(identify(w), std::string("ordered"));
}

TEST(runner, "identify selects OrderedAndNamed for Player") {
    // Gate: Ordered overload must work first
    identify(Weight{1.0});

    Player p{"Alice", 100};
    ASSERT_EQ(identify(p), std::string("ordered+named: Alice"));
}

TEST(runner, "identify selects OrderedAndNamed for another Player") {
    // Gate: Ordered overload must work first
    identify(Weight{1.0});

    Player p{"Bob", 50};
    ASSERT_EQ(identify(p), std::string("ordered+named: Bob"));
}

TEST(runner, "identify works with int (Ordered)") {
    ASSERT_EQ(identify(42), std::string("ordered"));
}

TEST(runner, "Ordered concept checks") {
    // Gate: identify must work first
    identify(1);

    ASSERT_TRUE(Ordered<int>);
    ASSERT_TRUE(Ordered<Weight>);
    ASSERT_TRUE(Ordered<Player>);
    ASSERT_FALSE(Ordered<Tag>);
}

TEST(runner, "Named concept checks") {
    // Gate: identify must work first
    identify(1);

    ASSERT_TRUE(Named<Player>);
    ASSERT_TRUE(Named<Tag>);
    ASSERT_FALSE(Named<int>);
    ASSERT_FALSE(Named<Weight>);
}

TEST(runner, "OrderedAndNamed concept checks") {
    // Gate: identify must work first
    identify(1);

    ASSERT_TRUE(OrderedAndNamed<Player>);
    ASSERT_FALSE(OrderedAndNamed<Weight>);  // no .name()
    ASSERT_FALSE(OrderedAndNamed<Tag>);     // no <
    ASSERT_FALSE(OrderedAndNamed<int>);     // no .name()
}

TESTKIT_MAIN(runner)
