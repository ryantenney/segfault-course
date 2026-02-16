# Lesson 47: Resource Pools

## Why This Lesson Exists

Some objects are expensive to create — database connections require a TCP
handshake and authentication, thread contexts allocate stack memory, GPU
buffers need device allocation.  Creating and destroying these on every use
wastes time and resources.

A **resource pool** keeps a reserve of pre-built (or lazily-created) objects.
Callers *acquire* an object from the pool, use it, and *release* it back when
done.  The pool recycles objects instead of destroying them.  This is one of
the most common patterns in server-side C++ code.

This lesson builds the pattern incrementally: from a basic stack of objects,
through RAII handles, factory-based creation, thread safety, health checks,
statistics, and timeout-based acquisition.

## Key Concepts

### Basic Pool (Acquire / Release)

The simplest pool is a stack of pre-built objects.  `acquire()` pops one off;
`release()` pushes it back:

```cpp
template <typename T>
class Pool {
    std::vector<T> objects_;
public:
    T acquire() {
        T obj = std::move(objects_.back());
        objects_.pop_back();
        return obj;
    }
    void release(T obj) {
        objects_.push_back(std::move(obj));
    }
};
```

### RAII Pool Handles

Manually calling `release()` is error-prone — if an exception is thrown or
the caller forgets, the object leaks out of the pool.  An RAII handle (like
`std::unique_ptr` with a custom deleter) automatically returns the object
when the handle goes out of scope.

### Factory Pools

A fixed-size pool runs out quickly under load.  A factory pool creates new
objects on demand (via a `std::function<T()>`) up to a maximum capacity.
Once the limit is reached, further `acquire()` calls throw.

### Thread Safety

In a multi-threaded server, many threads share one pool.  A `std::mutex`
protects the internal state.  A `std::condition_variable` lets threads block
when the pool is empty instead of throwing immediately:

```cpp
T acquire() {
    std::unique_lock lock(mtx_);
    cv_.wait(lock, [&] { return !objects_.empty(); });
    T obj = std::move(objects_.back());
    objects_.pop_back();
    return obj;
}
```

### Health Checks

Pooled objects can go stale (e.g., a database connection closed by the
server).  Before handing an object to a caller, the pool validates it.
Unhealthy objects are discarded and replacements are created via the factory.

### Timeouts

Blocking forever on an empty pool is dangerous in production.  A timeout-based
pool waits up to N milliseconds using `cv_.wait_for()`, then returns
`std::nullopt` if no resource became available.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 05-47

# Build and test a single exercise
./run exercise 05-47-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Basic Object Pool

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Implement `Pool<T>` — a template class that stores objects in a
`std::vector<T>` with stack semantics.

### What to do

1. Constructor: store the initial objects from the given vector.
2. `acquire()` — pop and return the last object.  Throw
   `std::runtime_error("pool exhausted")` if empty.
3. `release(T obj)` — push the object back into the pool.
4. `available()` — return the number of idle objects.
5. Run: `./run exercise 05-47-ex01`

---

## Exercise 2: RAII Pool Handle

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Implement `PoolHandle<T>` — an RAII wrapper that automatically returns an
object to the pool when the handle is destroyed.

### What to do

1. Constructor: store the object in a `std::optional<T>` and save the pool
   pointer.
2. Destructor: if the handle still owns an object, release it back to the
   pool.
3. `operator*()` / `operator->()`: provide access to the held object.
4. Move constructor and move assignment: transfer ownership.  The moved-from
   handle must not return anything to the pool.
5. Delete copy operations.
6. Run: `./run exercise 05-47-ex02`

---

## Exercise 3: Pool with Factory

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Implement `FactoryPool<T>` — a pool that creates new objects on demand via a
factory function, up to a maximum capacity.

### What to do

1. `acquire()` — if an idle object is available, return it.  Otherwise, if
   `total_created < max_size`, call the factory.  If at capacity, throw
   `std::runtime_error("pool at capacity")`.
2. `release(T obj)` — return to the idle pool.
3. `idle_count()` — number of objects sitting idle.
4. `total_created()` — total objects ever created by the factory.
5. Run: `./run exercise 05-47-ex03`

---

## Exercise 4: Thread-safe Pool

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Implement `ThreadSafePool<T>` — a pool protected by a mutex where `acquire()`
blocks until an object is available using a condition variable.

### What to do

1. `acquire()` — lock the mutex, wait on the condition variable until an
   object is available, then pop and return it.
2. `release(T obj)` — lock the mutex, push the object back, notify one
   waiting thread.
3. `available()` is provided.
4. Run: `./run exercise 05-47-ex04`

---

## Exercise 5: Pool with Health Check

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Implement `HealthCheckPool<T>` — a factory pool that validates objects before
handing them out.  Unhealthy objects are discarded and replacements are
created.

### What to do

1. `acquire()` — pop idle objects and run the health check on each.  Discard
   unhealthy ones (decrement alive count, increment discard count).  Return
   the first healthy one.  If none remain, create via the factory (if under
   max_size), otherwise throw `std::runtime_error("pool at capacity")`.
2. `release(T obj)` — push back to idle (no check).
3. `idle_count()`, `total_created()`, `discarded()` — statistics.
4. Run: `./run exercise 05-47-ex05`

---

## Exercise 6: Pool Statistics

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Implement `StatsPool<T>` — a pool that tracks how many objects are currently
checked out (active), idle, and total.

### What to do

1. Constructor: store the initial objects, set `total_created_` to their count.
2. `acquire()` — pop an idle object and increment the active count.  Throw
   `std::runtime_error("pool exhausted")` if empty.
3. `release(T obj)` — push back and decrement the active count.
4. `active_count()`, `idle_count()`, `total_created()` — return the counters.
5. Run: `./run exercise 05-47-ex06`

---

## Exercise 7: Pool with Timeout

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Implement `TimeoutPool<T>` — a thread-safe pool where `try_acquire()` waits
up to a given timeout for a resource.  Returns `std::nullopt` if the timeout
expires.

### What to do

1. `try_acquire(std::chrono::milliseconds timeout)` — lock the mutex, use
   `cv_.wait_for(lock, timeout, predicate)`.  Return the object if one
   becomes available, or `std::nullopt` if timed out.
2. `release(T obj)` — push back and notify one waiter.
3. `available()` is provided.
4. Run: `./run exercise 05-47-ex07`
