# Lesson 03: Value Semantics, const, and References

## Why This Lesson Exists

In Java and Python, variables hold references to objects.  Assigning one
variable to another gives you two references to the same object.  C++ is
fundamentally different: by default, variables hold *values*, and assignment
*copies* the value.  This lesson builds the mental model you need to reason
about copies, references, and const correctness — the foundation of safe,
efficient C++ code.

## Key Concepts

### Value Semantics

In C++, assignment and pass-by-value create independent copies:

```cpp
std::string a = "hello";
std::string b = a;       // b is a copy — independent from a
b += " world";           // only b is modified
// a is still "hello"
```

This applies to all types: `int`, `double`, `std::string`, `std::vector`,
and your own structs and classes.  The copy constructor and copy assignment
operator control *how* copying works for a type.

### Pass by Value vs Pass by Reference

**Pass by value** copies the argument into the parameter:

```cpp
void f(std::string s) {  // s is a copy
    s += "!";             // modifies the copy, not the caller's string
}
```

**Pass by reference** gives the function direct access to the caller's object:

```cpp
void f(std::string& s) { // s IS the caller's string
    s += "!";              // modifies the caller's string
}
```

**Pass by const reference** gives read-only access without copying:

```cpp
void f(const std::string& s) { // read-only alias
    // s += "!";                 // compiler error — s is const
    std::cout << s.size();      // OK — reading is fine
}
```

### When to Use Which

| Situation | Parameter type |
|-----------|---------------|
| Small, cheap to copy (int, double, char, bool) | Pass by value |
| Read-only access to a large object | `const T&` |
| Need to modify the caller's object | `T&` |
| Argument might not exist (nullable) | `T*` or `const T*` |

### `const` Methods

A method marked `const` promises not to modify the object's state:

```cpp
class Counter {
    int count_ = 0;
public:
    int get() const { return count_; }   // OK — doesn't modify
    void inc() { ++count_; }              // not const — modifies state
};
```

Only `const` methods can be called on a `const` object or through a
`const` reference.  This is why marking getters as `const` is essential.

### Const Correctness Chain

const propagates through the call chain.  If a function receives a `const T&`,
it can only call `const` methods on it.  If those methods return references,
those references must also be `const`:

```cpp
void print_name(const Person& p) {
    // p.set_name("x");         // error — p is const
    std::cout << p.get_name();  // OK — get_name() is const
}
```

### References and Object Lifetime

A reference is an alias — it doesn't own the object.  The object must outlive
the reference, or you get a **dangling reference**:

```cpp
const std::string& bad() {
    std::string local = "oops";
    return local;  // DANGLING — local is destroyed here
}
```

Safe patterns:
- Return a reference to a parameter (the caller owns it)
- Return a reference to a member (the object owns it)
- Return by value when in doubt

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 01-03

# Build and test a single exercise
./run exercise 01-03-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Prove Value Semantics

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

This exercise demonstrates that assignment creates an independent copy.
You'll implement `make_point()` and `offset_point()`, and the tests will
verify that modifying a copy doesn't affect the original.

### What to do

1. Implement `make_point(x, y)` — return a `Point{x, y}`.
2. Implement `offset_point(p, dx, dy)` — add `dx` to `p.x` and `dy` to
   `p.y`, then return `p`.  Since `p` is passed by value, the original
   is unaffected.
3. Run: `./run exercise 01-03-ex01`

---

## Exercise 2: Fix a Parameter Type

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

The `greet()` function takes a `std::string` by value — every call copies the
string unnecessarily.  Since the function only reads the string, it should take
a `const std::string&` instead.

### What to do

1. Change `std::string name` to `const std::string& name`.
2. Change both parameters of `full_greeting` to const references.
3. Implement `greet()` to return `"Hello, <name>!"`.
4. Implement `full_greeting()` to return `"Hello, <first> <last>!"`.
5. Run: `./run exercise 01-03-ex02`

