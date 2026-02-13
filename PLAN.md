# segfault-course: Modern C++ for Experienced Engineers

## Overview

A structured, exercise-driven course for senior+ engineers who are fluent in C
syntax and control flow but need to get up to speed on modern C++ (C++17/20/23)
quickly. Focused on features and patterns that appear constantly in web library
and web application development.

**Non-goals:** This is not an intro to programming. We don't cover basic control
flow, what a pointer is, how a for-loop works, or how to compile a program. We
assume you can read C and have shipped production code in at least one
systems-adjacent language.

---

## Part 1: Project Architecture

### Toolchain

- **Compiler:** g++ 13.3 (Ubuntu 24.04) — full C++20 support, partial C++23
- **Standard:** C++20 by default, C++23 where needed (noted per-lesson)
- **Build system:** CMake 3.28 + Make
- **Test framework:** Custom lightweight `testkit` (details below)

### Directory Layout

```
segfault-course/
├── CMakeLists.txt                          # Root: sets C++ standard, adds subdirs
├── run                                     # Convenience script (see below)
├── PLAN.md                                 # This file
├── testkit/
│   ├── CMakeLists.txt                      # Header-only interface library
│   └── include/
│       └── testkit/
│           └── testkit.h                   # Test framework + TODO() macro
│
└── courses/
    ├── CMakeLists.txt                      # Adds each course subdir
    ├── 01-foundations/
    │   ├── CMakeLists.txt                  # Adds each lesson subdir
    │   ├── README.md                       # Course overview
    │   ├── 01-const-and-references/
    │   │   ├── CMakeLists.txt              # One test target per exercise
    │   │   ├── README.md                   # Concept explanation + exercise briefs
    │   │   ├── ex01.h                      # Exercise file (student edits this)
    │   │   ├── ex01_test.cpp               # Tests for ex01 (read-only)
    │   │   ├── ex02.h
    │   │   ├── ex02_test.cpp
    │   │   ├── ex03.h
    │   │   └── ex03_test.cpp
    │   ├── 02-strings/
    │   │   └── ...
    │   └── ...
    ├── 02-standard-library/
    │   └── ...
    ├── 03-types-and-generics/
    │   └── ...
    ├── 04-concurrency/
    │   └── ...
    └── 05-web-patterns/
        └── ...
```

### Exercise File Convention

The first two lessons (compilation model and namespaces) use `.h` + `.cpp` pairs
from the start — you need to see the compilation model in action before you can
understand why header-only exercises work. After that, early exercises (rest of
Courses 1-2) use **header files** (`.h`) with inline functions. This keeps the
edit-compile-test loop tight — one file to edit, one command to test.

As complexity grows (Courses 3-5), exercises expand to `.h` + `.cpp` pairs, then
to multi-file exercises with classes, and finally to small multi-class designs.

Every exercise file ships with scaffolding and `TODO()` markers:

```cpp
// ex01.h — Fix the parameter type
#pragma once
#include <string>
#include <testkit/testkit.h>

// TODO: Change the parameter to accept a const reference instead of a copy.
inline std::string greet(std::string name) {
    return "Hello, " + name + "!";
}
```

The `TODO()` macro (when used as a placeholder expression/statement) throws
`testkit::not_implemented`, which the test runner catches and reports as
**skipped** rather than **failed**. This means you can build and run tests for
an entire lesson immediately — unfinished exercises show as skipped, not as a
wall of failures.

### Test Framework: `testkit`

A purpose-built, single-header test framework. No external dependencies.

**Key components:**

| Component | Purpose |
|---|---|
| `TODO()` | Throws `not_implemented`; placeholder for unfinished code |
| `testkit::TestRunner` | Collects and runs test cases, reports pass/fail/skip |
| `TEST(runner, "name") { ... }` | Registers a test case with the runner |
| `ASSERT_EQ(a, b)` | Equality assertion with lhs/rhs in error message |
| `ASSERT_NE(a, b)` | Inequality assertion |
| `ASSERT_TRUE(expr)` | Boolean assertion |
| `ASSERT_FALSE(expr)` | Boolean assertion |
| `ASSERT_THROWS(expr, type)` | Asserts that expr throws the given type |
| `ASSERT_NO_THROW(expr)` | Asserts that expr does not throw |
| `TESTKIT_MAIN(runner)` | Generates main() that runs tests and returns exit code |

**Test output format:**

```
 Lesson 01-01: const and references

  ✓ ex01 - passes string by const reference
  ✓ ex01 - does not copy the input string
  ✗ ex02 - swaps two integers: expected 20, got 10
  ○ ex03 - returns reference to largest (not implemented)
  ○ ex03 - returned reference is const (not implemented)

 3 passed, 1 failed, 2 skipped
```

**Design rationale:** Catch2 and Google Test are industry-standard, but a
custom framework here means (a) zero dependency management, (b) we can tailor
skip/not-implemented semantics exactly, (c) students read and understand the
framework itself as a learning exercise, and (d) we avoid pulling in a large
header that slows compilation of 150+ tiny exercise targets.

### Build System Details

**Root CMakeLists.txt:**
- Sets `CMAKE_CXX_STANDARD 20`, `CMAKE_CXX_STANDARD_REQUIRED ON`
- Enables warnings: `-Wall -Wextra -Wpedantic -Werror=return-type`
- Adds `testkit` and `courses` subdirectories
- Enables CTest

**Per-lesson CMakeLists.txt** pattern:
```cmake
# Helper function defined once at the courses level:
# add_exercise(TARGET_NAME TEST_SOURCE EXERCISE_DEPS...)
# - Creates an executable from the test source
# - Links testkit
# - Registers with CTest

add_exercise(01-01-ex01 ex01_test.cpp)
add_exercise(01-01-ex02 ex02_test.cpp)
add_exercise(01-01-ex03 ex03_test.cpp)
```

Each exercise compiles to its own executable. This means a syntax error in ex03
doesn't prevent ex01 and ex02 from compiling and running.

### Build System Literacy

This course uses CMake, but we don't dedicate a full lesson to it. Instead:

- The root `CMakeLists.txt` and the `add_exercise()` helper are documented inline
  with comments explaining every directive.
- The course READMEs reference specific CMake patterns when relevant (e.g., when
  exercises expand to `.h` + `.cpp` pairs, the README explains the corresponding
  CMake target change).
- A senior engineer should be able to modify the build files after reading the
  commented examples — the CMake used here is intentionally minimal.

### Convenience Runner Script

`./run` — a bash script wrapping cmake/ctest:

```
Usage:
  ./run build                  # Configure + build all exercises
  ./run lesson 01-03           # Build & test course 01, lesson 03
  ./run exercise 01-03-ex02    # Build & test a single exercise
  ./run course 01              # Build & test all of course 01
  ./run all                    # Build & test everything
  ./run clean                  # Remove build directory
```

First invocation auto-runs cmake configure. Subsequent runs only rebuild
changed files.

---

## Part 2: Course Curriculum

### Progression Philosophy

Exercises start trivially small and grow:

| Phase | What you write | Example |
|---|---|---|
| Lessons 1-7 | Fix a single statement or expression | Change a parameter type, add `const`, fix a cast |
| Lessons 8-14 | Fill in a function body (2-8 lines) | Implement a swap, a lookup, a transform |
| Lessons 15-23 | Write a complete function | String parser, algorithm pipeline |
| Lessons 24-34 | Refactor code to be more idiomatic | Raw pointers → smart pointers, C-style → ranges |
| Lessons 35-42 | Implement a class or component | Thread pool, connection pool, event emitter |
| Lessons 43-52 | Multi-class design | Middleware chain, HTTP handler framework |

---

