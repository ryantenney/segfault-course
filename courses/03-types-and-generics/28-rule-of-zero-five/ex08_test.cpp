// Exercise 08 -- Tests (read-only)
//
// Verifies that Document works with compiler-generated special members
// thanks to well-behaved member types (Rule of Zero through composition).

#include <type_traits>
#include <utility>
#include <testkit/testkit.h>
#include "ex08.h"

static testkit::TestRunner runner("03-28-ex08: Rule of Zero with Composition");

TEST(runner, "constructor initializes title and author") {
    Document doc("My Book", "Alice");
    ASSERT_EQ(doc.title(), std::string("My Book"));
    ASSERT_EQ(doc.author(), std::string("Alice"));
}

TEST(runner, "starts with zero sections") {
    Document doc("T", "A");
    ASSERT_EQ(doc.section_count(), 0u);
}

TEST(runner, "add_section increases count") {
    Document doc("T", "A");
    doc.add_section("Ch1", "Introduction");
    ASSERT_EQ(doc.section_count(), 1u);

    doc.add_section("Ch2", "Methods");
    ASSERT_EQ(doc.section_count(), 2u);
}

TEST(runner, "get_section returns correct data") {
    Document doc("T", "A");
    doc.add_section("Abstract", "Summary of the work");
    doc.add_section("Conclusion", "Final thoughts");

    ASSERT_EQ(doc.get_section(0).title, std::string("Abstract"));
    ASSERT_EQ(doc.get_section(0).body, std::string("Summary of the work"));
    ASSERT_EQ(doc.get_section(1).title, std::string("Conclusion"));
    ASSERT_EQ(doc.get_section(1).body, std::string("Final thoughts"));
}

TEST(runner, "copy produces independent document") {
    Document a("Book", "Bob");
    a.add_section("Ch1", "Hello");

    Document b(a);

    ASSERT_EQ(b.title(), std::string("Book"));
    ASSERT_EQ(b.author(), std::string("Bob"));
    ASSERT_EQ(b.section_count(), 1u);
    ASSERT_EQ(b.get_section(0).title, std::string("Ch1"));

    // Modifying original does not affect copy
    a.add_section("Ch2", "World");
    ASSERT_EQ(b.section_count(), 1u);
}

TEST(runner, "copy assignment works") {
    Document a("A", "Author A");
    a.add_section("S1", "Content");

    Document b("B", "Author B");
    b = a;

    ASSERT_EQ(b.title(), std::string("A"));
    ASSERT_EQ(b.author(), std::string("Author A"));
    ASSERT_EQ(b.section_count(), 1u);
}

TEST(runner, "move constructor works") {
    Document a("Title", "Author");
    a.add_section("Ch1", "Body");

    Document b(std::move(a));

    ASSERT_EQ(b.title(), std::string("Title"));
    ASSERT_EQ(b.author(), std::string("Author"));
    ASSERT_EQ(b.section_count(), 1u);
    ASSERT_EQ(b.get_section(0).title, std::string("Ch1"));
}

TEST(runner, "move assignment works") {
    Document a("Title", "Author");
    a.add_section("Ch1", "Body");

    Document b("Other", "Other");
    b = std::move(a);

    ASSERT_EQ(b.title(), std::string("Title"));
    ASSERT_EQ(b.author(), std::string("Author"));
    ASSERT_EQ(b.section_count(), 1u);
}

TEST(runner, "is copy constructible and move constructible") {
    Document doc("T", "A");
    doc.add_section("S", "B");
    (void)doc.section_count();

    ASSERT_TRUE(std::is_copy_constructible_v<Document>);
    ASSERT_TRUE(std::is_move_constructible_v<Document>);
    ASSERT_TRUE(std::is_copy_assignable_v<Document>);
    ASSERT_TRUE(std::is_move_assignable_v<Document>);
}

TESTKIT_MAIN(runner)
