---
title: "Lesson 09: RAII and Scope-Based Lifetime"
---

## Why This Lesson Exists

In C, you acquire a resource (memory, file handle, lock) and manually release it
later. If any code path — early return, error, exception — skips the release,
you have a leak or worse. Languages like Java and Python address this with
garbage collection, `try/finally`, or `with` statements.

C++ has a fundamentally different answer: **RAII** (Resource Acquisition Is
Initialization). The resource is acquired in a constructor and released in a
destructor. Since the compiler guarantees destructors run when objects go out of
scope — even during exception propagation — cleanup is automatic and
exception-safe.

RAII is not a library feature. It is the central design pattern of C++.
Everything from `std::string` to `std::unique_ptr` to `std::lock_guard` is an
RAII wrapper.

## Key Concepts

### The RAII Pattern

```cpp
class ResourceWrapper {
    Resource* res_;
public:
    ResourceWrapper()  { res_ = acquire_resource(); }  // acquire
    ~ResourceWrapper() { release_resource(res_); }     // release
};
```

The destructor is the key. It runs automatically when the object's scope ends:

```cpp
void process() {
    ResourceWrapper r;     // constructor acquires
    do_work();             // even if this throws...
}                          // ...destructor releases
```

### Destruction Order

Objects in the same scope are destroyed in **reverse order of construction**:

```cpp
{
    A a;  // constructed first
    B b;  // constructed second
    C c;  // constructed third
}         // destroyed: c, b, a
```

This guarantees that if `B` depends on `A`, `A` outlives `B`.

### RAII and Exceptions

C++ does not have `finally`. It doesn't need one. During stack unwinding (when
an exception propagates up the call stack), the compiler destroys all local
objects in each scope that is exited. RAII objects clean up their resources
automatically.

```cpp
void risky() {
    FileHandle file("data.txt");   // acquired
    process(file);                 // might throw!
}   // file's destructor runs — even if process() threw
```

### Non-Copyable RAII Types

Most RAII types should be **non-copyable**. If you copy a file handle wrapper,
both the original and the copy hold the same `FILE*`. When both destructors run,
`fclose()` is called twice on the same handle — undefined behavior.

```cpp
class FileHandle {
public:
    FileHandle(const FileHandle&) = delete;             // no copying
    FileHandle& operator=(const FileHandle&) = delete;  // no copying
};
```

Move semantics (covered in a later lesson) allow transferring ownership without
copying.

### Common RAII Wrappers in the Standard Library

| Class | Resource |
|-------|----------|
| `std::unique_ptr<T>` | Heap-allocated object |
| `std::shared_ptr<T>` | Reference-counted heap object |
| `std::lock_guard<M>` | Mutex lock |
| `std::unique_lock<M>` | Flexible mutex lock |
| `std::fstream` | File I/O |
| `std::string` | Character buffer |
| `std::vector<T>` | Dynamic array |

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 01-09

