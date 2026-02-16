---
title: "Lesson 37: Condition Variables"
---

## Why This Lesson Exists

Mutexes protect shared data, but they can't coordinate *when* threads should
proceed. A thread that needs to wait for a specific condition (e.g., "the queue
is non-empty" or "the result is ready") would have to spin in a loop, wasting
CPU cycles. Condition variables solve this by letting a thread sleep until
another thread signals that the condition may have changed.

`std::condition_variable` works hand-in-hand with `std::mutex` and is the
primary tool for inter-thread coordination in C++.

## Key Concepts

### The Wait/Notify Pattern

A condition variable always works with:
1. A **mutex** that protects the shared state.
2. A **predicate** (boolean condition) that the waiting thread checks.

```cpp
std::mutex mtx;
std::condition_variable cv;
bool ready = false;

// Waiting thread:
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [&]{ return ready; });
    // ready is guaranteed to be true here
}

// Notifying thread:
{
    std::lock_guard<std::mutex> lock(mtx);
    ready = true;
}
cv.notify_one();
```

### Spurious Wakeups

The OS may wake a waiting thread even when no one called `notify`. This is
called a "spurious wakeup." Always use the predicate overload of `wait()` to
guard against this:

```cpp
cv.wait(lock, predicate);
// equivalent to:
// while (!predicate()) cv.wait(lock);
```

### notify_one vs notify_all

- `notify_one()` wakes exactly one waiting thread. Use this when only one
  thread can make progress (e.g., one producer, one consumer).
- `notify_all()` wakes all waiting threads. Use this when multiple threads
  may need to re-check their condition (e.g., a barrier, or when the condition
  involves different predicates for different waiters).

### Timed Waits

`wait_for()` and `wait_until()` add a timeout to the wait. They return
`std::cv_status::timeout` if the timeout expired, or `true`/`false` with the
predicate overload:

```cpp
bool got_it = cv.wait_for(lock, std::chrono::milliseconds(100),
                          [&]{ return ready; });
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 04-37

# Build and test a single exercise
./run exercise 04-37-ex01
```

Unfinished exercises show as **skipped** (yellow circles). Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Basic Wait/Notify

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Implement a `Notifier` class that uses a mutex and condition variable to let
one thread signal another.

### What to do

1. Implement `notify()` -- lock the mutex, set `ready_` to true, unlock, call
   `cv_.notify_one()`.
2. Implement `wait()` -- lock the mutex with `unique_lock`, call
   `cv_.wait(lock, predicate)` where the predicate checks `ready_`.

---

## Exercise 2: Predicate Wait

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Implement a `PredicateNotifier` that stores an integer value and lets threads
wait until it reaches a specific target.

### What to do

1. Implement `set_value(int v)` -- lock, set `value_`, unlock, notify all.
2. Implement `wait_for_value(int target)` -- use `cv.wait(lock, predicate)`
   where the predicate checks `value_ == target`.

---

## Exercise 3: Bounded Buffer

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Build a classic producer-consumer bounded buffer. Producers block when the
buffer is full; consumers block when it's empty.

### What to do

1. Implement `put(T item)` -- wait until not full, push item, notify not-empty.
2. Implement `take()` -- wait until not empty, pop front item, notify not-full.
3. Implement `size()` -- lock and return `queue_.size()`.

---

## Exercise 4: Work Queue

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Build an unbounded work queue with a shutdown mechanism. Worker threads call
`pop()` to get tasks; the queue owner calls `shutdown()` when done.

### What to do

1. Implement `push(T item)` -- lock, push, notify one.
2. Implement `pop()` -- wait until non-empty or shut down. Return the item as
   `std::optional<T>`, or `std::nullopt` if shut down and empty.
3. Implement `shutdown()` -- set the flag, notify all.

---

## Exercise 5: One-shot Event

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Build a one-shot event (latch). Once signaled, all current and future waiters
pass through immediately.

### What to do

1. Implement `signal()` -- set `signaled_`, notify all.
2. Implement `wait()` -- wait with predicate checking `signaled_`.

---

## Exercise 6: notify_one vs notify_all

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Build a barrier that blocks threads until a specified number have arrived,
then releases them all at once. This requires `notify_all()`.

### What to do

1. Implement `arrive_and_wait()` -- lock, increment `arrived_`. If
   `arrived_ == expected_`, notify all. Otherwise, wait with predicate
   `arrived_ >= expected_`.

---

## Exercise 7: Timed Wait

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Build a timed event that lets callers specify a maximum wait duration.

### What to do

1. Implement `signal()` -- set `signaled_`, notify all.
2. Implement `wait_for_ms(unsigned ms)` -- use `cv.wait_for()` with a
   `chrono::milliseconds` duration and a predicate. Return the bool result.
