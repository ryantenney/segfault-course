# Lesson 16: Iterators

## Why This Lesson Exists

Iterators are the bridge between containers and algorithms in C++. Instead of
writing separate loop logic for every container type, iterators provide a
uniform interface for traversing elements. Understanding iterators is essential
for using the Standard Library effectively -- nearly every algorithm takes a
pair of iterators to define the range it operates on.

C++ iterators come in several categories, each with different capabilities:

- **Input / Output** -- single-pass, read-only or write-only
- **Forward** -- multi-pass, read/write (e.g., `std::forward_list`)
- **Bidirectional** -- forward + backward (e.g., `std::list`, `std::map`)
- **Random Access** -- bidirectional + jump (e.g., `std::vector`, `std::deque`)

## Key Concepts

### Basic Iterator Usage

Every container provides `begin()` and `end()`. The range `[begin, end)` is
half-open: `begin` points to the first element, `end` points one past the last.

```cpp
std::vector<int> v = {1, 2, 3};
for (auto it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << "\n";
}
```

### Const Iterators

`cbegin()` and `cend()` return const iterators that prevent modification:

```cpp
auto it = v.cbegin();   // *it is read-only
```

### Reverse Iterators

`rbegin()` and `rend()` traverse the container backwards:

```cpp
for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
    // visits elements in reverse order
}
```

### Iterator Utilities

The `<iterator>` header provides generic navigation functions:

```cpp
auto it = std::next(v.begin(), 3);   // 3 positions forward
auto dist = std::distance(a, b);      // count of steps from a to b
std::advance(it, n);                  // move it forward by n (in place)
```

### Output Iterators

`std::back_inserter` and `std::inserter` create output iterators that
grow a container automatically:

```cpp
std::vector<int> dst;
std::copy(src.begin(), src.end(), std::back_inserter(dst));
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 02-16

# Build and test a single exercise
./run exercise 02-16-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Manual Iteration

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Use iterators to traverse a `std::list` -- a container that does not support
random access with `[]`. Practice dereferencing, incrementing, and comparing
iterators.

### What to do

1. Implement `sum_list` -- iterate through the list with `begin()`/`end()`
   and accumulate the sum.
2. Implement `double_elements` -- iterate through the list and multiply
   each element by 2 using `*it`.
3. Implement `find_in_list` -- iterate and return an iterator to the first
   matching element, or `end()` if not found.

---

## Exercise 2: Const Iteration

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Use `cbegin()`/`cend()` for read-only traversal. Const iterators make your
intent clear and prevent accidental mutation.

### What to do

1. Implement `contains` -- search for a value using const iterators.
2. Implement `build_comma_string` -- join strings with `", "` separators
   using const iteration.
3. Implement `first_positive` -- return a `const_iterator` to the first
   element greater than zero.

---

## Exercise 3: Erase While Iterating

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Erasing from a container during iteration is a common source of bugs. The
correct pattern uses the return value of `erase()`, which provides a valid
iterator to the next element.

### What to do

1. Implement `remove_negative_values` -- erase map entries with negative
   values using the erase-during-iteration pattern.
2. Implement `remove_long_keys` -- erase map entries whose key exceeds
   a given length.
3. Implement `remove_if_map` -- generic erase using a predicate function.

---

## Exercise 4: Reverse Iteration

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Use `rbegin()`/`rend()` to traverse a container from back to front. Reverse
iterators are useful for finding the last occurrence of something or building
reversed copies.

### What to do

1. Implement `reverse_copy_vec` -- build a new vector by iterating backwards.
2. Implement `last_n_elements` -- extract the last `n` elements in their
   original order.
3. Implement `find_last` -- find the last occurrence of a value and return
   its index.

---

## Exercise 5: Iterator Arithmetic

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Use `std::next`, `std::advance`, and `std::distance` to navigate iterators
generically. These functions work with any iterator category, using the most
efficient method available.

### What to do

1. Implement `get_nth` -- return the nth element of a list using `std::next`.
2. Implement `distance_between` -- find two elements and return the distance
   between them.
3. Implement `advance_and_read` -- advance an iterator and return the element.
4. Implement `get_middle` -- return the middle element of a vector.

---

## Exercise 6: Back-Inserter

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Use `std::back_inserter` to create an output iterator that grows a container
by calling `push_back()` for each element written. This is essential for
safely writing algorithm output into an empty container.

### What to do

1. Implement `copy_to_vector` -- use `std::copy` with `std::back_inserter`
   to copy from a list to a vector.
2. Implement `transform_to_vector` -- use `std::transform` with
   `std::back_inserter` to apply a function to each element.
3. Implement `merge_vectors` -- use `std::copy` with `std::back_inserter`
   to append one vector to another.

---

## Exercise 7: Insert Iterator

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Use `std::inserter` with a position hint for ordered containers. Unlike
`back_inserter`, `inserter` works with any container that has an `insert()`
method, including `std::set` and `std::list`.

### What to do

1. Implement `vector_to_set` -- copy a vector into a set using `std::inserter`.
2. Implement `merge_sets` -- insert all elements from one set into another.
3. Implement `insert_at_front` -- use `std::inserter` with `lst.begin()` to
   prepend elements to a list.

---

## Exercise 8: Custom Iterator

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

Implement `begin()` and `end()` for a custom `IntRange` class so it works
in range-based for loops. A valid iterator needs `operator*`, `operator++`,
and `operator!=`.

### What to do

1. Implement `IntRange::Iterator::operator*` -- return the current value.
2. Implement `IntRange::Iterator::operator++` -- advance and return `*this`.
3. Implement `IntRange::Iterator::operator!=` -- compare two iterators.
4. Implement `IntRange::begin()` and `IntRange::end()`.
5. Implement `range_sum` and `collect_range` using range-for over `IntRange`.