### Course 1: Foundations — The C++ Mental Model

The bridge from "I know C" to "I can write correct modern C++." Starts with
the compilation model and organizational primitives that have no analog in
Java or Rust, then covers the type system, memory model, and ownership
semantics that every line of C++ code depends on.

---

#### Lesson 01: The C++ Compilation Model

**Concept:** Translation units, header files vs source files, the One Definition
Rule (ODR), `#pragma once` / include guards, forward declarations, `#include`
mechanics. Internal vs external linkage (`static`, anonymous namespaces, `extern`).
`inline` functions and variables (C++17). Brief awareness of C++20 modules.

*This is the lesson with no analog in Java or Rust. Without it, the exercise
file structure won't make sense.*

| # | Exercise | What you do |
|---|---|---|
| 1 | Fix include guards | Add `#ifndef`/`#define`/`#endif` guards to a header that causes duplicate-definition link errors |
| 2 | Pragma once | Replace verbose include guards with `#pragma once` in multiple headers |
| 3 | Forward declarations | Break a circular `#include` dependency using forward declarations |
| 4 | Header/source split | Move a function implementation from a `.h` to a `.cpp` file; fix the build |
| 5 | Inline function | Fix a "multiple definition" link error by marking a header-defined function `inline` |
| 6 | Extern variables | Declare a global in a header with `extern`; define it in exactly one `.cpp` |
| 7 | Internal linkage | Fix an ODR violation using anonymous namespace; understand the difference from `static` |
| 8 | Multi-TU build | Given 3 source files with interdependencies, fix the include graph so it compiles and links |

---

#### Lesson 02: Namespaces

**Concept:** `namespace`, nested namespaces (C++17 `A::B::C` syntax),
`using` declarations vs `using` directives (and why `using namespace std;`
is harmful), anonymous namespaces for internal linkage, argument-dependent
lookup (ADL) and when it surprises you.

| # | Exercise | What you do |
|---|---|---|
| 1 | Wrap in a namespace | Put free functions inside a namespace; fix the call sites |
| 2 | Nested namespaces | Convert verbose nested `namespace a { namespace b { ... }}` to C++17 `a::b` syntax |
| 3 | Using declarations | Add targeted `using` declarations for specific symbols from a namespace |
| 4 | Fix using-namespace pollution | Replace `using namespace std` with specific `using` declarations; fix the compile errors |
| 5 | Anonymous namespace | Move implementation-detail helpers into an anonymous namespace to hide them from other TUs |
| 6 | Namespace alias | Create a short alias for a deeply nested namespace; use it to simplify call sites |
| 7 | ADL basics | Predict which overload is called when ADL kicks in; fix unexpected behavior |
| 8 | ADL-friendly swap | Implement the two-step `using std::swap; swap(a, b);` idiom for generic code |

---

#### Lesson 03: Value Semantics, `const`, and References

**Concept:** The fundamental mental model shift from Java/Rust: in C++,
everything is a value by default. Objects live on the stack, assignment copies,
function parameters copy. lvalue references, `const` qualification, `const`
references as the default parameter-passing strategy.

*The README should explicitly name the "value semantics vs reference semantics"
mental model and contrast with Java (everything is a heap-allocated reference)
and Rust (ownership system prevents accidental copies).*

| # | Exercise | What you do |
|---|---|---|
| 1 | Prove value semantics | Show that assignment copies by modifying the copy and checking the original is unchanged |
| 2 | Fix a parameter type | Change `std::string name` → `const std::string& name` to avoid a copy |
| 3 | Const-qualify a method | Add `const` to a getter method that doesn't modify state |
| 4 | Const correctness chain | Fix a chain of three functions that should all be const-correct but aren't |
| 5 | Swap via references | Implement a `swap(int&, int&)` function body (3 lines) |
| 6 | Return a const reference | Return `const T&` to the largest element in a vector |
| 7 | Reference vs pointer parameter | Convert a pointer-based API (`int* out`) to use references; fix the call sites |
| 8 | Dangling reference | Identify and fix a function that returns a reference to a local variable |

---

#### Lesson 04: Strings and String Views

**Concept:** `std::string` vs `std::string_view`, when to use each, implicit
conversions, lifetime pitfalls.

| # | Exercise | What you do |
|---|---|---|
| 1 | String basics | Construct strings using different methods; use `size()`, `empty()`, `clear()` |
| 2 | Fix string copies | Change functions taking `const std::string&` to `std::string_view` where safe |
| 3 | Substring without allocation | Use `string_view::substr` to extract a portion without heap allocation |
| 4 | Build a string | Use `std::string` `+` operator and `append` to assemble formatted output |
| 5 | Find and extract | Use `find()`, `rfind()`, and `substr()` to parse a delimited string |
| 6 | String comparison | Implement case-insensitive comparison using `std::tolower` + `std::equal` |
| 7 | Dangling view | Identify and fix a function returning a dangling `string_view` |
| 8 | View lifetime traps | Given several `string_view` uses, mark which are safe and fix the ones that dangle |

---

#### Lesson 05: Scoped Enums and Strong Types

**Concept:** `enum class` vs C-style `enum`, underlying types, converting to/from
integers, using enums for type safety.

| # | Exercise | What you do |
|---|---|---|
| 1 | Convert a C enum to enum class | Change `enum Color` to `enum class Color` and fix call sites |
| 2 | Enum with explicit underlying type | Define an enum class with `uint8_t` backing for a wire format |
| 3 | Enum to string | Write a `to_string` function using a switch over an enum class |
| 4 | String to enum | Write a `from_string` that returns `std::optional<Enum>` for invalid input |
| 5 | Enum as bitflags | Define an enum class for permissions; overload `\|` and `&` for combining/testing flags |
| 6 | Scoped enum in switch | Use an enum class in a switch; get the compiler to warn about unhandled cases |
| 7 | Strong typedef | Create a wrapper struct to distinguish `UserId` from `OrderId` (both wrapping `int`) |

---

#### Lesson 06: `auto`, Type Deduction, and Type Aliases

**Concept:** `auto` for variables, return types, and range-for loops. `decltype`.
When `auto` helps and when explicit types are clearer. Type aliases with
`using` vs `typedef`.

| # | Exercise | What you do |
|---|---|---|
| 1 | Replace explicit types with `auto` | Simplify verbose iterator declarations using `auto` |
| 2 | `auto` with const/reference | Predict and fix type deduction with `const auto&` vs `auto` vs `auto&` |
| 3 | `auto` in range-for | Simplify range-for loops using `auto`, `const auto&`, and `auto&&` |
| 4 | Trailing return types | Convert functions to trailing return type syntax (`auto f() -> T`) |
| 5 | `decltype` for expression types | Use `decltype` to declare a variable matching another expression's type |
| 6 | Replace typedef with using | Convert `typedef` declarations to `using` aliases |
| 7 | Template alias | Write a `using` template alias to simplify a common partial specialization |
| 8 | `auto` return type | Write functions with deduced return types; verify the deduction is what you expect |

---

#### Lesson 07: Structured Bindings

**Concept:** `auto [a, b] = ...` for pairs, tuples, structs, and map iteration.

| # | Exercise | What you do |
|---|---|---|
| 1 | Decompose a pair | Use structured binding to unpack `std::pair` from a map insert |
| 2 | Iterate a map | Use structured bindings in a range-for over `std::map` |
| 3 | Unpack a struct | Bind fields of a returned struct |
| 4 | Tuple decomposition | Unpack a `std::tuple` from a function returning multiple values |
| 5 | Binding with const/reference | Use `const auto&` and `auto&` in structured bindings; understand which copies and which doesn't |
| 6 | If-init with binding | Combine structured bindings with `if`-statement initializer (`if (auto [it, ok] = ...; ok)`) |
| 7 | Multi-return function | Write a function returning a struct with named fields; decompose it at the call site |

