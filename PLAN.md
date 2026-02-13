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

Early exercises (Courses 1-2) use **header files** (`.h`) with inline functions.
This keeps the edit-compile-test loop tight — one file to edit, one command to
test.

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
| Lessons 1-5 | Fix a single statement or expression | Change a parameter type, add `const` |
| Lessons 6-12 | Fill in a function body (2-8 lines) | Implement a swap, a lookup, a transform |
| Lessons 13-20 | Write a complete function | String parser, algorithm pipeline |
| Lessons 21-30 | Refactor code to be more idiomatic | Raw pointers → smart pointers, C-style → ranges |
| Lessons 31-38 | Implement a class or component | Thread pool, connection pool, event emitter |
| Lessons 39-48 | Multi-class design | Middleware chain, HTTP handler framework |

---

### Course 1: Foundations — Types, Memory, and Ownership

The bridge from "I know C" to "I can write correct modern C++." Covers the
type system extensions, memory model, and ownership semantics that every
line of C++ code depends on.

---

#### Lesson 01: `const` and References

**Concept:** lvalue references, `const` qualification, `const` references as
the default parameter-passing strategy.

| # | Exercise | What you do |
|---|---|---|
| 1 | Fix a parameter type | Change `std::string name` → `const std::string& name` |
| 2 | Const-qualify a method | Add `const` to a getter method that doesn't modify state |
| 3 | Swap via references | Implement a `swap(int&, int&)` function body (3 lines) |
| 4 | Return a const reference | Return `const T&` to the largest element in a vector |

---

#### Lesson 02: Strings and String Views

**Concept:** `std::string` vs `std::string_view`, when to use each, implicit
conversions, lifetime pitfalls.

| # | Exercise | What you do |
|---|---|---|
| 1 | Fix string copies | Change functions taking `const std::string&` to `std::string_view` where safe |
| 2 | Substring without allocation | Use `string_view::substr` to extract a portion |
| 3 | Build a string with concatenation | Use `std::string` + operator and `append` to build output |
| 4 | Dangling view | Identify and fix a function returning a dangling `string_view` |

---

#### Lesson 03: Scoped Enums and Strong Types

**Concept:** `enum class` vs C-style `enum`, underlying types, converting to/from
integers, using enums for type safety.

| # | Exercise | What you do |
|---|---|---|
| 1 | Convert a C enum to enum class | Change `enum Color` to `enum class Color` and fix call sites |
| 2 | Enum with explicit underlying type | Define an enum class with `uint8_t` backing for wire format |
| 3 | Enum to string | Write a `to_string` function using a switch over an enum class |

---

#### Lesson 04: `auto` and Type Deduction

**Concept:** `auto` for variables, return types, and range-for loops. `decltype`.
When `auto` helps and when explicit types are clearer.

| # | Exercise | What you do |
|---|---|---|
| 1 | Replace explicit types with `auto` | Simplify verbose iterator declarations |
| 2 | `auto` with const/reference | Predict and fix type deduction with `const auto&` |
| 3 | Trailing return types | Convert functions to trailing return type syntax |
| 4 | `decltype` for expression types | Use `decltype` to declare a variable matching another's type |

---

#### Lesson 05: Structured Bindings

**Concept:** `auto [a, b] = ...` for pairs, tuples, structs, and map iteration.

| # | Exercise | What you do |
|---|---|---|
| 1 | Decompose a pair | Use structured binding to unpack `std::pair` from a map insert |
| 2 | Iterate a map | Use structured bindings in a range-for over `std::map` |
| 3 | Unpack a struct | Bind fields of a returned struct |
| 4 | Tuple decomposition | Unpack a `std::tuple` from a function returning multiple values |

---

#### Lesson 06: RAII and Scope-Based Lifetime

**Concept:** Resource Acquisition Is Initialization. Constructors acquire,
destructors release. Deterministic cleanup. Comparison with Java's
try-with-resources and Rust's `Drop`.

| # | Exercise | What you do |
|---|---|---|
| 1 | Write a scoped timer | Implement a class that records start time in ctor, prints elapsed in dtor |
| 2 | File handle wrapper | Wrap a `FILE*` in an RAII class with open-in-ctor, close-in-dtor |
| 3 | Scoped lock (manual) | Implement a simplified `lock_guard` that locks in ctor, unlocks in dtor |
| 4 | Prove cleanup order | Fill in expected output for nested RAII objects (destruction order) |

