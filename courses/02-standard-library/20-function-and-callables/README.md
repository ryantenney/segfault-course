# Lesson 20: std::function and Callable Objects

## Why This Lesson Exists

C++ has an unusually rich set of "things you can call": free functions, member
functions, function pointers, functors (classes with `operator()`), lambdas,
and `std::function`.  Understanding when and why to use each is essential for
writing flexible, efficient APIs.

`std::function` is the Swiss-army-knife wrapper: it can hold *any* callable
with a compatible signature.  But that flexibility comes at a cost (virtual
dispatch, possible heap allocation).  Template parameters give zero-overhead
dispatch but cannot be stored.  Knowing this tradeoff lets you make the right
choice for each situation.

## Key Concepts

### std::function

A general-purpose polymorphic function wrapper.  It can store lambdas, function
pointers, functors, or the result of `std::bind`.

```cpp
std::function<int(int, int)> op = [](int a, int b) { return a + b; };
op(3, 4);  // 7
```

A default-constructed `std::function` is empty; calling it throws
`std::bad_function_call`.  You can test for emptiness with `if (fn)`.

### Functors

Any class that defines `operator()`.  Functors can carry state across calls,
making them more powerful than plain functions.

```cpp
struct Accumulator {
    int total = 0;
    int operator()(int x) { total += x; return total; }
};
```

### Function Pointers

The lightest-weight callable — just an address.  No overhead, but no state
capture either.

```cpp
int add(int a, int b) { return a + b; }
using BinaryOp = int(*)(int, int);
BinaryOp op = &add;
op(3, 4);  // 7
```

### Template Parameters vs Type Erasure

| | `std::function` | Template parameter |
|---|---|---|
| Overhead | Virtual call + possible heap alloc | Zero (inlined) |
| Storable in container | Yes | No |
| Works with any signature | Yes (at runtime) | Yes (at compile time) |
| Error messages | Clear | Can be verbose |

### std::bind vs Lambdas

`std::bind` creates callables with pre-bound arguments, but lambdas are
clearer, faster, and preferred in modern C++.

### Higher-Order Functions

Functions that take or return other functions.  A powerful pattern for
composition, memoization, retry logic, and more.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 02-20

# Build and test a single exercise
./run exercise 02-20-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Callback Registration

**Files:** `ex01.h` (edit) - `ex01_test.cpp` (read-only)

`std::function<void(int)>` is the classic way to accept a callback.  The
caller decides what code runs; the library just stores and invokes it.

### What to do

Implement a `CallbackHolder` class with three methods:
1. `register_callback()` -- store a callback.
2. `fire()` -- invoke the stored callback with a value (do nothing if none).
3. `has_callback()` -- return whether a callback is registered.

---

## Exercise 2: Functor Class

**Files:** `ex02.h` (edit) - `ex02_test.cpp` (read-only)

A functor is a class with `operator()`.  Unlike lambdas, functors are named
types that can be reused, documented, and stored as class members.

### What to do

Implement a `RunningAverage` functor:
1. `operator()(double value)` -- add a value and return the running average.
2. `count()` -- return how many values have been added.
3. `average()` -- return the current average (0.0 if empty).

---

## Exercise 3: Function Pointer

**Files:** `ex03.h` (edit) - `ex03_test.cpp` (read-only)

Function pointers are the simplest callable type: just the address of a
function.  They have zero overhead and interop with C, but cannot capture
state.

### What to do

1. `apply()` -- call a function pointer with two arguments.
2. `select_operation()` -- return a pointer to `add_ints` or `multiply_ints`
   based on a character (`'+'` or `'*'`).
3. `compute()` -- combine `select_operation` and `apply`.

---

## Exercise 4: Store Callbacks in a Container

**Files:** `ex04.h` (edit) - `ex04_test.cpp` (read-only)

Since `std::function` is a regular value type, you can store many of them in a
vector.  This is the observer/listener pattern.

### What to do

Implement an `EventBus` class:
1. `subscribe()` -- add a callback.
2. `notify()` -- invoke all callbacks with a message.
3. `subscriber_count()` -- return the count.
4. `clear()` -- remove all callbacks.

---

## Exercise 5: Template Parameter vs Type Erasure

**Files:** `ex05.h` (edit) - `ex05_test.cpp` (read-only)

Compare two approaches: `std::function` (type-erased, flexible, small runtime
cost) vs a template parameter (zero-overhead, but generates separate code per
callable type).

### What to do

1. `apply_erased()` -- call a `std::function<int(int)>` with a value.
2. `apply_template()` -- same, but using a template parameter.
3. `transform_all_erased()` -- transform a vector using `std::function`.
4. `transform_all_template()` -- same, but with a template parameter.

---

## Exercise 6: Replace std::bind with Lambda

**Files:** `ex06.h` (edit) - `ex06_test.cpp` (read-only)

`std::bind` was useful before lambdas existed, but lambdas are universally
preferred in modern C++ for clarity and performance.

### What to do

Replace each `std::bind` expression with an equivalent lambda:
1. `lambda_add_10()` -- equivalent to `bind_add_10()`.
2. `lambda_triple()` -- equivalent to `bind_triple()`.
3. `lambda_swap_greet()` -- equivalent to `bind_swap_greet()`.

---

## Exercise 7: Higher-Order Function

**Files:** `ex07.h` (edit) - `ex07_test.cpp` (read-only)

Higher-order functions take or return other functions.  They enable powerful
composition patterns.

### What to do

1. `make_multiplier(factor)` -- return a lambda that multiplies by `factor`.
2. `compose(f, g)` -- return a callable that computes `f(g(x))`.
3. `call_n_times(f, n)` -- return a callable that invokes `f` n times,
   collecting results into a vector.
