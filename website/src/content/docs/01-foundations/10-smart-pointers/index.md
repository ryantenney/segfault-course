---
title: "Lesson 10: Smart Pointers"
---

## Why This Lesson Exists

Raw pointers in C++ are a source of bugs: memory leaks from forgotten `delete`,
double-free from deleting the same pointer twice, and dangling pointers from
using memory after it's been freed.  Smart pointers solve all of these problems
by tying the lifetime of heap-allocated objects to the lifetime of a stack
object.  When the smart pointer goes out of scope, cleanup happens
automatically.

C++11 introduced three smart pointer types in `<memory>`:

- **`std::unique_ptr`** -- exclusive ownership, zero overhead
- **`std::shared_ptr`** -- shared ownership via reference counting
- **`std::weak_ptr`** -- non-owning observer of a `shared_ptr`

Modern C++ code should almost never use `new` and `delete` directly.

## Key Concepts

### unique_ptr: Exclusive Ownership

`std::unique_ptr<T>` owns a heap-allocated `T` exclusively.  It cannot be
copied, only moved.  When it goes out of scope (or is reset), it calls
`delete` on the managed pointer.

```cpp
auto w = std::make_unique<Widget>("Bolt");   // preferred creation
std::cout << w->name;                         // use like a raw pointer
// w is automatically deleted at end of scope
```

Use `std::make_unique<T>(args...)` instead of `new T(args...)`.  It's
exception-safe and avoids writing the type twice.

### Moving unique_ptr

Because `unique_ptr` is non-copyable, transferring ownership requires
`std::move`:

```cpp
auto a = std::make_unique<Widget>("X");
auto b = std::move(a);  // a is now null, b owns the widget
```

Functions that consume a `unique_ptr` take it by value:

```cpp
void consume(std::unique_ptr<Widget> w);
consume(std::move(my_widget));  // caller gives up ownership
```

### shared_ptr: Reference Counting

`std::shared_ptr<T>` allows multiple owners.  Internally it maintains a
reference count.  The managed object is destroyed when the last `shared_ptr`
to it is destroyed or reset.

```cpp
auto a = std::make_shared<Connection>("db:5432");
auto b = a;                  // ref count goes from 1 to 2
a.reset();                   // ref count goes from 2 to 1
// b still valid; object destroyed when b goes out of scope
```

`use_count()` returns the current reference count (useful for debugging, not
for production logic).

### The Aliasing Constructor

The aliasing constructor creates a `shared_ptr` that shares ownership with
an existing `shared_ptr` but points to a different object:

```cpp
auto person = std::make_shared<Person>("Alice", address);
std::shared_ptr<Address> addr(person, &person->address);
// addr keeps person alive, but *addr is the Address member
```

This avoids a separate allocation for the sub-object while keeping the parent
alive.

### weak_ptr: Breaking Cycles

If object A has a `shared_ptr` to B, and B has a `shared_ptr` to A, neither
can ever be destroyed -- a reference cycle.  `std::weak_ptr` breaks the cycle
by observing without owning:

```cpp
struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;    // does NOT increase ref count
};
```

To use the observed object, call `lock()`:

```cpp
if (auto p = node->prev.lock()) {
    // p is a valid shared_ptr; the object is still alive
}
```

### Custom Deleters

By default, `unique_ptr` calls `delete`.  You can supply a custom deleter for
resources that need different cleanup (e.g., `free()`, `fclose()`):

