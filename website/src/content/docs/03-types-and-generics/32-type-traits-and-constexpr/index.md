---
title: "Lesson 32: Type Traits and constexpr"
---

## Why This Lesson Exists

Templates let you write generic code, but sometimes "too generic" is a problem.
What happens when someone instantiates your template with a type that makes no
sense -- like passing a `std::string` to a function that does arithmetic?
Without constraints, you get pages of incomprehensible compiler errors deep
inside your template implementation.

Type traits and `constexpr` are the tools that bring compile-time intelligence
to your templates. Type traits let you query and transform types at compile
time -- "Is T an integer? Is it copyable? Strip its reference." Meanwhile,
`constexpr` lets you run real C++ code at compile time -- computing lookup
tables, validating invariants, and eliminating runtime overhead.

Together, they let you write templates that are both generic and safe: code
that works for the types it should, rejects the types it shouldn't, and
computes everything it can before the program even starts.

## Key Concepts

### Type Traits (`<type_traits>`)

Type traits are template structs that answer questions about types at compile
time. They come in two flavors:

**Query traits** -- return a bool or a value:

```cpp
std::is_integral_v<int>          // true
std::is_floating_point_v<int>    // false
std::is_arithmetic_v<double>     // true
std::is_same_v<int, long>        // false
```

**Transformation traits** -- produce a modified type:

```cpp
std::remove_reference_t<int&>    // int
std::remove_const_t<const int>   // int
std::decay_t<const int&>         // int
std::add_pointer_t<int>          // int*
```

### static_assert

`static_assert(condition, "message")` checks a condition at compile time. If
false, compilation fails with the given message. Combined with type traits,
this gives clear error messages when templates are misused:

```cpp
template <typename T>
T add(T a, T b) {
    static_assert(std::is_arithmetic_v<T>, "add() requires a numeric type");
    return a + b;
}
```

### if constexpr

`if constexpr` evaluates its condition at compile time. The branch NOT taken
is discarded entirely -- it doesn't even need to compile for the given type:

```cpp
template <typename T>
std::string to_string(T val) {
    if constexpr (std::is_arithmetic_v<T>) {
        return std::to_string(val);  // only compiled for numbers
    } else {
        return val;  // only compiled for non-numbers
    }
}
```

### constexpr Functions

A `constexpr` function CAN be evaluated at compile time when called with
constant arguments. It can also run at runtime:

```cpp
constexpr int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

constexpr int x = factorial(5);  // compile time: 120
int y = factorial(n);            // runtime: computed when called
```

### consteval Functions (C++20)

A `consteval` function MUST be evaluated at compile time. Calling it with
non-constant arguments is a compile error:

```cpp
consteval int square(int n) { return n * n; }

constexpr int a = square(5);  // OK: compile-time constant
int n = 5;
int b = square(n);            // ERROR: n is not a constant
```

### enable_if (Legacy SFINAE)

Before C++20 concepts, `std::enable_if` was the primary way to constrain
templates using SFINAE (Substitution Failure Is Not An Error):

```cpp
template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
int to_int(T val) { return static_cast<int>(val); }
```

C++20 concepts replace this with cleaner syntax:

```cpp
template <typename T> requires std::integral<T>
int to_int(T val) { return static_cast<int>(val); }
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 03-32

# Build and test a single exercise
./run exercise 03-32-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: static_assert with Type Traits

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Use `static_assert` inside template functions to enforce type requirements
at compile time. This gives clear error messages instead of cryptic template
instantiation failures.

### What to do

1. In `numeric_add()`, add a `static_assert` that T is arithmetic, then
   return `a + b`.
2. In `safe_cast()`, add a `static_assert` that both `From` and `To` are
   integral, then return `static_cast<To>(v)`.
3. In `require_same()`, add a `static_assert` that T and U are the same type,
   then return `value`.

---

## Exercise 2: if constexpr Branching

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Use `if constexpr` to select different code paths based on type properties.
Only the taken branch needs to compile for the given type.

### What to do

1. Implement `stringify<T>()`: use `if constexpr` with type traits to convert
   arithmetic types via `std::to_string`, pass strings through directly, and
   return `"(unknown)"` for everything else.
2. Implement `default_value<T>()`: return the appropriate zero/empty value
   for integral, floating-point, string, or other types.

---

## Exercise 3: constexpr Function

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Write functions that can be evaluated at compile time. The stubs are NOT
marked `constexpr` yet (because TODO() throws, which is incompatible with
constexpr). Once you implement each body, add the `constexpr` keyword.

### What to do

1. Implement `constexpr_factorial(n)`: return n! using a loop. Add `constexpr`.
2. Implement `constexpr_fibonacci(n)`: return the n-th Fibonacci number.
   Add `constexpr`.
3. Implement `constexpr_is_prime(n)`: return true if n is prime.
   Add `constexpr`.

---

## Exercise 4: constexpr Variable (Compile-Time Lookup Table)

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Build lookup tables entirely at compile time. The tables are `constexpr`
variables initialized by `constexpr` helper functions.

### What to do

1. Implement `make_squares_table()`: fill and return a `std::array<int, 10>`
   where element `i` holds `i * i`.
2. Implement `make_ascii_table()`: fill and return a `std::array<bool, 128>`
   where element `i` is true if `i` is a lowercase letter ('a' through 'z').
3. Remove the `TODO()` from `ex04_gate()` when you're ready to test.

---

## Exercise 5: Type Manipulation

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Use transformation traits like `std::decay_t`, `std::remove_reference_t`, and
`std::is_same_v` to normalize types in template code.

### What to do

1. Implement `type_name_of<T>()`: apply `std::decay_t` to T, then compare
   with `std::is_same_v` to return a name string.
2. Implement `are_same_after_decay<T, U>()`: compare decayed T and U.
3. Implement `store_value<T>(val)`: return a `std::decay_t<T>` copy of val.

---

## Exercise 6: enable_if (Legacy) and Concepts (Modern)

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Practice the old way (SFINAE with `std::enable_if`) and the new way (C++20
concepts/requires) of constraining templates. The function signatures are
provided -- you fill in the bodies.

### What to do

1. Implement `to_int_sfinae()`: return `static_cast<int>(value)`.
2. Implement `to_int_concept()`: same logic, using a `requires` clause.
3. Implement `numeric_to_string_sfinae()`: return `std::to_string(value)`.
4. Implement `numeric_to_string_concept()`: same logic, with `requires`.

---

## Exercise 7: consteval (Immediate Functions)

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Write `consteval` functions that MUST be evaluated at compile time. The
function stubs have placeholder implementations (returning 0) instead of
TODO() -- because TODO() throws, and consteval functions cannot throw.

### What to do

1. Replace the body of `compile_time_square(n)` with `return n * n`.
2. Replace the body of `compile_time_abs(n)` with the correct logic.
3. Replace the body of `compile_time_gcd(a, b)` with the Euclidean algorithm.
4. Remove the `TODO()` from `ex07_gate()` when you're ready to test.

---

## Exercise 8: constexpr with std::array

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

Use constexpr functions to build and process `std::array` entirely at
compile time. The stubs are NOT marked `constexpr` yet. Once you implement
each body, add the `constexpr` keyword.

### What to do

1. Implement `constexpr_iota<N>()`: return `{0, 1, 2, ..., N-1}`.
   Add `constexpr`.
2. Implement `constexpr_sum(arr)`: return the sum of all elements.
   Add `constexpr`.
3. Implement `constexpr_reverse(arr)`: return a reversed copy.
   Add `constexpr`.
4. Implement `constexpr_contains(arr, value)`: linear search.
   Add `constexpr`.
