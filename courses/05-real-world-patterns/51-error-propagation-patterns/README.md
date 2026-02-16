# Lesson 51: Error Propagation Patterns

## Why This Lesson Exists

Exceptions are C++'s default error mechanism, but they have drawbacks: they
are invisible in function signatures, impose runtime overhead, and make
control flow hard to reason about.  Many modern C++ codebases (and languages
like Rust and Swift) prefer **value-based error handling** — functions return
a sum type that holds either a success value or an error.

C++23 introduced `std::expected` for this purpose, but it is not yet available
on all compilers (notably Apple Clang).  This lesson builds a
`Result<T, E>` type from scratch using `std::variant`, then progressively adds
monadic operations (`transform`, `and_then`, `or_else`, `map_error`) that let
you compose failable operations into clean pipelines without manual
if-error-return boilerplate at every step.

## Key Concepts

### Variant-based Sum Type

`Result<T, E>` wraps `std::variant<Ok<T>, Err<E>>`.  The `Ok` and `Err` tag
wrappers disambiguate even when `T` and `E` are the same type (e.g., both
`std::string`):

```cpp
template <typename T, typename E>
class Result {
    std::variant<Ok<T>, Err<E>> data_;
public:
    bool is_ok() const { return data_.index() == 0; }
    const T& value() const { return std::get<Ok<T>>(data_).val; }
    const E& error() const { return std::get<Err<E>>(data_).val; }
};
```

### Monadic Transform (map)

`transform(F)` applies a function to the success value, leaving errors
untouched.  If the result is `Ok(x)`, it returns `Ok(f(x))`.  If it is
`Err(e)`, the error propagates unchanged:

```cpp
auto doubled = result.transform([](int x) { return x * 2; });
```

### Monadic and_then (flat_map / bind)

`and_then(F)` chains operations that themselves return `Result`.  Unlike
`transform`, `F` returns a `Result<U, E>` rather than a plain `U`, so you
don't end up with nested `Result<Result<...>>`:

```cpp
auto parsed = input
    .and_then(parse_int)
    .and_then(validate_range);
```

### Monadic or_else (error recovery)

`or_else(F)` is the error-side counterpart of `and_then`.  It calls `F` with
the error and returns whatever `Result` the recovery function produces.  If
the result is already `Ok`, it passes through unchanged.

### Map Error

`map_error(F)` transforms the error type, leaving success values alone.  This
is useful when composing functions that use different error types — you can
normalize them to a common type before chaining.

### Error Context

When errors propagate up through layers, adding context produces human-readable
chains like `"initializing app: reading config: file not found"`.  A
`context(msg)` method wraps the error in a `ContextError<E>` that holds both
the message and the original error.

### Collect

`collect()` takes a vector of `Result` values and returns either a vector of
all success values (if every element is `Ok`) or the first error encountered.
This is the "all or nothing" pattern for batched operations.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 05-51

# Build and test a single exercise
./run exercise 05-51-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Result Type

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Build the core `Result<T, E>` type using `std::variant<Ok<T>, Err<E>>`.

### What to do

1. Remove the `TODO()` from the `Ok` and `Err` constructors (they are already
   wired up via the initializer list — just delete the `TODO()` call).
2. Implement `is_ok()` — check `data_.index() == 0`.
3. Implement `is_error()` — check `data_.index() == 1`.
4. Implement `value()` — return the `T` inside `Ok`.  Throw if error.
5. Implement `error()` — return the `E` inside `Err`.  Throw if ok.
6. Run: `./run exercise 05-51-ex01`

---

## Exercise 2: Monadic Transform

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Add `transform(F)` — apply a function to the success value, propagating
errors unchanged.

### What to do

1. If `is_ok()`, apply `f(value())` and wrap the return in `Ok`.
2. If `is_error()`, propagate the `Err` unchanged.
3. Return `Result<U, E>` where `U = decltype(f(value()))`.
4. Run: `./run exercise 05-51-ex02`

---

## Exercise 3: Monadic and_then

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Add `and_then(F)` — chain a failable operation.  `F` takes `const T&` and
returns `Result<U, E>`.

### What to do

1. If `is_ok()`, call `f(value())` and return its `Result` directly.
2. If `is_error()`, propagate the `Err` unchanged.
3. Run: `./run exercise 05-51-ex03`

---

## Exercise 4: Monadic or_else

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Add `or_else(F)` — attempt error recovery.  `F` takes `const E&` and returns
`Result<T, E>`.

### What to do

1. If `is_error()`, call `f(error())` and return its `Result`.
2. If `is_ok()`, pass through unchanged.
3. Run: `./run exercise 05-51-ex04`

---

## Exercise 5: Map Error

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Add `map_error(F)` — transform the error type, leaving success values alone.

### What to do

1. If `is_error()`, apply `f(error())` and wrap the return in `Err`.
2. If `is_ok()`, pass through unchanged.
3. Return `Result<T, E2>` where `E2 = decltype(f(error()))`.
4. Run: `./run exercise 05-51-ex05`

---

## Exercise 6: Error Context

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Add `context(msg)` — wrap the error with a descriptive message using a
`ContextError<E>` struct.  The `ContextError::describe()` method chains
messages recursively (e.g., `"outer: inner: root cause"`).

### What to do

1. If `is_error()`, wrap the error in `ContextError<E>{msg, error()}` and
   return `Err(ContextError<E>{...})`.
2. If `is_ok()`, pass through unchanged.
3. Return `Result<T, ContextError<E>>`.
4. Run: `./run exercise 05-51-ex06`

---

## Exercise 7: Collect Results

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Implement `collect()` — a free function that takes a vector of `Result<T, E>`
and returns a single `Result<std::vector<T>, E>`.

### What to do

1. Iterate the vector.  If all are `Ok`, collect their values into a
   `std::vector<T>` and return `Ok(vec)`.
2. If any is `Err`, return the first error immediately.
3. Run: `./run exercise 05-51-ex07`

---

## Exercise 8: Pipeline with Results

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Tie the whole lesson together by building a data-processing pipeline that
chains 4+ operations, any of which can fail.

### What to do

1. `parse_int(input)` — parse a string to `int`.  Return
   `Err("parse error")` on failure (use `std::stoi` in a try/catch).
2. `validate_range(value, min, max)` — return `Err` if out of range.
3. `double_value(value)` — multiply by 2.  Always succeeds.
4. `format_output(value)` — format as `"result: <value>"`.
5. `run_pipeline(input)` — chain: parse → validate [1, 100] → double →
   format.  Use `and_then` to compose the steps.
6. Run: `./run exercise 05-51-ex08`
