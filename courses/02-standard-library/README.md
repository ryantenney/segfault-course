# Course 2: The Standard Library Toolkit

Practical fluency with the containers, algorithms, and utilities you reach for
daily. This course covers the data structures, iteration patterns, algorithm
library, and functional programming tools that form the backbone of modern C++
development. You will also learn the ranges library (C++20) and essential
utilities for time, strings, and filesystem operations.

## Prerequisites

Complete Course 1 (Foundations) first. You should be comfortable with value
semantics, references, `const` correctness, smart pointers, move semantics,
and `std::optional`/`std::variant`. These concepts appear throughout the
standard library exercises.

## Lessons

| # | Lesson | Exercises | Description |
|---|--------|-----------|-------------|
| 14 | [vector, array, and span](14-vector-array-span/) | 8 | Dynamic arrays, fixed-size arrays, non-owning views over contiguous memory |
| 15 | [Maps, Sets, and Custom Hashing](15-maps-and-sets/) | 8 | Ordered and unordered associative containers, custom comparators and hash functions |
| 16 | [Iterators](16-iterators/) | 8 | Iterator abstraction, categories, reverse iteration, insert iterators, custom iterators |
| 17 | [Algorithms](17-algorithms/) | 8 | `sort`, `find_if`, `transform`, `accumulate`, `remove_if`, predicate composition |
| 18 | [Ranges and Views (C++20)](18-ranges-and-views/) | 8 | Lazy views, pipe syntax, `filter`, `transform`, `take`, `drop`, projections |
| 19 | [Lambdas](19-lambdas/) | 8 | Capture modes, `mutable`, generic lambdas, init-capture, IIFE |
| 20 | [std::function and Callable Objects](20-function-and-callables/) | 7 | Type-erased callables, functors, function pointers, higher-order functions |
| 21 | [Chrono](21-chrono/) | 7 | Time points, durations, clocks, duration casts, timing and sleeping |
| 22 | [String Processing](22-string-processing/) | 8 | Parsing, splitting, `std::format`, `from_chars`/`to_chars`, regex basics |
| 23 | [Filesystem](23-filesystem/) | 8 | Path manipulation, directory iteration, file metadata, portable path handling |

**Total: 10 lessons, 78 exercises**

## How to Run

```bash
# Run all tests for this course
./run course 02

# Run all tests for a specific lesson (e.g., lesson 17)
./run lesson 02-17

# Run a single exercise (e.g., lesson 17, exercise 01)
./run exercise 02-17-ex01
```

Unfinished exercises show as **skipped** (not-implemented). Completed exercises
show as **passed** or **failed**. Lessons build on each other and are best done
sequentially, though you can jump ahead if you already know a topic.