---

## Exercise 3: Const-Qualify a Method

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

The `Counter` class has `get_count()` and `get_name()` methods that are
correctly marked `const`.  The test creates a `const Counter` and calls these
methods, which only works because they are `const`.

### What to do

1. Implement `get_count()` to return `count_`.
2. Implement `get_name()` to return `name_`.
3. Run: `./run exercise 01-03-ex03`

**Experiment:** Try removing the `const` keyword from `get_count()` and observe
the compiler error when the test calls it on a `const Counter`.

---

## Exercise 4: Const Correctness Chain

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

The `Temperature` class has several methods.  The non-modifying ones are
marked `const`, which is what allows the free functions `describe_temp()` and
`warmer_celsius()` to work: they receive `const Temperature&` and can only
call const methods on it.

### What to do

1. Implement each method:
   - `celsius()` — return `celsius_`
   - `fahrenheit()` — return `celsius_ * 9.0 / 5.0 + 32.0`
   - `is_freezing()` — return `celsius_ <= 0.0`
3. Implement `describe_temp(t)` — return `"COLD"` if `t.is_freezing()`,
   `"WARM"` otherwise.
4. Implement `warmer_celsius(a, b)` — return the larger of `a.celsius()`
   and `b.celsius()`.
5. Run: `./run exercise 01-03-ex04`

---

## Exercise 5: Swap via References

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

The classic swap algorithm requires modifying the caller's variables, which
means using reference parameters.

### What to do

1. Implement `swap_ints(a, b)` using a temporary variable:
   ```cpp
   int tmp = a;
   a = b;
   b = tmp;
   ```
2. Implement `sort_three(a, b, c)` using `swap_ints` to bubble-sort three
   values in-place.  A simple approach:
   ```
   if a > b: swap a, b
   if b > c: swap b, c
   if a > b: swap a, b
   ```
3. Run: `./run exercise 01-03-ex05`

---

## Exercise 6: Return a Const Reference

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

When a function needs to return an element from a container without copying
it, it returns a `const T&`.  The reference points into the container's
storage, so the container must outlive the reference.

### What to do

1. Implement `max_element(v)` — iterate through the vector and return a
   const reference to the largest element.  Track the index or a pointer
   to the max element.
2. Implement `longest_string(v)` — return a const reference to the longest
   string.  On ties, return the first one found.
3. Run: `./run exercise 01-03-ex06`

The tests verify that the return value is a reference into the vector,
not a copy.

---

## Exercise 7: Reference vs Pointer Parameter

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

The functions use reference parameters (`int&`) instead of C-style pointer
parameters (`int*`).  Notice how the caller doesn't need to write `&x` and
the implementation doesn't need `*ptr` dereferences.  References communicate
"this argument is required and will be modified."

### What to do

1. Implement `double_value(int& value)` — multiply value by 2 in-place.
2. Implement `rectangle_stats(...)` — set `area = width * height` and
   `perimeter = 2 * (width + height)`.
3. Implement `order_pair(int& lo, int& hi)` — swap if `lo > hi`.
4. Run: `./run exercise 01-03-ex07`

---

## Exercise 8: Dangling Reference

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

A commented-out function `bad_max()` shows a classic bug: returning a
reference to a local variable.  You'll implement safe alternatives.

### What to do

1. Read the commented-out `bad_max()` to understand the bug.
2. Implement `safe_max(a, b)` — return the longer string **by value**.
   On ties, return `a`.
3. Implement `safe_max_ref(a, b)` — return a **const reference** to the
   longer parameter.  This is safe because `a` and `b` are references to
   the caller's objects.  On ties, return `a`.
4. Implement `first_or_default(v, fallback)` — if the vector is non-empty,
   return a const reference to `v[0]`.  Otherwise return a const reference
   to `fallback`.  Both are safe because the caller owns the objects.
5. Run: `./run exercise 01-03-ex08`
