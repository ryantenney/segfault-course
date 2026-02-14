// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>

#include "ex05.h"

static testkit::TestRunner runner("01-04-ex05: Find and Extract");

TEST(runner, "extract_key returns part before colon") {
    ASSERT_EQ(extract_key("host:localhost"), std::string("host"));
    ASSERT_EQ(extract_key("port:8080"), std::string("port"));
    ASSERT_EQ(extract_key("no-colon-here"), std::string("no-colon-here"));
    ASSERT_EQ(extract_key(":value"), std::string(""));
}

TEST(runner, "extract_value returns part after colon") {
    ASSERT_EQ(extract_value("host:localhost"), std::string("localhost"));
    ASSERT_EQ(extract_value("port:8080"), std::string("8080"));
    ASSERT_EQ(extract_value("no-colon-here"), std::string(""));
    ASSERT_EQ(extract_value("key:"), std::string(""));
}

TEST(runner, "extract_filename returns part after last slash") {
    ASSERT_EQ(extract_filename("/home/user/docs/report.txt"), std::string("report.txt"));
    ASSERT_EQ(extract_filename("report.txt"), std::string("report.txt"));
    ASSERT_EQ(extract_filename("/single"), std::string("single"));
    ASSERT_EQ(extract_filename("/a/b/c"), std::string("c"));
}

TEST(runner, "extract_extension returns part after last dot") {
    ASSERT_EQ(extract_extension("photo.jpg"), std::string("jpg"));
    ASSERT_EQ(extract_extension("archive.tar.gz"), std::string("gz"));
    ASSERT_EQ(extract_extension("no-extension"), std::string(""));
    ASSERT_EQ(extract_extension("file."), std::string(""));
}

TESTKIT_MAIN(runner)