---

#### Lesson 07: Smart Pointers

**Concept:** `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`.
`std::make_unique`, `std::make_shared`. Ownership semantics.

| # | Exercise | What you do |
|---|---|---|
| 1 | Raw to unique_ptr | Refactor `new`/`delete` code to use `make_unique` |
| 2 | Transfer ownership | Pass a `unique_ptr` to a function via `std::move` |
| 3 | Shared ownership | Use `shared_ptr` for a cache where multiple readers hold references |
| 4 | Break a cycle with weak_ptr | Fix a memory leak caused by circular `shared_ptr` references |

---

#### Lesson 08: Move Semantics

**Concept:** Rvalue references, `std::move`, move constructors, move assignment.
When and why the compiler moves. The "moved-from" state.

| # | Exercise | What you do |
|---|---|---|
| 1 | Move a string into a container | Use `std::move` to avoid copying when inserting into a vector |
| 2 | Write a move constructor | Implement a move ctor for a class owning a dynamic resource |
| 3 | Move assignment operator | Implement move assignment with proper self-assignment check |
| 4 | Return value optimization | Predict which calls trigger copy vs. move vs. RVO |

---

#### Lesson 09: `optional`, `variant`, and `expected`

**Concept:** Sum types in C++. `std::optional<T>` for nullable values,
`std::variant<Ts...>` for tagged unions, `std::expected<T,E>` (C++23) for
result types. Comparison with Rust's `Option`/`Result` and Java's `Optional`.

| # | Exercise | What you do |
|---|---|---|
| 1 | Return optional from lookup | Change a function from returning sentinel/-1 to `std::optional` |
| 2 | Chain optional operations | Use `transform`/`and_then` (C++23) or manual checks to chain lookups |
| 3 | Model a config value with variant | Use `std::variant<int, std::string, bool>` with `std::visit` |
| 4 | Error handling with expected | Rewrite a throwing function to return `std::expected<T, Error>` |

---

#### Lesson 10: Error Handling Patterns

**Concept:** Exceptions vs. error codes vs. `expected`. When to use each.
`noexcept`. Exception safety guarantees.

| # | Exercise | What you do |
|---|---|---|
| 1 | Throw and catch | Write a function that throws a custom exception; catch it at the call site |
| 2 | Exception safety with RAII | Make a function exception-safe by replacing raw `new`/`delete` with RAII |
| 3 | Convert exceptions to expected | Wrap a throwing function in a `try`/`catch` that returns `expected` |
| 4 | `noexcept` correctness | Mark functions `noexcept` where appropriate; fix one that lies |

---

### Course 2: The Standard Library Toolkit

Practical fluency with the containers, algorithms, and utilities you reach
for daily.

---

#### Lesson 11: `vector`, `array`, and `span`

**Concept:** Dynamic arrays, fixed-size arrays, and non-owning views over
contiguous memory. `std::span` as the modern way to accept "some contiguous
elements."

| # | Exercise | What you do |
|---|---|---|
| 1 | Populate a vector | Use `push_back`, `emplace_back`, and `reserve` |
| 2 | Bounds-safe access | Replace `operator[]` with `.at()` and handle the exception |
| 3 | Accept a span parameter | Change a function from `vector<int>&` to `std::span<const int>` |
| 4 | Fixed-size with std::array | Replace a C array with `std::array` and use `.size()` |

---

#### Lesson 12: Maps and Sets

**Concept:** `std::map`, `std::unordered_map`, `std::set`, `std::unordered_set`.
Ordered vs. unordered. `insert`, `emplace`, `try_emplace`, `contains`.

| # | Exercise | What you do |
|---|---|---|
| 1 | Word frequency counter | Use `unordered_map<string, int>` to count word occurrences |
| 2 | Safe lookup | Use `find()` / `contains()` instead of `operator[]` for non-mutating lookup |
| 3 | try_emplace for lazy init | Use `try_emplace` to insert-or-get in one operation |
| 4 | Ordered set operations | Use `std::set` to deduplicate and iterate in sorted order |

---

#### Lesson 13: Iterators

