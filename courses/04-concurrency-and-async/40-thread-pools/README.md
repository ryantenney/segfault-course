# Lesson 40: Thread Pools

## Why This Lesson Exists

Creating a new thread for every task is expensive: each thread allocates stack
memory, and the OS must schedule it. When you have thousands of short tasks,
the overhead of thread creation can dwarf the actual work.

A **thread pool** solves this by pre-creating a fixed set of worker threads
that pull tasks from a shared queue. Tasks are submitted to the pool and
executed by whichever worker thread is available. This amortizes the cost of
thread creation across many tasks.

Thread pools are the backbone of high-performance servers, game engines,
and parallel algorithms.

## Key Concepts

### Architecture

A thread pool has three parts:

1. **Worker threads** — a fixed set of threads that loop forever, waiting for
   tasks and executing them.
2. **Task queue** — a thread-safe queue that holds pending tasks. Workers
   dequeue from it; callers enqueue to it.
3. **Synchronization** — a mutex and condition variable to coordinate access
   to the queue and signal workers when new tasks arrive.

### Submission with Futures

When you submit a task to a pool, you want a way to retrieve the result.
`std::packaged_task` wraps a callable and provides a `std::future` for its
return value. The pool stores the packaged task in its queue; the caller
holds the future.

### Graceful Shutdown

When shutting down, the pool must:
1. Signal all workers to stop (e.g., set a flag).
2. Notify all waiting workers (so they wake up and see the flag).
3. Join all threads (wait for in-progress tasks to complete).

### Important Notes

Each exercise in this lesson is **self-contained**. Every exercise defines
its own pool-like class with just enough complexity to test the target
concept. Exercises do not depend on each other.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 04-40

# Build and test a single exercise
./run exercise 04-40-ex01
```

Unfinished exercises show as **skipped** (yellow circles). Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Fixed Thread Vector

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Implement `BasicPool` that creates N `std::jthread`s in its constructor. The
threads don't need to do useful work yet (they can just wait on a condition
variable). Provide a `size()` method returning the number of threads.

---

## Exercise 2: Worker Loop

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Implement `WorkerPool` where worker threads pull `std::function<void()>` tasks
from a shared queue and execute them. Provide `submit(std::function<void()>)`
to enqueue tasks.

---

## Exercise 3: Submit with Future

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Implement `FuturePool` with a `submit()` that returns `std::future<T>`. Use
`std::packaged_task` internally to connect the submitted callable to a future.

---

## Exercise 4: Submit Different Types

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Implement `TypedPool` that supports submitting tasks returning different types
(int, string, void). The `submit()` method should be a template.

---

## Exercise 5: Graceful Shutdown

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Implement `ShutdownPool` with an explicit `shutdown()` method. After shutdown,
no new tasks are accepted. Workers finish their current tasks and exit.

---

## Exercise 6: Pool Statistics

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Implement `StatsPool` that tracks `active_count()`, `pending_count()`, and
`completed_count()` — the number of currently executing tasks, queued tasks,
and finished tasks respectively.

---

## Exercise 7: Pool Resize

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Implement `ResizablePool` with a `resize(n)` method that grows or shrinks
the number of worker threads at runtime.