---

#### Lesson 08: C++ Casts

**Concept:** The four C++ cast operators: `static_cast`, `dynamic_cast`,
`const_cast`, `reinterpret_cast`. When to use each. Why C-style casts are
dangerous (they try multiple cast types silently). Coming from Java's single
`(Type)` cast, this needs explicit coverage.

| # | Exercise | What you do |
|---|---|---|
| 1 | Identify the right cast | Given several C-style casts, name which C++ cast each should use (no code change) |
| 2 | Replace C-style casts | Convert all C-style casts in a file to the correct C++ cast |
| 3 | Numeric and enum casts | Use `static_cast` for int↔double, int↔enum, and narrowing conversions |
| 4 | Safe downcasting (pointer) | Use `dynamic_cast<Derived*>` on a base pointer; handle the null case |
| 5 | Safe downcasting (reference) | Use `dynamic_cast<Derived&>` on a base reference; catch `std::bad_cast` |
| 6 | `const_cast` for legacy APIs | Use `const_cast` to call a C API that takes non-const but doesn't modify |
| 7 | Cast in a class hierarchy | Choose between `static_cast` and `dynamic_cast` for upcasts vs downcasts |
| 8 | Eliminate a cast | Refactor code to remove the need for a cast entirely by redesigning the API |

---

#### Lesson 09: RAII and Scope-Based Lifetime

**Concept:** Resource Acquisition Is Initialization. Constructors acquire,
destructors release. Deterministic cleanup. Comparison with Java's
try-with-resources and Rust's `Drop`.

| # | Exercise | What you do |
|---|---|---|
| 1 | Write a scoped timer | Implement a class that records start time in ctor, prints elapsed in dtor |
| 2 | File handle wrapper | Wrap a `FILE*` in an RAII class with open-in-ctor, close-in-dtor |
| 3 | Scoped lock (manual) | Implement a simplified `lock_guard` that locks in ctor, unlocks in dtor |
| 4 | Prove cleanup order | Fill in expected output for nested RAII objects (destruction is reverse of construction) |
| 5 | RAII for C allocation | Wrap `malloc`/`free` in an RAII class; ensure cleanup on all exit paths |
| 6 | Scope guard | Implement a generic `ScopeGuard` that runs any callable on destruction |
| 7 | RAII survives exceptions | Prove that destructors run even when an exception propagates through the scope |
| 8 | Non-copyable RAII | Make an RAII wrapper non-copyable (`= delete`); explain why copying would be a bug |

---

#### Lesson 10: Smart Pointers

**Concept:** `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`.
`std::make_unique`, `std::make_shared`. Ownership semantics.

| # | Exercise | What you do |
|---|---|---|
| 1 | Create a unique_ptr | Use `make_unique` to create and use a unique_ptr; observe automatic cleanup |
| 2 | Raw to unique_ptr | Refactor `new`/`delete` code to use `make_unique` |
| 3 | Transfer ownership | Pass a `unique_ptr` to a function via `std::move` |
| 4 | unique_ptr in containers | Store `unique_ptr`s in a `vector`; transfer elements between containers |
| 5 | Shared ownership | Use `shared_ptr` for a cache where multiple readers hold references |
| 6 | shared_ptr aliasing | Use the aliasing constructor to point into a member of a shared object |
| 7 | Break a cycle with weak_ptr | Fix a memory leak caused by circular `shared_ptr` references |
| 8 | Custom deleter | Use `unique_ptr` with a custom deleter to wrap a C resource (e.g., `fclose`) |

---

#### Lesson 11: Move Semantics

**Concept:** Rvalue references, `std::move`, move constructors, move assignment.
When and why the compiler moves. The "moved-from" state.

| # | Exercise | What you do |
|---|---|---|
| 1 | Move a string into a container | Use `std::move` to avoid copying when inserting into a vector |
| 2 | Move a local into a return | Use `std::move` to transfer a local string into a struct field |
| 3 | Write a move constructor | Implement a move ctor for a class owning a `unique_ptr` |
| 4 | Move assignment operator | Implement move assignment with proper self-assignment guard |
| 5 | Moved-from state | Demonstrate that a moved-from object is valid but unspecified; re-assign and reuse it |
| 6 | Move-only type | Create a class that can be moved but not copied; store it in a vector |
| 7 | Return value optimization | Predict which calls trigger copy vs. move vs. RVO (fill in expected output) |
| 8 | Move in algorithms | Use `std::move` (the algorithm) to bulk-transfer elements between containers |

---

#### Lesson 12: `optional`, `variant`, and `expected`

**Concept:** Sum types in C++. `std::optional<T>` for nullable values,
`std::variant<Ts...>` for tagged unions, `std::expected<T,E>` (C++23) for
result types. Comparison with Rust's `Option`/`Result` and Java's `Optional`.

| # | Exercise | What you do |
|---|---|---|
| 1 | Return optional from lookup | Change a function from returning sentinel/-1 to `std::optional` |
| 2 | Optional with value_or | Use `value_or` to provide a default when the optional is empty |
| 3 | Chain optional operations | Use `transform`/`and_then` (C++23) or manual checks to chain lookups |
| 4 | Variant basics | Store different types in a `std::variant`; access with `get` and `get_if` |
| 5 | std::visit | Use `std::visit` with a visitor to process a variant |
| 6 | Overloaded visitor | Implement the `overloaded{lambdas...}` pattern for concise visiting |
| 7 | Error handling with expected | Rewrite a throwing function to return `std::expected<T, Error>` |
| 8 | Expected chaining | Chain multiple `expected`-returning operations using `and_then`/`transform` |

---

#### Lesson 13: Error Handling Patterns

**Concept:** Exceptions vs. error codes vs. `expected`. When to use each.
`noexcept`. Exception safety guarantees.

| # | Exercise | What you do |
|---|---|---|
| 1 | Throw and catch | Write a function that throws `std::runtime_error`; catch it at the call site |
| 2 | Custom exception class | Define a custom exception inheriting from `std::runtime_error` with extra context |
| 3 | Multiple catch blocks | Catch different exception types in the correct order (most-derived first) |
| 4 | Exception safety with RAII | Make a function exception-safe by replacing raw `new`/`delete` with RAII |
| 5 | Convert exceptions to expected | Wrap a throwing function in a `try`/`catch` that returns `expected` |
| 6 | `noexcept` correctness | Mark functions `noexcept` where appropriate; fix one that lies |
| 7 | Exception vs error code | Implement the same operation both ways; compare the calling code |
| 8 | Nested exceptions | Use `std::throw_with_nested` / `rethrow_if_nested` to add error context |

---

### Course 2: The Standard Library Toolkit

Practical fluency with the containers, algorithms, and utilities you reach
for daily.

---

#### Lesson 14: `vector`, `array`, and `span`

**Concept:** Dynamic arrays, fixed-size arrays, and non-owning views over
contiguous memory. `std::span` as the modern way to accept "some contiguous
elements."

| # | Exercise | What you do |
|---|---|---|
| 1 | Populate a vector | Use `push_back`, `emplace_back`, and initializer-list construction |
| 2 | Reserve and capacity | Use `reserve` to preallocate; observe `size()` vs `capacity()` behavior |
| 3 | Bounds-safe access | Replace `operator[]` with `.at()` and handle `std::out_of_range` |
| 4 | Vector of objects | Store custom structs in a vector; access and modify them |
| 5 | Erase elements | Use the erase-remove idiom (and C++20 `std::erase_if`) to filter a vector |
| 6 | Fixed-size with std::array | Replace a C array with `std::array`; use `.size()` and bounds checking |
| 7 | Accept a span parameter | Change a function from `const vector<int>&` to `std::span<const int>` |
| 8 | Span from different sources | Create `std::span`s from a vector, a C array, and a `std::array`; pass all to one function |