**Concept:** The iterator abstraction. `begin()`/`end()`, iterator categories,
`std::next`/`std::prev`/`std::advance`. Why iterators matter as the bridge
between containers and algorithms.

| # | Exercise | What you do |
|---|---|---|
| 1 | Manual iteration | Use iterators to traverse a list and modify elements |
| 2 | Erase while iterating | Correctly erase elements from a map during iteration |
| 3 | Iterator arithmetic | Use `std::next`/`std::distance` to find the nth element |
| 4 | Back-inserter | Use `std::back_inserter` to write algorithm output into a vector |

---

#### Lesson 14: Algorithms

**Concept:** The `<algorithm>` header. `sort`, `find`, `find_if`, `count_if`,
`transform`, `accumulate`, `remove_if` + erase idiom, `any_of`/`all_of`/`none_of`.

| # | Exercise | What you do |
|---|---|---|
| 1 | Sort and search | Sort a vector, then use `lower_bound` to binary search |
| 2 | Transform elements | Use `std::transform` to apply a function to each element |
| 3 | Filter with remove-erase | Use `remove_if` + `erase` to filter elements from a vector |
| 4 | Accumulate and reduce | Use `std::accumulate` to compute stats over a collection |
| 5 | Predicate composition | Combine `any_of`, `all_of`, `none_of` for complex queries |

---

#### Lesson 15: Ranges and Views (C++20)

**Concept:** The ranges library. `std::ranges::sort`, views as lazy
transformations, pipe syntax, `filter`, `transform`, `take`, `drop`.

| # | Exercise | What you do |
|---|---|---|
| 1 | Ranges sort and find | Rewrite algorithm calls using `std::ranges::` versions |
| 2 | Filter-transform pipeline | Build a `views::filter \| views::transform` pipeline |
| 3 | Lazy evaluation with views | Use `views::take` and `views::drop` on a large range |
| 4 | Custom projection | Use the `proj` parameter in ranges algorithms |

---

#### Lesson 16: Lambdas

**Concept:** Lambda expressions. Capture by value, by reference, by move.
`mutable` lambdas. Generic lambdas with `auto`. Immediately-invoked lambdas
for complex initialization.

| # | Exercise | What you do |
|---|---|---|
| 1 | Basic lambda predicate | Write a lambda for `std::sort` custom comparison |
| 2 | Capture by reference | Write a counting lambda that modifies an outer variable |
| 3 | Capture by move | Capture a `unique_ptr` into a lambda using init-capture |
| 4 | Generic lambda | Write an `auto`-parameter lambda that works with multiple types |
| 5 | IIFE for initialization | Use an immediately-invoked lambda to initialize a `const` variable |

---

#### Lesson 17: `std::function` and Callable Objects

**Concept:** Type-erased callables. `std::function`, function pointers, functors
(classes with `operator()`). When to use each. Performance tradeoffs.

| # | Exercise | What you do |
|---|---|---|
| 1 | Callback registration | Accept a `std::function<void(int)>` callback and invoke it |
| 2 | Functor class | Write a functor that maintains state across invocations |
| 3 | Function pointer vs std::function | Convert between the two; understand when each works |
| 4 | Template parameter vs type erasure | Refactor a function to use a template parameter instead of `std::function` |

---

#### Lesson 18: Chrono

**Concept:** `std::chrono` — time points, durations, clocks.
`system_clock`, `steady_clock`. Duration casts. Formatting.

| # | Exercise | What you do |
|---|---|---|
| 1 | Measure elapsed time | Use `steady_clock` to time a function call |
| 2 | Duration arithmetic | Add, subtract, and convert between duration types |
| 3 | Timeout check | Implement a function that checks if a deadline has passed |
| 4 | Format a timestamp | Convert a `system_clock::time_point` to a human-readable string |

---

#### Lesson 19: String Processing

**Concept:** String manipulation utilities, `std::stoi`/`std::stod`, `std::to_string`,
`std::format` (C++20), `std::from_chars`/`std::to_chars`. Basic regex.

| # | Exercise | What you do |
|---|---|---|
| 1 | Parse key-value pairs | Split "key=value" strings using `find` and `substr` |
| 2 | Number conversion | Use `from_chars`/`to_chars` for locale-independent conversion |
| 3 | Format strings | Use `std::format` to build formatted output |
| 4 | Simple regex match | Use `std::regex` to validate an email-like pattern |

