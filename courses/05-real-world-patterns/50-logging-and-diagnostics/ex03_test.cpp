// Exercise 03 -- Tests (read-only)
//
// Verifies source location capture and formatting.

#include <testkit/testkit.h>
#include <string>
#include "ex03.h"

static testkit::TestRunner runner("05-50-ex03: Source Location");

TEST(runner, "to_string extracts base filename") {
    SourceLocation loc{"some/deep/path/myfile.cpp", 42};
    ASSERT_EQ(loc.to_string(), std::string("myfile.cpp:42"));
}

TEST(runner, "to_string with no directory in path") {
    SourceLocation loc{"myfile.cpp", 10};
    ASSERT_EQ(loc.to_string(), std::string("myfile.cpp:10"));
}

TEST(runner, "to_string with various line numbers") {
    SourceLocation loc{"file.h", 1};
    ASSERT_EQ(loc.to_string(), std::string("file.h:1"));
    SourceLocation loc2{"file.h", 9999};
    ASSERT_EQ(loc2.to_string(), std::string("file.h:9999"));
}

TEST(runner, "MAKE_LOCATION captures this file") {
    auto loc = MAKE_LOCATION();
    // The base filename should be "ex03_test.cpp"
    std::string str = loc.to_string();
    // It should end with "ex03_test.cpp:NN"
    ASSERT_TRUE(str.find("ex03_test.cpp:") != std::string::npos);
}

TEST(runner, "MAKE_LOCATION captures correct line") {
    int before_line = __LINE__;
    auto loc = MAKE_LOCATION();
    // loc.line should be before_line + 1
    ASSERT_EQ(loc.line, before_line + 1);
}

TEST(runner, "to_string with backslash path separator") {
    SourceLocation loc{"C:\\Users\\dev\\src\\main.cpp", 55};
    ASSERT_EQ(loc.to_string(), std::string("main.cpp:55"));
}

TESTKIT_MAIN(runner)
