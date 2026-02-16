---
title: "Lesson 13: Error Handling Patterns"
---

## Why This Lesson Exists

Error handling is one of the most debated topics in C++. The language supports
both exceptions (the standard library's default) and error codes (used heavily
in systems programming). Each has trade-offs. Knowing when and how to use
each approach — and how to make code exception-safe — is essential for writing
robust C++.

## Key Concepts

### Throwing and Catching Exceptions

C++ exceptions use `throw` to signal an error and `try`/`catch` to handle it.
The standard library provides a hierarchy rooted at `std::exception`:

```cpp
throw std::runtime_error("something went wrong");

try {
    risky_operation();
} catch (const std::runtime_error& e) {
    std::cerr << e.what() << "\n";
}
```

### Custom Exception Types

Define domain-specific exceptions by inheriting from `std::runtime_error` or
another standard exception class. This lets catch blocks distinguish between
error categories:

```cpp
class ParseError : public std::runtime_error {
    int line_;
public:
    ParseError(const std::string& msg, int line)
        : std::runtime_error(msg), line_(line) {}
    int line() const { return line_; }
};
```

### Catch Block Ordering

Catch blocks are tested in order. Always catch derived types before base types,
or the base catch will swallow everything:

```cpp
try { ... }
catch (const TimeoutError& e) { ... }     // most specific
catch (const NetworkError& e) { ... }      // base of TimeoutError
catch (const std::exception& e) { ... }    // most general
```

### Exception Safety and RAII

When an exception is thrown, local variables are destroyed (stack unwinding).
Raw `new`/`delete` leaks if `delete` is skipped. RAII objects (smart pointers,
containers, lock guards) ensure resources are released automatically:

```cpp
// Unsafe: leaks if process() throws
int* data = new int[100];
process(data);
delete[] data;

// Safe: unique_ptr cleans up automatically
auto data = std::make_unique<int[]>(100);
process(data.get());
```

### noexcept

The `noexcept` specifier promises a function will never throw. If it does,
`std::terminate` is called. Benefits:

- Enables compiler optimizations
- Move constructors should be noexcept (STL containers check this)
- Documents intent

```cpp
int add(int a, int b) noexcept { return a + b; }
static_assert(noexcept(add(1, 2)));  // compile-time check
```

### Exceptions vs Error Codes

| Aspect | Exceptions | Error Codes |
|--------|-----------|-------------|
| Happy path | Clean | Must check after every call |
| Failure path | Can't be ignored | Easy to ignore |
| Performance | Overhead on throw | Zero overhead |
| Use in destructors | Dangerous | Safe |

Neither is universally better. Many codebases use both: exceptions for
programming errors and recoverable failures, error codes for hot paths
and expected failure cases.

### Nested Exceptions

`std::throw_with_nested` wraps the current exception inside a new one,
preserving the error chain. `std::rethrow_if_nested` unpacks it:

```cpp
try {
    low_level_operation();
} catch (...) {
    std::throw_with_nested(std::runtime_error("high-level context"));
}
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 01-13

# Build and test a single exercise
./run exercise 01-13-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Throw and Catch

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Write a function that throws `std::runtime_error` on division by zero,
and a wrapper that catches it and returns a sentinel value.

### What to do

1. Implement `divide(a, b)` — throw if `b` is 0.
2. Implement `safe_divide(a, b)` — catch the exception and return -1.
3. Run: `./run exercise 01-13-ex01`

---

## Exercise 2: Custom Exception Class

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Define a `ParseError` exception that carries a line number, then use it
in a config-line parser.

### What to do

1. Complete `ParseError::line()` — return the stored line number.
2. Implement `parse_config_line()` — split on `=`, throw `ParseError` if
   no `=` is found.
3. Run: `./run exercise 01-13-ex02`

---

## Exercise 3: Multiple Catch Blocks

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Practice catching exceptions in the correct order: most specific first.
A `TimeoutError` is a kind of `NetworkError`, which is a kind of
`std::runtime_error`.

### What to do

1. Implement `simulate_request()` — throw different exceptions based on url.
2. Implement `classify_error()` — use ordered catch blocks to identify the
   exception type.
3. Run: `./run exercise 01-13-ex03`

---

## Exercise 4: Exception Safety with RAII

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Compare a raw `new`/`delete` version that leaks on exception with a
`std::unique_ptr` version that is exception-safe.

### What to do

1. Implement `process_data_unsafe()` — allocate with `new[]`, throw on
   zero factor (leaks the allocation).
2. Implement `process_data_safe()` — same logic with `std::unique_ptr<int[]>`.
3. Run: `./run exercise 01-13-ex04`

---

## Exercise 5: Convert Exceptions to Error Codes

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Wrap a throwing function in try/catch and return an error struct instead.
This is a common pattern at API boundaries.

### What to do

1. Implement `open_file()` — throw for specific bad filenames.
2. Implement `try_open_file()` — catch the exception and return a `FileResult`.
3. Run: `./run exercise 01-13-ex05`

---

## Exercise 6: noexcept Correctness

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Mark functions `noexcept` where appropriate. The tests verify both the
behavior and the noexcept property at compile time.

### What to do

1. Implement `add()` — noexcept, simple addition.
2. Implement `safe_access()` — noexcept, bounds-checked with default.
3. Implement `checked_access()` — NOT noexcept, uses `at()` which can throw.
4. Implement `swap_values()` — noexcept, swaps two ints.
5. Run: `./run exercise 01-13-ex06`

---

## Exercise 7: Exception vs Error Code

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Implement the same user-lookup operation twice: once with exceptions, once
with an error struct. Both approaches must produce identical results.

### What to do

1. Implement `lookup_user_throwing()` and `lookup_user_result()`.
2. Implement `greet_user_with_exceptions()` and `greet_user_with_result()`.
3. Run: `./run exercise 01-13-ex07`

---

## Exercise 8: Nested Exceptions

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Use `std::throw_with_nested` to add context when re-throwing, and walk
the exception chain to collect all error messages.

### What to do

1. Implement `read_sensor()` — throw for broken sensors.
2. Implement `process_sensor()` — catch and re-throw with nested context.
3. Implement `get_error_chain()` — walk the chain and collect messages.
4. Run: `./run exercise 01-13-ex08`
