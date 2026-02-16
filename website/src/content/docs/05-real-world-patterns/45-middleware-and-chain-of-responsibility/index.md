---
title: "Lesson 45: Middleware and Chain of Responsibility"
---

## Why This Lesson Exists

Middleware pipelines are one of the most common patterns in real-world software:
HTTP servers, logging frameworks, event processing systems, and plugin
architectures all use some form of "chain of responsibility" where each handler
can inspect, modify, or short-circuit a request before passing it downstream.

In C++, `std::function` and closures make it natural to compose middleware as
functions that wrap an inner "next" callback. This lesson builds that pattern
from scratch.

## Key Concepts

### Middleware as a Function

A middleware is a function that takes a context and a next callback:

```cpp
using Middleware = std::function<void(std::string& ctx, std::function<void()> next)>;
```

Calling `next()` passes control to the next middleware. Not calling it
short-circuits the chain.

### Chaining Middleware

Given a list of middleware and a final handler, you compose them by building
a recursive chain of next-functions:

```cpp
// Pseudocode:
// middleware[0]'s next calls middleware[1]
// middleware[1]'s next calls middleware[2]
// ...
// middleware[N-1]'s next calls the final handler
```

### Before and After

Because each middleware wraps `next()`, code before the call runs on the way
in, and code after runs on the way out (like an onion):

```cpp
[](std::string& ctx, std::function<void()> next) {
    // before: runs first
    ctx += "[start]";
    next();
    // after: runs last (on the way back out)
    ctx += "[end]";
};
```

### Early Exit / Short-Circuit

Any middleware can decide to stop the chain by not calling `next()`:

```cpp
[](std::string& ctx, std::function<void()> next) {
    if (!authorized(ctx)) {
        ctx = "401 Unauthorized";
        return;  // do NOT call next()
    }
    next();
};
```

### Error-handling Middleware

A middleware can wrap `next()` in a try/catch to convert exceptions into
error responses:

```cpp
[](std::string& ctx, std::function<void()> next) {
    try {
        next();
    } catch (const std::exception& e) {
        ctx = "500: " + std::string(e.what());
    }
};
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 05-45

# Build and test a single exercise
./run exercise 05-45-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Function Chain

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Implement `run_middleware()` — invoke the given middleware with the provided
context and next callback. This is the simplest building block.

---

## Exercise 2: Request/Response Context

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Implement `Context::set_metadata()` and `Context::get_metadata()`. The Context
struct carries request/response strings and a key-value metadata map.

---

## Exercise 3: Next Function

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Implement `chain_execute()` — given a vector of middleware and a final handler,
compose them so each middleware's next callback invokes the next middleware.

---

## Exercise 4: Early Exit

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Implement `make_auth_middleware()` and `chain_with_early_exit()`. The auth
middleware checks for an "AUTH:" prefix and short-circuits with "401
Unauthorized" if it is missing.

---

## Exercise 5: Middleware Composition

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Implement the `Pipeline` class with `use()` to add middleware and `execute()`
to run them all in order.

---

## Exercise 6: Error-handling Middleware

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Implement `make_error_handler()` which catches exceptions from downstream
middleware and sets context to `"500: " + e.what()`.

---

## Exercise 7: Timing Middleware

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Implement `make_timing_middleware()` which measures the wall-clock time spent
in the downstream chain and stores it in a reference variable.

---

## Exercise 8: Conditional Middleware

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Implement `make_path_middleware()` which only applies its tag when the context
starts with a given path prefix. Always calls next regardless.
