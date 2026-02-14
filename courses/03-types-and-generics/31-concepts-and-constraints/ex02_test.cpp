// Exercise 02 -- Tests (read-only)
//
// Verifies the Displayable concept with compound requirements.

#include <testkit/testkit.h>
#include <string>
#include "ex02.h"

// A type that satisfies Displayable.
struct Score {
    int value;

    bool operator<(const Score& other) const { return value < other.value; }
    bool operator==(const Score& other) const { return value == other.value; }

    std::string to_string() const {
        return "Score(" + std::to_string(value) + ")";
    }
};

// Another type that satisfies Displayable.
struct Label {
    std::string text;

    bool operator<(const Label& other) const { return text < other.text; }
    bool operator==(const Label& other) const { return text == other.text; }

    std::string to_string() const {
        return "Label[" + text + "]";
    }
};

static testkit::TestRunner runner("03-31-ex02: Compound Requirements");

TEST(runner, "compare_and_display returns smaller Score") {
    Score a{10}, b{20};
    ASSERT_EQ(compare_and_display(a, b), std::string("Score(10)"));
}

TEST(runner, "compare_and_display returns b when a is not less") {
    Score a{30}, b{20};
    ASSERT_EQ(compare_and_display(a, b), std::string("Score(20)"));
}

TEST(runner, "compare_and_display with equal values returns b") {
    Score a{10}, b{10};
    // a is not less than b, so return b.to_string()
    ASSERT_EQ(compare_and_display(a, b), std::string("Score(10)"));
}

TEST(runner, "compare_and_display works with Label") {
    Label a{"alpha"}, b{"beta"};
    ASSERT_EQ(compare_and_display(a, b), std::string("Label[alpha]"));
}

TEST(runner, "compare_and_display with Label b smaller") {
    Label a{"zebra"}, b{"apple"};
    ASSERT_EQ(compare_and_display(a, b), std::string("Label[apple]"));
}

TEST(runner, "Displayable concept accepts Score") {
    // Gate: compare_and_display must work first
    compare_and_display(Score{1}, Score{2});

    ASSERT_TRUE(Displayable<Score>);
}

TEST(runner, "Displayable concept accepts Label") {
    // Gate: compare_and_display must work first
    compare_and_display(Score{1}, Score{2});

    ASSERT_TRUE(Displayable<Label>);
}

TEST(runner, "Displayable concept rejects int") {
    // Gate: compare_and_display must work first
    compare_and_display(Score{1}, Score{2});

    // int has < and == but no .to_string() method
    ASSERT_FALSE(Displayable<int>);
}

TESTKIT_MAIN(runner)
