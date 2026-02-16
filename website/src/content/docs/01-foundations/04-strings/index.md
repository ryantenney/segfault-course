---
title: "Lesson 04: Strings and String Views"
---

## Why This Lesson Exists

Coming from languages like Java, Python, or Go, you might expect a single
string type.  C++ has two: `std::string` (an owning, heap-allocated string)
and `std::string_view` (a non-owning, zero-copy window into existing character
data).  Using the right one in the right place avoids unnecessary copies and
prevents entire categories of bugs.

This lesson teaches you when to use each, how they interact, and the lifetime
traps that `string_view` introduces.

## Key Concepts

### std::string — The Owning String

`std::string` manages its own memory.  When you copy a string, you get a
completely independent copy with its own heap allocation.

```cpp
std::string greeting = "Hello";     // allocates on the heap
std::string copy = greeting;         // independent copy, separate allocation
greeting += ", world!";              // only `greeting` changes
```

Key member functions:
- `size()` / `length()` — number of characters
- `empty()` — true if size is zero
- `clear()` — remove all characters
- `find(str)` / `rfind(str)` — search forward / backward
- `substr(pos, count)` — extract a substring (returns a new std::string)
- `operator+` / `append()` / `operator+=` — concatenation

### std::string_view — The Non-Owning View (C++17)

`std::string_view` is a (pointer, length) pair that refers to character data
owned by someone else.  It never allocates memory and is cheap to copy.

```cpp
void print_name(std::string_view name) {   // no copy, no allocation
    std::cout << name << "\n";
}

print_name("Alice");                        // works with string literals
print_name(some_std_string);                // works with std::string
print_name(some_string_view.substr(0, 5)); // works with sub-views
```

Use `string_view` when:
- You only need to **read** the data
- You do not need the data to **outlive** the function call
- You want to avoid forcing callers to create a `std::string`

### The Lifetime Rule

**A `string_view` is valid only as long as the data it points to exists.**

Safe:
- Viewing a `std::string` that outlives the view
- Viewing a string literal (literals have static lifetime)
- Returning a sub-view of a parameter that the caller owns

Dangerous:
- Viewing a **local** `std::string` and returning the view
- Viewing a **temporary** (e.g., the result of `operator+` or `std::to_string`)
- Storing a `string_view` in a data structure that outlives the source string

```cpp
// SAFE — sv points to caller's data
std::string_view first_char(std::string_view sv) {
    return sv.substr(0, 1);
}

// DANGLING — result is destroyed when the function returns
std::string_view bad() {
    std::string tmp = "hello";
    return tmp;  // tmp is destroyed → dangling view
}
```

### When to Use Which

| Situation | Use |
|-----------|-----|
| Function parameter (read-only) | `std::string_view` |
| Function needs to store the string | `std::string` (or `const std::string&`) |
| Return a newly-built string | `std::string` |
| Return a slice of caller-owned data | `std::string_view` |
| Class member that owns its data | `std::string` |

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 01-04

# Build and test a single exercise
./run exercise 01-04-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: String Basics

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

The foundational `std::string` operations: construction, querying size, checking
emptiness, and clearing.

`std::string` can be constructed from:
- A C-string literal: `std::string s("hello");` or `std::string s = "hello";`
- A count and a character: `std::string s(5, 'x');` produces `"xxxxx"`
- Another string (copy): `std::string s2 = s1;`

### What to do

1. `make_greeting(name)` — Construct a `std::string` from the given `const char*`.
2. `string_length(s)` — Return `s.size()`.
3. `is_empty(s)` — Return `s.empty()`.
4. `cleared_copy(s)` — Copy `s`, call `.clear()` on the copy, return it.
5. `repeat_char(count, ch)` — Use the `(count, char)` constructor.

---

## Exercise 2: Fix String Copies

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

These functions take `const std::string&`, which forces callers to construct a
`std::string`.  When a caller passes a string literal like `"hello"`, the
compiler creates a temporary `std::string` on the heap just to bind the
reference.  That is wasteful when the function only reads the data.

`std::string_view` accepts string literals, `std::string`, and other views
without any allocation.

### What to do

1. Add `#include <string_view>` to the header.
2. Change each parameter from `const std::string&` to `std::string_view`.
3. Implement the bodies:
   - `starts_with` — compare the first `prefix.size()` characters. In C++20,
     `string_view` has `.starts_with()`, but you can implement it with `substr`
     and `==` or by checking `text.compare(0, prefix.size(), prefix) == 0`.
   - `ends_with` — similar, but compare the last `suffix.size()` characters.
   - `contains` — use `text.find(substring) != std::string_view::npos`.

---

## Exercise 3: Substring Without Allocation

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

`std::string::substr()` allocates a new string on the heap.
`std::string_view::substr()` just adjusts the pointer and length — zero cost.

The key difference:

```cpp
std::string s = "hello world";
auto sub1 = s.substr(0, 5);                    // allocates "hello"

std::string_view sv = s;
auto sub2 = sv.substr(0, 5);                    // no allocation, just a view
```

