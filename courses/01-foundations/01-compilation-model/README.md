# Lesson 01: The C++ Compilation Model

## Why This Lesson Exists

If you're coming from Java, Rust, Go, or most other modern languages, the C++
compilation model will feel alien.  Those languages have modules or packages
where the compiler understands the project structure.  C++ (before C++20
modules) has **textual inclusion**: `#include` literally copy-pastes one file
into another before the compiler even sees it.

Everything in this lesson follows from that single fact.

## Key Concepts

### Translation Units

A **translation unit** (TU) is one `.cpp` file after all `#include` directives
have been expanded.  The compiler processes each TU independently, producing an
object file (`.o`).  The **linker** then combines all object files into the
final executable.

```
  ex04_test.cpp  ──compile──▶  ex04_test.o  ─┐
                                              ├──link──▶  01-01-ex04
  ex04.cpp       ──compile──▶  ex04.o       ─┘
```

### Declarations vs Definitions

A **declaration** tells the compiler that something exists and what its type is:

```cpp
int add(int a, int b);        // function declaration
extern int counter;            // variable declaration
class Car;                     // forward declaration (incomplete type)
```

A **definition** provides the actual implementation or storage:

```cpp
int add(int a, int b) {       // function definition
    return a + b;
}
int counter = 0;               // variable definition
class Car { ... };             // class definition
```

### The One Definition Rule (ODR)

The ODR says:
1. Within a single TU, no entity may be defined more than once.
2. Across the entire program, each non-inline function and each non-inline
   variable must be defined in **exactly one** TU.
3. **Inline** functions and variables may be defined in multiple TUs, but all
   definitions must be identical.

Most linker errors in C++ trace back to ODR violations.

### Include Guards

Because `#include` is textual copy-paste, including the same header twice in
one TU can cause redefinition errors.  **Include guards** prevent this:

```cpp
#ifndef MY_HEADER_H       // If not already included...
#define MY_HEADER_H        // ...mark as included...

struct MyStruct { ... };   // ...provide the definitions...

#endif                     // ...done.
```

The modern shorthand is `#pragma once` — one line, same effect.

### Internal vs External Linkage

By default, functions and variables at namespace scope have **external linkage**
— they are visible to other translation units.  This is how `ex04_test.cpp` can
call a function defined in `ex04.cpp`.

Sometimes you want a helper function that's private to one TU.  You can give it
**internal linkage** using either:

- **`static`** — the traditional C approach
- **Anonymous namespace** `namespace { ... }` — the idiomatic C++ approach

Both make the name invisible to the linker, so identically-named helpers in
different TUs don't conflict.

### `inline` Functions

Marking a function `inline` tells the compiler and linker: "this function may
appear in multiple TUs, and all copies are identical — keep just one."  This is
what makes it safe to put function bodies in header files.

### `extern` Variables

`extern` on a variable declaration says: "this variable exists, but its storage
is allocated elsewhere."  The actual definition (with initial value) goes in
exactly one `.cpp` file.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 01-01

# Build and test a single exercise
./run exercise 01-01-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Include Guards

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

When the preprocessor encounters `#include "ex01.h"`, it pastes the entire
contents of `ex01.h` into the current file.  If something causes the header to
be included a second time in the same TU, every `struct`, `class`, and non-inline
function definition appears twice — and the compiler rejects the duplicates.

**Include guards** prevent this.  They wrap the header contents in a
preprocessor conditional:

```cpp
#ifndef EX01_H          // first time: not defined, so we enter the block
#define EX01_H          // define the macro so next time the #ifndef is false

struct Point { int x, y; };

#endif                  // second time: EX01_H is defined, entire block is skipped
```

The macro name (`EX01_H`) is arbitrary, but conventionally matches the filename
in all-caps with underscores.

### What to do

1. Open `ex01.h`.
2. Wrap the entire file contents in `#ifndef EX01_H` / `#define EX01_H` /
   `#endif`.
3. Implement `add()` and `distance_squared()`.
4. Run: `./run exercise 01-01-ex01`

### What the test checks

The test includes `ex01.h` twice.  The second `#include` is guarded by
`#ifdef EX01_H` — so it only activates once you've added your guards.  This
proves the header survives double inclusion.

---

## Exercise 2: Pragma Once

**Files:** `ex02_point.h` · `ex02_color.h` · `ex02.h` (all edit) · `ex02_test.cpp` (read-only)

