# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

A structured, exercise-driven C++20 curriculum (~400 exercises across 52 lessons in 5 courses) targeting senior engineers transitioning to modern C++. No external dependencies — uses a custom single-header test framework (`testkit`).

## Build & Test Commands

```bash
./run build                  # Configure (if needed) + build all exercises
./run exercise 01-01-ex01    # Build & test a single exercise
./run lesson 01-01           # Build & test all exercises in a lesson
./run course 01              # Build & test all exercises in a course
./run all                    # Build & test everything
./run clean                  # Remove build directory
```

Exercise IDs follow the pattern `{course:2d}-{lesson:2d}-ex{num:2d}` (e.g., `01-03-ex05` is Course 1, Lesson 3, Exercise 5). Lesson IDs are `{course}-{lesson}` (e.g., `01-03`).

Under the hood, `./run` wraps cmake (Debug build) and ctest. First invocation auto-configures.

## Architecture

- **`testkit/include/testkit/testkit.h`** — Single-header test framework. Provides `TODO()`, `TEST()`, `ASSERT_EQ/NE/TRUE/FALSE/THROWS/NO_THROW`, `TESTKIT_MAIN()`. `TODO()` throws `testkit::not_implemented`, causing tests to report as "skipped" (not failed).
- **`courses/CMakeLists.txt`** — Defines `add_exercise(TARGET TEST_SRC [extra_srcs...])` function used by all lesson CMakeLists.
- **`CMakeLists.txt`** — Root config: C++20, strict warnings, CTest. Suppresses `-Wno-unused-parameter`, `-Wno-unused-private-field`, `-Wno-self-move`, `-Wno-self-assign-overloaded` for unfinished exercise stubs.

## Exercise Structure

Each exercise consists of:
- **`exNN.h`** (sometimes + `exNN.cpp`) — The file students edit. Contains scaffolding with `TODO()` placeholders.
- **`exNN_test.cpp`** — Read-only test file. Do not modify.
- Some exercises have supporting headers (e.g., `ex02_point.h`, `ex02_color.h`).

Exercise headers use `#pragma once` and include a comment block describing the problem, task, and learning goal.

## Course Layout

| Course | Lessons | Topics |
|--------|---------|--------|
| 01-foundations | 01–13 | Compilation model, value semantics, RAII, smart pointers, move semantics |
| 02-standard-library | 14–23 | Containers, algorithms, ranges, lambdas, chrono, filesystem |
| 03-types-and-generics | 24–34 | Classes, templates, concepts, type traits, constexpr, CRTP |
| 04-concurrency-and-async | 35–42 | Threads, mutexes, atomics, futures, coroutines |
| 05-real-world-patterns | 43–52 | Builder, middleware, serialization, HTTP modeling |

## When Implementing Exercises

- Replace `TODO()` calls with working implementations. Once `TODO()` is removed, tests switch from "skipped" to pass/fail.
- Each exercise compiles to its own executable — a broken exercise doesn't block others.
- Run `./run exercise <id>` to iterate on a single exercise; run `./run lesson <id>` to see progress across a lesson.
- Test files are read-only; only edit the exercise `.h`/`.cpp` files.