---

#### Lesson 15: Maps, Sets, and Custom Hashing

**Concept:** `std::map`, `std::unordered_map`, `std::set`, `std::unordered_set`.
Ordered vs. unordered. `insert`, `emplace`, `try_emplace`, `contains`. Writing
a custom hash function for use with unordered containers.

| # | Exercise | What you do |
|---|---|---|
| 1 | Word frequency counter | Use `unordered_map<string, int>` to count word occurrences |
| 2 | Safe lookup | Use `find()` / `contains()` instead of `operator[]` for non-mutating lookup |
| 3 | Insert or update | Use `insert_or_assign` to upsert a value |
| 4 | try_emplace for lazy init | Use `try_emplace` to insert-or-get in one operation |
| 5 | Ordered set operations | Use `std::set` to deduplicate and iterate in sorted order |
| 6 | Custom comparator | Use `std::map` with a custom comparator for case-insensitive key ordering |
| 7 | Multimap | Use `std::multimap` for a one-to-many relationship (e.g., tag → items) |
| 8 | Custom hash function | Write a custom hash + equality for `unordered_map` with a struct key |

---

#### Lesson 16: Iterators

**Concept:** The iterator abstraction. `begin()`/`end()`, iterator categories,
`std::next`/`std::prev`/`std::advance`. Why iterators matter as the bridge
between containers and algorithms.

| # | Exercise | What you do |
|---|---|---|
| 1 | Manual iteration | Use iterators to traverse a `std::list` and modify elements |
| 2 | Const iteration | Use `cbegin()`/`cend()` for read-only traversal; fix code that accidentally mutates |
| 3 | Erase while iterating | Correctly erase elements from a map during iteration (use the return value of `erase`) |
| 4 | Reverse iteration | Use `rbegin()`/`rend()` to traverse a container backwards |
| 5 | Iterator arithmetic | Use `std::next`, `std::advance`, and `std::distance` to navigate |
| 6 | Back-inserter | Use `std::back_inserter` to write algorithm output into a vector |
| 7 | Insert iterator | Use `std::inserter` with a position hint for ordered containers |
| 8 | Custom iterator | Implement `begin()`/`end()` for a custom range class so it works in range-for |

---

#### Lesson 17: Algorithms

**Concept:** The `<algorithm>` header. `sort`, `find`, `find_if`, `count_if`,
`transform`, `accumulate`, `remove_if` + erase idiom, `any_of`/`all_of`/`none_of`.

| # | Exercise | What you do |
|---|---|---|
| 1 | Sort and search | Sort a vector, then use `lower_bound` to binary search |
| 2 | Find and count | Use `find_if` and `count_if` with a predicate |
| 3 | Transform elements | Use `std::transform` to apply a function to each element, output to a new container |
| 4 | Filter with remove-erase | Use `remove_if` + `erase` to filter elements from a vector |
| 5 | Copy_if | Copy elements matching a predicate to a new container |
| 6 | Accumulate and reduce | Use `std::accumulate` to compute a sum, product, and custom fold |
| 7 | Min/max and partition | Use `min_element`, `max_element`, and `partition` on a range |
| 8 | Predicate composition | Combine `any_of`, `all_of`, `none_of` for complex queries |

---

#### Lesson 18: Ranges and Views (C++20)

**Concept:** The ranges library. `std::ranges::sort`, views as lazy
transformations, pipe syntax, `filter`, `transform`, `take`, `drop`.

| # | Exercise | What you do |
|---|---|---|
| 1 | Ranges sort and find | Rewrite classic algorithm calls using `std::ranges::` versions |
| 2 | Filter view | Use `views::filter` to lazily select elements matching a predicate |
| 3 | Transform view | Use `views::transform` to lazily apply a function to each element |
| 4 | Filter-transform pipeline | Chain `views::filter \| views::transform` using pipe syntax |
| 5 | Take and drop | Use `views::take` and `views::drop` to slice a range |
| 6 | Custom projection | Use the `proj` parameter in ranges algorithms to sort/find by a member |
| 7 | Compose a multi-stage pipeline | Build a 3+ stage view pipeline; materialize the result into a vector |
| 8 | Split and join | Use `views::split` to tokenize a string view; collect the parts |

---

#### Lesson 19: Lambdas

**Concept:** Lambda expressions. Capture by value, by reference, by move.
`mutable` lambdas. Generic lambdas with `auto`. Immediately-invoked lambdas
for complex initialization.

| # | Exercise | What you do |
|---|---|---|
| 1 | Basic lambda predicate | Write a lambda for `std::sort` custom comparison |
| 2 | Capture by reference | Write a counting lambda that modifies an outer variable |
| 3 | Capture by value | Capture by value with `mutable`; show the original is unchanged |
| 4 | Capture by move | Capture a `unique_ptr` into a lambda using init-capture (`[p = std::move(p)]`) |
| 5 | Generic lambda | Write an `auto`-parameter lambda that works with multiple types |
| 6 | Lambda returning lambda | Write a factory function that returns a configured lambda |
| 7 | IIFE for initialization | Use an immediately-invoked lambda to initialize a `const` variable with complex logic |
| 8 | Stateful comparator | Write a stateful lambda that changes sort behavior based on captured config |

---

#### Lesson 20: `std::function` and Callable Objects

**Concept:** Type-erased callables. `std::function`, function pointers, functors
(classes with `operator()`). When to use each. Performance tradeoffs.

| # | Exercise | What you do |
|---|---|---|
| 1 | Callback registration | Accept a `std::function<void(int)>` callback and invoke it |
| 2 | Functor class | Write a functor (class with `operator()`) that maintains state across invocations |
| 3 | Function pointer | Pass a plain function pointer where `std::function` isn't needed |
| 4 | Store callbacks in a container | Build a `vector<std::function<...>>` and invoke all callbacks |
| 5 | Template parameter vs type erasure | Refactor a `std::function` parameter to a template parameter; compare codegen |
| 6 | Replace std::bind with lambda | Convert `std::bind` expressions to equivalent (and clearer) lambdas |
| 7 | Higher-order function | Write a function that takes a callable and returns a new callable (e.g., memoize, retry) |

---

#### Lesson 21: Chrono

**Concept:** `std::chrono` — time points, durations, clocks.
`system_clock`, `steady_clock`. Duration casts. Formatting.

| # | Exercise | What you do |
|---|---|---|
| 1 | Measure elapsed time | Use `steady_clock` to time a function call and print the duration |
| 2 | Duration types | Declare durations in different units; compare `milliseconds`, `seconds`, `minutes` |
| 3 | Duration arithmetic | Add, subtract, and convert between duration types using `duration_cast` |
| 4 | Timeout check | Implement a function that checks if a deadline has passed |
| 5 | Periodic check | Implement a loop that fires an action every N milliseconds using chrono |
| 6 | Format a timestamp | Convert a `system_clock::time_point` to a human-readable string |
| 7 | Sleep with chrono | Use `std::this_thread::sleep_for` and `sleep_until` with chrono durations |

---

#### Lesson 22: String Processing

**Concept:** String manipulation utilities, `std::stoi`/`std::stod`, `std::to_string`,
`std::format` (C++20), `std::from_chars`/`std::to_chars`. Basic regex.

