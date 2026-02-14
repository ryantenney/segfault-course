# Lesson 25: Constructors, Initialization, and the Minefield

## Why This Lesson Exists

C++ has more ways to initialize an object than any other mainstream language.
Parentheses, braces, equals sign, designated initializers, member initializer
lists, in-class defaults, delegating constructors — each has different rules and
edge cases. This lesson walks through them systematically so you can write
initialization code with confidence instead of superstition.

## Key Concepts

### Member Initializer List

Members are constructed in the member initializer list, before the constructor
body runs:

```cpp
class Sensor {
    std::string name_;
    double value_;
public:
    Sensor(std::string n, double v) : name_(std::move(n)), value_(v) {}
    //                                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //                                member initializer list
};
```

Without the initializer list, `name_` would be default-constructed first, then
assigned in the body — two operations instead of one. For `const` members and
references, the initializer list is the only option.

### In-Class Member Initializers (NSDMIs)

C++11 lets you provide defaults directly in the class definition:

```cpp
class Config {
    int retries_ = 3;
    int timeout_ = 5000;
    bool verbose_ = false;
};
```

If a constructor does not mention a member in its initializer list, the in-class
default applies. This eliminates duplication across multiple constructors.

### Delegating Constructors

One constructor can delegate to another:

```cpp
class Log {
public:
    Log(std::string msg, std::string level, int ts)
        : msg_(std::move(msg)), level_(std::move(level)), ts_(ts) {}

    Log(std::string msg) : Log(std::move(msg), "INFO", 0) {}  // delegates
};
```

### The `explicit` Keyword

Single-argument constructors allow implicit conversion unless marked `explicit`:

```cpp
class Meters {
public:
    explicit Meters(double v);  // No implicit double -> Meters
};
```

### `= default` and `= delete`

You can explicitly request or forbid compiler-generated special members:

```cpp
class Foo {
public:
    Foo() = default;            // "please generate the default ctor"
    Foo(const Foo&) = delete;   // "forbid copying"
};
```

### Aggregate Initialization

An aggregate (no user-declared constructors, all public members) can be
initialized with braces and designated initializers:

```cpp
struct Config {
    std::string host = "";
    int port = 80;
};
Config c = {.host = "example.com", .port = 443};
```

### Direct Init `()` vs List Init `{}`

- `Type x(args)` — direct initialization, allows narrowing
- `Type x{args}` — list initialization, forbids narrowing, prefers
  `initializer_list` constructors

This distinction causes one of the most confusing behaviors in C++:

```cpp
std::vector<int> v1(5);    // 5 zeroes
std::vector<int> v2{5};    // one element: 5
```

### The Most Vexing Parse

```cpp
Timer t();  // Declares a function, NOT an object!
Timer t{};  // Constructs an object (C++11 fix)
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 03-25

# Build and test a single exercise
./run exercise 03-25-ex01
```

Unfinished exercises show as **skipped** (yellow circles). Implemented exercises
show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Member Initializer List

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

The `Sensor` class initializes members by assignment in the constructor body.
Rewrite it to use a member initializer list. Then uncomment the `const` member
`serial_number_` and initialize it there (you cannot assign to a const member
in the body).

### What to do

1. Replace the body assignments with a member initializer list.
2. Uncomment `serial_number_` and add it to the initializer list.
3. Implement all getters and the `record()` method.

---

## Exercise 2: In-Class Member Initializers

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

The `Config` class has three constructors. Instead of repeating default values
in each one, use in-class member initializers (NSDMIs).

### What to do

1. Add default values to member declarations.
2. Implement the three constructors. The default constructor can have an
   empty body; the others use initializer lists for the overridden values.
3. Implement the getter methods.

---

## Exercise 3: Delegating Constructors

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

The `LogEntry` class has a primary constructor taking all four fields and
three convenience constructors that provide defaults. Use delegating
constructors to avoid duplicating initialization logic.

### What to do

1. Implement the primary (4-argument) constructor with a member initializer list.
2. Each convenience constructor should delegate to the primary constructor.
3. Implement the getter methods.

---

## Exercise 4: Explicit Constructors

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

The `Meters` and `Kilograms` classes have single-argument constructors that
allow implicit conversion from `double`. Add `explicit` to prevent this.

### What to do

1. Add `explicit` to both constructors.
2. Implement `value()` getters.
3. Implement the free functions `add_distances`, `add_weights`, `is_tall`.

---

## Exercise 5: Default Constructor Control

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

The `Timestamp` class has a parameterized constructor, so it lost its default
constructor. Use `= default` to restore it. The `NonDefaultable` class should
use `= delete` to explicitly forbid default construction.

### What to do

1. Add `Timestamp() = default;` and in-class member initializers for the defaults.
2. Add `NonDefaultable() = delete;`.
3. Implement the getters and the free functions.

---

## Exercise 6: Aggregate Initialization

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

The `NetworkConfig` struct has four public members but no default values.
Add in-class member initializers (NSDMIs) and implement factory functions
using aggregate initialization and C++20 designated initializers.

### What to do

1. Add in-class default values to the four members (host="", port=80,
   use_tls=false, max_connections=10).
2. Do NOT add any constructors (aggregates must not have user-declared ctors).
3. Implement the factory functions using various initialization styles.

---

## Exercise 7: Direct vs List Initialization

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Demonstrate the difference between `()` and `{}` initialization. Each function
asks you to predict the result of a specific initialization expression.

### What to do

1. Implement each function to return the correct value.
2. Pay attention to `vector<int>(5)` vs `vector<int>{5}`.
3. Understand narrowing conversion behavior.

---

## Exercise 8: initializer_list Ambiguity

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

When both a regular constructor and an `initializer_list` constructor are
viable, braces prefer the `initializer_list` version. This exercise explores
the consequences.

### What to do

1. Implement each function to return the correct value.
2. `make_filled_vector()` must use `()` to call the count+value constructor.
3. `make_literal_vector()` must use `{}` for a literal list of elements.

---

## Exercise 9: Most Vexing Parse

**Files:** `ex09.h` (edit) | `ex09_test.cpp` (read-only)

Fix declarations that are parsed as function declarations instead of object
constructions.

### What to do

1. Fix `default_counter_value()` — use `{}` or remove `()` for default construction.
2. Implement `incremented_counter()` — construct a Counter at 10 and increment 3 times.
3. Implement `five_x_chars()` — create a string of 5 'x' characters.
4. Implement `empty_string_length()` — default-construct a string safely.
