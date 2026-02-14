# Lesson 07: Structured Bindings

## Why This Lesson Exists

Before C++17, unpacking multi-valued returns was painful. You either used
`.first`/`.second` on pairs, `std::get<0>(t)` on tuples, or passed output
parameters by reference. All of these obscure intent and make code harder
to read.

Structured bindings fix this. They let you decompose pairs, tuples, structs,
and arrays into named variables in a single declaration. The result is code
that reads like it was written in Python or JavaScript -- but with full
compile-time type safety.

## Key Concepts

### Basic Syntax

A structured binding decomposes an object into named parts:

```cpp
std::pair<int, bool> result = map.insert({key, value});
auto [iter, inserted] = result;
// iter is the iterator, inserted is the bool
```

The names in brackets are created in the same order as the object's fields
(for structs) or elements (for pairs/tuples/arrays).

### What Can Be Decomposed

Structured bindings work with three kinds of types:

1. **Arrays:** `int arr[3] = {1, 2, 3}; auto [a, b, c] = arr;`
2. **Tuple-like types:** `std::pair`, `std::tuple`, `std::array`
3. **Aggregates:** structs and classes with all public non-static members

### Qualifiers

Like `auto` variables, you control copying and mutability:

```cpp
auto [a, b] = pair;         // copies the pair, a and b are independent
auto& [a, b] = pair;        // a and b are references into pair
const auto& [a, b] = pair;  // read-only references (no copy)
```

### Range-for with Maps

Structured bindings make map iteration clean:

```cpp
// Before:
for (const auto& entry : m) {
    use(entry.first, entry.second);
}

// After:
for (const auto& [key, value] : m) {
    use(key, value);
}
```

### If-with-initializer

C++17 also added the ability to declare variables inside an `if` condition.
Combined with structured bindings:

```cpp
if (auto [iter, ok] = map.insert({k, v}); ok) {
    // insertion succeeded, iter points to new element
} else {
    // key existed, iter points to existing element
}
```

The variables (`iter`, `ok`) are scoped to the if/else block.

### Multi-return Pattern

The modern C++ idiom for returning multiple values:

```cpp
struct Stats {
    int count;
    double average;
    int max_val;
};

Stats compute(const std::vector<int>& v) {
    // ... compute and return {count, avg, max}
}

// Call site:
auto [count, avg, max] = compute(data);
```

This gives you named fields in the struct (for documentation) AND named
bindings at the call site (for readability).

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 01-07

# Build and test a single exercise
./run exercise 01-07-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Decompose a pair

**Files:** `ex01.h` (edit) -- `ex01_test.cpp` (read-only)

`std::map::insert` returns a `std::pair<iterator, bool>`. The iterator
points to the element (new or existing), and the bool says whether insertion
happened. Traditionally you'd write:

```cpp
auto result = m.insert({key, value});
if (result.second) { /* inserted */ }
auto it = result.first;
```

With structured bindings:

```cpp
auto [iter, inserted] = m.insert({key, value});
if (inserted) { /* inserted */ }
```

### What to do

1. In `try_insert()`, use a structured binding to unpack `insert()`'s return
   and return the `inserted` boolean.
2. In `insert_or_get()`, use a structured binding and return `iter->second`.
3. In `min_max()`, return a pair with the smaller value first.
4. Run: `./run exercise 01-07-ex01`

---

## Exercise 2: Iterate a map

**Files:** `ex02.h` (edit) -- `ex02_test.cpp` (read-only)

Map iteration is where structured bindings shine. Instead of `entry.first`
and `entry.second`, you write `[key, value]` and the code documents itself.

### What to do

1. `get_keys()` -- iterate with `const auto& [key, value]`, collect keys.
2. `sum_values()` -- iterate and accumulate values.
3. `key_of_max()` -- iterate and track the key with the highest value.
4. `format_map()` -- iterate and build a `"key=val,key=val"` string.
5. Run: `./run exercise 01-07-ex02`

