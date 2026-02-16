---
title: "Lesson 36: Mutexes and Locks"
---

## Why This Lesson Exists

The previous lesson introduced threads and basic safety with `std::atomic`.
Atomics work for individual variables, but most real-world shared state involves
multiple fields, containers, or compound operations that must happen together.
That's where mutexes come in: they protect arbitrary critical sections of code,
ensuring that only one thread (or multiple readers) can access shared data at
a time.

C++ provides several mutex types and RAII lock wrappers.  This lesson covers
them all, from the simple `lock_guard` to the flexible `unique_lock` to the
reader-friendly `shared_mutex`.

## Key Concepts

### std::mutex

A mutex (mutual exclusion) is a synchronization primitive.  A thread that
locks the mutex owns it exclusively — all other threads trying to lock it
will block until it's released.

```cpp
std::mutex mtx;
mtx.lock();
// critical section — only one thread at a time
mtx.unlock();
```

Never call `lock()` / `unlock()` directly.  Use RAII wrappers instead.

### std::lock_guard

The simplest RAII lock.  Acquires the mutex in its constructor, releases it in
its destructor.  Cannot be unlocked early or moved.

```cpp
{
    std::lock_guard<std::mutex> lock(mtx);
    // mutex held for this entire scope
}
// mutex released
```

### std::unique_lock

A more flexible RAII lock.  Supports deferred locking, try-locking, timed
locking, and manual lock/unlock:

```cpp
std::unique_lock<std::mutex> lock(mtx, std::try_to_lock);
if (lock.owns_lock()) {
    // got the lock
}
```

### std::scoped_lock (C++17)

Locks multiple mutexes simultaneously without risking deadlock:

```cpp
std::scoped_lock lock(mutex_a, mutex_b);
// both mutexes held; released when lock is destroyed
```

### std::shared_mutex (C++17)

Allows multiple simultaneous readers OR one exclusive writer:

```cpp
std::shared_mutex smtx;

// Reader:
std::shared_lock<std::shared_mutex> rlock(smtx);
// ... read shared data ...

// Writer:
std::unique_lock<std::shared_mutex> wlock(smtx);
// ... modify shared data ...
```

### std::timed_mutex

Like `std::mutex`, but supports `try_lock_for()` and `try_lock_until()` for
bounded waiting:

```cpp
std::timed_mutex tmtx;
std::unique_lock<std::timed_mutex> lock(tmtx, std::chrono::milliseconds(100));
if (lock.owns_lock()) {
    // acquired within timeout
}
```

### Deadlock

Deadlock occurs when two or more threads each hold a lock and wait for a lock
held by another thread.  The classic pattern:

- Thread 1: lock A, then try to lock B
- Thread 2: lock B, then try to lock A
- Both threads wait forever.

**Prevention:** Always acquire locks in a consistent order, or use
`std::scoped_lock` which handles ordering automatically.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 04-36

# Build and test a single exercise
./run exercise 04-36-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Protect Shared Data

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Implement `GuardedCounter` with `increment()`, `decrement()`, and `get()` — all
protected by a mutex and `lock_guard`.

---

## Exercise 2: lock_guard Scope

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Implement `transfer()` between two `GuardedAccount` objects.  Lock each account
in its own scope to minimize how long the lock is held.

---

## Exercise 3: Scoped Lock for Multiple Mutexes

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Implement `safe_swap()` using `std::scoped_lock` to lock two `LockedBox`
mutexes simultaneously.  The test verifies no deadlock under contention.

---

## Exercise 4: unique_lock Flexibility

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Implement `try_process()` using `std::unique_lock` with `std::try_to_lock`.
If the lock is busy, return -1 instead of blocking.

---

## Exercise 5: Timed Lock

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Implement `try_lock_for_ms()` using `std::timed_mutex` and
`unique_lock::try_lock_for`.  If the lock isn't acquired within the timeout,
give up.

---

## Exercise 6: Shared Mutex for Readers

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Implement `ReadWriteMap` with `put()`, `get()`, and `contains()`.  Use
`std::shared_lock` for reads and `std::unique_lock` for writes.

---

## Exercise 7: Deadlock Identification

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

The header shows a commented-out `broken_transfer()` that deadlocks.  Implement
`safe_transfer()` using `std::scoped_lock` to avoid the deadlock.

---

## Exercise 8: Thread-safe Wrapper

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Implement `Synchronized<T>` with an `apply()` method that locks the mutex and
passes the wrapped value to a callable.  This pattern makes it impossible to
access the data without holding the lock.
