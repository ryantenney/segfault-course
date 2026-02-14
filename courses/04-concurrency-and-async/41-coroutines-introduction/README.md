# Lesson 41: Coroutines Introduction (C++20)

## Why This Lesson Exists

C++20 introduced coroutines as a language feature. A coroutine is a function
that can suspend its execution and be resumed later. Unlike regular functions
that run from start to finish, coroutines can pause mid-execution, yield a
value to the caller, and pick up exactly where they left off.

If you have used generators in Python, async/await in JavaScript, or iterators
in Rust, C++ coroutines will feel familiar in concept. The difference is that
C++ coroutines are built on a low-level protocol (promise_type, awaiters) that
gives you full control over suspension and resumption — but requires more
boilerplate to set up.

In these exercises, the coroutine infrastructure (Generator, Task) is provided
for you. You focus on writing the coroutine bodies.

## Key Concepts

### The Three Coroutine Keywords

A function becomes a coroutine when its body contains any of these:

- **`co_yield expr`** — Suspend and produce a value. The caller can read
  the value and later resume the coroutine for the next one. Used in generators.
- **`co_return expr`** — Complete the coroutine and produce a final result.
  Used in tasks.
- **`co_await expr`** — Suspend until some awaitable is ready. Used for
  composing coroutines and async operations.

### Generator Pattern

A generator is a coroutine that uses `co_yield` to produce a sequence of
values lazily:

```cpp
Generator<int> count_up(int n) {
    for (int i = 0; i < n; ++i) {
        co_yield i;    // suspend here, caller gets i
    }
    // implicit co_return at end
}
```

The caller advances the generator one step at a time:

```cpp
auto gen = count_up(3);
gen.next();  // resumes, yields 0
gen.value(); // returns 0
gen.next();  // resumes, yields 1
gen.value(); // returns 1
```

### Task Pattern

A task is a coroutine that uses `co_return` to produce a single result:

```cpp
Task<int> compute(int x) {
    co_return x * x;
}
```

### Chaining with co_await

One coroutine can `co_await` another, suspending until the inner coroutine
completes:

```cpp
Task<int> outer(int x) {
    int doubled = co_await inner(x);  // wait for inner
    co_return doubled + 1;
}
```

### Exception Handling

When a coroutine throws, the exception is captured by the promise's
`unhandled_exception()` method. Depending on the coroutine type, the
exception can be rethrown when the caller next interacts with it.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 04-41

# Build and test a single exercise
./run exercise 04-41-ex01
```

Unfinished exercises show as **skipped** (yellow circles). Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Generator Basics

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Implement a `fibonacci()` generator that co_yields the Fibonacci sequence:
0, 1, 1, 2, 3, 5, 8, 13, ...

The Generator<T> infrastructure is provided. Remove the `ex01_gate()` call
and write the coroutine body.

---

## Exercise 2: Range-for with Generator

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Implement `range(start, end)` that co_yields integers from start (inclusive)
to end (exclusive). The Generator has iterator support, so you can use it in
a range-for loop.

---

## Exercise 3: Simple Coroutine Task

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Implement `compute_task(n)` that co_returns n * n. This uses the Task<T>
coroutine type — a coroutine that produces a single result instead of a
sequence.

---

## Exercise 4: Chained Coroutines

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Implement two coroutines: `double_value(n)` which co_returns n * 2, and
`double_and_add(n, m)` which co_awaits double_value and adds m to the result.

---

## Exercise 5: Lazy Evaluation

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Implement `lazy_squares(n)` that lazily co_yields i*i for i from 0 to n-1.

---

## Exercise 6: Infinite Sequence

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Implement `naturals()` — an infinite generator yielding 0, 1, 2, 3, ...
Also implement `take(gen, n)` which pulls exactly n values from a generator
and returns them in a vector.

---

## Exercise 7: Exception in Coroutine

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Implement `validated_range(start, end)` — a generator that yields integers
from start to end-1, but throws `std::invalid_argument` if start > end.
Uses ThrowingGenerator which propagates exceptions to the caller.