```cpp
auto cs = std::unique_ptr<char, decltype(&std::free)>(
    strdup("hello"), std::free
);
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 01-10

# Build and test a single exercise
./run exercise 01-10-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Create a unique_ptr

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Use `std::make_unique` to create a `unique_ptr<Widget>`.  Practice the basic
operations: dereference with `->`, check for null with `operator bool` or
comparison to `nullptr`, and call `reset()` to release the managed object.

### What to do

1. Implement `create_widget` -- return `std::make_unique<Widget>(name)`.
2. Implement `get_widget_name` -- dereference the pointer to access `name`.
3. Implement `is_valid` -- convert the pointer to bool.
4. Implement `reset_widget` -- save the name, call `reset()`, return the name.

---

## Exercise 2: Raw to unique_ptr

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Refactor code that would use raw `new`/`delete` to instead use `make_unique`.
Practice `release()` for interoperating with legacy APIs that expect raw
pointers.

### What to do

1. Implement `create_sensor` -- use `make_unique` to allocate a `Sensor`.
2. Implement `read_sensor` -- return the reading, or `-1.0` if null.
3. Implement `update_reading` -- assign to `sensor->reading`.
4. Implement `release_sensor` -- call `release()` to yield the raw pointer.

---

## Exercise 3: Transfer Ownership

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

`unique_ptr` cannot be copied.  To transfer ownership, you must `std::move` it.
After the move, the source pointer is null.

### What to do

1. Implement `make_gadget` -- return a `unique_ptr<Gadget>`.
2. Implement `consume_gadget` -- the parameter is taken by value, so the caller
   must `std::move` it in.  Return the label.
3. Implement `transfer_gadget` -- move from `source` to `dest`.

---

## Exercise 4: unique_ptr in Containers

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

`std::vector` can hold `unique_ptr` elements.  You must `std::move` them when
inserting.  This pattern is common for collections of polymorphic objects.

### What to do

1. Implement `make_parts` -- loop over codes, `push_back` a `make_unique<Part>`
   for each.
2. Implement `count_parts` -- count non-null elements.
3. Implement `pop_part` -- move the last element out, then `pop_back`.
4. Implement `merge_parts` -- move each element from source to dest, then clear
   source.

---

## Exercise 5: Shared Ownership

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

`shared_ptr` uses reference counting to support multiple owners of the same
object.  Copying a `shared_ptr` increments the count; destroying or resetting
one decrements it.

### What to do

1. Implement `open_connection` -- use `make_shared`.
2. Implement `get_ref_count` -- return `conn.use_count()`.
3. Implement `share_connection` -- return a copy of the `shared_ptr`.
4. Implement `close_and_report` -- reset `conn`, then return
   `observer.use_count()`.

---

## Exercise 6: shared_ptr Aliasing

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

The aliasing constructor creates a `shared_ptr` that shares ownership with
one object but points to a member of that object.  This lets you hand out
a `shared_ptr<Member>` without a separate heap allocation for the member.

### What to do

1. Implement `make_person` -- use `make_shared<Person>` and initialize the
   fields.
2. Implement `get_address_ptr` -- use the aliasing constructor:
   `std::shared_ptr<Address>(person, &person->address)`.
3. Implement `get_name_ptr` -- same pattern, aliasing the `name` member.

---

## Exercise 7: Break a Cycle with weak_ptr

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Two nodes with `shared_ptr` links to each other create a reference cycle --
neither can be destroyed.  Change one link to `weak_ptr` to break the cycle.

### What to do

1. Change `Node::prev` from `std::shared_ptr<Node>` to `std::weak_ptr<Node>`.
2. Implement `make_node` -- use `make_shared<Node>`.
3. Implement `link_nodes` -- set `a->next = b` and `b->prev = a`.
4. Implement `get_prev_name` -- call `prev.lock()`.  If the result is non-null,
   return its name; otherwise return `"expired"`.

---

## Exercise 8: Custom Deleter

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

Sometimes cleanup means something other than `delete`.  A custom deleter lets
you wrap C-style resources (malloc/free, FILE*, etc.) in a `unique_ptr`.

### What to do

1. Implement `make_c_string` -- use `std::malloc` + `std::strcpy` to create a
   copy of the text, then wrap it in a `unique_ptr` with `std::free` as the
   deleter.
2. Implement `create_resource` -- use `new Resource{id}` wrapped in a
   `unique_ptr` with `destroy_resource` as the deleter.
3. Implement `make_int_array` -- use `new int[size]` with a lambda deleter
   that calls `delete[]` and increments `deleter_call_count()`.
