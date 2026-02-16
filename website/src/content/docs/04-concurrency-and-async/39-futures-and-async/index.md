---
title: "Lesson 39: Futures and Async"
---

## Why This Lesson Exists

Threads give you concurrency, but they force you to manage shared state
manually with mutexes and condition variables. The futures and async model
provides a higher-level abstraction: you launch work and get back a handle
(a `std::future`) that you can query later for the result.

This is the foundation of task-based parallelism in C++. Instead of thinking
about threads and locks, you think about values that will be available in the
future.

## Key Concepts

### std::async

`std::async` launches a callable (potentially in a new thread) and returns a
`std::future` that will hold the result:

```cpp
auto f = std::async(std::launch::async, [] { return 42; });
int result = f.get();  // blocks until the result is ready
```

### Launch Policies

- `std::launch::async` — runs in a new thread immediately
- `std::launch::deferred` — runs lazily when `.get()` or `.wait()` is called
- Default (no policy) — implementation chooses

### std::promise and std::future

A `std::promise` is the "write" end of a channel; `std::future` is the "read"
end. You create a promise, extract its future, then set the value from any
thread:

```cpp
std::promise<int> p;
std::future<int> f = p.get_future();
p.set_value(42);
int result = f.get();
```

### Exception Propagation

If an async task throws, the exception is captured and re-thrown when you call
`.get()` on the future. This makes error handling natural.

### std::shared_future

A regular `std::future` can only be `.get()`-ed once (it moves the value out).
A `std::shared_future` allows multiple `.get()` calls and can be copied so
multiple threads can wait on the same result.

### std::packaged_task

A `std::packaged_task` wraps a callable and provides a future for its result.
Unlike `std::async`, it does not launch a thread — you decide when and where
to execute it.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 04-39

# Build and test a single exercise
./run exercise 04-39-ex01
```

Unfinished exercises show as **skipped** (yellow circles). Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Async Computation

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Implement `async_square(int n)` which returns a `std::future<int>` that
resolves to `n * n`. Use `std::async` to launch the computation.

---

## Exercise 2: Launch Policies

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Implement `deferred_compute(int n)` which returns a `std::future<int>` using
`std::launch::deferred`. The future should resolve to `n * n + 1`. Deferred
futures only execute when `.get()` or `.wait()` is called.

---

## Exercise 3: Promise-Future Channel

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Implement `send_value(std::promise<int>& p, int val)` which sets `val` on the
promise. The test creates a promise, calls `send_value`, and checks the future.

---

## Exercise 4: Exception Propagation

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Implement `async_divide(int a, int b)` which returns a `std::future<int>`.
If `b` is zero, the async task should throw `std::invalid_argument`. Otherwise
it returns `a / b`.

---

## Exercise 5: Multiple Futures

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Implement `async_transform(const std::vector<int>& v)` which returns a
`std::vector<std::future<int>>`. Each future computes the square of the
corresponding input element.

---

## Exercise 6: wait_for with Timeout

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Implement `slow_compute(int n)` which returns a `std::future<int>` that
resolves to `n * 2`. The computation itself should be straightforward (no
artificial delay needed).

---

## Exercise 7: Shared Future

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Implement `make_shared_result(int n)` which returns a `std::shared_future<int>`
that resolves to `n * 10`. A shared future can be `.get()`-ed multiple times
and copied across threads.

---

## Exercise 8: Packaged Task

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

Implement `make_task(int n)` which returns a `std::packaged_task<int()>`.
When executed, the task should produce `n * n + n`. The caller decides when
to run the task and retrieves the result via the associated future.
