---
title: "Lesson 35: Threads and Basic Thread Safety"
---

## Why This Lesson Exists

Modern CPUs have multiple cores, but a single-threaded program only uses one of
them.  C++ gives you direct control over threads — you can launch OS threads,
divide work across them, and synchronize their access to shared data.  This
lesson introduces the fundamentals: launching threads, passing arguments, joining
them, and understanding the most common concurrency bug — the data race.

## Key Concepts

### std::thread

`std::thread` runs a callable (function, lambda, functor) in a new OS thread:

```cpp
void work() { /* ... */ }
std::thread t(work);  // launches a new thread running work()
t.join();              // blocks until the thread finishes
```

You **must** either `join()` or `detach()` every thread before its destructor
runs.  Forgetting to do so calls `std::terminate`.

### Passing Arguments

`std::thread` copies arguments by default.  To pass by reference, use
`std::ref()`:

```cpp
void add_to(int& target, int amount) { target += amount; }

int value = 0;
std::thread t(add_to, std::ref(value), 42);
t.join();
// value is now 42
```

### std::jthread (C++20)

`std::jthread` is a safer alternative that automatically joins in its destructor
and supports cooperative cancellation via `std::stop_token`:

```cpp
{
    std::jthread jt([](std::stop_token token) {
        while (!token.stop_requested()) {
            // do work
        }
    });
    // jt.request_stop() called automatically in destructor
}
// thread has been joined
```

### Data Races

A **data race** occurs when two threads access the same memory location
concurrently, at least one access is a write, and there is no synchronization.
In C++, data races are undefined behavior.

### std::atomic

For simple shared variables, `std::atomic<T>` provides thread-safe operations
without explicit locking:

```cpp
std::atomic<int> counter{0};
counter.fetch_add(1);  // thread-safe increment
int value = counter.load();  // thread-safe read
```

### std::mutex and std::lock_guard

For protecting arbitrary critical sections, use a mutex with RAII locking:

```cpp
std::mutex mtx;
int shared_data = 0;

{
    std::lock_guard<std::mutex> lock(mtx);
    shared_data += 1;  // safe: mutex is held
}
// mutex released when lock_guard is destroyed
```

### thread_local

`thread_local` variables have a separate instance per thread.  Each thread gets
its own copy, initialized independently:

```cpp
thread_local int call_count = 0;
++call_count;  // only affects this thread's copy
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 04-35

# Build and test a single exercise
./run exercise 04-35-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Launch and Join

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Implement `compute_answer(int& result)` so it sets `result` to 42.  The tests
first call it directly (no threading), then from a `std::thread` to verify it
works in both contexts.

---

## Exercise 2: Thread with Arguments

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Implement `add_to(int& target, int amount)` to add `amount` to `target`.  The
tests pass arguments via `std::ref` when launching the thread.

---

## Exercise 3: jthread Basics

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Implement `fill_vector(std::vector<int>& v, int count)` to push the integers
0 through count-1 into the vector.  The tests use `std::jthread` which
automatically joins when it goes out of scope.

---

## Exercise 4: jthread and stop_token

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Implement `count_until_stopped(std::stop_token, std::atomic<int>&)` to increment
the counter in a loop until stop is requested.  The tests verify that the thread
actually stops when asked.

---

## Exercise 5: Identify a Data Race

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Implement `safe_increment(std::atomic<int>& counter)` to atomically increment
the counter by 1.  The tests run many threads concurrently to verify correctness.

---

## Exercise 6: Fix the Data Race

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Implement the `ThreadSafeCounter` class with `increment()` and `get()` methods,
both protected by a `std::mutex` and `std::lock_guard`.

---

## Exercise 7: Thread-local Storage

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Implement `get_call_count()` using a `thread_local` variable.  It should return
the number of times it has been called on the current thread (first call
returns 1, second returns 2, etc.).  Remove the `ex07_gate()` call and add your
implementation.

---

## Exercise 8: Launch N Threads

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Implement `parallel_sum(const std::vector<int>& data, int num_threads)` to split
the data across multiple threads, compute partial sums in parallel, and return
the total.  Each thread should write to its own element of a results vector so
no synchronization is needed.
