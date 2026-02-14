# Lesson 08: C++ Casts

## Why This Lesson Exists

C inherited a single, all-powerful cast syntax: `(Type)expr`. C++ kept that
syntax for backward compatibility, but it is dangerously permissive. A C-style
cast will silently perform whichever conversion happens to compile — numeric
conversion, pointer reinterpretation, const removal, or even a combination — and
you have no way to know which one the compiler chose just by reading the code.

C++ introduced four named casts that make your intent explicit, searchable, and
individually restrictable. Using them is a non-negotiable best practice in modern
C++.

## Key Concepts

### The Four C++ Casts

| Cast | Purpose | Checked |
|------|---------|---------|
| `static_cast<T>` | Numeric conversions, enum↔int, upcasts, known-safe downcasts | Compile-time |
| `dynamic_cast<T>` | Safe downcasts in polymorphic hierarchies (requires virtual) | Runtime (RTTI) |
| `const_cast<T>` | Add or remove `const` / `volatile` qualifiers | Compile-time |
| `reinterpret_cast<T>` | Bit-level reinterpretation of pointers/integers | None — trust the programmer |

### static_cast

The most common cast. Use it for:

```cpp
double d = 3.14;
int i = static_cast<int>(d);          // truncates to 3

enum class Color { Red, Green, Blue };
int c = static_cast<int>(Color::Green); // 1
```

Also used for explicit upcasts (Derived* to Base*), though those are implicit in
most contexts.

### dynamic_cast

The only cast that checks at runtime. It uses RTTI (Run-Time Type Information)
to verify that a base pointer/reference actually points to the target derived
type.

```cpp
Base* b = get_some_object();

// Pointer form: returns nullptr on failure
if (auto* d = dynamic_cast<Derived*>(b)) {
    d->derived_method();
}

// Reference form: throws std::bad_cast on failure
try {
    auto& d = dynamic_cast<Derived&>(*b);
    d.derived_method();
} catch (const std::bad_cast&) {
    // not a Derived
}
```

**Requirements:** The base class must have at least one virtual function
(typically a virtual destructor).

### const_cast

Exclusively for adding or removing `const`. The primary legitimate use case is
interfacing with C APIs that lack const-correctness:

```cpp
void legacy_print(char* str);  // doesn't modify str, but missing const

void modern_print(const char* str) {
    legacy_print(const_cast<char*>(str));
}
```

**Warning:** Using `const_cast` to modify an object that was originally declared
`const` is undefined behavior.

### reinterpret_cast

The most dangerous cast. It performs no conversion — just reinterprets the bit
pattern. Common uses include pointer-to-integer round-trips and interfacing with
hardware registers.

```cpp
int* p = &some_int;
std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(p);
```

### When in Doubt

If you need a cast, work through this decision tree:

1. **Numeric conversion?** → `static_cast`
2. **Downcast in polymorphic hierarchy?** → `dynamic_cast`
3. **Remove/add const?** → `const_cast`
4. **Pointer/integer bit reinterpretation?** → `reinterpret_cast`
5. **None of the above fit?** → Redesign the code to avoid the cast

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 01-08

