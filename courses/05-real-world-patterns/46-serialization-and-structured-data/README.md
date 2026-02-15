# Lesson 46: Serialization and Structured Data

## Why This Lesson Exists

Almost every real-world program needs to read and write structured data: config
files, API responses, database records, log entries. Understanding how to model
dynamic, heterogeneous data in a type-safe language like C++ is a fundamental
skill.

This lesson builds a JSON-like data model from scratch using `std::variant` and
`std::shared_ptr`, then adds serialization, parsing, pretty-printing, and the
visitor pattern for traversal.

## Key Concepts

### Flat Serialization

The simplest approach converts a struct to and from a `map<string, string>`:

```cpp
std::map<std::string, std::string> to_map(const Person& p);
Person from_map(const std::map<std::string, std::string>& m);
```

### Dynamic Value with std::variant

`std::variant` creates a tagged union that can hold exactly one of several
types at a time:

```cpp
using Value = std::variant<std::monostate, std::string, int, double, bool>;
```

`std::monostate` represents null/empty. Use `std::holds_alternative<T>()` and
`std::get<T>()` to inspect and access values.

### Recursive Data Structures

JSON arrays and objects are recursive — they contain values that may themselves
be arrays or objects. Since `std::variant` cannot hold a `vector<variant>` of
itself (incomplete type), we use `std::shared_ptr` to break the cycle:

```cpp
struct Node;
using NodePtr = std::shared_ptr<Node>;
using Array = std::vector<NodePtr>;
using Object = std::map<std::string, NodePtr>;
```

### Type-safe Accessors

Instead of raw `std::get<T>()` (which throws on type mismatch), return
`std::optional<T>` for a safe API:

```cpp
std::optional<std::string> as_string(const NodePtr& n);
```

### The Visitor Pattern

`std::visit` dispatches to a callable based on the active variant member.
For tree traversal, a Visitor struct with typed callbacks provides a clean,
extensible way to process every node.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 05-46

# Build and test a single exercise
./run exercise 05-46-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: To/From Map

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Implement `to_map()` and `from_map()` to convert a Person struct to and from a
flat `map<string, string>`. Test round-trip fidelity and default values.

---

## Exercise 2: Dynamic Value Type

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Implement type-checking methods (`is_string()`, `is_int()`, etc.) and
`type_name()` for a variant-based Value type.

---

## Exercise 3: Array and Object Values

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Implement factory functions and mutation helpers for a recursive Node type
using `shared_ptr`. Build nested arrays and objects.

---

## Exercise 4: Type-safe Accessors

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Implement `as_string()`, `as_int()`, etc. returning `optional<T>` for safe
access to Node values without risking `bad_variant_access`.

---

## Exercise 5: Serialize to String

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Implement `stringify()` to convert a Node tree into a compact JSON-like string.

---

## Exercise 6: Parse from String

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Implement `parse()` to convert a JSON-like string into a Node tree. Handle
strings, numbers, bools, null, arrays, and objects.

---

## Exercise 7: Pretty Print

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Implement `pretty_print()` to produce indented, multi-line output from a Node
tree with configurable indent width.

---

## Exercise 8: Visitor Pattern

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Implement `visit_value()` to traverse a Node tree depth-first, calling typed
callbacks from a Visitor struct for each node.