| # | Exercise | What you do |
|---|---|---|
| 1 | Parse key-value pairs | Split "key=value" strings using `find` and `substr` |
| 2 | Split a string | Implement a `split(str, delimiter)` function returning a `vector<string>` |
| 3 | Number conversion | Use `from_chars`/`to_chars` for locale-independent int/double conversion |
| 4 | Format strings | Use `std::format` to build formatted output with positional args |
| 5 | Trim whitespace | Implement `trim`, `ltrim`, `rtrim` using `find_first/last_not_of` |
| 6 | Case conversion | Implement `to_lower`/`to_upper` for ASCII strings using `std::transform` |
| 7 | Simple regex match | Use `std::regex` to validate a pattern (e.g., email-like format) |
| 8 | Regex capture groups | Use `std::smatch` to extract named parts from a patterned string |

---

#### Lesson 23: Filesystem

**Concept:** `std::filesystem` — paths, existence checks, directory iteration,
file operations. Portable path handling.

| # | Exercise | What you do |
|---|---|---|
| 1 | Path construction | Join paths using `/` operator; observe platform-correct separators |
| 2 | Path decomposition | Extract `stem()`, `extension()`, `parent_path()`, `filename()` from a path |
| 3 | Existence and type checks | Use `exists()`, `is_regular_file()`, `is_directory()` to inspect the filesystem |
| 4 | Directory listing | Iterate over `directory_iterator` entries and filter by extension |
| 5 | Recursive listing | Use `recursive_directory_iterator` to walk a tree; skip hidden directories |
| 6 | File size and timestamps | Get `file_size()` and `last_write_time()`; compare modification times |
| 7 | Create directory tree | Use `create_directories()` and handle errors with `std::error_code` |
| 8 | Temp directory with RAII | Create a temporary working directory; clean it up automatically using RAII |

---

### Course 3: Types and Generic Programming

Designing types, APIs, and generic code. Where C++ diverges most
from Java and Rust.

---

#### Lesson 24: Classes and Encapsulation

**Concept:** `struct` vs `class` (only default access differs), access specifiers,
member functions, `this` pointer. Data hiding and API design.

| # | Exercise | What you do |
|---|---|---|
| 1 | struct vs class | Change a `struct` to a `class`; fix the access errors that result |
| 2 | Add access specifiers | Organize a class into `public`, `private`, and `protected` sections |
| 3 | Getter methods | Implement `const` getter methods for private data |
| 4 | Setter with validation | Implement setters that enforce constraints (e.g., non-empty name) |
| 5 | Invariant enforcement | Ensure a class's internal state is always valid via constructor + method design |
| 6 | Static member variable | Add a static member to count instances; increment in ctor, decrement in dtor |
| 7 | Static factory method | Add a named `static` factory method as an alternative to constructors |
| 8 | Friend function | Grant a non-member `operator<<` access to private members using `friend` |

---

#### Lesson 25: Constructors, Initialization, and the Minefield

**Concept:** Default, parameterized, and delegating constructors. Member
initializer lists. `explicit`. In-class member initializers. Aggregate init.

**The initialization minefield:** C++ has the most complex initialization story
of any mainstream language. This lesson covers the traps: direct init `()` vs
list init `{}` vs copy init `=`, narrowing conversions, `std::initializer_list`
ambiguity (`vector<int>{10}` vs `vector<int>(10)`), and the most vexing parse.

| # | Exercise | What you do |
|---|---|---|
| 1 | Member initializer list | Fix a class to use initializer list instead of assignment in body |
| 2 | In-class member initializers | Add default values to member declarations; observe when they apply |
| 3 | Delegating constructors | Refactor duplicated init logic using constructor delegation |
| 4 | Explicit constructors | Fix implicit conversion bugs by adding `explicit` |
| 5 | Default constructor control | Observe when you lose the implicit default ctor; restore it with `= default` |
| 6 | Aggregate initialization | Design a config struct that supports aggregate init (and designated initializers) |
| 7 | Direct vs list initialization | Predict the result of `()` vs `{}` init; fix narrowing conversion errors |
| 8 | `initializer_list` ambiguity | Distinguish `vector<int>{10}` from `vector<int>(10)`; fix the intent |
| 9 | Most vexing parse | Identify and fix a declaration that's parsed as a function instead of an object |

---

#### Lesson 26: Operator Overloading

**Concept:** Overloading `==`, `<=>` (spaceship), `<<` (stream insertion),
`[]`, and arithmetic operators. C++20's defaulted comparisons.

| # | Exercise | What you do |
|---|---|---|
| 1 | Equality operator | Implement `operator==` for a struct (member-by-member) |
| 2 | Defaulted equality | Use `= default` for `operator==`; verify it works for simple aggregates |
| 3 | Spaceship operator | Use `<=>` to get all six comparison operators for free |
| 4 | Arithmetic operators | Implement `operator+` and `operator+=` for a numeric wrapper type |
| 5 | Stream insertion | Implement `operator<<` for debug/log output of a class |
| 6 | Stream extraction | Implement `operator>>` to parse a class from an input stream |
| 7 | Subscript operator | Implement `operator[]` with both const and non-const overloads |
| 8 | Function call operator | Implement `operator()` to make a class usable as a functor |

---

#### Lesson 27: Inheritance and Polymorphism

**Concept:** Single inheritance, `virtual` functions, `override`, `final`,
pure virtual (abstract classes). Virtual destructors.

| # | Exercise | What you do |
|---|---|---|
| 1 | Basic inheritance | Derive a class from a base; access inherited members |
| 2 | Virtual method dispatch | Add a `virtual` method to the base; override it in derived; call through a base pointer |
| 3 | Abstract interface | Define a pure virtual interface; implement it in two concrete classes |
| 4 | Virtual destructor | Fix a memory leak caused by deleting a derived object through a base pointer |
| 5 | Override keyword | Use `override` to catch a signature mismatch the compiler would otherwise miss |
| 6 | Final keyword | Use `final` on a class and a method; observe what errors it prevents |
| 7 | Object slicing | Demonstrate slicing by assigning derived to base by value; fix with references/pointers |
| 8 | Protected members | Use `protected` to share implementation details between base and derived |

---

#### Lesson 28: Rule of Zero / Five

**Concept:** When to write special member functions (copy/move ctor, copy/move
assignment, destructor) and when to rely on compiler defaults. The Rule of
Zero (prefer it) and Rule of Five (when you must manage a resource).

| # | Exercise | What you do |
|---|---|---|
| 1 | Spot the bug | Identify a class that has a destructor but no copy ctor/assignment (Rule of Three violation) |
| 2 | Rule of Zero | Refactor the class to use smart pointers, eliminating all special members |
| 3 | Deleted copy | Disable copying for a resource-owning class using `= delete` |
| 4 | Default keyword | Use `= default` to explicitly request compiler-generated members |
| 5 | Rule of Five | Implement all five special members for a class wrapping a C resource |
| 6 | Copy-and-swap idiom | Implement copy assignment using the swap idiom for strong exception safety |
| 7 | Move-only type | Build a non-copyable, move-only resource wrapper; use it in a container |
| 8 | Rule of Zero with composition | Show that composing well-behaved member types gives Rule of Zero for free |

---

#### Lesson 29: Function Templates

**Concept:** Template functions. Type parameter deduction. Multiple type params.
Non-type template parameters.

| # | Exercise | What you do |
|---|---|---|
| 1 | Generic max function | Write a `max_of(T a, T b)` template |
| 2 | Multiple type parameters | Write a `convert<To>(From val)` template |
| 3 | Non-type template parameter | Write a `fixed_buffer<size_t N>` with compile-time size |
| 4 | Template argument deduction | Fix call sites that need explicit template arguments vs. those that don't |
| 5 | Explicit specialization | Specialize a template function for `std::string` with different behavior |
| 6 | Overload vs specialization | Show that a non-template overload is preferred over a specialization; refactor accordingly |
| 7 | Default template parameter | Add a default template parameter for a comparator/policy |
| 8 | Variadic template intro | Write a simple variadic `print(args...)` that prints all arguments |

