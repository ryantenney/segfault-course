# Lesson 50: Logging and Diagnostics

## Why This Lesson Exists

Every production system needs logging. Good logging helps you understand what
your program is doing, diagnose bugs, and monitor performance. This lesson
builds a logging system from scratch, exercising level filtering, structured
output, sink abstraction, compile-time optimization, scoped context, and
thread safety.

## Key Concepts

### Log Levels

Loggers filter messages by severity. Common levels (lowest to highest):
Debug, Info, Warn, Error. Messages below the configured threshold are
discarded.

### Structured Logging

Instead of free-form strings, structured logs attach key-value fields to
each entry. This makes logs machine-parseable and easy to query.

### Sink Abstraction

A "sink" is where log output goes. By defining an abstract `Sink` interface
with a `write()` method, the logger is decoupled from the output destination.
Concrete sinks include console output, file writers, and in-memory buffers
for testing.

### if constexpr for Zero-Cost Logging

When a log level is known at compile time (via a template parameter),
`if constexpr` can eliminate disabled log statements entirely. The compiler
removes the dead branch, producing zero runtime overhead.

### RAII Context Scoping

Log context (like a request ID) can be pushed onto a stack when entering
a scope and automatically popped when leaving. This RAII pattern ensures
context is always cleaned up, even if exceptions are thrown.

### Thread Safety

When multiple threads share a logger, internal data structures must be
protected with a mutex. `std::lock_guard` provides exception-safe locking.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 05-50

# Build and test a single exercise
./run exercise 05-50-ex01
```

Unfinished exercises show as **skipped** (yellow circles). Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Basic Logger

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Implement a logger with level filtering (debug/info/warn/error). Messages
below the threshold are silently discarded.

---

## Exercise 2: Formatted Output

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Build log messages with key-value fields using ostringstream. Format:
"[LEVEL] message | key1=val1 key2=val2".

---

## Exercise 3: Source Location

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Capture file and line at the call site using `__FILE__` and `__LINE__`
macros. Format the location as "filename:line".

---

## Exercise 4: Structured Log Entry

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Create a `LogEntry` with timestamp, level, message, and fields map.
Format it into a human-readable string with ISO-style timestamp.

---

## Exercise 5: Log Sink Abstraction

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Define a `Sink` interface and implement `ConsoleSink` and `MemorySink`.
The logger writes formatted messages through the sink abstraction.

---

## Exercise 6: Zero-cost Disabled Logs

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Use `if constexpr` with a template level parameter so that disabled log
levels produce no entries and incur zero runtime cost.

---

## Exercise 7: Log Context/Scope

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Push/pop context strings that prefix all nested log messages. Use RAII
(`LogScope`) so context is automatically cleaned up.

---

## Exercise 8: Thread-safe Logger

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Add mutex protection to the logger. Tests verify correctness with
single-threaded gating, then exercise concurrent reads and writes.
