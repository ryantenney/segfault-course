# Lesson 49: HTTP Request/Response Modeling

## Why This Lesson Exists

HTTP is the lingua franca of the web. Even if you never write a web server
from scratch, understanding how requests and responses are structured helps you
design cleaner APIs, debug network issues, and work with HTTP libraries
effectively. This lesson models the core HTTP abstractions in C++ using
enums, structs, optional, and string parsing.

## Key Concepts

### Enum Class for Fixed Sets

HTTP methods (GET, POST, PUT, ...) and status code categories are perfect
candidates for `enum class`. This gives you compile-time safety and prevents
accidental integer-to-enum conversions.

### Case-Insensitive Comparison

HTTP header names are case-insensitive per the spec. A common approach is
to normalize keys to lowercase before storing them in a `std::map`.

### Fluent Builder API

When an object has many optional fields, a builder with method chaining
(`builder.status(200).header("X","Y").build()`) gives a readable,
self-documenting construction interface.

### String Parsing

Parsing Content-Type headers and query strings exercises core string
manipulation: splitting on delimiters, trimming whitespace, and decoding
URL-encoded characters.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 05-49

# Build and test a single exercise
./run exercise 05-49-ex01
```

Unfinished exercises show as **skipped** (yellow circles). Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: HTTP Method Enum

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Define an `enum class Method` for HTTP verbs and implement `to_string()` and
`method_from_string()` for converting between the enum and strings.

---

## Exercise 2: Status Code Enum

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Implement category-checking functions (`is_success`, `is_redirect`,
`is_client_error`, `is_server_error`) and a `reason_phrase` function for
standard status codes.

---

## Exercise 3: Headers Class

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Build a case-insensitive header map with `set()`, `get()`, `has()`, and
`remove()` methods.

---

## Exercise 4: Multi-value Headers

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Extend the header concept to support multiple values per key with `add()`,
`get_all()`, and `get_first()`.

---

## Exercise 5: Request Type

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Model an HTTP request as a struct with method, path, query, headers, and
optional body. Implement helper functions for construction and inspection.

---

## Exercise 6: Response Builder

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Build an HTTP response using a fluent API: `ResponseBuilder().status(200)
.header("X","Y").set_body("...").build()`.

---

## Exercise 7: Content-Type Parsing

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Parse a Content-Type header string like "text/html; charset=utf-8" into its
type, subtype, and parameter map.

---

## Exercise 8: Query String Parsing

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Parse a URL query string like "?key=val&k2=v2" into a map. Handle
URL-encoded values, missing values, and leading '?'.
