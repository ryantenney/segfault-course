---
title: "Lesson 26: Operator Overloading"
---

## Why This Lesson Exists

C++ lets you define what operators like `==`, `+`, `<<`, and `[]` mean for
your own types.  This is not just syntactic sugar -- operator overloading is
how types integrate with the language and the standard library.  Without
`operator==`, your type cannot be used as a key in `std::unordered_map`.
Without `operator<`, it cannot be sorted.  Without `operator<<`, it cannot
be printed.

C++20 dramatically simplified comparison operators: a single `= default`
on `operator<=>` gives you all six comparison operators for free.

## Key Concepts

### Member vs. Free Function

Operators can be defined as member functions or free (non-member) functions:

```cpp
// Member: left-hand side is *this
struct Point {
    bool operator==(const Point& other) const;
};

// Free function: both operands are parameters
bool operator==(const Color& a, const Color& b);
```

Use a member function when the operator naturally belongs to the type.
Use a free function when the left-hand side is not your type (e.g.,
`operator<<` where the left side is `std::ostream`).

### Defaulted Comparisons (C++20)

For simple aggregates, the compiler can generate comparison operators:

```cpp
struct Rect {
    double x, y, width, height;
    bool operator==(const Rect&) const = default;
};
```

This compares each member in declaration order.  Defaulting `operator==`
also synthesizes `operator!=`.

### The Spaceship Operator (C++20)

`operator<=>` performs three-way comparison.  Defaulting it gives you all
six comparison operators (`==`, `!=`, `<`, `<=`, `>`, `>=`):

```cpp
struct Version {
    int major, minor, patch;
    auto operator<=>(const Version&) const = default;
};
```

### Arithmetic Operators

The canonical pattern is to implement `+=` as a member, then define `+`
as a free function that delegates to `+=`:

```cpp
Vec2& Vec2::operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2 operator+(Vec2 a, const Vec2& b) {
    return a += b;
}
```

### Stream Operators

`operator<<` and `operator>>` must be free functions:

```cpp
std::ostream& operator<<(std::ostream& os, const MyType& obj) {
    return os << obj.x << ", " << obj.y;
}
```

### Subscript Operator

Provide both const and non-const overloads:

```cpp
int&       operator[](size_t i);       // allows modification
const int& operator[](size_t i) const; // read-only
```

### Function Call Operator

`operator()` makes an object callable like a function (a "functor"):

```cpp
struct Multiplier {
    int factor;
    int operator()(int x) const { return x * factor; }
};
Multiplier m{3};
int result = m(7);  // 21
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 03-26

# Build and test a single exercise
./run exercise 03-26-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Equality Operator

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Implement `operator==` for two struct types: `Point` (as a member function)
and `Color` (as a free function).

### What to do

1. `Point::operator==` -- return true if both `x` and `y` match.
2. `operator==(Color, Color)` -- return true if `r`, `g`, and `b` all match.
3. Both also give you `operator!=` for free via C++20 rewrite rules.

---

## Exercise 2: Defaulted Equality

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Instead of writing comparison logic by hand, ask the compiler to generate
it.  Add `bool operator==(const T&) const = default;` to both `Rect` and
`Employee`.

### What to do

1. Add `bool operator==(const Rect&) const = default;` inside `Rect`.
2. Add `bool operator==(const Employee&) const = default;` inside `Employee`.
3. Implement `exercise_ready()` -- just return `true`.

---

## Exercise 3: Spaceship Operator

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Use `operator<=>` to get all six comparison operators from a single
declaration.  The compiler compares members in declaration order, which
gives `Version` natural version-number ordering and `FullName` natural
alphabetical ordering (last name first).

### What to do

1. Add `auto operator<=>(const Version&) const = default;` inside `Version`.
2. Add `auto operator<=>(const FullName&) const = default;` inside `FullName`.
3. Implement `exercise_ready()` -- just return `true`.

---

## Exercise 4: Arithmetic Operators

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Implement addition and scalar multiplication for a 2D vector type.  Follow
the canonical pattern: implement the compound assignment operator (`+=`,
`*=`) as a member, then build the binary operator (`+`, `*`) on top.

### What to do

1. `Vec2::operator+=` -- add `other.x` to `x`, `other.y` to `y`, return `*this`.
2. `operator+(Vec2, Vec2)` -- copy `a`, do `a += b`, return the copy.
3. `Vec2::operator*=` -- multiply both components by `scalar`, return `*this`.
4. `operator*(Vec2, double)` -- copy `v`, do `v *= scalar`, return the copy.

---

## Exercise 5: Stream Insertion

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Implement `operator<<` for two types so they can be printed to any output
stream.

### What to do

1. `operator<<(os, Timestamp)` -- format as `"HH:MM:SS"` with leading zeros.
   Use `std::setw(2)` and `std::setfill('0')` from `<iomanip>`.
2. `operator<<(os, Coordinate)` -- format as `"(lat, lon)"`.

---

## Exercise 6: Stream Extraction

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Implement `operator>>` to parse structured data from an input stream.

### What to do

1. `operator>>(is, Dimensions)` -- parse `"WxH"`.  Read `width`, consume
   the `'x'` character (use `char sep; is >> sep;` or `is.get()`), read
   `height`.
2. `operator>>(is, DateParts)` -- parse `"YYYY-MM-DD"`.  Read `year`,
   consume `'-'`, read `month`, consume `'-'`, read `day`.

---

## Exercise 7: Subscript Operator

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Implement `operator[]` for a fixed-size array wrapper with bounds checking.
Provide both const and non-const overloads.

### What to do

1. `operator[](size_t)` -- return `data_[index]`.  Throw
   `std::out_of_range` if `index >= N`.
2. `operator[](size_t) const` -- same logic, but returns `const int&`.
3. `size()` -- return `N`.

---

## Exercise 8: Function Call Operator

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

Implement `operator()` to create callable objects (functors).  Functors
can hold state and are used extensively with STL algorithms.

### What to do

1. `Multiplier::operator()(int)` -- return `value * factor_`.
2. `Counter::operator()()` -- return the current count, then increment.
3. `Counter::current()` -- return the count without incrementing.
4. `InRange::operator()(int)` -- return `value >= low_ && value <= high_`.
