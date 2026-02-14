# Lesson 11: Move Semantics

## Why This Lesson Exists

Before C++11, every time you passed an object around -- inserting into a
container, returning from a function, assigning to a variable -- the compiler
made a full copy.  For objects managing heap memory (strings, vectors, buffers),
that means allocating new memory and copying bytes, only to immediately destroy
the original.

Move semantics fix this.  When the compiler knows an object is about to be
destroyed (a temporary, or an object you've explicitly `std::move`'d), it can
*steal* the resources instead of copying them.  A move typically reduces to a
few pointer swaps -- constant time instead of linear.

## Key Concepts

### Lvalues and Rvalues

An **lvalue** has a name and persists beyond a single expression:

```cpp
std::string name = "Alice";  // name is an lvalue
```

An **rvalue** is a temporary with no lasting identity:

```cpp
std::string("Alice")         // temporary, rvalue
name + " Smith"              // result is a temporary, rvalue
```

`std::move(x)` casts an lvalue to an rvalue reference, telling the compiler:
"I'm done with `x`, you may steal its resources."

### Move Constructor and Move Assignment

A **move constructor** takes an rvalue reference and transfers resources:

```cpp
Buffer(Buffer&& other) noexcept
    : data_(std::move(other.data_)),
      size_(other.size_) {
    other.size_ = 0;
}
```

A **move assignment operator** does the same for an existing object:

```cpp
Buffer& operator=(Buffer&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        size_ = other.size_;
        other.size_ = 0;
    }
    return *this;
}
```

Both should be marked `noexcept`.  Standard library containers check for
`noexcept` move operations before choosing move over copy during reallocation.

### The Moved-From State

After a move, the source object is in a **valid but unspecified** state.  You
can:
- Destroy it (the destructor always runs)
- Assign a new value to it
- Call operations that don't depend on value (like `size()`, `empty()`, `clear()`)

You should NOT assume the moved-from object is empty or unchanged.

### Move-Only Types

A class that deletes its copy constructor and copy assignment operator but
provides move operations is called **move-only**.  Examples:

- `std::unique_ptr` -- exclusive ownership of a heap object
- `std::thread` -- ownership of a running thread
- `std::fstream` -- ownership of a file handle

Move-only types can be stored in standard containers.

### Return Value Optimization (RVO)

The compiler can eliminate copies/moves when returning objects:

- **Guaranteed RVO** (C++17): returning a prvalue (`return Widget{args}`)
  constructs directly in the caller's storage.  Zero copies, zero moves.
- **NRVO** (Named RVO): returning a named local variable.  Not guaranteed by
  the standard, but applied by all major compilers.

Do **not** write `return std::move(local)` -- this inhibits NRVO and forces a
move.  Just write `return local`.

### std::move (the algorithm)

`<algorithm>` provides `std::move(first, last, dest)`, which is like
`std::copy` but applies `std::move` to each element.  It's useful for
bulk-transferring elements between containers.

```cpp
std::vector<std::string> src = {"a", "b", "c"};
std::vector<std::string> dst(3);
std::move(src.begin(), src.end(), dst.begin());
// src elements are now in a moved-from state
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 01-11

# Build and test a single exercise
./run exercise 01-11-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Move a String into a Container

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Practice the difference between `push_back(item)` (copies) and
`push_back(std::move(item))` (moves).  A `TrackedString` class logs whether
copies or moves occur so the tests can verify your implementation.

### What to do

1. Implement `add_by_copy` -- call `vec.push_back(item)` (copy).
2. Implement `add_by_move` -- call `vec.push_back(std::move(item))` (move).
3. Implement `build_collection` -- create TrackedStrings from the inputs and
   move each into a result vector.

---

## Exercise 2: Move a Local into a Return Value

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

When building a struct from local variables, `std::move` avoids copying strings
into struct fields.

### What to do

1. Implement `make_config` -- initialize a `Config` struct, moving `host` and
   `path` into the fields.
2. Implement `compose_message` -- build a body string locally, then move it
   into a `Message`.
3. Implement `build_messages` -- compose messages from parallel vectors.

---

## Exercise 3: Write a Move Constructor

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

`Buffer` owns a `unique_ptr<int[]>`.  Because `unique_ptr` is non-copyable,
`Buffer` needs a move constructor to transfer ownership.

### What to do

1. Implement the move constructor body.
2. Move `other.data_` into `data_` using `std::move`.
3. Copy `other.size_` into `size_`, then set `other.size_ = 0`.

---

## Exercise 4: Move Assignment Operator

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Move assignment is like the move constructor, but the destination already
exists and may own resources.  Guard against self-assignment.

### What to do

1. Check `if (this != &other)`.
2. Move `other.items_` into `items_`.
3. Copy `other.capacity_` into `capacity_`, then zero out `other.capacity_`.
4. Return `*this`.

---

## Exercise 5: Moved-From State

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Explore what you can and cannot do with a moved-from object.  All standard
library types guarantee the moved-from state is valid for destruction and
assignment.

### What to do

1. Implement `move_and_check_empty` -- move the source, then check `empty()`.
2. Implement `move_and_reassign` -- move the source, then assign a new value.
3. Implement `drain_vector` -- move the vector, then `clear()` the source.
4. Implement `move_and_get_size` -- move the source, then return its `size()`.

---

## Exercise 6: Move-Only Type

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Create a class that deletes copy operations and provides move operations.
Then store instances in a `std::vector` to prove they work with containers.

### What to do

1. Implement the move constructor -- transfer all fields, mark source invalid.
2. Implement move assignment -- guard self-assignment, transfer, invalidate.
3. Implement `make_handles` -- create `count` handles with ids 0 through
   count-1, using `emplace_back` or `push_back` with `std::move`.

---

## Exercise 7: Return Value Optimization

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Observe when the compiler elides copies and moves, and when it cannot.  The
`Tracker` class counts copies and moves so the tests can verify.

### What to do

1. Implement `make_tracker` -- return `Tracker{label}` (prvalue, guaranteed RVO).
2. Implement `make_named_tracker` -- create a local and return it (NRVO).
3. Implement `passthrough_tracker` -- return the parameter `t` (no RVO, implicit
   move).
4. Implement `move_tracker_bad` -- create a local and return `std::move(local)`
   (inhibits NRVO).

---

## Exercise 8: Move in Algorithms

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

Use `std::move` from `<algorithm>` to bulk-transfer elements between
containers.  This is different from `std::move` in `<utility>` -- the
algorithm version takes iterators.

### What to do

1. Implement `bulk_move` -- use `std::move(src.begin(), src.end(), dst.begin())`
   to transfer all elements.
2. Implement `extract_range` -- create a destination vector of the right size,
   then use `std::move` on the sub-range.
3. Implement `partition_by_length` -- iterate over source, moving each string
   into the appropriate bucket based on its length.