---

#### Lesson 20: Filesystem

**Concept:** `std::filesystem` — paths, existence checks, directory iteration,
file operations. Portable path handling.

| # | Exercise | What you do |
|---|---|---|
| 1 | Path manipulation | Join, decompose, and normalize paths using `std::filesystem::path` |
| 2 | Directory listing | Iterate over directory entries and filter by extension |
| 3 | File existence and size | Check existence, get file size, compare modification times |
| 4 | Create directory tree | Use `create_directories` and handle errors |

---

### Course 3: Types and Generic Programming

Designing types, APIs, and generic code. Where C++ diverges most
from Java and Rust.

---

#### Lesson 21: Classes and Encapsulation

**Concept:** `struct` vs `class` (only default access differs), access specifiers,
member functions, `this` pointer. Data hiding and API design.

| # | Exercise | What you do |
|---|---|---|
| 1 | Convert struct to class | Add proper access control to a data-only struct |
| 2 | Getter/setter methods | Implement getters (const) and setters with validation |
| 3 | Invariant enforcement | Ensure a class's internal state is always valid via constructor + methods |

---

#### Lesson 22: Constructors and Initialization

**Concept:** Default, parameterized, and delegating constructors. Member
initializer lists. `explicit`. In-class member initializers. Aggregate init.

| # | Exercise | What you do |
|---|---|---|
| 1 | Member initializer list | Fix a class to use initializer list instead of assignment in body |
| 2 | Delegating constructors | Refactor duplicated init logic using constructor delegation |
| 3 | Explicit constructors | Fix implicit conversion bugs by adding `explicit` |
| 4 | Aggregate initialization | Design a config struct that supports aggregate init |

---

#### Lesson 23: Operator Overloading

**Concept:** Overloading `==`, `<=>` (spaceship), `<<` (stream insertion),
`[]`, and arithmetic operators. C++20's defaulted comparisons.

| # | Exercise | What you do |
|---|---|---|
| 1 | Equality operator | Implement `operator==` for a struct |
| 2 | Spaceship operator | Use `<=>` to get all comparison operators for free |
| 3 | Stream insertion | Implement `operator<<` for debug/log output |
| 4 | Subscript operator | Implement `operator[]` (const and non-const overloads) |

---

#### Lesson 24: Inheritance and Polymorphism

**Concept:** Single inheritance, `virtual` functions, `override`, `final`,
pure virtual (abstract classes). Virtual destructors.

| # | Exercise | What you do |
|---|---|---|
| 1 | Virtual method dispatch | Create a base class with virtual method; override in derived |
| 2 | Abstract interface | Define a pure virtual interface; implement it in a concrete class |
| 3 | Virtual destructor | Fix a memory leak by adding a virtual destructor |
| 4 | Override and final | Use `override` to catch signature mismatches; `final` to prevent further overrides |

---

#### Lesson 25: Rule of Zero / Five

**Concept:** When to write special member functions (copy/move ctor, copy/move
assignment, destructor) and when to rely on compiler defaults. The Rule of
Zero (prefer it) and Rule of Five (when you must manage a resource).

| # | Exercise | What you do |
|---|---|---|
| 1 | Rule of Zero | Refactor a class with manual copy/dtor to use smart pointers (eliminate special members) |
| 2 | Deleted copy | Disable copying for a resource-owning class using `= delete` |
| 3 | Rule of Five | Implement all five special members for a class wrapping a C resource |
| 4 | Default keyword | Use `= default` to explicitly request compiler-generated members |

---

#### Lesson 26: Function Templates

**Concept:** Template functions. Type parameter deduction. Multiple type params.
Non-type template parameters.

| # | Exercise | What you do |
|---|---|---|
| 1 | Generic max function | Write a `max_of(T a, T b)` template |
| 2 | Multiple type parameters | Write a `convert<To>(From val)` template |
| 3 | Non-type template parameter | Write a `fixed_buffer<size_t N>` with compile-time size |
| 4 | Template argument deduction | Fix call sites that need explicit template arguments vs. those that don't |

---

#### Lesson 27: Class Templates

**Concept:** Template classes. Member function definitions. Template
specialization. Class template argument deduction (CTAD).

