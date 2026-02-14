# Lesson 17: Algorithms

## Why This Lesson Exists

The `<algorithm>` and `<numeric>` headers provide dozens of ready-made
operations for searching, sorting, transforming, and reducing data. These
algorithms operate on iterator ranges, so they work with any standard
container. Using them instead of hand-written loops makes your code
shorter, clearer, and less error-prone.

The key insight is that algorithms separate *what* you want to do (sort, find,
transform) from *how* you iterate. You provide the range and the operation;
the library handles the rest.

## Key Concepts

### Sorting

```cpp
std::sort(v.begin(), v.end());                    // ascending
std::sort(v.begin(), v.end(), std::greater<>());  // descending
```

After sorting, use `std::lower_bound` for O(log n) binary search.

### Searching and Counting

```cpp
auto it = std::find_if(v.begin(), v.end(), pred);   // first match
int n   = std::count_if(v.begin(), v.end(), pred);  // count matches
```

### Transforming

```cpp
std::transform(src.begin(), src.end(),
               std::back_inserter(dst), func);     // unary
std::transform(a.begin(), a.end(), b.begin(),
               std::back_inserter(dst), binary_fn); // binary
```

### Removing Elements

The erase-remove idiom is needed because `remove_if` only shuffles elements:

```cpp
auto it = std::remove_if(v.begin(), v.end(), pred);
v.erase(it, v.end());
```

### Accumulating

```cpp
int sum = std::accumulate(v.begin(), v.end(), 0);
int dot = std::inner_product(a.begin(), a.end(), b.begin(), 0);
```

### Predicate Queries

```cpp
bool any  = std::any_of(v.begin(), v.end(), pred);
bool all  = std::all_of(v.begin(), v.end(), pred);
bool none = std::none_of(v.begin(), v.end(), pred);
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 02-17

# Build and test a single exercise
./run exercise 02-17-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Sort and Search

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Sort a vector, then use `std::lower_bound` to perform binary search. Practice
both ascending and descending sort orders.

### What to do

1. Implement `sort_ascending` -- sort a vector in ascending order.
2. Implement `sort_descending` -- sort with `std::greater<int>()`.
3. Implement `binary_search_index` -- sort, then use `lower_bound` to find
   the target. Return its index, or -1 if not found.

---

## Exercise 2: Find and Count

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Use `std::find_if` and `std::count_if` with lambda predicates to search
and count elements.

### What to do

1. Implement `find_first_even` -- find the first even number.
2. Implement `count_strings_starting_with` -- count strings starting with
   a given character.
3. Implement `find_first_longer_than` -- find the first string longer than
   `n` characters.

---

## Exercise 3: Transform Elements

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Use `std::transform` to apply a function to each element and output the
results into a new container.

### What to do

1. Implement `to_uppercase` -- transform each string to uppercase.
2. Implement `square_all` -- transform each int to its square.
3. Implement `pairwise_sum` -- use the binary form of `transform` to add
   corresponding elements of two vectors.

---

## Exercise 4: Filter with Remove-Erase

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Use the erase-remove idiom (`std::remove_if` + `erase`) to filter elements
from a vector in place. Also practice `std::unique` for removing consecutive
duplicates.

### What to do

1. Implement `remove_odds` -- erase all odd numbers.
2. Implement `remove_empty_strings` -- erase all empty strings.
3. Implement `remove_duplicates` -- sort, then use `unique` + `erase`.

---

## Exercise 5: Copy_if

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Use `std::copy_if` to filter elements into a new container without modifying
the original. This is the non-destructive alternative to erase-remove.

### What to do

1. Implement `filter_evens` -- copy even numbers to a new vector.
2. Implement `filter_by_prefix` -- copy strings matching a prefix.
3. Implement `filter_in_range` -- copy numbers within [low, high].

---

## Exercise 6: Accumulate and Reduce

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Use `std::accumulate` to compute sums, products, and custom folds. Use
`std::inner_product` for dot products.

### What to do

1. Implement `sum_all` -- sum with `std::accumulate`.
2. Implement `product_all` -- product with a custom binary operation.
3. Implement `concat_strings` -- concatenate strings with a separator.
4. Implement `dot_product` -- compute a dot product with `std::inner_product`.

---

## Exercise 7: Min/Max and Partition

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Use `std::min_element` and `std::max_element` to find extremes. Use
`std::partition` and `std::partition_copy` to split elements by a predicate.

### What to do

1. Implement `find_min_max` -- return {min, max} from a vector.
2. Implement `partition_evens_first` -- partition evens before odds.
3. Implement `partition_by_threshold` -- split into below/at-or-above vectors.

---

## Exercise 8: Predicate Composition

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

Combine `std::any_of`, `std::all_of`, and `std::none_of` for expressive
range queries.

### What to do

1. Implement `has_negative` -- check if any element is negative.
2. Implement `all_positive` -- check if every element is positive.
3. Implement `none_empty` -- check if no string is empty.
4. Implement `classify_numbers` -- return "all positive", "all negative",
   "mixed", or "empty".