# Build and test a single exercise
./run exercise 01-08-ex01
```

---

## Exercise 1: Replace C-Style Casts

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

C-style casts like `(int)value` or `(double)x` are inherited from C. They are
dangerous because they silently pick whichever cast happens to work — you can't
tell from the syntax whether it's performing a numeric conversion or a pointer
reinterpretation.

### What to do

1. Open `ex01.h`.
2. Replace each `TODO()` with the appropriate C++ named cast.
3. `double_to_int` and `int_to_double` → `static_cast`
4. `ptr_to_int` and `int_to_ptr` → `reinterpret_cast`
5. Run: `./run exercise 01-08-ex01`

---

## Exercise 2: Numeric Casts

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

`static_cast` is the workhorse for numeric conversions. It handles int↔double,
int↔enum, and intentional narrowing. Using it makes every conversion deliberate
and visible in code review.

### What to do

1. Open `ex02.h`.
2. Implement each function using `static_cast`.
3. For `safe_divide`, cast the numerator to `double` before dividing.
4. For `color_to_int` and `int_to_color`, use `static_cast` to convert between
   `Color` and `int`.
5. Run: `./run exercise 01-08-ex02`

---

## Exercise 3: Safe Downcasting (Pointer)

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

When you have a `Base*` and need to determine whether it's actually a `Derived*`,
`dynamic_cast` is the safe choice. The pointer form returns `nullptr` if the cast
fails, which you can check with an `if` statement.

### What to do

1. Open `ex03.h`.
2. In `try_get_circle_area`, use `dynamic_cast<Circle*>` on the shape pointer.
   If it succeeds, return the circle's area. If it returns null, return -1.0.
3. Do the same for `try_get_rectangle_area` with `Rectangle*`.
4. Run: `./run exercise 01-08-ex03`

### Key pattern

```cpp
if (auto* derived = dynamic_cast<Derived*>(base_ptr)) {
    // cast succeeded — use derived
} else {
    // base_ptr doesn't point to a Derived
}
```

---

## Exercise 4: Safe Downcasting (Reference)

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

When you use `dynamic_cast` with a reference instead of a pointer, failure
throws `std::bad_cast` instead of returning null. A reference cannot be null,
so an exception is the only way to signal failure.

### What to do

1. Open `ex04.h`.
2. In `try_dog_speak`, attempt `dynamic_cast<Dog&>(animal)` inside a try block.
   If it succeeds, return `dog.speak()`. Catch `std::bad_cast` and return
   `"unknown"`.
3. Do the same for `try_cat_speak` with `Cat&`.
4. Run: `./run exercise 01-08-ex04`

### Key pattern

```cpp
try {
    auto& derived = dynamic_cast<Derived&>(base_ref);
    return derived.method();
} catch (const std::bad_cast&) {
    return fallback;
}
```

---

## Exercise 5: const_cast for Legacy APIs

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Real-world code often interfaces with C libraries that lack const-correctness.
`const_cast` exists specifically for this situation: when a function takes
non-const but promises not to modify the data.

### What to do

1. Open `ex05.h`.
2. In `safe_strlen`, use `const_cast<char*>` to call `legacy_strlen`.
3. In `safe_copy`, use `const_cast<char*>` on the source to call `legacy_copy`.
4. In `to_string`, use the string constructor on the const pointer.
5. Run: `./run exercise 01-08-ex05`

### Warning

Never use `const_cast` to modify data that was declared `const`. That is
undefined behavior. `const_cast` should only be used when you know the target
function won't actually modify the data.

---

## Exercise 6: Cast in a Class Hierarchy

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Upcasts (Derived* to Base*) are always safe and don't strictly need a cast —
they happen implicitly. But using `static_cast` makes the conversion explicit.

Downcasts (Base* to Derived*) are where the choice matters:
- `static_cast`: No runtime check. You're asserting "I know this is a Derived."
- `dynamic_cast`: Runtime check. Safe but requires virtual functions.

### What to do

1. Open `ex06.h`.
2. In `car_to_vehicle`, use `static_cast<Vehicle*>`.
3. In `vehicle_to_car`, use `dynamic_cast<Car*>`.
4. In `get_doors` and `get_payload`, use `dynamic_cast` and check for null.
5. Run: `./run exercise 01-08-ex06`

---

## Exercise 7: Eliminate a Cast

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

The best cast is no cast. A `void*` container (the C way) forces casts on every
access. A C++ class template provides the same generality with full type safety
and zero casts.

### What to do

1. Open `ex07.h`.
2. Add a `T value_` member to the `Container` template.
3. Implement `store()` to save the value and `retrieve()` to return it.
4. Implement `store_and_get_int` and `store_and_get_string` using your
   type-safe Container — no casts anywhere.
5. Run: `./run exercise 01-08-ex07`

### Design lesson

If you find yourself reaching for a cast, consider whether better type design
would eliminate the need entirely. Templates, virtual functions, and
`std::variant` are usually better than `void*` + casts.

---

## Exercise 8: Identify the Right Cast

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

This capstone exercise presents four scenarios, each requiring a different cast.
You need to pick the right one for each situation.

### What to do

1. Open `ex08.h`.
2. `int_to_float`: numeric conversion → `static_cast<float>`
3. `call_legacy_read`: const removal → `const_cast<char*>`
4. `smart_print`: runtime type check → `dynamic_cast<Label*>`
5. `round_trip_pointer`: pointer-to-integer → `reinterpret_cast`
6. Run: `./run exercise 01-08-ex08`
