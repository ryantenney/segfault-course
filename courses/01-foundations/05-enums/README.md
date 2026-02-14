# Lesson 05: Scoped Enums and Strong Types

## Why This Lesson Exists

C inherited its enums from the 1970s: unscoped, implicitly converting to `int`,
and leaking names into the enclosing scope.  C++11 introduced `enum class`
(scoped enumerations) to fix all three problems.  This lesson teaches you the
modern enum idiom and extends the idea to "strong typedefs" — wrapper types that
prevent accidentally swapping arguments.

## Key Concepts

### Unscoped Enums (C-style)

```cpp
enum Color { Red, Green, Blue };
int x = Red;          // implicit conversion to int — compiles
int y = Red + Green;  // arithmetic on enumerators — compiles
```

Problems:
- `Red`, `Green`, `Blue` pollute the surrounding namespace
- Implicit conversion to `int` allows nonsensical operations
- Two enums with the same enumerator name clash

### Scoped Enums (enum class)

```cpp
enum class Color { Red, Green, Blue };
Color c = Color::Red;   // must qualify the name
// int x = c;           // ERROR: no implicit conversion
int x = static_cast<int>(c);  // explicit conversion required
```

Benefits:
- Names are scoped: `Color::Red` does not collide with `TrafficLight::Red`
- No implicit conversion to `int` — catches bugs at compile time
- Can specify the underlying type: `enum class Status : uint8_t { ... }`

### Explicit Underlying Type

```cpp
enum class Opcode : uint8_t {
    Nop   = 0x00,
    Load  = 0x01,
    Store = 0x02
};
static_assert(sizeof(Opcode) == 1);  // guaranteed
```

Use this when you need a specific size for serialization, FFI, or when modeling
hardware registers.

### Enum to/from String

There is no built-in reflection for enums in C++ (before C++26).  The standard
patterns are:

```cpp
// Enum → string
std::string_view to_string(Color c) {
    switch (c) {
        case Color::Red:   return "Red";
        case Color::Green: return "Green";
        case Color::Blue:  return "Blue";
    }
    // no default — compiler warns if a case is missing
}

// String → enum
std::optional<Color> from_string(std::string_view s) {
    if (s == "Red")   return Color::Red;
    if (s == "Green") return Color::Green;
    if (s == "Blue")  return Color::Blue;
    return std::nullopt;
}
```

Omitting `default:` in the switch is intentional — it lets `-Wswitch` warn you
if a new enumerator is added but the switch is not updated.

### Bitflag Enums

When each enumerator is a power of two, you can combine them with bitwise OR:

```cpp
enum class Permission : uint8_t {
    None    = 0,
    Read    = 1,
    Write   = 2,
    Execute = 4
};

// Must overload operators — enum class forbids implicit int conversion
Permission operator|(Permission a, Permission b) {
    return static_cast<Permission>(
        static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}
```

### Strong Typedefs

Type aliases (`using UserId = int;`) do not create new types — they are just
alternate names for the same type.  A "strong typedef" wraps the value in a
struct:

```cpp
struct UserId {
    int value;
    explicit UserId(int v) : value(v) {}
    bool operator==(const UserId&) const = default;
};
```

Now `UserId` and `OrderId` (similarly defined) are distinct types.  Passing an
`OrderId` where a `UserId` is expected is a compile error.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 01-05

# Build and test a single exercise
./run exercise 01-05-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Convert a C Enum to enum class

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

The header defines a C-style `enum Color { Red, Green, Blue }`.  The
enumerators leak into the global scope and implicitly convert to `int`.

### What to do

1. Change `enum Color` to `enum class Color`.
2. Update the function bodies to use qualified names: `Color::Red`, etc.
3. Implement:
   - `is_red(c)` — return `c == Color::Red`
   - `opposite(c)` — Red maps to Blue, Blue to Red, Green stays Green
   - `same_color(a, b)` — return `a == b`

---

## Exercise 2: Enum with Explicit Underlying Type

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Define a `Severity` enum class backed by `uint8_t`.  This ensures the enum is
exactly one byte, suitable for compact storage or serialization.

### What to do

1. Define `enum class Severity : uint8_t` with values Trace=0 through Fatal=5.
2. Implement:
   - `is_warning_or_above(s)` — return `s >= Severity::Warning`
   - `severity_value(s)` — return `static_cast<uint8_t>(s)`
   - `more_severe(a, b)` — compare the underlying values

---

## Exercise 3: Enum to String

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Convert `Direction` enum values to human-readable strings.  Use a switch
statement without a default case.

### What to do

1. `to_string(d)` — switch on `d`, return the direction name as a string_view.
   Use string literals (they have static lifetime, so returning a `string_view`
   to them is safe).
2. `to_arrow(d)` — switch on `d`, return the arrow character.

---

## Exercise 4: String to Enum

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Parse a string into a `Season` enum value.  Return `std::nullopt` if the string
does not match any known season.

### What to do

1. `from_string(name)` — compare `name` against each season string.  Use
   `if`/`else if` chains.  Return the matching `Season` wrapped in
   `std::optional`, or `std::nullopt`.
2. `is_valid_season(name)` — return `from_string(name).has_value()`.

---

## Exercise 5: Enum as Bitflags

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

The `Permission` enum class is already defined with placeholder values (all
set to 0).  You need to assign the correct power-of-two values and implement
the bitwise operators.

### What to do

1. Fix the enumerator values: None=0, Read=1, Write=2, Execute=4.
2. Implement `operator|` — cast both operands to `uint8_t`, OR them, cast back.
3. Implement `operator&` — same pattern with bitwise AND.
4. Implement:
   - `has_permission(perms, flag)` — `(perms & flag) != Permission::None`
   - `read_write()` — `Permission::Read | Permission::Write`
   - `all_permissions()` — all three flags combined

---

## Exercise 6: Scoped Enum in Switch

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Use `HttpMethod` in switch statements to classify HTTP methods.  The key
practice here is omitting `default:` so the compiler warns about missing cases.

### What to do

1. `method_name(m)` — return "GET", "POST", "PUT", or "DELETE".
2. `is_safe(m)` — only Get is safe.
3. `is_idempotent(m)` — Get, Put, and Delete are idempotent; Post is not.

Use a switch in each function.  Do not add a `default` case.

---

## Exercise 7: Strong Typedef

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Stub structs `UserId` and `OrderId` are provided with a `value` member and
comparison operators already defaulted.  You need to add explicit constructors
and implement the helper functions.

### What to do

1. Add an `explicit` constructor to `UserId`:
   `explicit UserId(int v) : value(v) {}`
2. Add an `explicit` constructor to `OrderId`:
   `explicit OrderId(int v) : value(v) {}`
3. Implement:
   - `make_user_id(id)` — return `UserId(id)`
   - `make_order_id(id)` — return `OrderId(id)`
   - `user_id_value(id)` — return `id.value`
   - `order_id_value(id)` — return `id.value`

With these types in place, the compiler rejects code that mixes `UserId` and
`OrderId` — exactly the kind of bug that plain `int` aliases allow.
