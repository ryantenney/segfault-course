// Exercise 08: Regex Capture Groups
//
// Regular expressions can capture parts of a match into groups using
// parentheses. In C++, the match results are stored in std::smatch
// (for std::string) or std::cmatch (for const char*).
//
//   std::string s = "2024-01-15";
//   std::regex pattern(R"((\d{4})-(\d{2})-(\d{2}))");
//   std::smatch match;
//   if (std::regex_match(s, match, pattern)) {
//       match[0].str();  // "2024-01-15" -- entire match
//       match[1].str();  // "2024"       -- first capture group
//       match[2].str();  // "01"         -- second capture group
//       match[3].str();  // "15"         -- third capture group
//       match.size();    // 4 (full match + 3 groups)
//   }
//
// You can also iterate over all matches in a string using
// std::sregex_iterator:
//
//   std::string text = "cat 10 dog 20";
//   std::regex num_pattern(R"(\d+)");
//   auto begin = std::sregex_iterator(text.begin(), text.end(), num_pattern);
//   auto end   = std::sregex_iterator();
//   for (auto it = begin; it != end; ++it) {
//       std::cout << it->str() << "\n";  // prints "10" then "20"
//   }
//
// TODO:
//   1. Implement parse_date() -- extract year, month, day from a
//      "YYYY-MM-DD" string. Return them as a struct with int fields.
//      Return {0, 0, 0} if the string does not match.
//   2. Implement extract_urls() -- find all http/https URLs in a string
//      and return them as a vector. Use std::sregex_iterator with a
//      pattern like https?://\S+ to find URLs.
//   3. Implement parse_log_entry() -- parse a log line of the form
//      "[LEVEL] message" and extract the level and message.
//      Return {"", ""} if the format doesn't match.

#pragma once

#include <regex>
#include <string>
#include <vector>
#include <testkit/testkit.h>

struct Date {
    int year;
    int month;
    int day;
};

// Parse a "YYYY-MM-DD" date string using regex capture groups.
// Return {0, 0, 0} if the string does not match the expected format.
inline Date parse_date(const std::string& s) {
    TODO();
}

struct LogEntry {
    std::string level;
    std::string message;
};

// Parse a log line of the form "[LEVEL] message text here".
// The level is the text inside the brackets (e.g., "ERROR").
// The message is everything after the "] " (with leading space trimmed).
// Return {"", ""} if the format doesn't match.
inline LogEntry parse_log_entry(const std::string& line) {
    TODO();
}

// Find all http:// or https:// URLs in the text.
// A URL starts with http:// or https:// and continues until whitespace.
// Return them in the order they appear.
inline std::vector<std::string> extract_urls(const std::string& text) {
    TODO();
}
