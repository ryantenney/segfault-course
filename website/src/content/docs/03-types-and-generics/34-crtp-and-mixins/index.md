---
title: "Lesson 34: CRTP and Mixin Patterns"
---

## Why This Lesson Exists

The Curiously Recurring Template Pattern (CRTP) is one of C++'s most distinctive
idioms. A class derives from a template base, passing *itself* as the template
argument:

```cpp
template <typename Derived>
class Base { ... };

class Widget : public Base<Widget> { ... };
```

This gives the base class compile-time knowledge of the derived class, enabling
static polymorphism without virtual dispatch overhead. The pattern is used
throughout the C++ ecosystem for:

- **Instance counting** -- each derived type gets its own static counter
- **Static interfaces** -- compile-time enforcement of an API contract
- **Operator generation** -- auto-generating `!=` from `==`, or `>` from `<`
- **Mixins** -- composable units of functionality bolted onto any class

Before C++20's `<=>` operator and concepts, CRTP was often the only clean way to
achieve these goals. Even in modern C++, it remains relevant for performance-
critical code and for policy-based design.

## Key Concepts

### CRTP Mechanics

When `Widget` inherits from `Base<Widget>`, the base class can access Widget's
members via `static_cast<const Derived*>(this)`. This cast is safe because
`this` really is a `Widget` -- the compiler verifies this at compile time.

```cpp
template <typename Derived>
class Printable {
public:
    void print() const {
        // Derived MUST have a format() method
        std::cout << static_cast<const Derived*>(this)->format();
    }
};
```

### Static vs. Dynamic Polymorphism

| Property | Virtual Dispatch | CRTP |
|---|---|---|
| Resolved at | Runtime | Compile time |
| Overhead | vtable pointer + indirect call | Zero (inlined) |
| Open set of types | Yes (plugins, etc.) | No (all types known at compile time) |
| Heterogeneous containers | Yes (`vector<Base*>`) | No (each instantiation is a different type) |

Choose virtual dispatch when new types can be added without recompilation.
Choose CRTP when all types are known at compile time and performance matters.

### Mixins via CRTP

A mixin adds a capability to any class that satisfies its requirements. Unlike
traditional inheritance ("is-a"), mixins model "can-do":

```cpp
class Sensor : public Loggable<Sensor>, public Serializable<Sensor> {
    // Must provide to_string() for Loggable
    // Must provide serialize() for Serializable
};
```

Multiple mixins compose cleanly because each CRTP base is a separate template
instantiation with no shared state.

### Policy-Based Design

Template parameters can customize a class's behavior at compile time:

```cpp
template <typename Storage, typename Threading>
class Buffer : private Storage, private Threading { ... };
```

Each "policy" is a small class responsible for one aspect of behavior. This is
an alternative to deep inheritance hierarchies and gives zero-overhead
customization.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 03-34

# Build and test a single exercise
./run exercise 03-34-ex01
```

Unfinished exercises show as **skipped** (yellow circles). Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: CRTP Counter

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

A `Counter<Derived>` CRTP base tracks how many instances of each derived type
are alive. Each instantiation (e.g., `Counter<Dog>` vs. `Counter<Cat>`) has its
own independent static count.

### What to do

1. Implement `Dog::name()` -- return the stored name.
2. Implement `Cat::name()` -- return the stored name.
3. Implement `make_dogs()` -- create a `vector<Dog>` from the given names.
4. Implement `total_animals()` -- return `Dog::count() + Cat::count()`.

---

## Exercise 2: Static Interface via CRTP

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

The `Shape<Derived>` CRTP base defines a public API (`area()`, `perimeter()`,
`name()`) that delegates to the derived class via `static_cast`. The derived
class must provide `area_impl()`, `perimeter_impl()`, and `name_impl()`.

### What to do

1. Implement `Circle::area_impl()` -- return pi * r * r.
2. Implement `Circle::perimeter_impl()` -- return 2 * pi * r.
3. Implement `Rectangle::area_impl()` -- return width * height.
4. Implement `Rectangle::perimeter_impl()` -- return 2 * (width + height).
5. Implement `print_area()` -- format as `"<name>: <area>"`.

---

## Exercise 3: CRTP for Operator Generation

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

`EqualityComparable<Derived>` generates `operator!=` from `operator==`.
`LessThanComparable<Derived>` generates `>`, `<=`, and `>=` from `<`.
This was the standard pre-C++20 pattern for reducing operator boilerplate.

### What to do

1. Implement `Token::operator==` -- compare type and value.
2. Implement `Coordinate::operator==` -- compare x, y, and z.
3. Implement `Coordinate::operator<` -- lexicographic comparison by (x, y, z).

---

## Exercise 4: Logging Mixin

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

`Loggable<Derived>` adds a `log(level)` method that formats a log string by
calling the derived class's `to_string()` method. This is a classic example
of a CRTP mixin -- adding cross-cutting functionality to unrelated types.

### What to do

1. Implement `Event::to_string()` -- return `"Event(<name>)"`.
2. Implement `Metric::to_string()` -- return `"Metric(<name>=<value>)"`.
3. Implement `format_log_entry()` -- call `obj.log(level)`.

---

## Exercise 5: Composable Policies

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Policy-based design parameterizes a class with small, focused policy types.
A `Buffer` template composes a `StoragePolicy` (how data is stored) with a
`ThreadingPolicy` (how concurrency is handled).

### What to do

1. Implement `FixedStorage<N>::store()` -- store a value at an index.
2. Implement `FixedStorage<N>::get()` -- return the value at an index.
3. Implement `FixedStorage<N>::capacity()` -- return N.
4. Implement `DynamicStorage::store()` -- resize if needed, then store.
5. Implement `DynamicStorage::get()` -- return the value at an index.
6. Implement `DynamicStorage::capacity()` -- return current size.

---

## Exercise 6: CRTP vs Virtual Dispatch

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

The virtual dispatch version (`VirtualOp`, `VirtualAdd`, `VirtualMultiply`) is
provided. Implement the CRTP equivalent (`CrtpOp`, `CrtpAdd`, `CrtpMultiply`)
with identical behavior but without virtual functions.

### What to do

1. Implement `CrtpAdd::apply_impl(a, b)` -- return a + b.
2. Implement `CrtpMultiply::apply_impl(a, b)` -- return a * b.
3. Implement `crtp_compute()` -- call `op.apply(x, y)`.

---

## Exercise 7: Multiple Mixin Bases

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Compose two CRTP mixin bases -- `Printable<Derived>` and `Cloneable<Derived>`
-- into single derived classes. Each mixin adds independent functionality
(printing and cloning), and the derived class must satisfy both interfaces.

### What to do

1. Implement `Config::format()` -- return `"Config{<key>=<value>}"`.
2. Implement `Config::clone_impl()` -- return a copy of `*this`.
3. Implement `Message::format()` -- return `"Message{<sender>: <text>}"`.
4. Implement `Message::clone_impl()` -- return a copy of `*this`.
5. Implement `print_and_clone()` -- return `{obj.print(), obj.clone()}`.
