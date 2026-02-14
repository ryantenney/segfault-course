// Exercise 05 -- Tests (read-only)

#include <testkit/testkit.h>
#include <memory>
#include <string>

#include "ex05.h"

static testkit::TestRunner runner("03-27-ex05: Override Keyword");

TEST(runner, "to_upper converts to uppercase") {
    ASSERT_EQ(to_upper("hello"), std::string("HELLO"));
    ASSERT_EQ(to_upper("World"), std::string("WORLD"));
    ASSERT_EQ(to_upper("ABC"), std::string("ABC"));
    ASSERT_EQ(to_upper(""), std::string(""));
}

TEST(runner, "BrokenPrinter print works when called directly") {
    BrokenPrinter bp;
    std::string result = bp.print(std::string("test"));
    // Just verify it doesn't crash and returns something
    ASSERT_FALSE(result.empty());
}

TEST(runner, "BrokenPrinter dispatches through base pointer after fix") {
    auto bp = std::make_unique<BrokenPrinter>();
    Printer* base = bp.get();
    std::string result = base->print("hello");
    // After fixing the signature, virtual dispatch should work
    ASSERT_FALSE(result.empty());
}

TEST(runner, "LoudPrinter converts to uppercase") {
    LoudPrinter lp;
    ASSERT_EQ(lp.print("hello"), std::string("HELLO"));
    ASSERT_EQ(lp.print("quiet"), std::string("QUIET"));
}

TEST(runner, "LoudPrinter dispatches through base pointer") {
    std::unique_ptr<Printer> p = make_loud_printer();
    ASSERT_EQ(p->print("whisper"), std::string("WHISPER"));
}

TEST(runner, "base Printer returns message unchanged") {
    Printer p;
    ASSERT_EQ(p.print("unchanged"), std::string("unchanged"));
}

TEST(runner, "virtual dispatch chooses the right override") {
    Printer base;
    LoudPrinter loud;

    const Printer& ref1 = base;
    const Printer& ref2 = loud;

    ASSERT_EQ(ref1.print("test"), std::string("test"));
    ASSERT_EQ(ref2.print("test"), std::string("TEST"));
}

TESTKIT_MAIN(runner)
