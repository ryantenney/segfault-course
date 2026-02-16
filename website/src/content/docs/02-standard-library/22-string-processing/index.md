---
title: "Lesson 22: String Processing"
---

## Why This Lesson Exists

Strings are everywhere -- configuration files, log messages, user input, network
protocols, serialization formats. C++ gives you a rich set of tools for working
with strings, from low-level `find`/`substr` operations to C++17's `from_chars`
for fast number parsing to C++20's `std::format` for type-safe formatting to
`<regex>` for pattern matching.

This lesson covers the practical string operations you will use daily.

## Key Concepts

### Searching and Extracting Substrings

`std::string` provides `find()` and `substr()` as the fundamental building
blocks for string parsing:

```cpp
std::string s = "key=value";
auto pos = s.find('=');                    // 3
auto key = s.substr(0, pos);              // "key"
auto val = s.substr(pos + 1);            // "value"
```

`find_first_not_of()` and `find_last_not_of()` are useful for trimming
characters from the edges of a string.

### Number Conversion with from_chars / to_chars (C++17)

`std::from_chars` and `std::to_chars` provide fast, locale-independent number
conversion without memory allocation:

```cpp
int value = 0;
auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);
// ec == std::errc{} on success

char buf[32];
auto [end, ec2] = std::to_chars(buf, buf + sizeof(buf), 42);
std::string result(buf, end);  // "42"
```

### Formatted Output with std::format (C++20)

`std::format` replaces `printf` and `ostringstream` with a type-safe,
extensible formatting system:

```cpp
std::format("Hello, {}!", name);         // positional replacement
std::format("{:.2f}", 3.14159);          // "3.14"
std::format("{:>10}", "hi");             // "        hi"
```

### Case Conversion with std::transform

There is no built-in `to_lower()` for strings, but `std::transform` with
`std::tolower` (from `<cctype>`) provides one:

```cpp
std::transform(s.begin(), s.end(), s.begin(),
               [](unsigned char c) { return std::tolower(c); });
```

The `unsigned char` cast is important -- `std::tolower` has undefined behavior
for negative values.

### Regular Expressions

`<regex>` provides pattern matching with `std::regex_match` (whole string) and
`std::regex_search` (substring). Capture groups let you extract parts of a
match:

```cpp
std::regex pattern(R"((\d{4})-(\d{2})-(\d{2}))");
std::smatch match;
if (std::regex_match(date_str, match, pattern)) {
    auto year = match[1].str();
}
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 02-22

# Build and test a single exercise
./run exercise 02-22-ex01
```

Unfinished exercises show as **skipped** (yellow circles). Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Parse Key-Value Pairs

**Files:** `ex01.h` (edit) - `ex01_test.cpp` (read-only)

Use `std::string::find` and `substr` to split a `"key=value"` string into its
two parts. This is the most fundamental string parsing operation in C++.

### What to do

1. `parse_key()` -- return the part before the first `'='`. If there is no
   `'='`, return the entire string.
2. `parse_value()` -- return the part after the first `'='`. If there is no
   `'='`, return an empty string.
3. `parse_pair()` -- return both parts as a `std::pair<string, string>`.

---

## Exercise 2: Split a String

**Files:** `ex02.h` (edit) - `ex02_test.cpp` (read-only)

Build a general-purpose `split()` function that divides a string at every
occurrence of a delimiter. This is surprisingly absent from the C++ standard
library, so knowing how to implement it is essential.

### What to do

1. `split()` -- split a string by a delimiter string and return a
   `vector<string>`. Consecutive delimiters produce empty strings between them.
2. `join()` -- the inverse of split: combine a vector of strings with a
   separator between each element.

---

## Exercise 3: Number Conversion

**Files:** `ex03.h` (edit) - `ex03_test.cpp` (read-only)

C++17's `from_chars` and `to_chars` provide fast, locale-independent number
conversion. Unlike `stoi` or `stod`, they do not throw exceptions on error --
they report success or failure via `std::errc`.

### What to do

1. `int_to_string()` -- convert an int to its string representation using
   `std::to_chars`.
2. `string_to_int()` -- parse a string as an int using `std::from_chars`.
   Return 0 on failure.
3. `string_to_int_checked()` -- parse a string as an int, returning
   `std::optional<int>`. Return `std::nullopt` if parsing fails or if there
   are leftover characters.

---

## Exercise 4: Format Strings

**Files:** `ex04.h` (edit) - `ex04_test.cpp` (read-only)

C++20's `std::format` provides Python-style string formatting that is type-safe
and extensible. This exercise covers basic replacement fields, precision
specifiers, and alignment.

### What to do

1. `greet()` -- format a greeting message with a name and age.
2. `format_price()` -- format a dollar amount to exactly 2 decimal places.
3. `format_table_row()` -- format a row with a left-aligned name column
   (20 chars) and a right-aligned score column (5 chars).

---

## Exercise 5: Trim Whitespace

**Files:** `ex05.h` (edit) - `ex05_test.cpp` (read-only)

Trimming whitespace from strings is a fundamental operation not provided
directly by `std::string`. You can build it using `find_first_not_of` and
`find_last_not_of`, which find the first/last character not in a given set.

### What to do

1. `ltrim()` -- remove leading whitespace.
2. `rtrim()` -- remove trailing whitespace.
3. `trim()` -- remove both leading and trailing whitespace.

---

## Exercise 6: Case Conversion

**Files:** `ex06.h` (edit) - `ex06_test.cpp` (read-only)

Convert strings between cases using `std::transform` with `std::tolower` and
`std::toupper` from `<cctype>`. Remember to use `unsigned char` to avoid
undefined behavior with negative char values.

### What to do

1. `to_lower()` -- convert all ASCII uppercase letters to lowercase.
2. `to_upper()` -- convert all ASCII lowercase letters to uppercase.
3. `is_equal_ignore_case()` -- compare two strings case-insensitively.

---

## Exercise 7: Simple Regex Match

**Files:** `ex07.h` (edit) - `ex07_test.cpp` (read-only)

`<regex>` provides `std::regex_match` (matches entire string) and
`std::regex_search` (finds pattern anywhere in string). This exercise uses
both for validation tasks.

### What to do

1. `is_valid_identifier()` -- check if a string is a valid C++ identifier
   (starts with letter or underscore, followed by letters/digits/underscores).
2. `contains_number()` -- check if a string contains any sequence of digits.
3. `is_valid_email_simple()` -- check if a string matches a simplified email
   pattern.

---

## Exercise 8: Regex Capture Groups

**Files:** `ex08.h` (edit) - `ex08_test.cpp` (read-only)

Capture groups in regular expressions let you extract specific parts of a
match. `std::smatch` holds the results, where `match[0]` is the full match
and `match[1]`, `match[2]`, etc. are the capture groups.

### What to do

1. `parse_date()` -- extract year, month, and day from a "YYYY-MM-DD" string
   using capture groups.
2. `parse_log_entry()` -- extract the level and message from a "[LEVEL] message"
   log line.
3. `extract_urls()` -- find all http/https URLs in a text string using
   `std::sregex_iterator`.
