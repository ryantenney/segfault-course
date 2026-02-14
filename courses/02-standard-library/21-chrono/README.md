# Lesson 21: Chrono

## Why This Lesson Exists

Time handling in C and early C++ was messy: raw integers for seconds, manual
conversions between units, and easy-to-confuse parameters (is that argument in
seconds or milliseconds?).  `<chrono>` fixes all of this with a type-safe time
library where units are part of the type system.  The compiler catches
unit-mismatch bugs at compile time.

## Key Concepts

### Clocks

C++ provides three clocks:

| Clock | Purpose | Monotonic? |
|---|---|---|
| `steady_clock` | Measuring intervals | Yes |
| `system_clock` | Wall-clock / calendar time | No |
| `high_resolution_clock` | Alias for the finest clock available | Varies |

Use `steady_clock` for benchmarking and timeouts.  Use `system_clock` when you
need to display or persist calendar dates/times.

### Durations

`std::chrono::duration<Rep, Period>` represents a time span.  Predefined
types include `nanoseconds`, `microseconds`, `milliseconds`, `seconds`,
`minutes`, and `hours`.

```cpp
using namespace std::chrono;
auto a = seconds(3);
auto b = milliseconds(500);
auto c = a + b;          // milliseconds(3500) — auto-converts to finer unit
c.count();                // 3500
```

### Duration Arithmetic

Durations support `+`, `-`, `*`, `/`.  Mixed-unit arithmetic promotes to the
finer unit.  To go from fine to coarse, use `duration_cast` (which truncates):

```cpp
auto ms = milliseconds(2500);
auto s = duration_cast<seconds>(ms);  // seconds(2) — truncated
```

### Time Points

`time_point<Clock, Duration>` represents a specific moment.  Subtracting two
time points yields a duration.  Adding a duration to a time point yields a
new time point.

```cpp
auto start = steady_clock::now();
// ... do work ...
auto end = steady_clock::now();
auto elapsed = end - start;  // a duration
```

### Formatting

To display a `system_clock::time_point` as a human-readable string, convert
through `time_t` and use `std::put_time`:

```cpp
auto tp = system_clock::now();
auto t = system_clock::to_time_t(tp);
auto tm = *std::gmtime(&t);
std::cout << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
```

### Sleeping

`std::this_thread::sleep_for(duration)` and `sleep_until(time_point)` accept
chrono types directly:

```cpp
std::this_thread::sleep_for(std::chrono::milliseconds(100));
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 02-21

# Build and test a single exercise
./run exercise 02-21-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Measure Elapsed Time

**Files:** `ex01.h` (edit) - `ex01_test.cpp` (read-only)

`steady_clock` is the right clock for measuring durations.  Subtract two time
points to get a duration, then use `duration_cast` to convert to the unit you
need.

### What to do

1. `elapsed_ms()` -- return milliseconds between two time points.
2. `elapsed_us()` -- return microseconds between two time points.
3. `elapsed_between()` -- add a duration offset to a start time point.

---

## Exercise 2: Duration Types

**Files:** `ex02.h` (edit) - `ex02_test.cpp` (read-only)

Chrono provides type aliases for common units.  Implicit conversion works from
coarse to fine (no data loss); explicit `duration_cast` is required from fine
to coarse.

### What to do

1. `to_milliseconds()` -- convert seconds to milliseconds.
2. `to_seconds()` -- convert milliseconds to seconds (truncating).
3. `to_minutes()` -- convert seconds to minutes (truncating).
4. `total_ms()` -- combine hours, minutes, and seconds into total milliseconds.

---

## Exercise 3: Duration Arithmetic

**Files:** `ex03.h` (edit) - `ex03_test.cpp` (read-only)

Durations support `+`, `-`, and `*`.  When mixing units, the result type is
the finer unit.

### What to do

1. `add_durations()` -- add two millisecond durations.
2. `subtract_durations()` -- subtract one from another.
3. `mixed_add()` -- add seconds and milliseconds together.
4. `scale_duration()` -- multiply a duration by an integer factor.
5. `remaining_ms()` -- compute remaining time (clamped to 0).

---

## Exercise 4: Timeout Check

**Files:** `ex04.h` (edit) - `ex04_test.cpp` (read-only)

A deadline is a time_point in the future.  Checking whether it has passed is
a simple comparison.

### What to do

1. `is_expired()` -- check if "now" is at or past a deadline.
2. `time_remaining_ms()` -- compute ms remaining (0 if expired).
3. `make_deadline()` -- compute a deadline from start + timeout.
4. `extend_deadline()` -- push a deadline further into the future.

---

## Exercise 5: Periodic Timer Logic

**Files:** `ex05.h` (edit) - `ex05_test.cpp` (read-only)

Periodic timers fire at regular intervals.  The key insight is to anchor each
fire to the start time (not to "now") to avoid accumulating drift.

### What to do

1. `compute_fire_times()` -- determine which timestamps trigger a periodic fire.
2. `count_intervals()` -- count how many complete intervals fit in a range.
3. `next_fire_time()` -- compute the next fire time from the last one.

---

## Exercise 6: Format a Timestamp

**Files:** `ex06.h` (edit) - `ex06_test.cpp` (read-only)

`system_clock` time points can be displayed as human-readable strings by
converting through `time_t` and using `std::gmtime` + `std::put_time`.

### What to do

1. `format_utc()` -- format as "YYYY-MM-DD HH:MM:SS" in UTC.
2. `format_date_only()` -- format as "YYYY-MM-DD" in UTC.
3. `to_time_t_value()` -- convert a time_point to its raw time_t value.

---

## Exercise 7: Sleep with Chrono

**Files:** `ex07.h` (edit) - `ex07_test.cpp` (read-only)

`sleep_for` and `sleep_until` accept chrono types directly.  This exercise
builds the chrono values that would be passed to these functions, without
actually sleeping.

### What to do

1. `make_sleep_duration()` -- convert integer ms to `chrono::milliseconds`.
2. `compute_wake_time()` -- compute when a thread would wake after sleeping.
3. `sleep_durations()` -- convert a vector of ints to a vector of durations.
4. `total_sleep_ms()` -- sum a vector of durations.