### What to do

Use `std::string_view::substr(pos, count)` in each function.  Remember:
- `substr(pos)` — from `pos` to end
- `substr(pos, count)` — from `pos`, at most `count` characters

1. `first_n(sv, n)` — `sv.substr(0, n)` (substr automatically clamps).
2. `last_n(sv, n)` — compute the start position, handle n > size.
3. `drop_first_n(sv, n)` — `sv.substr(n)` if n &lt;= size, else empty.
4. `slice(sv, from, to)` — clamp, then `sv.substr(from, to - from)`.

---

## Exercise 4: Build a String

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Strings can be assembled using `operator+` (returns a new string) or `append()`
/ `operator+=` (modifies in place).

```cpp
std::string a = "Hello" + std::string(", ") + "World";   // + with literals
std::string b;
b += "Hello";
b += ", World";  // same result, potentially fewer allocations
```

### What to do

1. `make_greeting(name)` — Return `"Hello, " + name + "!"`.
2. `make_tag(label)` — Return `"[" + label + "]"`.
3. `make_pair(key, value)` — Return `key + "=" + value`.
4. `join_path(a, b, c)` — Return `a + "/" + b + "/" + c`.

---

## Exercise 5: Find and Extract

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Parsing delimited strings is a common task.  `find()` searches forward for a
substring and returns its position (or `std::string::npos` if not found).
`rfind()` searches backward.  `substr()` extracts a portion.

```cpp
std::string path = "/home/user/file.txt";
auto pos = path.rfind('/');          // pos = 10
auto name = path.substr(pos + 1);   // "file.txt"
```

### What to do

1. `extract_key(kv)` — Find `':'`, return everything before it.
2. `extract_value(kv)` — Find `':'`, return everything after it.
3. `extract_filename(path)` — Use `rfind('/')`, return after the last slash.
4. `extract_extension(filename)` — Use `rfind('.')`, return after the last dot.

Always check whether `find`/`rfind` returned `npos` before using the position.

---

## Exercise 6: String Comparison

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

C++ strings compare lexicographically with `==` and `<`, but there is no
built-in case-insensitive comparison.  You build one from `std::tolower` and
`std::equal`.

```cpp
// tolower requires unsigned char to avoid undefined behavior
char lower(char c) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
}
```

`std::equal` compares two ranges element-by-element.  With a custom predicate,
you can compare lowercased characters:

```cpp
std::equal(a.begin(), a.end(), b.begin(), [](char x, char y) {
    return std::tolower(static_cast<unsigned char>(x))
        == std::tolower(static_cast<unsigned char>(y));
});
```

### What to do

1. `to_lower(sv)` — Build a `std::string` from `sv`, transform each character
   with `std::tolower`. You can use a range-for loop or `std::transform`.
2. `iequals(a, b)` — Check sizes match, then use `std::equal` with a tolower
   predicate.
3. `istarts_with(text, prefix)` — Check prefix fits, then compare the first
   `prefix.size()` characters case-insensitively.

---

## Exercise 7: Dangling View

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

This exercise teaches the most dangerous `string_view` mistake: returning a view
that points to a local or temporary string.  When the function returns, the
string is destroyed, and the view dangles.  The compiler usually does **not**
warn about this.

The header shows a commented-out example of the bug, then asks you to implement
the correct version.

### What to do

1. `make_label(prefix, id)` — Assemble `"item-42"` from a prefix and id.
   Since concatenation creates new data, you must return `std::string` (the
   return type is already correct).  Implement: return
   `std::string(prefix) + "-" + std::to_string(id)`.
2. `first_word(sentence)` — Return the part before the first space.  The
   parameter is `std::string_view` and the return is `std::string_view`.  Use
   `sentence.substr(0, pos)` which returns a sub-view (safe, no allocation).
3. `trim_prefix` — Already implemented correctly.  No changes needed.

---

## Exercise 8: View Lifetime Traps

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Five functions labeled SAFE or BUGGY in the comments.  Each teaches a different
aspect of string_view lifetime safety.  Read the comments to understand why each
return type was chosen, then implement the body.

### What to do

1. `strip_quotes(sv)` — **SAFE.** Return `sv.substr(1, sv.size() - 2)`.  The
   returned view still points into the caller's data.
2. `concat(a, b)` — Returns `std::string` because concatenation creates new
   data.  Read the comment to see what the buggy version would look like.
   Implement: return `std::string(a) + std::string(b)`.
3. `is_all_digits(sv)` — **SAFE.** Return whether every char is `'0'`-`'9'`.
   Use `std::all_of` or a loop.  Return `false` for empty strings.
4. `int_to_str(value)` — Returns `std::string` because `std::to_string` creates
   a temporary.  Implement: return `std::to_string(value)`.
5. `find_pos(haystack, needle)` — **SAFE.** Return `haystack.find(needle)`.
   The result is a `size_t`, not a reference — no lifetime issue.
