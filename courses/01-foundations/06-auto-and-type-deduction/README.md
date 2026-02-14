# Lesson 06: auto, Type Deduction, and Type Aliases

## Why This Lesson Exists

C++ is a statically typed language, but that doesn't mean you have to spell out
every type by hand. Modern C++ provides `auto`, `decltype`, and `using` aliases
to let the compiler do the tedious type bookkeeping while you focus on logic.

If you're coming from a language with type inference (Rust's `let`, Go's `:=`,
Kotlin's `val`), `auto` will feel familiar. If you're coming from Java, think
of `auto` as what `var` does in Java 10+ -- but more powerful.

## Key Concepts

### auto Variable Deduction

`auto` tells the compiler: "figure out the type from the initializer."

```cpp
auto x = 42;          // int
auto pi = 3.14;       // double
auto name = "hello";  // const char*
auto v = std::vector<int>{1, 2, 3};  // std::vector<int>
```

The type is fixed at compile time -- `auto` is **not** dynamic typing.

### auto with const and References

`auto` by itself strips top-level `const` and references. You must add them
back explicitly:

```cpp
int x = 10;
const int& cr = x;

auto a = cr;        // int       (copy -- const and & stripped)
auto& b = cr;       // const int& (reference preserved, const kept)
const auto& c = x;  // const int& (explicitly const reference)
auto&& d = x;       // int&      (forwarding reference to lvalue)
```

### Range-for with auto

The form of `auto` in range-for controls copying and mutation:

```cpp
for (auto x : v)         // copies each element
for (auto& x : v)        // mutable reference
for (const auto& x : v)  // read-only reference (most common)
for (auto&& x : v)       // forwarding reference (generic code)
```

### Trailing Return Types

Instead of putting the return type before the function name, you can write it
after with `-> T`:

```cpp
int add(int a, int b);            // traditional
auto add(int a, int b) -> int;    // trailing return type
```

Both are equivalent. Trailing return types are required in some template
contexts and preferred by some style guides for visual alignment.

### decltype

`decltype(expr)` yields the type of an expression without evaluating it:

```cpp
int x = 42;
decltype(x) y = 10;        // int (same as x's declared type)
decltype(x + 1.0) z = 0;   // double (type of the expression)
```

### auto Return Type Deduction

C++14 allows `auto` as a return type -- the compiler deduces it from the
`return` statement(s):

```cpp
auto square(int x) { return x * x; }  // deduced as int
```

All `return` statements must produce the same type.

### Type Aliases with using

`using` is the modern replacement for `typedef`:

```cpp
typedef std::vector<int> IntVec;     // old C-style
using IntVec = std::vector<int>;     // modern C++ (preferred)
```

The `using` form reads left-to-right and also supports templates:

```cpp
template <typename T>
using Vec = std::vector<T>;

Vec<int> numbers;     // std::vector<int>
Vec<std::string> words;  // std::vector<std::string>
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 01-06

# Build and test a single exercise
./run exercise 01-06-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Replace Explicit Types with auto

**Files:** `ex01.h` (edit) -- `ex01_test.cpp` (read-only)

When iterating containers with `begin()`/`end()`, the iterator type can be
extremely verbose:

```cpp
std::vector<int>::const_iterator it = v.begin();  // painful
auto it = v.begin();                               // clean
```

`auto` deduces the exact same type the compiler would give you -- just without
the visual noise.

### What to do

1. Open `ex01.h`.
2. In `find_first()`, iterate using `auto it = v.begin()` and loop until
   `it != v.end()`. Return `*it` if found, `-1` otherwise.
3. In `sum_elements()`, iterate with `auto` and accumulate a sum.
4. In `longest_string()`, track the longest string using `auto`.
5. Run: `./run exercise 01-06-ex01`

---

## Exercise 2: auto with const/reference

**Files:** `ex02.h` (edit) -- `ex02_test.cpp` (read-only)

Choosing the right form of `auto` matters:

| Form | Copies? | Mutable? | Use when |
|------|---------|----------|----------|
| `auto` | Yes | Yes | You need an independent copy |
| `auto&` | No | Yes | You want to modify the original |
| `const auto&` | No | No | You only need to read |

### What to do

1. In `first_copy()`, use plain `auto` to return a copy of the first element.
2. In `last_ref()`, use `const auto&` to return a reference to the last element.
3. In `double_all()`, use `auto&` in a range-for to modify elements in place.
4. In `count_long_strings()`, use `const auto&` to read without copying.
5. Run: `./run exercise 01-06-ex02`

---

## Exercise 3: auto in range-for

**Files:** `ex03.h` (edit) -- `ex03_test.cpp` (read-only)

Range-for loops are the most natural place to use `auto`. The pattern
`for (const auto& elem : container)` is the standard idiom for read-only
iteration in modern C++.

### What to do

1. `sum()` -- iterate with `const auto&`, accumulate a total.
2. `negate_all()` -- iterate with `auto&`, flip each element's sign.
3. `join()` -- iterate with `const auto&`, build a comma-separated string.
4. `exclaim_all()` -- iterate with `auto&`, append `"!"` to each string.
5. `contains()` -- iterate with `const auto&`, return true on match.
6. Run: `./run exercise 01-06-ex03`

---

## Exercise 4: Trailing Return Types

**Files:** `ex04.h` (edit) -- `ex04_test.cpp` (read-only)

The trailing return type syntax puts the return type after the parameters:

```cpp
// Traditional:
int add(int a, int b) { return a + b; }

