---
title: "Lesson 02: Namespaces"
---

## Why This Lesson Exists

If you've used Java packages, Python modules, or Rust's `mod` system, namespaces
will feel familiar in purpose but different in mechanics.  C++ namespaces are
purely a name-scoping mechanism — they don't imply directory structure, access
control, or module boundaries.  Understanding them is essential because every
C++ codebase uses them, and subtle features like ADL can cause real confusion
if you aren't prepared.

## Key Concepts

### Namespaces as Name Scopes

A namespace groups declarations under a common name to prevent collisions:

```cpp
namespace math {
    int add(int a, int b) { return a + b; }
}

namespace graphics {
    int add(Color a, Color b) { /* blend colors */ }
}
```

Both `add` functions coexist because their fully-qualified names differ:
`math::add` vs `graphics::add`.

### Nested Namespaces (C++17)

Before C++17, nested namespaces required verbose nesting:

```cpp
namespace company { namespace project { namespace module {
    void func();
}}}
```

C++17 lets you write:

```cpp
namespace company::project::module {
    void func();
}
```

Same result, much cleaner.

### `using` Declarations vs `using namespace`

A **`using` declaration** imports one specific name:

```cpp
using std::string;     // just string
string name = "hello"; // OK
vector<int> v;         // error — vector not imported
```

A **`using namespace`** directive imports *everything*:

```cpp
using namespace std;   // ALL of std is now in scope
string name = "hello"; // OK
vector<int> v;         // also OK — but risky
```

**Rule of thumb:** Never put `using namespace` in a header file.  In a `.cpp`
file it's tolerable, but specific `using` declarations are always safer.

### Anonymous Namespaces

An anonymous namespace gives its contents **internal linkage** — the names are
invisible to the linker and can't conflict with identically-named symbols in
other translation units:

```cpp
namespace {
    int helper() { return 42; }  // internal linkage
}
```

This is the modern C++ replacement for `static` at file scope.

### Namespace Aliases

When a fully-qualified name is long, you can create a shorter alias:

```cpp
namespace units = engine::physics::units;
double feet = units::meters_to_feet(1.0);
```

Aliases are scoped — they can be local to a function, so they don't pollute the
enclosing namespace.

### Argument-Dependent Lookup (ADL)

When you call a function with an unqualified name, the compiler searches not
only the current scope but also the namespaces of the argument types.  This is
called **ADL** (or Koenig lookup):

```cpp
namespace geo {
    struct Point { int x, y; };
    void print(const Point& p);  // in namespace geo
}

geo::Point p{1, 2};
print(p);  // finds geo::print via ADL — no geo:: needed
```

ADL is why `std::cout << x` works: `operator<<` is defined in namespace `std`,
and `cout` is a `std` type, so ADL finds it.

### The Two-Step Swap Idiom

The standard pattern for generic swapping is:

```cpp
using std::swap;  // make std::swap available as fallback
swap(a, b);       // unqualified — ADL can find a custom swap
```

If the type of `a` has a custom `swap` in its namespace, ADL finds it.
Otherwise, `std::swap` is used as a fallback.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 01-02

# Build and test a single exercise
./run exercise 01-02-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Wrap in a Namespace

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

The three functions (`add`, `subtract`, `multiply`) live inside `namespace math`.
The test file calls them as `math::add(...)`, `math::subtract(...)`, and
`math::multiply(...)`.  Without the namespace, these generic names could collide
with identically-named functions from other libraries.

### What to do