| # | Exercise | What you do |
|---|---|---|
| 1 | Generic stack | Implement `Stack<T>` backed by `std::vector` |
| 2 | Key-value pair | Implement `Pair<K, V>` with comparison operators |
| 3 | CTAD guide | Add a deduction guide so `Pair{1, "hello"}` works |
| 4 | Partial specialization | Specialize a `Serializer<T>` template for string types |

---

#### Lesson 28: Concepts and Constraints (C++20)

**Concept:** `concept`, `requires` clause, `requires` expression.
Constraining templates for better error messages and API design.

| # | Exercise | What you do |
|---|---|---|
| 1 | Simple concept | Write a `Numeric` concept and use it to constrain a function |
| 2 | Compound requirements | Write a concept that requires `<`, `==`, and `.to_string()` |
| 3 | Constrained class template | Constrain a container adaptor to work only with specific types |
| 4 | Concept-based overloading | Use concepts to select between function overloads |

---

#### Lesson 29: Type Traits and `constexpr`

**Concept:** `<type_traits>` — `is_same_v`, `is_integral_v`, `decay_t`,
`remove_reference_t`. `constexpr` functions, `if constexpr`, `static_assert`.

| # | Exercise | What you do |
|---|---|---|
| 1 | static_assert with type traits | Add compile-time checks that template args meet requirements |
| 2 | if constexpr branching | Use `if constexpr` to select code paths based on type properties |
| 3 | constexpr function | Write a compile-time-evaluable function and test with `static_assert` |
| 4 | Type manipulation | Use `remove_reference_t` / `decay_t` to normalize types in a template |

---

#### Lesson 30: CRTP and Mixin Patterns

**Concept:** Curiously Recurring Template Pattern for static polymorphism.
Mixin classes. Composition vs. inheritance with templates.

| # | Exercise | What you do |
|---|---|---|
| 1 | CRTP counter | Implement a CRTP base that counts instances of each derived class |
| 2 | Static interface | Use CRTP to enforce a static interface without virtual dispatch |
| 3 | Mixin for logging | Write a logging mixin that adds `.log()` to any class |
| 4 | Composable policies | Build a type by composing template-parameterized policy classes |

---

### Course 4: Concurrency and Async

Essential for web servers. Thread management, synchronization, and async
patterns.

---

#### Lesson 31: Threads and Basic Thread Safety

**Concept:** `std::thread`, `std::jthread` (C++20), `join()`, `detach()`.
Passing arguments to threads. Data races.

| # | Exercise | What you do |
|---|---|---|
| 1 | Launch and join | Start a thread that computes a result; join and read the result |
| 2 | jthread and stop_token | Use `jthread` with a stop token for cooperative cancellation |
| 3 | Thread with arguments | Pass arguments to a thread function by value and by reference |
| 4 | Identify a data race | Find and fix a data race in provided code |

---

#### Lesson 32: Mutexes and Locks

**Concept:** `std::mutex`, `std::lock_guard`, `std::unique_lock`,
`std::scoped_lock`. Deadlock avoidance.

| # | Exercise | What you do |
|---|---|---|
| 1 | Protect shared data | Add a mutex + lock_guard to a shared counter |
| 2 | Scoped lock for multiple mutexes | Use `scoped_lock` to lock two mutexes without deadlock |
| 3 | unique_lock flexibility | Use `unique_lock` with deferred locking and manual unlock |
| 4 | Shared mutex | Use `std::shared_mutex` for reader-writer locking |

---

#### Lesson 33: Condition Variables

**Concept:** `std::condition_variable`, `wait`, `notify_one`, `notify_all`.
Producer-consumer pattern. Spurious wakeups.

| # | Exercise | What you do |
|---|---|---|
| 1 | Bounded buffer | Implement a thread-safe bounded buffer with condition variables |
| 2 | Work queue | Implement a queue where consumers block until work is available |
| 3 | One-shot event | Use a condition variable for a one-time "ready" signal |

---

#### Lesson 34: Atomic Operations

**Concept:** `std::atomic<T>`. Lock-free counters and flags.
`memory_order` basics (sequentially consistent default).

| # | Exercise | What you do |
|---|---|---|
| 1 | Atomic counter | Replace mutex-protected counter with `std::atomic<int>` |
| 2 | Atomic flag | Use `std::atomic_flag` for a simple spinlock |
| 3 | Compare-and-swap | Implement a lock-free stack push using `compare_exchange_weak` |