---

#### Lesson 30: Class Templates

**Concept:** Template classes. Member function definitions. Template
specialization. Class template argument deduction (CTAD).

| # | Exercise | What you do |
|---|---|---|
| 1 | Generic stack | Implement `Stack<T>` backed by `std::vector` with `push`, `pop`, `top` |
| 2 | Member functions out-of-line | Move `Stack<T>` member function definitions outside the class body |
| 3 | Key-value pair | Implement `Pair<K, V>` with comparison operators |
| 4 | CTAD guide | Add a deduction guide so `Pair{1, "hello"}` works without explicit types |
| 5 | Partial specialization | Specialize a `Serializer<T>` template for pointer types |
| 6 | Full specialization | Fully specialize `Serializer<std::string>` with custom logic |
| 7 | Static member per instantiation | Add a `static` counter to a class template; show each `T` has its own count |
| 8 | Dependent type names | Fix a template that fails to compile because of missing `typename` for dependent types |

---

#### Lesson 31: Concepts and Constraints (C++20)

**Concept:** `concept`, `requires` clause, `requires` expression.
Constraining templates for better error messages and API design.

| # | Exercise | What you do |
|---|---|---|
| 1 | Simple concept | Write a `Numeric` concept and use it to constrain a function template |
| 2 | Compound requirements | Write a concept requiring `<`, `==`, and a `.to_string()` method |
| 3 | Requires clause on function | Add a `requires` clause to an existing template to restrict valid types |
| 4 | Constrained class template | Constrain a container adaptor to work only with types satisfying a concept |
| 5 | Concept-based overloading | Use concepts to select between two function overloads |
| 6 | Standard library concepts | Use `std::integral`, `std::floating_point`, `std::convertible_to` from `<concepts>` |
| 7 | Subsumption ordering | Define general and refined concepts; show the compiler picks the most constrained match |
| 8 | Ad-hoc requires expression | Use an inline `requires` expression (not a named concept) to constrain one function |

---

#### Lesson 32: Type Traits and `constexpr`

**Concept:** `<type_traits>` — `is_same_v`, `is_integral_v`, `decay_t`,
`remove_reference_t`. `constexpr` functions, `if constexpr`, `static_assert`.

| # | Exercise | What you do |
|---|---|---|
| 1 | static_assert with type traits | Add compile-time checks that template args meet requirements |
| 2 | if constexpr branching | Use `if constexpr` to select code paths based on type properties |
| 3 | constexpr function | Write a compile-time-evaluable function and verify with `static_assert` |
| 4 | constexpr variable | Compute a lookup table at compile time using `constexpr` |
| 5 | Type manipulation | Use `remove_reference_t` / `decay_t` to normalize types in a template |
| 6 | Enable_if (legacy) | Use `std::enable_if_t` for SFINAE; then rewrite the same constraint using concepts |
| 7 | consteval | Write an immediate function (`consteval`) that must be evaluated at compile time |
| 8 | constexpr with std::array | Use `constexpr` to build and process a `std::array` entirely at compile time |

---

#### Lesson 33: Forwarding References and Perfect Forwarding

**Concept:** `T&&` in template context is a forwarding reference, not an rvalue
reference. `std::forward` for perfect forwarding. Reference collapsing rules.
Essential for writing generic wrappers, factory functions, and understanding
`emplace`-style APIs.

| # | Exercise | What you do |
|---|---|---|
| 1 | Forwarding vs rvalue reference | Identify which `T&&` parameters are forwarding refs vs rvalue refs in given code |
| 2 | Reference collapsing | Predict the resulting type from `T& &&`, `T&& &&`, etc. (fill-in-the-blank) |
| 3 | Perfect forwarding wrapper | Write a `log_and_call(f, args...)` that forwards all arguments without copies |
| 4 | Forward to constructor | Forward arguments through a wrapper to construct an object in place |
| 5 | Emplace with forwarding | Write a container `emplace_back` method using perfect forwarding |
| 6 | Factory function | Write a `make<T>(args...)` that perfectly forwards constructor arguments |
| 7 | Variadic forwarding | Forward a parameter pack to another function, preserving value category of each arg |
| 8 | decltype(auto) return | Use `decltype(auto)` to perfectly preserve the return type in a forwarding wrapper |

---

#### Lesson 34: CRTP and Mixin Patterns

**Concept:** Curiously Recurring Template Pattern for static polymorphism.
Mixin classes. Composition vs. inheritance with templates.

| # | Exercise | What you do |
|---|---|---|
| 1 | CRTP counter | Implement a CRTP base that counts instances of each derived class |
| 2 | Static interface | Use CRTP to enforce a static interface without virtual dispatch |
| 3 | CRTP for operator generation | Use a CRTP base to auto-generate `!=` from `==` (pre-C++20 pattern) |
| 4 | Mixin for logging | Write a logging mixin that adds `.log()` to any class via CRTP |
| 5 | Composable policies | Build a type by composing template-parameterized policy classes (e.g., storage + threading) |
| 6 | CRTP vs virtual | Rewrite a virtual-dispatch hierarchy using CRTP; compare the call overhead |
| 7 | Multiple mixin bases | Compose two mixin templates into a single derived class |

---

### Course 4: Concurrency and Async

Essential for web servers. Thread management, synchronization, and async
patterns.

---

#### Lesson 35: Threads and Basic Thread Safety

**Concept:** `std::thread`, `std::jthread` (C++20), `join()`, `detach()`.
Passing arguments to threads. Data races.

| # | Exercise | What you do |
|---|---|---|
| 1 | Launch and join | Start a thread that runs a function; `join()` it and read the result |
| 2 | Thread with arguments | Pass arguments to a thread function by value and by `std::ref` |
| 3 | jthread basics | Replace `std::thread` + manual `join()` with `std::jthread` |
| 4 | jthread and stop_token | Use `jthread` with a `stop_token` for cooperative cancellation |
| 5 | Identify a data race | Find the data race in provided code (two threads, one shared counter) |
| 6 | Fix the data race | Apply a fix (mutex or atomic) to the race from exercise 5 |
| 7 | Thread-local storage | Use `thread_local` to give each thread its own copy of a variable |
| 8 | Launch N threads | Start N worker threads, each processing a slice of work; join all and merge results |

---

#### Lesson 36: Mutexes and Locks

**Concept:** `std::mutex`, `std::lock_guard`, `std::unique_lock`,
`std::scoped_lock`. Deadlock avoidance.

| # | Exercise | What you do |
|---|---|---|
| 1 | Protect shared data | Add a `mutex` + `lock_guard` to a shared counter |
| 2 | lock_guard scope | Show that the lock releases at scope end; restructure code to minimize critical section |
| 3 | Scoped lock for multiple mutexes | Use `scoped_lock` to lock two mutexes without deadlock |
| 4 | unique_lock flexibility | Use `unique_lock` with deferred locking and manual `unlock()` |
| 5 | Timed lock | Use `unique_lock::try_lock_for()` with a timeout |
| 6 | Shared mutex for readers | Use `std::shared_mutex` + `shared_lock` for concurrent reads |
| 7 | Deadlock identification | Identify a deadlock in provided code (inconsistent lock ordering); fix it |
| 8 | Thread-safe wrapper | Build a generic `Synchronized<T>` wrapper that locks on every access |

---

#### Lesson 37: Condition Variables