// Trailing:
auto add(int a, int b) -> int { return a + b; }
```

This is required in some template contexts where the return type depends on
the parameter types (which aren't in scope yet when the return type is
written in the traditional position).

### What to do

1. Convert each function signature to use trailing return type syntax.
2. Implement each function body.
3. Run: `./run exercise 01-06-ex04`

---

## Exercise 5: decltype for Expression Types

**Files:** `ex05.h` (edit) -- `ex05_test.cpp` (read-only)

`decltype(expr)` gives you the exact type of an expression at compile time,
without evaluating it. This is useful when you want a variable that matches
another expression's type:

```cpp
auto val = compute();
decltype(val) another_val = 0;  // same type as val
```

You can also use `decltype` with `::value_type` to extract container element
types:

```cpp
decltype(v)::value_type total = 0;  // if v is vector<int>, total is int
```

### What to do

1. `sum_with_decltype()` -- use `decltype` to declare the accumulator.
2. `deduced_size()` -- use `decltype(v.size())` for the variable type.
3. `multiply_add()` -- use `decltype(a * b)` to declare the result.
4. `reversed()` -- return a reversed copy of the string.
5. Run: `./run exercise 01-06-ex05`

---

## Exercise 6: Replace typedef with using

**Files:** `ex06.h` (edit) -- `ex06_test.cpp` (read-only)

The `using` keyword replaces `typedef` with cleaner syntax:

```cpp
// Old:
typedef std::vector<std::pair<std::string, int>> Scoreboard;

// New:
using Scoreboard = std::vector<std::pair<std::string, int>>;
```

The `using` form reads left-to-right, which makes complex types easier to
parse -- especially function pointers and nested templates.

### What to do

1. Convert each `typedef` in `ex06.h` to a `using` alias.
2. Implement `make_range()`, `highest_score()`, and `total_score()`.
3. Run: `./run exercise 01-06-ex06`

---

## Exercise 7: Template Alias

**Files:** `ex07.h` (edit) -- `ex07_test.cpp` (read-only)

`typedef` cannot be templated, but `using` can:

```cpp
template <typename T>
using Vec = std::vector<T>;

Vec<int> numbers;            // std::vector<int>
Vec<std::string> words;      // std::vector<std::string>
```

This is called a **template alias** (or alias template). It simplifies code
that uses a common pattern with different type parameters.

### What to do

1. Study the existing `Pair<T>` and `Table<T>` template aliases.
2. Implement `make_int_pair()`, `sum_and_diff()`, `table_lookup()`, and
   `table_size()`.
3. (Bonus) Write the `StringMap<T>` alias as practice.
4. Run: `./run exercise 01-06-ex07`

---

## Exercise 8: auto Return Type

**Files:** `ex08.h` (edit) -- `ex08_test.cpp` (read-only)

C++14 allows `auto` as a return type. The compiler deduces the type from the
`return` statement:

```cpp
auto square(int x) { return x * x; }  // deduced as int
```

This works well for short functions where the return type is obvious from
context. For longer functions or public APIs, an explicit return type is
usually better for documentation.

### What to do

1. Change each function's explicit return type to `auto`.
2. Implement the function body so it returns the correct value.
3. Run: `./run exercise 01-06-ex08`

Note: The initial code uses explicit return types so it compiles with `TODO()`.
After you implement the body with a `return` statement, you can safely change
to `auto`.
