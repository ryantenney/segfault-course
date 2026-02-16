---
title: "Lesson 30: Class Templates"
---

## Why This Lesson Exists

Function templates let you write generic *functions*; class templates let you
write generic *types*.  A `Stack<int>` and a `Stack<std::string>` share the
same source code but are distinct types with distinct compiled code.  Class
templates are the foundation of the entire C++ Standard Library -- `vector`,
`map`, `optional`, `unique_ptr`, and `shared_ptr` are all class templates.

This lesson covers the mechanics of writing, specializing, and using class
templates in practice.

## Key Concepts

### Defining a Class Template

```cpp
template<typename T>
class Stack {
    std::vector<T> data_;
public:
    void push(const T& value) { data_.push_back(value); }
    const T& top() const      { return data_.back(); }
};
```

The compiler generates a new class for each unique `T` that you instantiate.

### Multiple Type Parameters

```cpp
template<typename K, typename V>
class Pair {
    K key_;
    V value_;
public:
    Pair(const K& k, const V& v) : key_(k), value_(v) {}
};
```

### Out-of-Line Member Definitions

You can move member function bodies outside the class, but you must repeat the
template parameter list and qualify the name:

```cpp
template<typename T>
void Stack<T>::push(const T& value) {
    data_.push_back(value);
}
```

These definitions must remain in the header -- the compiler needs to see them
when it instantiates the template.

### CTAD and Deduction Guides (C++17)

Class Template Argument Deduction lets you write `Pair{1, 2}` instead of
`Pair<int, int>{1, 2}`.  When the compiler's default deduction is wrong, you
provide a *deduction guide*:

```cpp
Pair(K, const char*) -> Pair<K, std::string>;
```

### Template Specialization

- **Partial specialization**: customize for a *pattern* of types (e.g., all
  pointers: `Serializer<T*>`).
- **Full specialization**: customize for *one specific type*
  (e.g., `Serializer<std::string>`).

The compiler picks the most specialized match.

### Static Members

Each instantiation of a class template is a distinct class.  If the template
has a static member, each instantiation gets its own copy.

### Dependent Type Names

A name that depends on a template parameter and refers to a type must be
prefixed with `typename`:

```cpp
template<typename T>
typename T::value_type get_first(const T& container);
```

Without `typename`, the compiler assumes the name is a value and produces a
confusing error.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 03-30

# Build and test a single exercise
./run exercise 03-30-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Generic Stack

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

Implement a `Stack<T>` backed by `std::vector<T>`.

### What to do

1. Implement `push()` -- add a value to the top (back of the vector).
2. Implement `pop()` -- remove the top element; throw `std::out_of_range` if
   the stack is empty.
3. Implement `top()` -- return a const reference to the top element; throw
   `std::out_of_range` if empty.
4. Implement `empty()` -- return whether the stack has no elements.
5. Implement `size()` -- return the number of elements.

---

## Exercise 2: Member Functions Out-of-Line

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

Implement a `Queue<T>` with all member functions defined outside the class
body.  The function signatures are already declared inside the class -- you
fill in the out-of-line definitions below it.

### What to do

1. Implement `enqueue()` -- add an element to the back (end of the vector).
2. Implement `dequeue()` -- remove and return the front element; throw
   `std::out_of_range` if empty.
3. Implement `front()` -- return a const reference to the front element;
   throw `std::out_of_range` if empty.
4. Implement `empty()` -- return whether the queue has no elements.
5. Implement `size()` -- return the number of elements.

---

## Exercise 3: Key-Value Pair

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

Implement a `Pair<K, V>` with two type parameters.  Practice defining
comparison operators as non-member (free) function templates.

### What to do

1. Implement `key()` and `value()` accessors.
2. Implement `operator==` -- two pairs are equal if both key and value match.
3. Implement `operator!=` -- the negation of equality.
4. Implement `operator<` -- compare by key first; if keys are equal, compare
   by value.

---

## Exercise 4: CTAD Guide

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

Add a deduction guide so that `Pair{1, "hello"}` deduces
`Pair<int, std::string>` instead of `Pair<int, const char*>`.

### What to do

1. Implement `create_pair()` to create a Pair with explicit types.
2. Add the deduction guide after the class definition:
   `Pair(K, const char*) -> Pair<K, std::string>;`

---

## Exercise 5: Partial Specialization

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

Specialize `Serializer<T>` for all pointer types `T*`.

### What to do

1. Implement the primary template's `serialize()` -- return
   `"value:" + std::to_string(value)`.
2. Write a partial specialization `Serializer<T*>` whose `serialize()`
   returns `"null"` for nullptr or `"ptr:" + std::to_string(*ptr)` otherwise.

---

## Exercise 6: Full Specialization

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Fully specialize `Serializer<std::string>` with custom serialization logic.

### What to do

1. Implement the primary template's `serialize()` and `describe()`.
2. Write `template<> class Serializer<std::string>` with:
   - `serialize()` returning `"str:" + value.substr(0, 10)`
   - `describe()` returning `"string"`

---

## Exercise 7: Static Member Per Instantiation

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Add a static counter to a class template and observe that each instantiation
gets its own independent counter.

### What to do

1. Add a `static int count_` member to the `Counter` class template.
2. Define the static member below the class:
   `template<typename T> int Counter<T>::count_ = 0;`
3. Implement `increment()`, `count()`, and `reset()`.

---

## Exercise 8: Dependent Type Names

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

Practice working with dependent type names -- types nested inside template
parameters like `T::value_type`.  The function signatures are already written
for you using `typename T::value_type` (the `typename` keyword tells the
compiler this is a type, not a value).  Your job is to implement the bodies.

### What to do

1. Implement `get_first()` -- return the first element of a container.
2. Implement `get_size()` -- return the container's size.
3. Implement `get_begin()` -- return a const iterator to the beginning.
4. Implement `find_or_default()` -- search for a target value; return it if
   found, or a default-constructed value if not found.  Use `std::find` from
   `<algorithm>`.
