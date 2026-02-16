---
title: "Lesson 14: vector, array, and span"
---

## Why This Lesson Exists

`std::vector` is the most-used container in C++.  If you only learn one
container, make it vector.  `std::array` replaces C-style fixed-size arrays
with bounds checking and value semantics.  `std::span` (C++20) lets you write
functions that accept *any* contiguous range without caring about the
underlying container.

Together these three types cover the vast majority of "I need a sequence of
things" use cases.

## Key Concepts

### std::vector

A dynamically-sized array that owns its elements on the heap.

```cpp
std::vector<int> v = {1, 2, 3};
v.push_back(4);          // append an element
v.emplace_back(5);       // construct in-place (avoids copy)
v.size();                 // 5
v.capacity();             // >= 5 (may be larger)
v[0];                     // unchecked access
v.at(0);                  // bounds-checked access (throws on out-of-range)
```

**Capacity vs size:** `size()` is the number of elements currently stored.
`capacity()` is how many the vector has allocated room for.  When
`size() == capacity()`, the next `push_back` triggers a reallocation (usually
doubling capacity).  Use `reserve(n)` to preallocate if you know the count
ahead of time.

### std::array

A fixed-size array that lives on the stack.  Unlike C arrays, it knows its own
size and supports `.at()` for bounds checking.

```cpp
std::array<int, 4> a = {10, 20, 30, 40};
a.size();                 // 4 (compile-time constant)
a.at(5);                  // throws std::out_of_range
```

### std::span (C++20)

A non-owning *view* over a contiguous sequence of elements.  It stores a
pointer and a length, nothing more.  This makes it cheap to pass by value.

```cpp
void print_all(std::span<const int> data) {
    for (int x : data) std::cout << x << ' ';
}

std::vector<int> v = {1, 2, 3};
std::array<int, 3> a = {4, 5, 6};
int c[] = {7, 8, 9};

print_all(v);   // works
print_all(a);   // works
print_all(c);   // works
```

### The Erase-Remove Idiom

Before C++20, removing elements matching a predicate from a vector required
two steps:

```cpp
auto it = std::remove_if(v.begin(), v.end(), predicate);
v.erase(it, v.end());
```

C++20 simplified this to:

```cpp
std::erase_if(v, predicate);
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 02-14

# Build and test a single exercise
./run exercise 02-14-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Populate a Vector

**Files:** `ex01.h` (edit) - `ex01_test.cpp` (read-only)

Vectors can be constructed in several ways: from an initializer list, or by
appending elements one at a time with `push_back` or `emplace_back`.

- `push_back(value)` copies or moves the value into the vector.
- `emplace_back(args...)` constructs the element in-place, which can be more
  efficient for complex types.
- Initializer-list construction: `std::vector<int> v = {1, 2, 3};`

### What to do

Implement three functions:
1. `make_vector_with_list()` -- return a vector built from an initializer list.
2. `make_vector_push_back()` -- build a vector by pushing elements one at a time.
3. `make_vector_emplace()` -- build a vector of pairs using `emplace_back`.

---

## Exercise 2: Reserve and Capacity

**Files:** `ex02.h` (edit) - `ex02_test.cpp` (read-only)

When you know ahead of time how many elements you'll add, `reserve(n)`
preallocates memory so that `push_back` doesn't trigger repeated
reallocations.

- `reserve(n)` sets `capacity()` to at least `n` but does not change `size()`.
- `size()` is the number of elements; `capacity()` is allocated storage.
- After `reserve(n)`, pushing up to `n` elements won't reallocate.

### What to do

1. `reserved_push()` -- reserve space, then push N elements, returning the
   final vector.
2. `capacity_after_reserve()` -- return the capacity after reserving.
3. `grow_and_report()` -- push elements one at a time and count how many
   times the capacity changed.

---

## Exercise 3: Bounds-Safe Access

**Files:** `ex03.h` (edit) - `ex03_test.cpp` (read-only)

`operator[]` performs no bounds checking -- accessing an out-of-range index
is undefined behavior.  `.at(index)` throws `std::out_of_range` if the index
is invalid, making it safe for untrusted input.

### What to do

1. `safe_element()` -- return the element at the given index using `.at()`.
2. `safe_sum()` -- sum a range of indices using `.at()`, letting exceptions
   propagate on out-of-range access.
3. `get_or_default()` -- return the element at an index, or a default value
   if the index is out of range. Use try/catch with `.at()`.

---

## Exercise 4: Vector of Objects

**Files:** `ex04.h` (edit) - `ex04_test.cpp` (read-only)

Vectors can hold any copyable/movable type, including your own structs.  This
exercise practices storing, accessing, and modifying custom objects in a
vector.

### What to do

A `Student` struct is provided with `name` and `grade` fields.

1. `make_class()` -- create a vector of Students from given data.
2. `find_top_student()` -- return the name of the student with the highest
   grade.
3. `curve_grades()` -- add a bonus to every student's grade (capped at 100).

---

## Exercise 5: Erase Elements

**Files:** `ex05.h` (edit) - `ex05_test.cpp` (read-only)

Removing elements from a vector while maintaining order requires the
"erase-remove idiom" (pre-C++20) or `std::erase` / `std::erase_if` (C++20).

- `std::erase(vec, value)` removes all elements equal to `value`.
- `std::erase_if(vec, predicate)` removes all elements satisfying the
  predicate.

### What to do

1. `remove_value()` -- remove all occurrences of a specific value.
2. `remove_negatives()` -- remove all negative numbers.
3. `remove_duplicates()` -- remove duplicate values, keeping the first
   occurrence of each (hint: use a set to track seen values).

---

## Exercise 6: Fixed-Size with std::array

**Files:** `ex06.h` (edit) - `ex06_test.cpp` (read-only)

`std::array<T, N>` is a stack-allocated, fixed-size container.  Unlike C
arrays, it knows its own size, supports `.at()` bounds checking, and has
proper value semantics (copyable, assignable).

### What to do

1. `make_zeros()` -- return a `std::array<int, 5>` filled with zeros.
2. `array_sum()` -- return the sum of all elements.
3. `safe_array_access()` -- access an element by index using `.at()`, letting
   `std::out_of_range` propagate if the index is invalid.
4. `reverse_array()` -- return a copy of the array with elements in reverse
   order.

---

## Exercise 7: Accept a Span Parameter

**Files:** `ex07.h` (edit) - `ex07_test.cpp` (read-only)

`std::span<const T>` is a non-owning view over contiguous data.  Functions
that accept `span` work with vectors, arrays, C arrays, and subranges -- all
through one parameter type.

### What to do

1. `span_sum()` -- sum all elements in a `span<const int>`.
2. `span_contains()` -- return whether the span contains a given value.
3. `span_min_max()` -- return a pair of the min and max values in the span.

---

## Exercise 8: Span from Different Sources

**Files:** `ex08.h` (edit) - `ex08_test.cpp` (read-only)

A single `std::span`-accepting function can be called with data from many
different container types.  This exercise demonstrates creating spans from
vectors, C arrays, and `std::array`, and passing them all to the same function.

### What to do

1. `compute_average()` -- compute the average of a `span<const double>`.
2. `from_vector()` -- call `compute_average` with data from a `std::vector`.
3. `from_c_array()` -- call `compute_average` with data from a C-style array.
4. `from_std_array()` -- call `compute_average` with data from a `std::array`.