`#pragma once` is a compiler directive that does the same job as include guards:
it tells the preprocessor "only include this file once per translation unit."
It's not part of the C++ standard, but every major compiler supports it, and
it's simpler than the `#ifndef`/`#define`/`#endif` dance.

```cpp
#pragma once            // one line — that's it

struct Point2D { double x, y; };
```

### When to use which

| Feature | Include guards | `#pragma once` |
|---------|---------------|----------------|
| Standard? | Yes (preprocessor) | No (de facto universal) |
| Boilerplate | 3 lines | 1 line |
| Risk of name collision | Yes (two headers with same macro) | No |
| Works with symlinks/copies | Yes | Sometimes not |

Most modern codebases use `#pragma once` by default.

### What to do

1. Add `#pragma once` to the top of `ex02_point.h`, `ex02_color.h`, and `ex02.h`.
2. Implement `point_distance_sq()` and `make_color()`.
3. Run: `./run exercise 01-01-ex02`

---

## Exercise 3: Forward Declarations

**Files:** `ex03_engine.h` (edit) · `ex03_car.h` · `ex03.h` · `ex03_test.cpp` (read-only)

A **forward declaration** tells the compiler "this type exists" without
providing its full definition:

```cpp
class Car;   // forward declaration — Car is an incomplete type
```

An incomplete type is enough for:
- Declaring pointers (`Car*`) or references (`Car&`)
- Function parameters and return types that are pointers/references

An incomplete type is **not** enough for:
- Creating an object (`Car c;`)
- Accessing members (`car.name()`)
- Calling `sizeof(Car)`

### Why bother?

Every `#include` is a transitive dependency.  If `engine.h` includes `car.h`,
then every file that includes `engine.h` also pulls in `car.h`.  In a large
project, this cascading inclusion slows compilation and creates coupling.

If `Engine` only stores a `Car*`, a forward declaration breaks that dependency
chain.

### What to do

1. In `ex03_engine.h`, replace `#include "ex03_car.h"` with `class Car;`.
2. Implement `is_installed()` — return whether `car_` is non-null.
3. Run: `./run exercise 01-01-ex03`

The test file includes both `ex03_car.h` and `ex03_engine.h` (via `ex03.h`),
so it has access to both full definitions.

---

## Exercise 4: Header / Source Split

**Files:** `ex04.h` · `ex04.cpp` (both edit) · `ex04_test.cpp` (read-only)

In C++ the standard pattern is:

- **Header (`.h`):** Declarations — the function's name, parameters, and return
  type.  This is the *interface*.
- **Source (`.cpp`):** Definitions — the function's body.  This is the
  *implementation*.

Each `.cpp` file compiles to one object file.  The linker resolves calls across
TUs by matching function names from declarations to their single definition.

If you put a non-inline function *body* in a header, every `.cpp` that includes
it gets its own copy of the definition.  The linker sees multiple definitions of
the same function → **ODR violation** → linker error.

### What to do

Currently `ex04.h` defines `multiply_add()` as an `inline` function.

1. In `ex04.h`, remove the `inline` keyword and the function body.  Leave only
   the declaration: `int multiply_add(int a, int b, int c);`
2. In `ex04.cpp`, implement the function: `return a * b + c;`
3. Run: `./run exercise 01-01-ex04`

Both `ex04_test.cpp` and `ex04.cpp` include `ex04.h`.  After your split, the
header only has a declaration, so both TUs compile without conflict.

---

## Exercise 5: Inline Functions

**Files:** `ex05.h` (edit) · `ex05_helper.cpp` (edit) · `ex05_test.cpp` (read-only)

The `inline` keyword is widely misunderstood.  Its primary purpose in modern
C++ is **not** "please inline this function call" — the compiler will inline
(or not) regardless.  What `inline` actually means:

> "This function may be defined in multiple translation units.  All definitions
> are identical.  Linker, pick any one and discard the rest."

This is what makes it legal to define a function body directly in a header file.
Without `inline`, two TUs including the same header each get a definition → ODR
violation.

### What to do

1. In `ex05.h`, add the `inline` keyword to both `square()` and `cube()`.
2. Implement `cube()` — return `x * x * x`.
3. In `ex05_helper.cpp`, uncomment `#include "ex05.h"` and implement
   `compute_volume()` using `cube()`.
