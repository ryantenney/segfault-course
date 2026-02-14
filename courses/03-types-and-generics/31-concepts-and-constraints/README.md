# Lesson 31: Concepts and Constraints (C++20)

## Why This Lesson Exists

Before C++20, constraining template parameters was painful.  You either used
`static_assert` (which gives no SFINAE) or `std::enable_if` (which is nearly
unreadable).  Error messages for template misuse were infamous for being pages
of incomprehensible compiler output.

C++20 concepts solve all of this.  A concept is a named compile-time predicate
over types.  It lets you state exactly what a template parameter must support,
and the compiler produces short, clear error messages when the requirement
isn't met.

## Key Concepts

### Defining a Concept

```cpp
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;
```

A concept evaluates to `true` or `false` at compile time.

### Using a Concept as a Constraint

Three equivalent syntaxes:

```cpp
// 1. Constrained template parameter
template<Numeric T>
T add(T a, T b) { return a + b; }

// 2. Requires clause
template<typename T>
    requires Numeric<T>
T add(T a, T b) { return a + b; }

// 3. Trailing requires clause
template<typename T>
T add(T a, T b) requires Numeric<T> { return a + b; }
```

### Compound Requirements

A `requires` expression can check multiple operations:

```cpp
template<typename T>
concept Displayable = requires(T a, T b) {
    { a < b }        -> std::convertible_to<bool>;
    { a == b }       -> std::convertible_to<bool>;
    { a.to_string() } -> std::convertible_to<std::string>;
};
```

Each `{ expr }` checks that the expression is valid.  The optional
`-> std::convertible_to<R>` checks the return type.

### Concept-Based Overloading

```cpp
template<std::integral T>
std::string describe(T v) { return "integer"; }

template<std::floating_point T>
std::string describe(T v) { return "float"; }
```

The compiler picks the overload whose concept matches the argument.

### Subsumption Ordering

When two concepts overlap, the compiler picks the more constrained one:

```cpp
template<typename T>
concept Ordered = requires(T a, T b) { a < b; };

template<typename T>
concept OrderedAndNamed = Ordered<T> && Named<T>;

template<Ordered T>          std::string f(T);  // general
template<OrderedAndNamed T>  std::string f(T);  // more constrained -- preferred
```

For subsumption to work, the refined concept must be defined using `&&` on the
general concept.

### Standard Library Concepts

`<concepts>` provides pre-defined concepts:

- `std::integral`, `std::floating_point`, `std::signed_integral`
- `std::convertible_to<To>`, `std::constructible_from<Args...>`
- `std::equality_comparable`, `std::totally_ordered`
- `std::copyable`, `std::movable`, `std::regular`

Prefer these over custom concepts when they fit.

### Ad-Hoc Requires Expressions

For one-off constraints, use an inline `requires requires` directly on the
function:

```cpp
template<typename T>
    requires requires(T t) { { t.length() } -> std::convertible_to<std::size_t>; }
std::size_t get_length(const T& t) { return t.length(); }
```

### What You Cannot Test at Runtime

Concepts are compile-time.  You can test that valid types work correctly, but
you cannot test at runtime that invalid types fail to compile.  To verify
negative cases, try uncommenting the noted lines in the exercise files --
the compiler should reject them with a clear constraint error.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 03-31

# Build and test a single exercise
./run exercise 03-31-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Simple Concept

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Define a `Numeric` concept that accepts arithmetic types, then use it to
constrain `add` and `multiply` functions.

### What to do

1. Fix the `Numeric` concept (replace `true` with `std::is_arithmetic_v<T>`).
2. Constrain `add` and `multiply` with `template<Numeric T>`.
3. Implement the function bodies.

---

## Exercise 2: Compound Requirements

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Write a `Displayable` concept that requires `<`, `==`, and a `.to_string()`
method, then implement a function constrained by it.

### What to do

1. Fix the `Displayable` concept (replace `true` with the compound requirements).
2. Constrain `compare_and_display` with Displayable.
3. Return the string form of the smaller value.

---

## Exercise 3: Requires Clause on Function

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Add `requires` clauses directly on function templates instead of defining
named concepts.

### What to do

1. Add `requires std::is_signed_v<T>` to `absolute_value`.
2. Add `requires std::totally_ordered<T>` to `clamp_value`.
3. Implement both function bodies.

---

## Exercise 4: Constrained Class Template

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Define a `Comparable` concept and use it to constrain a `SortedContainer`
class template.

### What to do

1. Fix the `Comparable` concept (replace `true` with requirements for `<` and `==`).
2. Constrain `SortedContainer` with `template<Comparable T>`.
3. Implement `insert` (use `std::lower_bound`), `contains` (use
   `std::binary_search`), `size`, and `at`.

---

## Exercise 5: Concept-Based Overloading

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Use concepts to select between two function overloads -- one for integers,
one for floating-point types.

### What to do

1. Fix `Integral` and `FloatingPoint` concepts (replace `true` with proper type trait checks).
2. Constrain the existing `describe` and uncomment the floating-point overload.
3. Constrain the existing `double_it` and uncomment the floating-point overload.
4. You must constrain BOTH overloads for overload resolution to work.

---

## Exercise 6: Standard Library Concepts

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Practice using concepts from `<concepts>` instead of defining your own.

### What to do

1. Implement `to_int` constrained by `std::integral`.
2. Implement `halve` constrained by `std::floating_point`.
3. Implement `stringify` constrained by `std::convertible_to<std::string>`.
4. Implement `are_equal` constrained by `std::equality_comparable`.

---

## Exercise 7: Subsumption Ordering

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Define a general concept and a refined concept.  Show that the compiler picks
the most constrained overload.

### What to do

1. Fix `Ordered` (replace `true` with a requires expression checking `<`).
2. Fix `Named` (replace `true` with a requires expression checking `.name()`).
3. Fix `OrderedAndNamed` (replace `true` with `Ordered<T> && Named<T>`).
4. Constrain the existing `identify` overload and uncomment the second one.

---

## Exercise 8: Ad-Hoc Requires Expression

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

Use inline `requires` expressions (not named concepts) to constrain functions.

### What to do

1. Constrain `get_length` with an ad-hoc requires checking for `.length()`.
2. Constrain `serialize_pair` with ad-hoc requires checking for `to_string()`.
3. Implement both function bodies.
