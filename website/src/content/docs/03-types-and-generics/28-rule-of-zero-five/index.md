---
title: "Lesson 28: Rule of Zero / Five"
---

## Why This Lesson Exists

When a C++ class manages resources -- heap memory, file handles, network
connections -- the compiler-generated copy and move operations do the wrong
thing.  A shallow copy duplicates the pointer, leaving two objects fighting over
the same resource.  One destructs and frees the memory; the other now owns a
dangling pointer.

C++ has two strategies for handling this correctly:

1. **Rule of Five:** If you need a custom destructor, you almost certainly need
   custom copy constructor, copy assignment, move constructor, and move
   assignment.  Implement all five.

2. **Rule of Zero:** Design your class so that all members are well-behaved
   types (string, vector, unique_ptr, shared_ptr) that handle their own
   resources.  Then the compiler-generated special members do the right thing
   automatically, and you don't write any of them.

Rule of Zero is the preferred default.  Rule of Five is for the rare cases
where you're wrapping a raw C resource or building a low-level container.

## Key Concepts

### The Special Members

C++ has six special member functions.  The compiler can generate default
versions of all of them:

| Member | Signature |
|--------|-----------|
| Default constructor | `T()` |
| Destructor | `~T()` |
| Copy constructor | `T(const T&)` |
| Copy assignment | `T& operator=(const T&)` |
| Move constructor | `T(T&&)` |
| Move assignment | `T& operator=(T&&)` |

### Rule of Three (C++98)

If you define any of: destructor, copy constructor, copy assignment -- define
all three.  A custom destructor means the class manages a resource, so the
default (shallow) copy is wrong.

### Rule of Five (C++11)

C++11 added move semantics.  The Rule of Three becomes the Rule of Five: if you
define any special member, define or explicitly default/delete all five (plus
destructor).

### Rule of Zero

The best option: don't define any special members.  Use member types that
already handle resources correctly.  The compiler generates correct copy, move,
and destruction for free.

### = delete

Declaring a special member as `= delete` explicitly forbids that operation:

```cpp
class NonCopyable {
public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};
```

### = default

Declaring a special member as `= default` explicitly requests the
compiler-generated implementation:

```cpp
class Widget {
public:
    Widget(const Widget&) = default;
    Widget& operator=(const Widget&) = default;
    ~Widget() = default;
};
```

### Copy-and-Swap Idiom

A technique for writing exception-safe copy assignment:

1. Take the parameter **by value** (invokes the copy constructor).
2. Swap the copy with `*this`.
3. The old data in the temporary is destroyed when it goes out of scope.

This handles self-assignment automatically and provides the strong exception
guarantee.

### Move-Only Types

A class that deletes copy operations but provides move operations.  This
models exclusive ownership -- exactly one object owns the resource at a time.
Standard library examples: `unique_ptr`, `thread`, `fstream`.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 03-28

# Build and test a single exercise
./run exercise 03-28-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Spot the Bug (Rule of Three Violation)

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

The `IntArray` class has a destructor that frees memory but no copy constructor
or copy assignment.  This means copying an IntArray creates a shallow copy that
shares the same pointer -- leading to double-free on destruction.

### What to do

1. Implement the copy constructor: allocate new memory and copy elements from
   `other`.
2. Implement the copy assignment operator: handle self-assignment, free old
   memory, allocate new memory, and copy elements. Return `*this`.

---

## Exercise 2: Rule of Zero

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Refactor `ManagedArray` to use `std::vector<int>` instead of raw memory
management.  With a vector member, the compiler-generated copy, move, and
destructor all do the right thing automatically.

### What to do

1. Add a `std::vector<int>` member.
2. Implement the constructor to create a vector of the given size (zero-init).
3. Implement `operator[]`, `size()`, and `data()` by delegating to the vector.
4. Do NOT add any destructor, copy, or move operations.

---

## Exercise 3: Deleted Copy

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Some resources cannot be meaningfully duplicated.  For these types, explicitly
delete the copy operations to prevent accidental copying.

### What to do

1. Delete the copy constructor: `UniqueResource(const UniqueResource&) = delete;`
2. Delete the copy assignment: `UniqueResource& operator=(const UniqueResource&) = delete;`
3. Implement the constructor and `is_open()`.

---

## Exercise 4: The = default Keyword

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Use `= default` to explicitly request compiler-generated special members.
This documents that the default behavior is intentional, not accidental.

### What to do

1. Implement the constructor to initialize all three members.
2. Default all five special members using `= default`.

---

## Exercise 5: Rule of Five

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

`DynamicBuffer` wraps a raw `int*` array.  The destructor is provided.
Implement the other four special members.

### What to do

1. Copy constructor: allocate new array, copy elements from `other`.
2. Move constructor: steal pointer and size, set other to null/zero.
3. Copy assignment: handle self-assignment, free old memory, allocate new, copy.
4. Move assignment: handle self-assignment, free old memory, steal from other.
5. Add `noexcept` to the move operations after they are working.

---

## Exercise 6: Copy-and-Swap Idiom

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Implement copy assignment using the copy-and-swap idiom for strong exception
safety.

### What to do

1. Implement `swap()`: exchange `data_` and `size_` between `*this` and `other`.
2. Implement the copy constructor: allocate and copy elements.
3. Implement the move constructor: steal pointer and size, null the source.
4. Implement the copy assignment operator: the parameter is taken by value,
   so just `swap(*this, other)` and return `*this`.
5. Add `noexcept` to swap and move operations after they are working.

---

## Exercise 7: Move-Only Type

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Build `UniqueHandle`, a move-only type. The copy operations are already deleted.
Implement the move constructor and move assignment to transfer ownership.

### What to do

1. Implement the move constructor: copy all fields, mark source as invalid.
2. Implement the move assignment: transfer all fields, mark source as invalid,
   return `*this`.
3. Implement `make_handles`: create `count` handles with ids 0 through count-1,
   each labeled "handle-N". Use `emplace_back` or `push_back(std::move(...))`.
4. Add `noexcept` to the move operations after they are working.

---

## Exercise 8: Rule of Zero with Composition

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

`Document` is composed entirely of `std::string` and `std::vector` members.
These types handle their own resources, so the compiler generates correct
copy, move, and destruction automatically.

### What to do

1. Implement the constructor: initialize `title_` and `author_`.
2. Implement `add_section`: push a `Section` onto the vector.
3. Implement `section_count` and `get_section`.
4. Do NOT add any special members -- the defaults are correct.