**Concept:** `std::condition_variable`, `wait`, `notify_one`, `notify_all`.
Producer-consumer pattern. Spurious wakeups.

| # | Exercise | What you do |
|---|---|---|
| 1 | Basic wait/notify | Use a condition variable to signal between two threads |
| 2 | Predicate wait | Use the predicate overload of `wait()` to handle spurious wakeups correctly |
| 3 | Bounded buffer | Implement a thread-safe bounded buffer (producer blocks when full, consumer when empty) |
| 4 | Work queue | Implement a work queue where consumers block until work is available |
| 5 | One-shot event | Use a condition variable for a one-time "ready" signal (latch-like) |
| 6 | notify_one vs notify_all | Demonstrate the difference: wake one consumer vs. wake all |
| 7 | Timed wait | Use `wait_for()` with a timeout; handle the timeout case |

---

#### Lesson 38: Atomic Operations

**Concept:** `std::atomic<T>`. Lock-free counters and flags.
`memory_order` basics (sequentially consistent default).

| # | Exercise | What you do |
|---|---|---|
| 1 | Atomic counter | Replace a mutex-protected counter with `std::atomic<int>` |
| 2 | Atomic load/store | Use explicit `load()` and `store()` methods; understand their role |
| 3 | Atomic flag | Use `std::atomic_flag` for a simple spinlock |
| 4 | Compare-and-swap | Implement a lock-free stack push using `compare_exchange_weak` |
| 5 | Atomic accumulation | Use `fetch_add` / `fetch_sub` for a thread-safe statistics counter |
| 6 | Spinlock with backoff | Improve the spinlock from ex3 with a `yield`/backoff strategy |
| 7 | Memory order awareness | Demonstrate the visible difference between `memory_order_relaxed` and `seq_cst` |

---

#### Lesson 39: Futures and Async

**Concept:** `std::async`, `std::future`, `std::promise`, `std::packaged_task`.
Fire-and-forget vs. waiting for results.

| # | Exercise | What you do |
|---|---|---|
| 1 | Async computation | Use `std::async` to run a computation on another thread; get the result |
| 2 | Launch policies | Compare `launch::async` vs `launch::deferred`; observe the difference |
| 3 | Promise-future channel | Use `promise`/`future` as a one-shot communication channel between threads |
| 4 | Exception propagation | Show that exceptions thrown in `async` propagate through `future::get` |
| 5 | Multiple futures | Launch multiple async tasks and collect all results |
| 6 | wait_for with timeout | Use `future::wait_for` to poll a future with a timeout |
| 7 | Shared future | Use `std::shared_future` so multiple consumers can read the same result |
| 8 | Packaged task | Wrap a function in `packaged_task` for deferred execution on a different thread |

---

#### Lesson 40: Thread Pools

**Concept:** Why thread pools exist. Implementing a basic pool with a work
queue, condition variable, and fixed worker threads.

| # | Exercise | What you do |
|---|---|---|
| 1 | Fixed thread vector | Create a fixed number of worker `jthread`s that wait for work |
| 2 | Worker loop | Implement the core loop: dequeue a task from the shared queue, execute, repeat |
| 3 | Submit with future | Implement `submit()` returning a `std::future<T>` for the result |
| 4 | Submit different types | Submit tasks returning different types (`int`, `string`, `void`) |
| 5 | Graceful shutdown | Implement shutdown: stop accepting, finish in-flight work, join all threads |
| 6 | Pool statistics | Add methods to query active count, pending count, total completed |
| 7 | Pool resize | Add the ability to grow/shrink the pool while it's running |

---

#### Lesson 41: Coroutines Introduction (C++20)

**Concept:** `co_await`, `co_return`, `co_yield`. Promise types. Generators.
High-level concepts — enough to read and use coroutine-based async libraries.

| # | Exercise | What you do |
|---|---|---|
| 1 | Generator basics | Implement a generator that `co_yield`s Fibonacci numbers |
| 2 | Range-for with generator | Make the generator work with range-for by implementing `begin()`/`end()` |
| 3 | Simple coroutine task | Implement a basic `Task<T>` that `co_return`s a value |
| 4 | Chained coroutines | `co_await` one coroutine from another; chain two async steps |
| 5 | Lazy evaluation | Use a coroutine to lazily produce values on demand (pull-based) |
| 6 | Infinite sequence | Build a generator that produces an infinite sequence; consume it with `take(n)` |
| 7 | Exception in coroutine | Handle an exception thrown inside a coroutine; observe how it propagates |

---

#### Lesson 42: Async I/O Patterns

**Concept:** Callback-based vs. future-based vs. coroutine-based async.
Modeling async operations. Event loop concepts.

| # | Exercise | What you do |
|---|---|---|
| 1 | Callback-based API | Implement an async operation that takes a completion callback |
| 2 | Callback with error handling | Add an error parameter to the callback; handle success and failure |
| 3 | Future-based wrapper | Wrap the callback API in a `future`-returning interface |
| 4 | Callback to coroutine | Wrap the callback API so it can be `co_await`ed |
| 5 | Simulated event loop | Implement a simple event loop that drains a queue of deferred callbacks |
| 6 | Timer in event loop | Add delayed/timer callback support to the event loop |
| 7 | Multiple pending operations | Handle multiple concurrent async operations in the event loop |

---

### Course 5: Real-World Patterns for Web Development

Applying everything to patterns you'll encounter in HTTP servers, API clients,
middleware frameworks, and service infrastructure.

---

#### Lesson 43: Builder Pattern

**Concept:** Fluent builder interfaces for constructing complex objects
(HTTP requests, configuration, queries). Method chaining. Type-state
builder pattern.

| # | Exercise | What you do |
|---|---|---|
| 1 | Basic builder | Implement a `RequestBuilder` with setter methods that store state |
| 2 | Method chaining | Make each setter return `*this` for fluent chaining |
| 3 | Build method | Implement `build()` that constructs the final object from accumulated state |
| 4 | Required vs optional fields | Return `expected` from `build()` when required fields are missing |
| 5 | Builder with defaults | Provide sensible defaults so only non-default fields need to be set |
| 6 | Type-state builder | Use templates so `.build()` only compiles when required fields are set |
| 7 | Nested builder | Build a complex object containing sub-objects with their own builders |

---

#### Lesson 44: Type-Safe Configuration

**Concept:** Strongly-typed config over stringly-typed. Using `variant`,
`optional`, and custom types to model configuration. Parsing and validation.

| # | Exercise | What you do |
|---|---|---|
| 1 | Config struct with defaults | Design a config type with in-class member defaults |
| 2 | Override methods | Implement `with_port()`, `with_host()` etc. that return modified copies |
| 3 | Parse from key-value | Implement parsing from `vector<pair<string,string>>` into typed config |
| 4 | Merge two configs | Override a base config with values from an overlay config |
| 5 | Validation | Add validation that returns a list of errors for invalid field combinations |
| 6 | Nested config | Config struct containing sub-configs (e.g., `ServerConfig` has `TlsConfig`) |
| 7 | Config diffing | Compare two configs and report which fields differ |

---

#### Lesson 45: Middleware and Chain of Responsibility

**Concept:** Request pipelines, middleware chains. `std::function` chains.
Template-based middleware. Think Express.js middleware in C++.

| # | Exercise | What you do |
|---|---|---|
| 1 | Function chain | Implement a chain of `std::function` middleware; each calls `next()` |
| 2 | Request/Response context | Design a `Context` type that middleware reads and modifies |
| 3 | Next function | Implement the "call next" mechanism that passes control down the chain |
| 4 | Early exit (short-circuit) | Support middleware that sends a response without calling next |
| 5 | Middleware composition | Build a `Pipeline` class that composes middleware from an ordered list |
| 6 | Error-handling middleware | Write middleware that catches exceptions and returns error responses |
| 7 | Timing middleware | Write middleware that records elapsed time and adds it to the response |
| 8 | Conditional middleware | Write middleware that only runs for certain request paths (e.g., `/api/*`) |

