# Lesson 19: Lambdas

## Why This Lesson Exists

Lambdas are the glue that makes the STL algorithms practical. Before
lambdas (C++11), passing custom logic to `std::sort`, `std::find_if`, or
`std::for_each` required writing a separate function or functor class --
even for trivial one-line predicates. Lambdas let you define that logic
inline, right where it is used.

Beyond simple predicates, lambdas support captures (by value, by reference,
and by move), mutable state, generic parameters, and can be returned from
functions as first-class values. Mastering lambdas is essential for writing
modern, expressive C++.

## Key Concepts

### Lambda Syntax

The basic form is:

```cpp
[capture](parameters) -> return_type { body }
```

The return type is usually deduced and can be omitted. Captures control
which variables from the enclosing scope are accessible inside the lambda.

### Capture Modes

```cpp
int x = 10;
auto by_val   = [x]()  { return x; };      // copy of x (const)
auto by_ref   = [&x]() { return x; };      // reference to x
auto by_val_m = [x]() mutable { ++x; };    // mutable copy
auto by_move  = [p = std::move(ptr)]() {};  // init-capture (move)
```

- `[=]` captures everything by value (avoid -- unclear what is captured)
- `[&]` captures everything by reference (use sparingly)
- Prefer explicit captures for clarity

### Mutable Lambdas

By default, a lambda's `operator()` is const -- captured-by-value
variables cannot be modified. Adding `mutable` lets you modify the copies:

```cpp
int n = 0;
auto counter = [n]() mutable { return n++; };
counter(); // 0
counter(); // 1
// n is still 0
```

### Init-Capture (C++14)

Creates a new variable in the capture clause, which can be initialized
from a move or an expression:

```cpp
auto ptr = std::make_unique<Widget>();
auto fn = [p = std::move(ptr)]() { p->do_work(); };
```

### Generic Lambdas (C++14)

Use `auto` parameters to create a templated call operator:

```cpp
auto add = [](auto a, auto b) { return a + b; };
```

### Returning Lambdas

Functions can return lambdas. Use `std::function<>` for the return type:

```cpp
std::function<int(int)> make_adder(int n) {
    return [n](int x) { return x + n; };
}
```

### IIFE (Immediately Invoked Function Expression)

Define and call a lambda in one expression, useful for complex `const`
initialization:

```cpp
const auto val = [&]() {
    if (condition) return compute_a();
    else           return compute_b();
}();
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 02-19

# Build and test a single exercise
./run exercise 02-19-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Basic Lambda Predicate

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Write lambdas as comparators for `std::sort`. This is the most common
use of lambdas in practice.

### What to do

1. Implement `sort_ascending()` -- sort with a `<` comparator lambda.
2. Implement `sort_by_absolute()` -- sort by absolute value.
3. Implement `sort_strings_by_length()` -- sort by length, break ties alphabetically.

---

## Exercise 2: Capture by Reference

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Use `[&]` capture to let a lambda modify variables in the enclosing scope.
The lambda accumulates results directly into local variables.

### What to do

1. Implement `count_if_positive()` -- count positives using `for_each` with `[&]`.
2. Implement `sum_elements()` -- sum via `for_each` with a captured accumulator.
3. Implement `apply_to_each()` -- multiply and collect results via captured vector.

---

## Exercise 3: Capture by Value

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Capture by value with `mutable` to give the lambda its own independent
copy. The original variable remains unchanged.

### What to do

1. Implement `make_counter()` -- return a lambda that counts up from a start value.
2. Implement `demonstrate_value_capture()` -- show original is unchanged.
3. Implement `accumulate_calls()` -- return a lambda that builds up a string.

---

## Exercise 4: Capture by Move

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Use init-capture (`[p = std::move(p)]`) to move a `unique_ptr` or other
move-only type into a lambda.

### What to do

1. Implement `capture_unique_ptr()` -- move a unique_ptr into a lambda.
2. Implement `capture_string_by_move()` -- move a string, return length.
3. Implement `transfer_ownership()` -- accept and capture a unique_ptr.

---

## Exercise 5: Generic Lambda

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Write lambdas with `auto` parameters that work with multiple types.
Also practice the pattern of applying a function twice.

### What to do

1. Implement `make_int_adder()` -- return a lambda that adds two ints.
2. Implement `make_double_adder()` -- return a lambda that adds two doubles.
3. Implement `apply_twice()` -- apply a callable twice: `fn(fn(value))`.
4. Implement `make_max_finder()` -- return a lambda that finds the max element.

---

## Exercise 6: Lambda Returning Lambda

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Write factory functions that configure a lambda with captured state and
return it. Each returned lambda is independently configured.

### What to do

1. Implement `make_multiplier()` -- return a lambda that multiplies by a factor.
2. Implement `make_adder()` -- return a lambda that adds an offset.
3. Implement `make_range_checker()` -- return a lambda that checks if a value is in [lo, hi].

---

## Exercise 7: IIFE for Initialization

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Use immediately-invoked lambdas to initialize `const` variables with
complex logic, keeping the initialization self-contained.

### What to do

1. Implement `classify_number()` -- IIFE returning "negative", "zero", or "positive".
2. Implement `build_greeting()` -- IIFE returning formal or informal greeting.
3. Implement `first_n_squares()` -- IIFE returning a vector of perfect squares.

---

## Exercise 8: Stateful Comparator

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Write lambdas that capture runtime configuration and use it to control
sort behavior. This is more flexible than `std::less` or `std::greater`.

### What to do

1. Implement `configurable_sort()` -- sort ascending or descending based on flag.
2. Implement `priority_sort()` -- priority items first, rest alphabetical.
3. Implement `nth_element_sort()` -- divisible elements first, then the rest.
