# Lesson 42: Async I/O Patterns

## Why This Lesson Exists

Async I/O is how high-performance servers, network clients, and UI frameworks
handle concurrency without creating a thread per operation. Instead of blocking
a thread while waiting for I/O, you register a callback that fires when the
operation completes. A single thread can manage thousands of concurrent
operations this way.

This lesson builds up the async pattern stack from the ground floor: callbacks,
futures, coroutine awaitables, and event loops. Everything is single-threaded
and simulated — no actual I/O or threading is involved. This lets you focus on
the patterns without race conditions or timing issues.

## Key Concepts

### Callback Pattern

The simplest async pattern: pass a function that gets called when the
operation completes.

```cpp
void async_read(std::function<void(const std::string&)> callback) {
    // ...operation happens...
    callback("result");
}
```

**Pros:** Simple, zero overhead.
**Cons:** Callback hell when chaining operations.

### Error-First Callbacks

Callbacks take an error code as the first argument:

```cpp
void async_read(std::function<void(int error, const std::string& data)> cb) {
    if (success) cb(0, "data");
    else         cb(1, "");
}
```

### Future/Promise Bridge

Wrap a callback API into a `std::future`:

```cpp
std::future<std::string> future_read() {
    auto promise = std::make_shared<std::promise<std::string>>();
    async_read([promise](const std::string& data) {
        promise->set_value(data);
    });
    return promise->get_future();
}
```

### Coroutine Awaitables

Wrap a callback API into something a coroutine can `co_await`:

```cpp
struct ReadAwaitable {
    std::string result;
    bool await_ready() { /* call async API, store result */ return true; }
    void await_suspend(std::coroutine_handle<>) {}
    std::string await_resume() { return result; }
};
```

### Event Loop

A single-threaded loop that processes a queue of callbacks:

```cpp
class EventLoop {
    std::queue<std::function<void()>> queue_;
public:
    void post(std::function<void()> cb) { queue_.push(std::move(cb)); }
    void run() { while (!queue_.empty()) { queue_.front()(); queue_.pop(); } }
};
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 04-42

# Build and test a single exercise
./run exercise 04-42-ex01
```

---

## Exercise 1: Callback-based API

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Implement `async_read(callback)` that calls the callback with "hello, world".

---

## Exercise 2: Callback with Error Handling

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Implement `async_read_success()` and `async_read_failure()` with error-first
callbacks: (error_code, result).

---

## Exercise 3: Future-based Wrapper

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Wrap a callback-based API into a `std::future<std::string>` returning function.

---

## Exercise 4: Callback to Coroutine

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Create a `ReadAwaitable` that wraps a callback API for use with `co_await`.
Implement `coroutine_read()` that co_awaits and co_returns the result.

---

## Exercise 5: Simulated Event Loop

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Implement an `EventLoop` class with `post()` and `run()`. Single-threaded,
FIFO execution.

---

## Exercise 6: Timer in Event Loop

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Extend the event loop with `post_delayed(ticks, callback)`. Callbacks execute
in tick order using a priority queue.

---

## Exercise 7: Multiple Pending Operations

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Implement an `OperationTracker` that submits named operations with delays to
the event loop and tracks completion order.
