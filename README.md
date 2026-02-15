# segfault-course: Modern C++ for Experienced Engineers

A structured, exercise-driven course that takes you from "I know C" to "I write
idiomatic modern C++." Five courses, 52 lessons, ~400 exercises. No fluff, no
intro-to-programming warmups. You edit code, run tests, and move on.

## Who This Is For

Senior+ engineers who are fluent in C syntax and have shipped production code
in at least one systems-adjacent language (C, Java, Rust, Go). You know what a
pointer is, how a for-loop works, and how to read a compiler error. You need to
get up to speed on modern C++ (C++17/20/23) quickly and correctly.

**Non-goals:** This is not an intro to programming. We don't cover basic control
flow, what a variable is, or how to compile hello world.

## What It Covers

| Course | Lessons | Exercises | Focus |
|--------|---------|-----------|-------|
| 1 -- Foundations | 13 | 103 | Compilation model, types, memory, ownership |
| 2 -- Standard Library | 10 | 78 | Containers, algorithms, ranges, lambdas |
| 3 -- Types & Generics | 11 | 88 | Classes, templates, concepts, forwarding |
| 4 -- Concurrency | 8 | 59 | Threads, synchronization, async, coroutines |
| 5 -- Web Patterns | 10 | 78 | Builder, middleware, serialization, HTTP modeling |
| **Total** | **52** | **~400** | |

Exercises start small (fix a single parameter type) and grow to multi-class
designs (HTTP handler framework with routing, middleware, and serialization).

## Prerequisites

- **C syntax fluency.** You can read C, understand pointers, and follow
  header/source conventions.
- **A C++20 compiler.** GCC 13+, Clang 16+, or MSVC 19.30+.
- **CMake 3.20+** and Make (or Ninja).
- **A terminal.** The `./run` script wraps cmake and ctest.

## Quick Start

```bash
git clone <repo-url> segfault-course
cd segfault-course

./run build               # configure + build all exercises
./run all                 # build and test everything

./run lesson 01-01        # build and test a single lesson
./run exercise 01-01-ex01 # build and test a single exercise
```

First invocation auto-runs cmake configure. Subsequent runs only rebuild
changed files.

## How Exercises Work

Every exercise file ships with scaffolding and `TODO()` markers:

```cpp
// ex01.h -- Fix the parameter type
#pragma once
#include <string>
#include <testkit/testkit.h>

// TODO: Change the parameter to accept a const reference instead of a copy.
inline std::string greet(std::string name) {
    return "Hello, " + name + "!";
}
```

You edit the `.h` file (or `.h` + `.cpp` pair in later lessons), then run the
tests. The `TODO()` macro throws a "not implemented" exception that the test
runner catches and reports as **skipped** rather than **failed**. This means
you can build and run an entire lesson immediately -- unfinished exercises show
as skipped, not as a wall of failures.

```
 Lesson 01-01: const and references

  [pass] ex01 - passes string by const reference
  [pass] ex01 - does not copy the input string
  [FAIL] ex02 - swaps two integers: expected 20, got 10
  [skip] ex03 - returns reference to largest (not implemented)
  [skip] ex03 - returned reference is const (not implemented)

 3 passed, 1 failed, 2 skipped
```

**The workflow:** edit the exercise file, run `./run exercise <id>`, read the
test output, repeat. Each lesson README explains every exercise.

## The `./run` Script

```
./run build                  # Configure + build all exercises
./run lesson 01-01           # Build & test a lesson (course-lesson)
./run exercise 01-01-ex01    # Build & test a single exercise
./run course 01              # Build & test all of a course
./run all                    # Build & test everything
./run clean                  # Remove build directory
```

## Project Structure

```
segfault-course/
  CMakeLists.txt                 # Root build config: C++20, warnings, CTest
  run                            # Convenience script (cmake/ctest wrapper)
  PLAN.md                        # Full curriculum design document
  testkit/
    include/testkit/testkit.h    # Test framework + TODO() macro
  courses/
    01-foundations/
      01-compilation-model/
        README.md                # Lesson explanation + exercise briefs
        ex01.h                   # Exercise file (you edit this)
        ex01_test.cpp            # Tests (read-only)
        ex02.h
        ex02_test.cpp
        ...
      02-namespaces/
      03-value-semantics/
      ...
    02-standard-library/
    03-types-and-generics/
    04-concurrency-and-async/
    05-real-world-patterns/
```

Each exercise compiles to its own executable. A syntax error in ex03 does not
prevent ex01 and ex02 from compiling and running.

## Course Overview

**Course 1: Foundations -- The C++ Mental Model.**
The bridge from "I know C" to "I can write correct modern C++." Compilation
model, namespaces, value semantics, const, references, strings, enums, auto,
structured bindings, casts, RAII, smart pointers, move semantics, optional/
variant/expected, and error handling.

**Course 2: The Standard Library Toolkit.**
Practical fluency with the containers, algorithms, and utilities you reach for
daily. Vectors, maps, sets, iterators, algorithms, ranges, lambdas, callables,
chrono, string processing, and filesystem.

**Course 3: Types and Generic Programming.**
Designing types, APIs, and generic code. Classes, constructors, operator
overloading, inheritance, Rule of Zero/Five, function templates, class
templates, concepts, type traits, constexpr, forwarding references, and CRTP.

**Course 4: Concurrency and Async.**
Essential for servers. Threads, mutexes, condition variables, atomics, futures,
thread pools, coroutines, and async I/O patterns.

**Course 5: Real-World Patterns for Web Development.**
Applying everything to patterns found in HTTP servers, API clients, and service
infrastructure. Builder, configuration, middleware, serialization, resource
pools, event systems, HTTP modeling, logging, error propagation, and a capstone
HTTP handler framework.

## Test Framework

The course uses `testkit`, a purpose-built single-header test framework with
zero external dependencies. Key components:

| Component | Purpose |
|-----------|---------|
| `TODO()` | Placeholder for unfinished code; tests report "skipped" |
| `TEST(runner, "name") { ... }` | Registers a test case |
| `ASSERT_EQ(a, b)` | Equality assertion with values in error output |
| `ASSERT_TRUE(expr)` | Boolean assertion |
| `ASSERT_THROWS(expr, type)` | Exception assertion |
| `TESTKIT_MAIN(runner)` | Generates `main()` |

## License

See LICENSE file for details.
