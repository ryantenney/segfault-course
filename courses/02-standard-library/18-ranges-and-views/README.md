# Lesson 18: Ranges and Views (C++20)

## Why This Lesson Exists

C++20 ranges transform how you write algorithm pipelines.  Instead of
passing iterator pairs everywhere, you pass containers directly.  Instead of
allocating temporary vectors for each intermediate step, you chain lazy
*views* with the pipe operator -- no extra allocations, readable code, and
the same performance as hand-written loops.

If you've used LINQ (C#), Java Streams, or Python generators, the mental
model is similar: describe *what* you want, let the library handle the
iteration.

## Key Concepts

### std::ranges algorithms

`std::ranges::sort`, `std::ranges::find`, `std::ranges::min_element`, etc.
accept an entire container instead of `begin/end` pairs:

```cpp
std::vector<int> v = {3, 1, 2};
std::ranges::sort(v);                     // v is now {1, 2, 3}
auto it = std::ranges::find(v, 2);        // points to element 2
```

### Lazy views

Views are lightweight wrappers that transform elements on-the-fly as you
iterate, without creating intermediate containers:

```cpp
auto view = vec | std::views::filter([](int x) { return x > 0; })
                | std::views::transform([](int x) { return x * x; });
// No work happens until you iterate `view`
```

### Pipe syntax

The pipe operator `|` chains views left-to-right, making complex pipelines
easy to read:

```cpp
auto result = data
    | views::filter(pred)
    | views::transform(fn)
    | views::take(10);
```

### Projections

Ranges algorithms accept an optional *projection* parameter -- a callable
that extracts the value to operate on. This replaces many custom comparators:

```cpp
struct Employee { std::string name; int salary; };
std::ranges::sort(employees, {}, &Employee::salary);  // sort by salary
```

### Materializing views

Views are lazy -- to store results, collect them into a container:

```cpp
std::vector<int> result;
for (int x : view) result.push_back(x);
```

### views::split

Splits a range into subranges at each delimiter occurrence.  Useful for
tokenizing strings without `std::istringstream`:

```cpp
for (auto part : "a,b,c"sv | std::views::split(',')) {
    std::string token(part.begin(), part.end());
}
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 02-18

# Build and test a single exercise
./run exercise 02-18-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Ranges Sort and Find

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Rewrite classic algorithm calls using the `std::ranges::` versions.
Instead of `std::sort(v.begin(), v.end())`, use `std::ranges::sort(v)`.

### What to do

1. Implement `sort_ascending()` -- sort using `std::ranges::sort`.
2. Implement `find_value()` -- use `std::ranges::find` to check existence.
3. Implement `sort_descending()` -- sort with `std::greater<>{}` comparator.

---

## Exercise 2: Filter View

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Use `views::filter` to lazily select elements matching a predicate.
Materialize the view into a vector by iterating and pushing back.

### What to do

1. Implement `filter_positives()` -- keep only positive values.
2. Implement `filter_long_strings()` -- keep strings longer than a threshold.
3. Implement `count_matching()` -- count elements satisfying a predicate.

---

## Exercise 3: Transform View

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Use `views::transform` to lazily apply a function to each element.
Collect the results into a vector.

### What to do

1. Implement `double_values()` -- double each integer.
2. Implement `extract_lengths()` -- extract the length of each string.
3. Implement `negate_values()` -- negate each integer.

---

## Exercise 4: Filter-Transform Pipeline

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Chain `views::filter | views::transform` using the pipe operator.
This is where ranges start to feel expressive.

### What to do

1. Implement `squares_of_evens()` -- filter evens, then square them.
2. Implement `uppercase_short_words()` -- filter short strings, uppercase them.
3. Implement `sum_of_positives_doubled()` -- filter positives, double, sum.

---

## Exercise 5: Take and Drop

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Use `views::take` and `views::drop` to slice a range.  These views
gracefully handle cases where `n` exceeds the range size.

### What to do

1. Implement `first_n()` -- take the first n elements.
2. Implement `skip_n()` -- drop the first n elements.
3. Implement `middle_slice()` -- combine drop and take for a subrange.

---

## Exercise 6: Custom Projection

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Use the `proj` parameter in ranges algorithms to sort and find by a
specific struct member, without writing a custom comparator.

### What to do

1. Implement `sort_by_age()` -- sort people by age using a projection.
2. Implement `find_by_name()` -- find a person by name using a projection.
3. Implement `youngest_person()` -- find the youngest using `min_element` with a projection.

---

## Exercise 7: Compose a Multi-Stage Pipeline

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Build 3+ stage view pipelines that combine filter, transform, take, and
drop.  Materialize the final view into a vector.

### What to do

1. Implement `top_scores()` -- filter passing, sort descending, take top n.
2. Implement `transform_pipeline()` -- filter, square, drop first skip.
3. Implement `label_pipeline()` -- filter, format strings, take limited count.

---

## Exercise 8: Split and Join

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Use `views::split` to tokenize a string view by a delimiter character.
Collect the subranges into strings.

### What to do

1. Implement `split_by_comma()` -- split a comma-separated string.
2. Implement `split_by_char()` -- split by an arbitrary delimiter.
3. Implement `count_words()` -- split by spaces, count non-empty parts.
