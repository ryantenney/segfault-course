# Lesson 29: Function Templates

## Why This Lesson Exists

Without templates, you'd need a separate function for every type combination:
`max_int`, `max_double`, `max_string`, and so on.  Function templates let you
write the algorithm once and have the compiler generate type-specific versions
automatically.

Templates are the backbone of the C++ Standard Library.  Every algorithm in
`<algorithm>`, every container in `<vector>` and `<map>`, and every utility in
`<memory>` is a template.  Understanding how they work is essential for writing
and using modern C++.

## Key Concepts

### Template Declaration

A function template is declared with the `template` keyword followed by template
parameters in angle brackets:

```cpp
template<typename T>
T max_of(T a, T b) {
    return (a < b) ? b : a;
}
```

`T` is a placeholder for any type.  When you call `max_of(3, 7)`, the compiler
deduces `T = int` and generates `int max_of(int, int)`.

### Template Argument Deduction

The compiler deduces template arguments from the function arguments:

```cpp
max_of(3, 7);          // T = int (deduced)
max_of(3.14, 2.71);   // T = double (deduced)
```

Deduction fails when it's ambiguous or when the return type can't be deduced:

```cpp
convert<double>(42);   // To = double (explicit), From = int (deduced)
```

### Multiple Type Parameters

Templates can have multiple type parameters:

```cpp
template<typename T, typename U>
std::pair<T, U> make_pair_of(T a, U b);
```

### Non-Type Template Parameters

Templates can take compile-time constants as parameters:

```cpp
template<std::size_t N>
class FixedBuffer {
    std::array<int, N> data_;
};
```

`FixedBuffer<5>` and `FixedBuffer<10>` are completely different types.

### Explicit Specialization

You can provide a custom implementation for a specific type:

```cpp
template<>
std::string stringify<bool>(bool val) {
    return val ? "true" : "false";
}
```

### Overload vs Specialization

For function templates, non-template overloads are preferred over
specializations during overload resolution.  Best practice: use overloads
instead of specializations for functions.

### Default Template Parameters

Template parameters can have defaults:

```cpp
template<typename T, typename Compare = std::less<T>>
T min_of(T a, T b, Compare comp = Compare{});
```

### Variadic Templates

Templates can accept any number of arguments using parameter packs:

```cpp
template<typename... Args>
std::string concat(Args... args);
```

Use `sizeof...(args)` to get the count, and fold expressions to process them.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 03-29

# Build and test a single exercise
./run exercise 03-29-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Generic Max Function

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Write a `max_of(T a, T b)` template that returns the larger of two values
using `operator<`.

### What to do

1. Implement `max_of`: if `a < b`, return `b`; otherwise return `a`.

---

## Exercise 2: Multiple Type Parameters

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Write templates with multiple type parameters: `convert<To>(From)` that uses
`static_cast`, and `make_pair_of(T, U)` that creates a `std::pair`.

### What to do

1. Implement `convert<To, From>`: use `static_cast<To>(val)`.
2. Implement `make_pair_of`: return `std::pair<T, U>{a, b}`.

---

## Exercise 3: Non-Type Template Parameter

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Implement `FixedBuffer<N>`, a class template with a compile-time size.
It wraps a `std::array<int, N>` and provides element access, fill, and sum.

### What to do

1. Implement `operator[]`: delegate to `data_[index]`.
2. Implement `size()`: return `N`.
3. Implement `fill()`: set all elements to the given value.
4. Implement `sum()`: return the sum of all elements.

---

## Exercise 4: Template Argument Deduction

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Practice when template arguments are deduced automatically vs. when they must
be specified explicitly.

### What to do

1. Implement `clamp_value`: return `val` clamped to `[lo, hi]`.
2. Implement `as_unsigned<To>(From)`: use `static_cast<To>(val)`.
3. Implement `add_mixed<To>(From1, From2)`: use `static_cast<To>(a + b)`.

---

## Exercise 5: Explicit Specialization

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Specialize a `stringify` template for specific types that need different
behavior than the default `std::to_string`.

### What to do

1. Primary template: return `std::to_string(val)`.
2. Specialization for `std::string`: return the string wrapped in quotes.
3. Specialization for `bool`: return `"true"` or `"false"`.

---

## Exercise 6: Overload vs Specialization

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Demonstrate that non-template overloads are preferred over template
specializations.  Write overloads for string types.

### What to do

1. Primary template: return `"value: " + std::to_string(val)`.
2. Overload for `const char*`: return `"text: " + std::string(val)`.
3. Overload for `const std::string&`: return `"text: " + val`.

---

## Exercise 7: Default Template Parameter

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Add a default template parameter for a comparator, following the STL pattern.

### What to do

1. Implement `min_of`: return the smaller value using `comp(a, b)`.
2. Implement `sort_pair`: return a pair with smaller first, using the comparator.

---

## Exercise 8: Variadic Template Intro

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

Write variadic template functions that work with any number of arguments.

### What to do

1. Implement `concat_all`: use `std::ostringstream` with a fold expression
   `(oss << ... << args)` to concatenate all arguments into a string.
2. Implement `count_args`: return `sizeof...(args)`.