4. Run: `./run exercise 01-01-ex05`

Notice that `square()` already works before you add `inline` — because only one
TU currently includes the header.  Adding `inline` is what unlocks the second
TU (`ex05_helper.cpp`).

---

## Exercise 6: Extern Variables

**Files:** `ex06.h` · `ex06.cpp` (both edit) · `ex06_test.cpp` (read-only)

Variables follow the same rules as functions.  A variable *definition* at
namespace scope allocates storage.  Put it in a header, and every TU that
includes the header gets its own copy → linker error.

`extern` converts a definition into a *declaration*:

```cpp
// header — declaration only (no storage allocated)
extern int max_connections;

// one .cpp file — the single definition
int max_connections = 100;
```

### What to do

1. In `ex06.h`, change each variable to an `extern` declaration (remove the
   `= value` initializer).
2. In `ex06.cpp`, include `ex06.h` and define each variable with its value:
   - `max_connections = 100`
   - `pi = 3.14159265358979`
   - `app_name = "SegfaultCourse"`
3. Implement `init_config()` — it can be an empty function body since the
   variables are initialized at their definitions.
4. Run: `./run exercise 01-01-ex06`

### Note

In C++17 you can also use `inline` on variables (`inline int x = 42;`), which
works like `inline` on functions — multiple identical definitions are OK.  But
for mutable global state, `extern` + one definition is the traditional and more
explicit pattern.

---

## Exercise 7: Anonymous Namespaces

**Files:** `ex07_a.cpp` · `ex07_b.cpp` (both edit) · `ex07.h` · `ex07_test.cpp` (read-only)

When two `.cpp` files define a function with the same name at namespace scope,
the linker sees two definitions → ODR violation.  But sometimes you *want* a
small helper function that's local to one file.

An **anonymous namespace** gives everything inside it **internal linkage**:

```cpp
namespace {
    int helper() { return 42; }  // only visible in this TU
}
```

This is the modern C++ equivalent of `static` at file scope:

```cpp
static int helper() { return 42; }  // same effect, C-style
```

Both work.  The anonymous namespace is preferred in C++ because it also works
for types, templates, and variables — not just functions.

### What to do

Both `ex07_a.cpp` and `ex07_b.cpp` define a function called `detail()` inside
an anonymous namespace.  They return different values.

1. In `ex07_a.cpp`, implement `detail()` to return `42`.
2. In `ex07_b.cpp`, implement `detail()` to return `7`.
3. Run: `./run exercise 01-01-ex07`

The test verifies that `compute_a()` (which calls `ex07_a.cpp`'s `detail()`)
and `compute_b()` (which calls `ex07_b.cpp`'s `detail()`) produce different
results — proving the two `detail()` functions are truly separate.

---

## Exercise 8: Multi-TU Build (Capstone)

**Files:** `ex08_math.cpp` · `ex08_format.cpp` (both edit) · `ex08_math.h` · `ex08_format.h` · `ex08_test.cpp` (read-only)

This exercise ties together everything from the lesson.  You have two modules —
math utilities and formatting — each split across a header and a source file.

The include graph looks like this:

```
  ex08_test.cpp  ──▶  ex08_format.h  ──▶  ex08_math.h
  ex08_format.cpp ──▶  ex08_format.h  ──▶  ex08_math.h
  ex08_math.cpp  ──▶  ex08_math.h
```

`ex08_math.h` gets included three times (once per TU), but `#pragma once`
ensures it's processed at most once per TU.  Each function is *declared* in a
header and *defined* in exactly one `.cpp` file — no ODR violations.

### What to do

Implement the functions in `ex08_math.cpp` and `ex08_format.cpp`:

**Math (`ex08_math.cpp`):**
- `abs_val(x)` — return the absolute value of `x`
- `max_val(a, b)` — return the larger of `a` and `b`
- `clamp_val(a, lo, hi)` — return `a` clamped to the range `[lo, hi]`

**Format (`ex08_format.cpp`):**
- `format_signed(value)` — return `"+5"`, `"-3"`, or `"+0"` (always include a sign)
- `format_range(a, b, min, max)` — clamp both values to `[min, max]`, sort
  them, and return `"lo..hi"`

The format functions can use the math functions — that's why `ex08_format.h`
includes `ex08_math.h`.

Run: `./run exercise 01-01-ex08`