# Build and test a single exercise
./run exercise 01-09-ex01
```

---

## Exercise 1: Scoped Timer

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

A timer is a clean example of RAII: the constructor starts the measurement, and
the destructor records the result. The "resource" is the timing measurement
itself.

### What to do

1. Open `ex01.h`.
2. Add member variables: a `double&` for the output and a
   `std::chrono::steady_clock::time_point` for the start time.
3. Constructor: store the output reference and call `steady_clock::now()`.
4. Destructor: compute elapsed milliseconds and write to the output reference.
5. `elapsed_ms()`: return current elapsed time without stopping.
6. Run: `./run exercise 01-09-ex01`

---

## Exercise 2: File Handle Wrapper

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Wrap a C-style `FILE*` in an RAII class. The constructor opens the file with
`fopen()`, and the destructor closes it with `fclose()`. This is what
`std::fstream` does internally.

### What to do

1. Open `ex02.h`.
2. Add a `FILE*` member initialized to `nullptr`.
3. Constructor: call `fopen(path, mode)` and store the result.
4. Destructor: call `fclose()` if the file was opened.
5. Implement `is_open()`, `write()`, and `read_all()`.
6. Run: `./run exercise 01-09-ex02`

---

## Exercise 3: Scoped Lock (Manual)

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Build a simplified `std::lock_guard`: lock in the constructor, unlock in the
destructor. Then use it to build a thread-safe counter.

### What to do

1. Open `ex03.h`.
2. Add a `std::mutex&` member to `ScopedLock`.
3. Constructor: call `mtx.lock()`.
4. Destructor: call `mtx_.unlock()`.
5. In `SafeCounter`, use `ScopedLock` to protect `increment()` and `get()`.
6. Run: `./run exercise 01-09-ex03`

---

## Exercise 4: Prove Cleanup Order

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

This exercise makes destruction order concrete. You implement a `Logger` class
that appends to a string in its constructor and destructor, then predict the
output.

### What to do

1. Open `ex04.h`.
2. In the `Logger` constructor, append `"ctor:<name> "` to the log.
3. In the destructor, append `"dtor:<name> "` to the log.
4. In `predicted_output()`, return the expected string for three objects A, B, C
   constructed and destroyed in a single scope.
5. In `predicted_nested_output()`, return the expected string for nested scopes.
6. Run: `./run exercise 01-09-ex04`

---

## Exercise 5: RAII for Dynamic Allocation

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Build a simplified `unique_ptr<int>`. The constructor calls `new`, the
destructor calls `delete`. An `AllocTracker` lets the tests verify that all
allocations are properly freed.

### What to do

1. Open `ex05.h`.
2. Add an `int*` member.
3. Constructor: allocate with `new int(value)`, increment `AllocTracker`.
4. Destructor: `delete` the pointer, decrement `AllocTracker`.
5. Implement `get()`, `value()`, and `set()`.
6. Run: `./run exercise 01-09-ex05`

---

## Exercise 6: Scope Guard

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

A scope guard is a generic RAII wrapper: it takes any callable and runs it in the
destructor. This lets you write ad-hoc cleanup without creating a dedicated class.

### What to do

1. Open `ex06.h`.
2. Add a `Func` member to `ScopeGuard`.
3. Constructor: store the callable.
4. Destructor: invoke the callable.
5. In `make_scope_guard`, return a `ScopeGuard<Func>` constructed from the
   callable.
6. Run: `./run exercise 01-09-ex06`

---

## Exercise 7: RAII Survives Exceptions

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

This exercise proves that destructors run during stack unwinding. You create RAII
objects, throw an exception, and verify that all destructors executed in the
correct order.

### What to do

1. Open `ex07.h`.
2. In the `Tracker` constructor, append `"acquire:<name> "` to the log.
3. In the destructor, append `"release:<name> "` to the log.
4. In `function_that_throws`, create two Trackers then throw.
5. In `demonstrate_exception_safety`, call it in a try/catch, append "caught ".
6. In `predicted_exception_output`, return the expected string.
7. Run: `./run exercise 01-09-ex07`

---

## Exercise 8: Non-Copyable RAII

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Copying an RAII object that owns a resource creates a double-ownership bug: both
copies think they own the resource, and both destructors release it. The fix is
to delete the copy operations.

### What to do

1. Open `ex08.h`.
2. Add `char*` and `int` members to `UniqueBuffer`.
3. Constructor: allocate with `new char[size]`, fill with `memset`.
4. Destructor: `delete[]` the buffer.
5. Notice the copy constructor and copy assignment are already `= delete`.
   Understand why: copying would leave two objects pointing at the same buffer.
6. Implement `size()`, `at()`, `set()`, and `as_string()`.
7. In `why_no_copy()`, return `"double free"` — because both destructors would
   call `delete[]` on the same pointer.
8. Run: `./run exercise 01-09-ex08`