1. Open `ex01.h` — observe how `namespace math { ... }` wraps the functions.
2. Implement each function body (they're all one-liners).
3. Run: `./run exercise 01-02-ex01`

---

## Exercise 2: Nested Namespaces

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

The functions live inside `namespace engine { namespace physics { namespace units { ... }}}`.
This compiles fine, but C++17 offers a cleaner syntax.

### What to do

1. Convert the verbose nested namespaces to C++17 compact form:
   `namespace engine::physics::units { ... }`
2. Implement the three conversion functions:
   - `meters_to_feet(m)` — multiply by `3.28084`
   - `feet_to_meters(ft)` — divide by `3.28084`
   - `celsius_to_fahrenheit(c)` — `c * 9.0 / 5.0 + 32.0`
3. Run: `./run exercise 01-02-ex02`

---

## Exercise 3: Using Declarations

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

The `containers` namespace provides `make_vector`, `sum`, and `product`.  The
`test_helpers` namespace has wrapper functions that should use these — but
instead of fully-qualifying every call, you'll import specific names with
`using` declarations.

### What to do

1. Inside `build_and_sum()`, add:
   ```cpp
   using containers::make_vector;
   using containers::sum;
   ```
2. Use the imported names to create a vector and return its sum.
3. Do the same in `build_and_product()` with `make_vector` and `product`.
4. Run: `./run exercise 01-02-ex03`

---

## Exercise 4: Fix using-namespace Pollution

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

The header starts with `using namespace std;` — a common antipattern that
dumps thousands of names into the global namespace for every file that
includes this header.

### What to do

1. Remove the `using namespace std;` line.
2. Fix the function signatures by qualifying std types (e.g., `std::string`,
   `std::vector<std::string>`).
3. Implement each function:
   - `repeat_string(s, count)` — concatenate `s` with itself `count` times
   - `join(parts, separator)` — join strings with a separator between them
   - `describe_size(v)` — return `"size: N"` where N is the vector size
     (use `std::to_string`)
4. Run: `./run exercise 01-02-ex04`

---

## Exercise 5: Anonymous Namespace

**Files:** `ex05.h` (read-only) · `ex05_detail.cpp` (edit) · `ex05_test.cpp` (read-only)

Two `.cpp` files each define a `bonus()` helper function that returns a
different value.  Without protection, the linker would see two definitions
of `bonus()` and reject the build.

### What to do

1. In `ex05_detail.cpp`, wrap `bonus()` in `namespace { ... }`.
2. Implement `bonus()` to return `10`.
3. Implement `compute_score_b()` to return `base + bonus()`.
4. Run: `./run exercise 01-02-ex05`

The test file already has its own `bonus()` returning `5` inside its own
anonymous namespace.  Both coexist because anonymous namespaces give
internal linkage.

---

## Exercise 6: Namespace Alias

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

The `engine::physics::units` namespace provides conversion functions.  The
`converter` namespace wraps them, but writing the full path every time is
tedious.

### What to do

1. Inside each `converter` function, create a namespace alias:
   ```cpp
   namespace units = engine::physics::units;
   ```
2. Use the alias to call the appropriate conversion function and return
   its result.
3. Run: `./run exercise 01-02-ex06`

---

## Exercise 7: ADL Basics

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

There are two `describe()` functions: one in the `geometry` namespace (for
`Circle`) and one at global scope (for `int`).  You need to understand
which one gets called in each context.

### What to do

1. Implement `geometry::describe(const Circle& c)` to return
   `"circle(r=<radius>)"` using `std::to_string(c.radius)`.
2. Implement `describe_shape(const geometry::Circle& c)` — just call
   `describe(c)`.  ADL finds `geometry::describe` because `Circle` lives
   in the `geometry` namespace.
3. Implement `describe_number(int n)` — just call `describe(n)`.  No ADL
   here because `int` has no associated namespace; normal lookup finds
   the global `describe`.
4. Run: `./run exercise 01-02-ex07`

---

## Exercise 8: ADL-Friendly Swap

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

This exercise teaches the most important ADL idiom in C++: the two-step
swap.  You'll implement a custom swap for a type and use the standard
pattern to invoke it.

### What to do

1. Implement `Pair::swap(Pair& other)` — swap both `first` and `second`
   with the other pair (use `std::swap` on each field).
2. Implement the free function `container::swap(Pair&, Pair&)` — call
   `a.swap(b)`.
3. Implement `sort_pair(Pair& p)` — if `p.first > p.second`, swap them
   using `std::swap(p.first, p.second)`.
4. Implement `generic_swap_pairs(Pair& a, Pair& b)` using the two-step
   idiom:
   ```cpp
   using std::swap;
   swap(a, b);  // ADL finds container::swap
   ```
5. Run: `./run exercise 01-02-ex08`
