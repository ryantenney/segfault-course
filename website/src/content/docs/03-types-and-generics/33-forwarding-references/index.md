---
title: "Lesson 33: Forwarding References and Perfect Forwarding"
---

## Why This Lesson Exists

When you write a wrapper function -- something that takes arguments and passes
them along to another function -- you want zero overhead. No extra copies, no
extra moves, no accidental value category changes. If the caller passed an
lvalue, the inner function should see an lvalue. If the caller passed an
rvalue, the inner function should see an rvalue and be free to move from it.

This is "perfect forwarding," and it's one of the most important patterns in
modern C++. It's the mechanism behind `std::make_unique`, `emplace_back`,
`std::invoke`, and countless other standard library utilities.

Getting it right requires understanding three interconnected concepts:
forwarding references (`T&&` where T is deduced), reference collapsing rules,
and `std::forward`. This lesson builds that understanding step by step.

## Key Concepts

### Forwarding References vs Rvalue References

`T&&` means different things depending on whether `T` is deduced:

```cpp
template <typename T>
void f(T&& x);       // T&& is a FORWARDING reference (T is deduced)

void g(int&& x);     // int&& is an RVALUE reference (type is concrete)
```

A forwarding reference can bind to both lvalues and rvalues. An rvalue
reference can only bind to rvalues.

### Reference Collapsing

When template substitution creates a "reference to a reference," C++ collapses
it according to these rules:

| Expression | Result |
|------------|--------|
| `T& &`    | `T&`   |
| `T& &&`   | `T&`   |
| `T&& &`   | `T&`   |
| `T&& &&`  | `T&&`  |

The rule: if either reference is an lvalue reference, the result is an lvalue
reference.

When you call `f(T&& x)` with an lvalue of type `int`, T deduces to `int&`,
and `T&&` becomes `int& &&` which collapses to `int&`.

### std::forward

`std::forward<T>(x)` performs a conditional cast:

- If T is an lvalue reference type, x stays an lvalue (cast to `T&`).
- If T is a non-reference type, x becomes an rvalue (cast to `T&&`).

This is what "perfect forwarding" means: the value category is preserved.

```cpp
template <typename T>
void wrapper(T&& arg) {
    inner(std::forward<T>(arg));  // preserves lvalue/rvalue
}
```

### The Forwarding Pattern

The standard pattern for a perfect-forwarding function is:

```cpp
template <typename... Args>
auto wrapper(Args&&... args) -> decltype(auto) {
    return target(std::forward<Args>(args)...);
}
```

Key elements:
- `Args&&...` -- forwarding references for all parameters
- `std::forward<Args>(args)...` -- expand with forward applied to each
- `decltype(auto)` -- preserve the exact return type (including references)

### decltype(auto) vs auto

`auto` always strips references and top-level const:

```cpp
int x = 42;
int& ref = x;
auto a = ref;     // int (copy, not reference)
```

`decltype(auto)` preserves the exact type:

```cpp
decltype(auto) b = ref;   // int& (reference preserved)
decltype(auto) c = 42;    // int (prvalue stays a value)
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 03-33

# Build and test a single exercise
./run exercise 03-33-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Forwarding Reference vs Rvalue Reference

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Understand the difference between forwarding references (`T&&` with deduced T)
and rvalue references (concrete `Type&&`). Use type traits to classify what
kind of argument was received.

### What to do

1. Implement `is_forwarding_ref_call()` -- pass an lvalue to `identify()`.
2. Implement `takes_rvalue_only()` -- pass an rvalue to `consume()` using
   `std::move`.
3. Implement `classify_argument()` -- use `std::is_lvalue_reference_v<T>` to
   detect the value category.

---

## Exercise 2: Reference Collapsing

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Observe how C++ collapses references when templates produce "reference to
reference" types. The results demonstrate the rules in action.

### What to do

1. Implement `collapsed_type_is_lref<T>()` -- check that `T&` is always an
   lvalue reference after collapsing.
2. Implement `deduce_and_report<T>()` -- report whether T deduced as an
   lvalue reference or a non-reference.
3. Implement `apply_collapse<T>()` -- report whether `T&&` collapses to an
   lvalue reference or rvalue reference.

---

## Exercise 3: Perfect Forwarding Wrapper

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Write a `log_and_call` wrapper that increments a counter and then perfectly
forwards all arguments to a callable.

### What to do

1. Increment `call_count`.
2. Call `f(std::forward<Args>(args)...)` and return the result.

---

## Exercise 4: Forward to Constructor

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Forward arguments through a wrapper function directly to a constructor. This
is the pattern behind `std::make_unique`.

### What to do

1. Implement `construct_in_place<T>()` -- return `T(std::forward<Args>(args)...)`.
2. Implement `construct_pair()` -- forward two arguments to the `NamedPair`
   constructor.

---

## Exercise 5: Emplace with Forwarding

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Build a simplified container with an `emplace_back` method that constructs
elements in place using perfect forwarding.

### What to do

1. Implement `MiniVec::emplace_back()` -- forward all arguments to construct
   a T and add it to the internal storage.

---

## Exercise 6: Factory Function

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Write generic factory functions that construct objects by forwarding arguments.

### What to do

1. Implement `make<T>()` -- construct and return a T on the stack.
2. Implement `make_on_heap<T>()` -- construct a T on the heap and return
   a `std::unique_ptr<T>`.

---

## Exercise 7: Variadic Forwarding

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Work with parameter packs and forwarding. Apply a function to each argument
individually, or forward all arguments to a single call.

### What to do

1. Implement `apply_to_each()` -- call `f` once per argument using a fold
   expression.
2. Implement `forward_to()` -- forward all args to a single target call.
3. Implement `count_args()` -- return `sizeof...(Args)`.

---

## Exercise 8: decltype(auto) Return

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

Use `decltype(auto)` to preserve the exact return type of a forwarded call,
including references.

### What to do

1. Implement `forward_result()` -- call `f` with forwarded args and return
   the result using `decltype(auto)` to preserve references.
2. Implement `get_or_default()` -- return a reference to `*ptr` if non-null,
   or a reference to `default_val` if null.
