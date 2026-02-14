# Lesson 15: Maps, Sets, and Custom Hashing

## Why This Lesson Exists

After `std::vector`, associative containers are the next most-used data
structures.  Maps give you key-value lookup; sets give you membership testing
and deduplication.  C++ offers both **ordered** (`std::map`, `std::set`) and
**unordered** (`std::unordered_map`, `std::unordered_set`) flavors.

Understanding when to use each, how to look up without accidentally inserting,
and how to provide custom comparators or hash functions unlocks the full power
of these containers.

## Key Concepts

### Ordered vs Unordered

| Feature | `std::map` / `std::set` | `std::unordered_map` / `std::unordered_set` |
|---------|-------------------------|---------------------------------------------|
| Backing structure | Red-black tree | Hash table |
| Lookup complexity | O(log n) | O(1) average |
| Iteration order | Sorted by key | Arbitrary |
| Key requirement | `operator<` (or comparator) | `std::hash` + `operator==` |

### Safe Lookup

`operator[]` on a map will **insert** a default-constructed value if the key
doesn't exist.  For non-mutating lookup, use:

```cpp
auto it = m.find(key);
if (it != m.end()) { /* use it->second */ }

// C++20:
if (m.contains(key)) { /* ... */ }
```

### Insert Patterns

```cpp
m.insert_or_assign(key, val);  // insert or overwrite
m.try_emplace(key, args...);   // insert only if key doesn't exist
```

`try_emplace` is useful when construction is expensive -- it only constructs
the value if the key is new.

### Custom Comparators

`std::map` and `std::set` accept a comparator as a template parameter:

```cpp
struct CaseInsensitiveLess {
    bool operator()(const std::string& a, const std::string& b) const;
};

std::map<std::string, int, CaseInsensitiveLess> m;
```

### Custom Hash Functions

For `unordered_map` with struct keys, you must provide both a hash function
and an equality operator:

```cpp
struct MyHash {
    std::size_t operator()(const MyKey& k) const;
};

std::unordered_map<MyKey, Value, MyHash> m;
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 02-15

# Build and test a single exercise
./run exercise 02-15-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Word Frequency Counter

**Files:** `ex01.h` (edit) - `ex01_test.cpp` (read-only)

`std::unordered_map<std::string, int>` is the classic tool for counting
things.  `operator[]` default-constructs the value (0 for int) on first
access, so `++counts[word]` just works.

### What to do

Implement `count_words()` which takes a vector of strings and returns an
`unordered_map` where each key is a word and each value is how many times
it appeared.

---

## Exercise 2: Safe Lookup

**Files:** `ex02.h` (edit) - `ex02_test.cpp` (read-only)

Using `operator[]` for lookup silently inserts default values.  For
non-mutating access, use `find()` (which returns an iterator) or
`contains()` (C++20, returns bool).

### What to do

1. `lookup_grade()` -- look up a student's grade by name, returning -1 if
   not found. Use `find()` instead of `operator[]`.
2. `has_student()` -- check if a student exists using `contains()`.
3. `count_passing()` -- count how many students have a grade >= 60.

---

## Exercise 3: Insert or Update

**Files:** `ex03.h` (edit) - `ex03_test.cpp` (read-only)

`insert_or_assign(key, value)` is the cleanest way to "upsert" -- insert a
new key-value pair, or overwrite the value if the key already exists.  Unlike
`operator[]`, it works with non-default-constructible value types.

### What to do

1. `build_config()` -- build a config map from a vector of key-value pairs,
   using `insert_or_assign`. Later entries overwrite earlier ones.
2. `update_setting()` -- update a single setting in a config map.

---

## Exercise 4: try_emplace for Lazy Init

**Files:** `ex04.h` (edit) - `ex04_test.cpp` (read-only)

`try_emplace(key, args...)` inserts a new element only if the key doesn't
already exist.  If the key exists, it does nothing (no overwrite, no wasted
construction).

This is particularly useful for building "get-or-create" patterns:

```cpp
auto [it, inserted] = m.try_emplace(key, default_value);
// it->second is the existing or newly inserted value
```

### What to do

1. `get_or_create()` -- return a reference to the value for a key, inserting
   a default if the key is new.
2. `group_by_length()` -- group words by their length using try_emplace.

---

## Exercise 5: Ordered Set Operations

**Files:** `ex05.h` (edit) - `ex05_test.cpp` (read-only)

`std::set` stores unique elements in sorted order.  Inserting a duplicate is
a no-op.  Iterating over a set always produces elements in ascending order.

### What to do

1. `unique_sorted()` -- given a vector, return its elements deduplicated and
   sorted (as a vector) using a set as intermediate storage.
2. `set_intersection()` -- return the elements common to two vectors.
3. `set_difference()` -- return elements in the first vector but not the second.

---

## Exercise 6: Custom Comparator

**Files:** `ex06.h` (edit) - `ex06_test.cpp` (read-only)

`std::map` uses `operator<` by default, but you can supply a custom
comparator as a template parameter.  A comparator is a type with
`bool operator()(const Key& a, const Key& b) const` that defines a strict
weak ordering.

### What to do

1. Write a `CaseInsensitiveLess` comparator that compares strings
   case-insensitively.
2. `build_case_insensitive_map()` -- build a map using this comparator.
3. `lookup_case_insensitive()` -- look up a key in the case-insensitive map.

---

## Exercise 7: Multimap

**Files:** `ex07.h` (edit) - `ex07_test.cpp` (read-only)

`std::multimap` allows multiple values per key.  This is useful for
one-to-many relationships like "tag to items" or "category to products."

Use `equal_range(key)` to get all values for a key, which returns a pair of
iterators (begin, end).

### What to do

1. `build_tag_index()` -- build a multimap mapping tags to item names.
2. `items_for_tag()` -- return all items associated with a given tag.
3. `all_tags()` -- return a sorted, deduplicated list of all tags.

---

## Exercise 8: Custom Hash Function

**Files:** `ex08.h` (edit) - `ex08_test.cpp` (read-only)

When using a struct as a key in `unordered_map`, you need to provide:
1. A hash function: `std::size_t operator()(const Key& k) const`
2. An equality operator: `bool operator==(const Key&) const`

A common approach for combining hash values of multiple fields is:

```cpp
std::size_t h1 = std::hash<Type1>{}(field1);
std::size_t h2 = std::hash<Type2>{}(field2);
return h1 ^ (h2 << 1);  // simple hash combine
```

### What to do

1. Define `operator==` on the `Point` struct.
2. Write a `PointHash` functor.
3. `build_point_map()` -- build an unordered_map with Point keys.
4. `lookup_point()` -- look up a value by Point key.
