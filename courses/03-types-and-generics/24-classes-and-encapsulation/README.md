# Lesson 24: Classes and Encapsulation

## Why This Lesson Exists

If you are coming from Java, Python, or another OOP language, C++ classes will
feel familiar on the surface. But the details differ in important ways. C++ gives
you fine-grained control over access, lifetime, and memory layout that other
languages abstract away. This lesson covers the foundations: access specifiers,
getters and setters, invariant enforcement, static members, and friend functions.

## Key Concepts

### struct vs class

In C++, `struct` and `class` are almost identical. The only difference is the
default access level:

```cpp
struct Point {
    int x;  // public by default
    int y;
};

class Point {
    int x;  // private by default
    int y;
};
```

By convention, `struct` is used for plain data aggregates (no invariants), and
`class` is used for types with behavior and invariants.

### Access Specifiers

C++ provides three access levels:

- **`public`**: accessible from anywhere
- **`private`**: accessible only from within the class and its friends
- **`protected`**: accessible from the class and its derived classes

You can switch between them freely within a class definition. Members are grouped
by access level for readability.

### Encapsulation and Invariants

An **invariant** is a condition that is always true between method calls. For
example, a `Fraction` class might guarantee that the denominator is always
positive and the fraction is in lowest terms.

The constructor establishes the invariant. Every public method preserves it. If
you make the data private and only expose controlled operations, the invariant
can never be violated from the outside.

### Static Members

A `static` member belongs to the class, not to any instance:

```cpp
class Widget {
    static int count_;  // one copy shared by all Widgets
public:
    Widget()  { ++count_; }
    ~Widget() { --count_; }
    static int count() { return count_; }
};
```

Static member functions can be called without an instance:
`Widget::count()`.

### Friend Functions

The `friend` keyword grants a non-member function access to a class's private
members:

```cpp
class Rect {
    double w_, h_;
    friend std::ostream& operator<<(std::ostream&, const Rect&);
};

std::ostream& operator<<(std::ostream& os, const Rect& r) {
    return os << r.w_ << "x" << r.h_;  // can access w_, h_
}
```

`friend` is intentional and controlled: the class decides who gets access.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 03-24

# Build and test a single exercise
./run exercise 03-24-ex01
```

Unfinished exercises show as **skipped** (yellow circles). Implemented exercises
show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: struct vs class

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

A `Point` is defined as a `struct` with public members. Your job is to convert
it to a `class` and make the members explicitly public.

### What to do

1. Change `struct Point` to `class Point`.
2. Add `public:` before the member declarations so they remain accessible.
3. Implement `distance_to()` using the Euclidean distance formula.
4. Implement the free function `midpoint()`.

---

## Exercise 2: Add Access Specifiers

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

The `BankAccount` class has all members at the default (private) access level
because it uses the `class` keyword. The constructor and methods need to be
public, the data members need to stay private, and one member needs to be
protected for future subclassing.

### What to do

1. Add `private:` before `account_id_`, `balance_`.
2. Add `protected:` before `overdraft_limit_`.
3. Add `public:` before the constructor and methods.
4. Implement all the methods.

---

## Exercise 3: Getter Methods

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

The `Color` class stores private RGB values. External code needs read-only
access. Getters marked `const` provide this.

### What to do

1. Implement `red()`, `green()`, `blue()` to return the corresponding component.
2. Implement `luminance()` using the weighted formula.
3. Implement `is_grayscale()` to check if all components are equal.
4. Implement the free function `is_bright()`.

---

## Exercise 4: Setter with Validation

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

The `User` class has setters that must enforce constraints. Invalid input should
throw `std::invalid_argument` and leave the object unchanged.

### What to do

1. Implement `name()`, `age()`, `email()` getters.
2. Implement `set_name()` — reject empty strings.
3. Implement `set_age()` — reject values outside [0, 150].
4. Implement `set_email()` — reject strings without `@`.

---

## Exercise 5: Invariant Enforcement

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

A `Fraction` class must always be in reduced form with a positive denominator.
A helper `normalize()` method is provided.

### What to do

1. In the constructor, validate that `den != 0` (throw if so), then call
   `normalize()`.
2. Implement `numerator()` and `denominator()` getters.
3. Implement `add()` and `multiply()` — each returns a new `Fraction`.
4. Implement `equals()` to compare normalized fractions.

---

## Exercise 6: Static Member Variable

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

The `Widget` class tracks how many instances are alive using a static counter.
The constructor and destructor are provided — they increment and decrement the
counter.

### What to do

1. Implement `instance_count()` — return the static counter.
2. Implement `reset_count()` — reset the counter and next ID to zero.
3. Implement `id()` — return this widget's unique ID.

---

## Exercise 7: Static Factory Method

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

The `Temperature` class stores its value internally as Celsius. The constructor
is private. You create instances through named static factory methods that make
the units explicit.

### What to do

1. Implement `from_celsius()`, `from_fahrenheit()`, `from_kelvin()`.
2. `from_kelvin()` should throw `std::invalid_argument` if the value is negative.
3. Implement `celsius()`, `fahrenheit()`, `kelvin()` getters.

---

## Exercise 8: Friend Function

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

The `Rect` class has private width and height. A `friend operator<<` needs
access to these members to print the rectangle in a specific format.

### What to do

1. Implement `width()`, `height()`, `area()`, `perimeter()` getters.
2. Implement `operator<<` to output `Rect(W x H)`.
3. The `friend` declaration is already in the class — you just need to write
   the function body.