---

## Exercise 3: Unpack a struct

**Files:** `ex03.h` (edit) -- `ex03_test.cpp` (read-only)

Structured bindings decompose aggregates (structs with public members) in
member-declaration order:

```cpp
struct Point { double x; double y; };
auto [x, y] = make_point(3.0, 4.0);
```

The binding names don't need to match the member names, but it's good
practice to keep them consistent.

### What to do

1. Implement `make_point()`, `make_rect()`, and `make_person()` to return
   the appropriate structs.
2. Implement `distance_from_origin()`, `rect_area()`, and `greet()`.
3. Run: `./run exercise 01-07-ex03`

The tests use structured bindings to decompose your returned structs.

---

## Exercise 4: Tuple decomposition

**Files:** `ex04.h` (edit) -- `ex04_test.cpp` (read-only)

`std::tuple` holds a fixed-size collection of different types. Structured
bindings unpack them cleanly:

```cpp
auto [quotient, remainder] = divmod(17, 5);
```

This is much better than `std::get<0>(result)` and `std::get<1>(result)`.

### What to do

1. `stats()` -- compute min, max, and sum; return as a tuple.
2. `divmod()` -- return quotient and remainder.
3. `split_name()` -- split on the first space, return first/last names.
4. `count_and_sum_positive()` -- count and sum positive values.
5. Run: `./run exercise 01-07-ex04`

---

## Exercise 5: Binding with const/reference

**Files:** `ex05.h` (edit) -- `ex05_test.cpp` (read-only)

Structured bindings respect `const` and `&` qualifiers:

```cpp
auto& [key, value] = *m.begin();   // mutable references
value += 10;                        // modifies the map entry

const auto& [k, v] = *m.begin();   // read-only
// v += 10;  // ERROR: v is const
```

When iterating a map with `auto& [key, value]`, note that `key` is still
`const` (because map keys are always `const Key`), but `value` is mutable.

### What to do

1. `swap_values()` -- find two entries and swap their values.
2. `increment_all()` -- use `auto& [key, value]` to modify all values.
3. `summarize()` -- use `const auto& [key, value]` to read entries.
4. `any_exceeds()` -- use `const auto& [key, value]` to check values.
5. Run: `./run exercise 01-07-ex05`

---

## Exercise 6: If-init with binding

**Files:** `ex06.h` (edit) -- `ex06_test.cpp` (read-only)

C++17's if-with-initializer lets you declare variables inside the `if`
statement and scope them to the if/else block:

```cpp
if (auto it = map.find(key); it != map.end()) {
    // it is valid here
} else {
    // it is also valid here (but points to end())
}
// it is NOT accessible here
```

Combined with structured bindings for `insert()`:

```cpp
if (auto [iter, ok] = map.insert({k, v}); ok) {
    // inserted
}
```

### What to do

1. `describe_insert()` -- use if-init with `insert()` to report the outcome.
2. `find_or()` -- use if-init with `find()` to return a value or fallback.
3. `classify_value()` -- use if-init with `find()` to classify the result.
4. Run: `./run exercise 01-07-ex06`

---

## Exercise 7: Multi-return function (Capstone)

**Files:** `ex07.h` (edit) -- `ex07_test.cpp` (read-only)

This exercise ties together the whole lesson. You will:

1. Work with a struct (`TextStats`) that bundles multiple return values.
2. Implement a function that computes all fields and returns the struct.
3. Implement a formatting function that uses structured bindings to
   decompose the struct at the call site.

This is the idiomatic modern C++ pattern for multi-return functions: define
a struct with named fields, return it, and decompose with structured bindings.

### What to do

1. Implement `analyze_text()` to populate a `TextStats` struct. Words are
   separated by single spaces (no leading/trailing/double spaces).
2. Implement `text_summary()` using structured bindings to format the result
   as `"N words, M chars, longest: L"`.
3. Run: `./run exercise 01-07-ex07`
