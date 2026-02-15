# Course 4: Concurrency and Async

Essential for web servers and high-performance applications. This course covers
thread management, synchronization primitives, lock-free programming, and async
patterns from low-level threading through high-level coroutines. By the end,
you will be able to write correct concurrent code, build a thread pool, and
understand the tradeoffs between callbacks, futures, and coroutines.

## Prerequisites

Complete Courses 1 through 3 first. You should be comfortable with RAII, smart
pointers, move semantics, lambdas, `std::function`, and class design. Concurrency
builds heavily on ownership semantics -- understanding who owns shared data and
how lifetimes interact with threads is critical to writing safe concurrent code.

## Lessons

| # | Lesson | Exercises | Description |
|---|--------|-----------|-------------|
| 35 | [Threads and Basic Thread Safety](35-threads-and-basic-thread-safety/) | 8 | `std::thread`, `std::jthread`, `stop_token`, data races, thread-local storage |
| 36 | [Mutexes and Locks](36-mutexes-and-locks/) | 8 | `mutex`, `lock_guard`, `scoped_lock`, `unique_lock`, `shared_mutex`, deadlock avoidance |
| 37 | [Condition Variables](37-condition-variables/) | 7 | `wait`/`notify`, spurious wakeups, bounded buffer, producer-consumer pattern |
| 38 | [Atomic Operations](38-atomic-operations/) | 7 | `std::atomic`, `atomic_flag`, compare-and-swap, spinlocks, memory ordering basics |
| 39 | [Futures and Async](39-futures-and-async/) | 8 | `std::async`, `future`, `promise`, `packaged_task`, `shared_future` |
| 40 | [Thread Pools](40-thread-pools/) | 7 | Work queue, fixed worker threads, `submit()` with futures, graceful shutdown |
| 41 | [Coroutines Introduction (C++20)](41-coroutines-introduction/) | 7 | `co_yield`, `co_return`, `co_await`, generators, lazy sequences |
| 42 | [Async I/O Patterns](42-async-io-patterns/) | 7 | Callback-based, future-based, and coroutine-based async; event loop concepts |

**Total: 8 lessons, 59 exercises**

## How to Run

```bash
# Run all tests for this course
./run course 04

# Run all tests for a specific lesson (e.g., lesson 36)
./run lesson 04-36

# Run a single exercise (e.g., lesson 36, exercise 01)
./run exercise 04-36-ex01
```

Unfinished exercises show as **skipped** (not-implemented). Completed exercises
show as **passed** or **failed**. Work through the lessons in order -- each one
builds on the primitives introduced in the previous lesson.
