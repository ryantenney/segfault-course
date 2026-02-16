---
title: "Lesson 12: optional, variant, and expected"
---

## Why This Lesson Exists

C++ has historically used sentinel values (-1, nullptr, empty strings) and
exceptions to represent "might not have a value" or "this operation can fail."
Modern C++ offers vocabulary types that encode these possibilities directly
in the type system, making missing-value and error-handling bugs impossible
to ignore at compile time.

## Key Concepts

### std::optional\&lt;T\>

An `optional<T>` either holds a value of type `T` or is empty (`std::nullopt`).
It replaces sentinel return values and makes the "nothing" case explicit:

```cpp
std::optional<int> find(const std::string& key);

auto result = find("foo");
if (result) {
    use(*result);        // dereference like a pointer
}
int val = result.value_or(42);  // provide a default
```

Key operations: `has_value()`, `value()`, `value_or(default)`, `operator*`,
`operator bool`.

### std::variant\&lt;Types...\>

A `variant` is a type-safe tagged union. It always holds exactly one of its
alternative types, and the compiler tracks which one is active:

```cpp
std::variant<int, std::string, bool> setting = 42;

std::holds_alternative<int>(setting);    // true
std::get<int>(setting);                  // 42
std::get<std::string>(setting);          // throws bad_variant_access
```

### std::visit

`std::visit` applies a callable to the active alternative in a variant. The
callable must handle every type:

```cpp
std::visit([](auto& val) {
    std::cout << val << "\n";
}, setting);
```

### The Overloaded Pattern

A common idiom combines multiple lambdas into a single visitor:

```cpp
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

std::visit(overloaded{
    [](int i)                { /* ... */ },
    [](const std::string& s) { /* ... */ },
    [](bool b)               { /* ... */ },
}, my_variant);
```

### Expected\&lt;T, E\> (Result Types)

An `Expected<T, E>` holds either a success value (`T`) or an error (`E`).
This pattern (standardized as `std::expected` in C++23) enables error handling
without exceptions. Errors are encoded in the return type, making them
impossible to accidentally ignore.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 01-12

# Build and test a single exercise
./run exercise 01-12-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Return optional from Lookup

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Replace a sentinel-based lookup with `std::optional`. The function
`find_user_age()` should return the user's age wrapped in optional, or
`std::nullopt` when the user is not found.

### What to do

1. Open `ex01.h`.
2. Implement `find_user_age()` using a simple if-chain or map lookup.
3. Return the age as `std::optional<int>`, or `std::nullopt` if not found.
4. Run: `./run exercise 01-12-ex01`

---

## Exercise 2: Optional with value_or

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Use `value_or()` to provide a fallback when an optional is empty. Implement
a config lookup that returns optional, then a convenience wrapper that uses
`value_or()` to supply defaults.

### What to do

1. Implement `get_config_value()` — return the value for known keys, nullopt
   otherwise.
2. Implement `get_config_or_default()` — call `get_config_value()` and use
   `.value_or()` to provide the default.
3. Run: `./run exercise 01-12-ex02`

---

## Exercise 3: Chain Optional Operations

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Practice chaining multiple optional-returning lookups. Each step might fail,
and you must check before proceeding to the next.

### What to do

1. Implement `find_employee_department()` — look up an employee's department.
2. Implement `find_department_head()` — look up who heads a department.
3. Implement `find_boss()` — chain both lookups. If either returns nullopt,
   the whole chain returns nullopt.
4. Run: `./run exercise 01-12-ex03`

---

## Exercise 4: Variant Basics

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Store different types in a `std::variant` and access them with `std::get`,
`std::get_if`, and `std::holds_alternative`.

### What to do

1. Implement `make_int_setting()`, `make_string_setting()`, `make_bool_setting()`.
2. Implement `setting_type_name()` — return "int", "string", or "bool".
3. Implement `get_int_or()` — return the int value or a default.
4. Run: `./run exercise 01-12-ex04`

---

## Exercise 5: std::visit

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Use `std::visit` with a visitor to process a variant. The visitor must handle
all alternative types.

### What to do

1. Implement `setting_to_string()` — visit the variant and convert each type
   to a string.
2. Implement `double_setting()` — visit the variant and "double" each type
   (int*2, string+string, !bool).
3. Run: `./run exercise 01-12-ex05`

---

## Exercise 6: Overloaded Visitor

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Implement the `overloaded{lambdas...}` pattern for concise variant visiting.
Apply it to a shape hierarchy (Circle, Rectangle, Triangle).

### What to do

1. Define the `overloaded` template (uncomment and fill in the struct).
2. Implement `describe_shape()` using `std::visit` with `overloaded{...}`.
3. Implement `shape_area()` using `std::visit` with `overloaded{...}`.
4. Run: `./run exercise 01-12-ex06`

---

## Exercise 7: Error Handling with Expected

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Implement a simplified `Expected<T, E>` template that wraps a
`std::variant<T, E>`. This teaches the same pattern as C++23's `std::expected`
without requiring compiler support.

### What to do

1. Implement `has_value()`, `value()`, `error()`, and `value_or()` on the
   Expected template.
2. Implement `parse_int()` — parse a string to int, returning success or
   an error message.
3. Run: `./run exercise 01-12-ex07`

---

## Exercise 8: Expected Chaining

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Chain multiple Expected-returning operations using the railway pattern. If
any step fails, the error propagates through the rest of the chain.

### What to do

1. Implement `and_then()` — apply a function to the success value, or
   propagate the error.
2. Implement `validate_positive()` and `double_value()`.
3. Implement `validate_and_double()` — chain parse, validate, and double
   using `and_then()`.
4. Run: `./run exercise 01-12-ex08`