---

#### Lesson 35: Futures and Async

**Concept:** `std::async`, `std::future`, `std::promise`, `std::packaged_task`.
Fire-and-forget vs. waiting for results.

| # | Exercise | What you do |
|---|---|---|
| 1 | async computation | Use `std::async` to run a computation on another thread |
| 2 | Promise-future channel | Use `promise`/`future` as a one-shot communication channel |
| 3 | Multiple futures | Launch multiple async tasks and collect all results |
| 4 | Packaged task | Wrap a function in `packaged_task` for deferred execution |

---

#### Lesson 36: Thread Pools

**Concept:** Why thread pools exist. Implementing a basic pool with a work
queue, condition variable, and fixed worker threads.

| # | Exercise | What you do |
|---|---|---|
| 1 | Worker loop | Implement the core worker loop: dequeue task, execute, repeat |
| 2 | Submit and wait | Implement `submit()` returning a `future` for the result |
| 3 | Graceful shutdown | Implement shutdown that finishes in-flight work then joins threads |

---

#### Lesson 37: Coroutines Introduction (C++20)

**Concept:** `co_await`, `co_return`, `co_yield`. Promise types. Generators.
High-level concepts — enough to read and use coroutine-based async libraries.

| # | Exercise | What you do |
|---|---|---|
| 1 | Generator | Implement a generator that yields Fibonacci numbers |
| 2 | Simple coroutine task | Implement a basic `Task<T>` coroutine that co_returns a value |
| 3 | Lazy evaluation | Use a coroutine to lazily produce values on demand |

---

#### Lesson 38: Async I/O Patterns

**Concept:** Callback-based vs. future-based vs. coroutine-based async.
Modeling async operations. Event loop concepts.

| # | Exercise | What you do |
|---|---|---|
| 1 | Callback-based API | Implement an async operation that takes a completion callback |
| 2 | Future-based wrapper | Wrap the callback API in a future-returning interface |
| 3 | Simulated event loop | Implement a simple event loop that processes deferred callbacks |

---

### Course 5: Real-World Patterns for Web Development

Applying everything to patterns you'll encounter in HTTP servers, API clients,
middleware frameworks, and service infrastructure.

---

#### Lesson 39: Builder Pattern

**Concept:** Fluent builder interfaces for constructing complex objects
(HTTP requests, configuration, queries). Method chaining. Type-state
builder pattern.

| # | Exercise | What you do |
|---|---|---|
| 1 | Basic builder | Implement a `RequestBuilder` with method chaining |
| 2 | Required vs optional fields | Enforce required fields via compile-time or runtime check |
| 3 | Type-state builder | Use templates so `.build()` only compiles when required fields are set |

---

#### Lesson 40: Type-Safe Configuration

**Concept:** Strongly-typed config over stringly-typed. Using `variant`,
`optional`, and custom types to model configuration. Parsing and validation.

| # | Exercise | What you do |
|---|---|---|
| 1 | Config struct with defaults | Design a config type with in-class defaults and override methods |
| 2 | Parse from key-value | Implement parsing from `vector<pair<string,string>>` into typed config |
| 3 | Validation | Add validation that returns errors for invalid combinations |

---

#### Lesson 41: Middleware and Chain of Responsibility

**Concept:** Request pipelines, middleware chains. `std::function` chains.
Template-based middleware. Think Express.js middleware in C++.

| # | Exercise | What you do |
|---|---|---|
| 1 | Function chain | Implement a chain of `std::function` middleware |
| 2 | Request/Response context | Design a `Context` type that middleware reads and modifies |
| 3 | Early exit (short-circuit) | Support middleware that sends a response without calling next |
| 4 | Middleware composition | Build a pipeline from reusable middleware components |

---

#### Lesson 42: Serialization and Structured Data

**Concept:** Converting between C++ types and wire formats. Visitor pattern
for serialization. Simple JSON-like data structures.

| # | Exercise | What you do |
|---|---|---|
| 1 | To/from map | Implement `to_map`/`from_map` for a struct |
| 2 | Dynamic value type | Build a `Value` type (variant of string/int/double/bool/array/object) |
| 3 | Recursive data structure | Implement a JSON-like tree using `variant` + `map` + `vector` |
| 4 | Serialize to string | Implement a `stringify` function for the `Value` type |

