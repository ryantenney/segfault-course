---
title: "Lesson 38: Atomic Operations"
---

## Why This Lesson Exists

Mutexes are the workhorse of concurrent programming, but they have overhead:
a mutex lock/unlock involves a system call when there's contention. For simple
operations on small values (counters, flags, pointers), `std::atomic` provides
thread-safe access without any locking.

Atomic operations are the foundation of lock-free programming. Every mutex,
condition variable, and thread-safe container is ultimately built on top of
atomic hardware instructions like compare-and-swap (CAS).

## Key Concepts

### std::atomic&lt;T>

`std::atomic<T>` wraps a value of type `T` and guarantees that all reads
and writes are atomic (indivisible). For integral types and pointers, it also
provides arithmetic operations like `fetch_add` and `fetch_sub`.

```cpp
std::atomic<int> counter{0};
counter++;                    // atomic increment
int val = counter.load();     // atomic read
counter.store(42);            // atomic write
```

### Load and Store

Explicit `load()` and `store()` make the atomic intent clear:

```cpp
std::atomic<bool> flag{false};
flag.store(true);              // atomic write
bool b = flag.load();          // atomic read
```

### std::atomic_flag

The most primitive atomic type. Guaranteed lock-free on all platforms. Supports
only two operations: `test_and_set()` and `clear()`. Ideal for building
spinlocks.

```cpp
std::atomic_flag lock = ATOMIC_FLAG_INIT;
while (lock.test_and_set()) { /* spin */ }  // acquire
lock.clear();                                // release
```

### Compare-and-Swap (CAS)

`compare_exchange_weak` is the key to lock-free algorithms:

```cpp
int expected = current;
int desired = compute(current);
if (atom.compare_exchange_weak(expected, desired)) {
    // Success: atom was `expected`, now it's `desired`
} else {
    // Failure: atom wasn't `expected`; `expected` now holds actual value
}
```

The "weak" variant may fail spuriously (report failure even when values match),
so it's always used in a loop.

### fetch_add / fetch_sub

Atomic read-modify-write for integers. More efficient than a CAS loop for
simple arithmetic:

```cpp
std::atomic<int> x{10};
int old = x.fetch_add(3);   // old == 10, x is now 13
old = x.fetch_sub(5);       // old == 13, x is now 8
```

### Memory Orders

By default, atomics use `memory_order_seq_cst` (sequential consistency). This
is the safest and easiest to reason about. Other memory orders trade safety
for performance:

| Order | Guarantee |
|-------|-----------|
| `seq_cst` | Total order across all threads |
| `acquire` | This load "receives" writes from a release store |
| `release` | This store "publishes" all prior writes |
| `relaxed` | Only atomicity; no ordering guarantees |

The acquire-release pair creates a "happens-before" relationship:
```cpp
// Thread 1                      // Thread 2
data = 42;                       //
flag.store(true, release);       // if (flag.load(acquire))
                                 //     assert(data == 42);  // guaranteed
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 04-38

# Build and test a single exercise
./run exercise 04-38-ex01
```

Unfinished exercises show as **skipped** (yellow circles). Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Atomic Counter

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Implement a thread-safe counter using `std::atomic<int>`.

### What to do

1. Implement `increment()` -- use `++` or `fetch_add(1)`.
2. Implement `get()` -- use `load()`.
3. Implement `reset()` -- use `store(0)`.

---

## Exercise 2: Atomic Load/Store

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Practice using explicit `load()` and `store()` with `std::atomic<bool>`.

### What to do

1. Implement `set()` -- `flag_.store(true)`.
2. Implement `clear()` -- `flag_.store(false)`.
3. Implement `is_set()` -- `return flag_.load()`.

---

## Exercise 3: Atomic Flag Spinlock

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Build the simplest possible mutex using `std::atomic_flag`.

### What to do

1. Implement `lock()` -- spin on `test_and_set()` until it returns `false`.
2. Implement `unlock()` -- call `clear()`.

---

## Exercise 4: Compare-and-Swap

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Use `compare_exchange_weak` to implement lock-free algorithms: an atomic
maximum function and a lock-free stack push.

### What to do

1. Implement `atomic_max(atom, value)` -- CAS loop that updates atom to be
   `max(atom, value)`.
2. Implement `atomic_push(stack, value)` -- allocate a `StackNode`, point its
   `next` at the current head, then CAS the head from old to new.

---

## Exercise 5: Atomic Accumulation

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Use `fetch_add` and `fetch_sub` to build a statistics counter.

### What to do

1. Implement `add(int n)` -- `return value_.fetch_add(n)`.
2. Implement `subtract(int n)` -- `return value_.fetch_sub(n)`.
3. Implement `get()` -- `return value_.load()`.

---

## Exercise 6: Spinlock with Backoff

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Improve the spinlock from Exercise 3 by adding `std::this_thread::yield()`
in the spin loop.

### What to do

1. Implement `lock()` -- spin on `test_and_set()`, calling `yield()` on
   each failed attempt.
2. Implement `unlock()` -- call `clear()`.

---

## Exercise 7: Memory Order Awareness

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Practice using explicit memory orders: release stores and acquire loads.

### What to do

1. Implement `publish(int value)` -- store payload with `memory_order_release`,
   then store `ready_ = true` with `memory_order_release`.
2. Implement `consume()` -- load `ready_` with `memory_order_acquire`. If true,
   load and return payload with `memory_order_acquire`. Otherwise return `-1`.
3. Implement `payload_relaxed()` -- load payload with `memory_order_relaxed`.