---

#### Lesson 46: Serialization and Structured Data

**Concept:** Converting between C++ types and wire formats. Visitor pattern
for serialization. Simple JSON-like data structures.

| # | Exercise | What you do |
|---|---|---|
| 1 | To/from map | Implement `to_map` / `from_map` for a flat struct |
| 2 | Dynamic value type | Build a `Value` type using `variant<string, int, double, bool, nullptr_t>` |
| 3 | Array and object values | Extend `Value` with `vector<Value>` and `map<string, Value>` (recursive) |
| 4 | Type-safe accessors | Implement `as_string()`, `as_int()`, etc. returning `optional<T>` |
| 5 | Serialize to string | Implement a `stringify(Value)` function producing JSON-like output |
| 6 | Parse from string | Implement a simple parser that reads JSON-like input into a `Value` tree |
| 7 | Pretty print | Format the `Value` type with indentation for readable output |
| 8 | Visitor pattern | Implement a `visit_value()` that traverses the tree, calling typed callbacks |

---

#### Lesson 47: Resource Pools

**Concept:** Connection pools, object pools. RAII checkout/return. Thread-safe
pool with bounded size and waiting.

| # | Exercise | What you do |
|---|---|---|
| 1 | Basic object pool | Implement a pool that hands out objects and accepts returns |
| 2 | RAII pool handle | Return a custom smart-pointer-like handle that returns the object on destruction |
| 3 | Pool with factory | Pool creates new objects on demand up to a max size |
| 4 | Thread-safe pool | Add `mutex` + `condition_variable` for safe concurrent access |
| 5 | Pool with health check | Validate objects before handing them out; discard unhealthy ones |
| 6 | Pool statistics | Track active, idle, and total-created counts |
| 7 | Pool with timeout | Block up to N ms for an available resource; return `expected` on timeout |

---

#### Lesson 48: Observer and Event System

**Concept:** Publish-subscribe, event emitters, signal-slot pattern. Callback
registration and lifetime management.

| # | Exercise | What you do |
|---|---|---|
| 1 | Simple event emitter | Implement `on(callback)` and `emit()` for a single event type |
| 2 | Return a subscription ID | Make `on()` return an ID; implement `off(id)` to unsubscribe |
| 3 | Multi-event dispatcher | Template the emitter to support different event types |
| 4 | Event with payload | Emit events carrying typed data (e.g., `emit(UserEvent{...})`) |
| 5 | Auto-unsubscribe | Return an RAII subscription handle that removes the listener on destruction |
| 6 | Weak observer | Use `weak_ptr` to detect and skip destroyed observers |
| 7 | Event filtering | Let subscribers register a predicate so they only receive matching events |
| 8 | Ordered dispatch | Guarantee notification order matches subscription order |

---

#### Lesson 49: HTTP Request/Response Modeling

**Concept:** Designing types for HTTP method, headers, body, status codes.
Using enums, maps, `variant`, and `optional` together.

| # | Exercise | What you do |
|---|---|---|
| 1 | HTTP method enum | Model HTTP methods as an enum class with `to_string` / `from_string` |
| 2 | Status code enum | Model HTTP status codes with category helpers (`is_success()`, `is_error()`) |
| 3 | Headers class | Implement a case-insensitive header map (uses custom hash from Lesson 15) |
| 4 | Multi-value headers | Support headers with multiple values (e.g., `Set-Cookie`) |
| 5 | Request type | Assemble a `Request` with method, path, headers, optional body |
| 6 | Response builder | Implement a `Response` with builder pattern for status, headers, body |
| 7 | Content-Type parsing | Parse and validate a Content-Type header (type, subtype, parameters) |
| 8 | Query string parsing | Parse `?key=value&key2=value2` from a URL path into a map |

---

#### Lesson 50: Logging and Diagnostics

**Concept:** `std::source_location`, `std::format`, log levels, structured
logging. Using templates for zero-cost disabled log levels.

| # | Exercise | What you do |
|---|---|---|
| 1 | Basic logger | Implement a logger with level filtering (debug, info, warn, error) |
| 2 | Formatted output | Use `std::format` to build structured log messages |
| 3 | Source location | Use `std::source_location` to auto-capture file/line at the call site |
| 4 | Structured log entry | Build a log entry type with timestamp, level, message, and key-value fields |
| 5 | Log sink abstraction | Define a sink interface; implement console and in-memory sinks |
| 6 | Zero-cost disabled logs | Use `if constexpr` to eliminate disabled log levels at compile time |
| 7 | Log context/scope | Implement push/pop context (e.g., `request_id=abc`) that prefixes all nested logs |
| 8 | Thread-safe logger | Make the logger safe for concurrent use from multiple threads |

---

#### Lesson 51: Error Propagation Patterns

**Concept:** Building a `Result<T, E>` monad. Monadic chaining with
`and_then`/`or_else`/`transform`. Unified error handling strategy for an
application.

| # | Exercise | What you do |
|---|---|---|
| 1 | Result type | Implement a `Result<T, E>` wrapper over `std::expected` |
| 2 | Monadic transform | Implement `transform` to map the success value |
| 3 | Monadic and_then | Implement `and_then` to chain failable operations |
| 4 | Monadic or_else | Implement `or_else` to handle/recover from errors |
| 5 | Map error | Implement `map_error` to transform the error type |
| 6 | Error context wrapping | Add context (string message) to an error without losing the original |
| 7 | Collect results | Gather a `vector<Result<T,E>>` into a `Result<vector<T>, E>` (fail on first error) |
| 8 | Pipeline with Results | Chain 4+ failable operations into a pipeline using the Result API |

---

#### Lesson 52: Capstone — Mini HTTP Handler Framework

**Concept:** Integrate concepts from across the entire course to build a small
but functional HTTP handler framework. Router, middleware, handlers, request
parsing, response building.

| # | Exercise | What you do |
|---|---|---|
| 1 | Route registration | Register handler functions for method + path pairs |
| 2 | Router dispatch | Implement dispatch: match incoming request to the right handler |
| 3 | Path parameters | Support `/users/:id` style path parameters; extract them into the request |
| 4 | Middleware integration | Wire the middleware chain from Lesson 45 into the router |
| 5 | Request parsing | Parse a raw HTTP-like string into a `Request` object |
| 6 | Response serialization | Serialize a `Response` object to an HTTP-like string |
| 7 | Error handling | Return proper 400/404/500 responses for bad requests and unmatched routes |
| 8 | JSON-like body | Parse a simple key-value body into a `Value`; use it in a handler |
| 9 | End-to-end test | Full request → route → middleware → handler → response pipeline |

---

## Summary

| Course | Lessons | Exercises | Focus |
|---|---|---|---|
| 1 — Foundations | 13 | 103 | Compilation model, types, memory, ownership |
| 2 — Standard Library | 10 | 78 | Containers, algorithms, utilities |
| 3 — Types & Generics | 11 | 88 | Classes, templates, concepts, forwarding |
| 4 — Concurrency | 8 | 59 | Threads, sync, async |
| 5 — Web Patterns | 10 | 78 | Architecture and design patterns |
| **Total** | **52** | **~400** | |

---

## Next Steps

Once this plan is approved:

1. Build the `testkit` framework and root CMake infrastructure
2. Build the `run` convenience script
3. Implement Course 1, lesson by lesson — each with README, exercises, and tests
4. Repeat for Courses 2-5