---

#### Lesson 43: Resource Pools

**Concept:** Connection pools, object pools. RAII checkout/return. Thread-safe
pool with bounded size and waiting.

| # | Exercise | What you do |
|---|---|---|
| 1 | Basic object pool | Implement a pool that hands out objects and reclaims them |
| 2 | RAII pool handle | Return a smart-pointer-like handle that returns the object on destruction |
| 3 | Thread-safe pool | Add mutex + condition variable for thread safety and bounded waiting |

---

#### Lesson 44: Observer and Event System

**Concept:** Publish-subscribe, event emitters, signal-slot pattern. Callback
registration and lifetime management.

| # | Exercise | What you do |
|---|---|---|
| 1 | Simple event emitter | Implement `on()`, `emit()` for a single event type |
| 2 | Multi-event dispatcher | Template the emitter to support multiple event types |
| 3 | Auto-unsubscribe | Return an RAII subscription handle that removes the listener on destruction |
| 4 | Weak observer | Use `weak_ptr` to avoid calling destroyed observers |

---

#### Lesson 45: HTTP Request/Response Modeling

**Concept:** Designing types for HTTP method, headers, body, status codes.
Using enums, maps, `variant`, and `optional` together.

| # | Exercise | What you do |
|---|---|---|
| 1 | HTTP method enum | Model HTTP methods as an enum class with `to_string`/`from_string` |
| 2 | Headers class | Implement a case-insensitive header map |
| 3 | Request type | Assemble a full `Request` type with method, path, headers, body |
| 4 | Response builder | Implement a `Response` with builder pattern and status codes |

---

#### Lesson 46: Logging and Diagnostics

**Concept:** `std::source_location`, `std::format`, log levels, structured
logging. Using templates for zero-cost disabled log levels.

| # | Exercise | What you do |
|---|---|---|
| 1 | Basic logger | Implement a logger with level filtering and formatted output |
| 2 | Source location | Use `std::source_location` to capture call-site file/line automatically |
| 3 | Structured log entry | Build a log entry type with timestamp, level, message, key-value fields |
| 4 | Zero-cost disabled logs | Use `if constexpr` to eliminate disabled log levels at compile time |

---

#### Lesson 47: Error Propagation Patterns

**Concept:** Building a `Result<T, E>` monad. Monadic chaining with
`and_then`/`or_else`/`transform`. Unified error handling strategy for an
application.

| # | Exercise | What you do |
|---|---|---|
| 1 | Result type | Implement a `Result<T, E>` wrapper over `std::expected` |
| 2 | Monadic operations | Add `and_then`, `transform`, and `or_else` methods |
| 3 | Error context | Implement `map_error` and error wrapping for adding context |
| 4 | Pipeline with Results | Chain multiple failable operations using the Result API |

---

#### Lesson 48: Capstone — Mini HTTP Handler Framework

**Concept:** Integrate concepts from across the entire course to build a small
but functional HTTP handler framework. Router, middleware, handlers, request
parsing, response building.

| # | Exercise | What you do |
|---|---|---|
| 1 | Router | Implement a `Router` that maps method + path to handler functions |
| 2 | Middleware integration | Wire the middleware chain from Lesson 41 into the router |
| 3 | Request parsing | Parse a raw HTTP-like string into a `Request` object |
| 4 | Response serialization | Serialize a `Response` object to an HTTP-like string |
| 5 | End-to-end handler | Write a handler that parses JSON-like body, queries a map, returns a response |

---

## Summary

| Course | Lessons | ~Exercises | Focus |
|---|---|---|---|
| 1 — Foundations | 10 | 38 | Types, memory, ownership |
| 2 — Standard Library | 10 | 41 | Containers, algorithms, utilities |
| 3 — Types & Generics | 10 | 36 | Classes, templates, concepts |
| 4 — Concurrency | 8 | 27 | Threads, sync, async |
| 5 — Web Patterns | 10 | 37 | Architecture and design patterns |
| **Total** | **48** | **~179** | |

---

## Next Steps

Once this plan is approved:

1. Build the `testkit` framework and root CMake infrastructure
2. Build the `run` convenience script
3. Implement Course 1, lesson by lesson — each with README, exercises, and tests
4. Repeat for Courses 2-5
