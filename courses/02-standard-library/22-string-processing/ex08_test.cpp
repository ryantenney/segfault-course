// Exercise 08 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex08.h"

static testkit::TestRunner runner("02-22-ex08: Regex Capture Groups");

TEST(runner, "parse_date extracts year month day") {
    auto d = parse_date("2024-01-15");
    ASSERT_EQ(d.year, 2024);
    ASSERT_EQ(d.month, 1);
    ASSERT_EQ(d.day, 15);
}

TEST(runner, "parse_date handles different date") {
    auto d = parse_date("1999-12-31");
    ASSERT_EQ(d.year, 1999);
    ASSERT_EQ(d.month, 12);
    ASSERT_EQ(d.day, 31);
}

TEST(runner, "parse_date returns zeros for invalid format") {
    auto d = parse_date("not-a-date");
    ASSERT_EQ(d.year, 0);
    ASSERT_EQ(d.month, 0);
    ASSERT_EQ(d.day, 0);
}

TEST(runner, "parse_date returns zeros for empty string") {
    auto d = parse_date("");
    ASSERT_EQ(d.year, 0);
    ASSERT_EQ(d.month, 0);
    ASSERT_EQ(d.day, 0);
}

TEST(runner, "parse_log_entry extracts level and message") {
    auto entry = parse_log_entry("[ERROR] Connection refused");
    ASSERT_EQ(entry.level, std::string("ERROR"));
    ASSERT_EQ(entry.message, std::string("Connection refused"));
}

TEST(runner, "parse_log_entry handles INFO level") {
    auto entry = parse_log_entry("[INFO] Server started on port 8080");
    ASSERT_EQ(entry.level, std::string("INFO"));
    ASSERT_EQ(entry.message, std::string("Server started on port 8080"));
}

TEST(runner, "parse_log_entry handles WARN level") {
    auto entry = parse_log_entry("[WARN] Disk usage above 90%");
    ASSERT_EQ(entry.level, std::string("WARN"));
    ASSERT_EQ(entry.message, std::string("Disk usage above 90%"));
}

TEST(runner, "parse_log_entry returns empty for invalid format") {
    auto entry = parse_log_entry("no brackets here");
    ASSERT_EQ(entry.level, std::string(""));
    ASSERT_EQ(entry.message, std::string(""));
}

TEST(runner, "extract_urls finds single URL") {
    auto urls = extract_urls("Visit https://example.com for info");
    ASSERT_EQ(urls.size(), 1u);
    ASSERT_EQ(urls[0], std::string("https://example.com"));
}

TEST(runner, "extract_urls finds multiple URLs") {
    auto urls = extract_urls("See http://a.com and https://b.org here");
    ASSERT_EQ(urls.size(), 2u);
    ASSERT_EQ(urls[0], std::string("http://a.com"));
    ASSERT_EQ(urls[1], std::string("https://b.org"));
}

TEST(runner, "extract_urls returns empty when none found") {
    auto urls = extract_urls("no links here");
    ASSERT_EQ(urls.size(), 0u);
}

TEST(runner, "extract_urls handles URL with path") {
    auto urls = extract_urls("Go to https://example.com/path/to/page for details");
    ASSERT_EQ(urls.size(), 1u);
    ASSERT_EQ(urls[0], std::string("https://example.com/path/to/page"));
}

TESTKIT_MAIN(runner)
