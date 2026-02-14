# Lesson 27: Inheritance and Polymorphism

## Why This Lesson Exists

Inheritance and polymorphism are the core mechanisms for building extensible,
type-safe abstractions in C++. Inheritance lets a derived class reuse and
extend a base class. Polymorphism (via virtual methods) lets you write code
that works with any type in a hierarchy, without knowing the concrete type
at compile time.

These features power plugin architectures, strategy patterns, and any design
where you want to program against an interface rather than a concrete type.

## Key Concepts

### Public Inheritance

Public inheritance means "Derived IS-A Base." The derived class inherits
all public and protected members of the base:

```cpp
class Student : public Person {
    std::string major_;
public:
    Student(std::string name, int age, std::string major)
        : Person(std::move(name), age), major_(std::move(major)) {}
};
```

### Virtual Methods and Dynamic Dispatch

Marking a method `virtual` enables runtime dispatch based on the actual
object type, not the pointer/reference type:

```cpp
class Animal {
public:
    virtual ~Animal() = default;
    virtual std::string speak() const = 0;  // pure virtual
};

class Dog : public Animal {
public:
    std::string speak() const override { return "Woof"; }
};
```

### Abstract Classes

A class with at least one pure virtual method (`= 0`) is abstract and
cannot be instantiated. It serves as an interface.

### Virtual Destructors

If a class has any virtual methods, its destructor MUST be virtual.
Otherwise, deleting a derived object through a base pointer causes
undefined behavior (the derived destructor is not called):

```cpp
class Base {
public:
    virtual ~Base() = default;  // REQUIRED
};
```

### The override Keyword

`override` asks the compiler to verify that a method actually overrides
a base class virtual method. Without it, a signature mismatch silently
creates a new method instead of overriding.

### The final Keyword

`final` on a method prevents further overriding. `final` on a class
prevents inheritance:

```cpp
class Concrete final : public Base {  // no one can inherit from Concrete
    void method() override final {}   // no one can override method()
};
```

### Object Slicing

Assigning a derived object to a base object by value "slices off" the
derived part. To preserve polymorphism, always use pointers or references:

```cpp
Derived d;
Base b = d;      // SLICED: b is only a Base
Base& ref = d;   // OK: ref refers to the full Derived
```

### Protected Members

`protected` members are accessible to the class and its derived classes,
but not to outside code. Use them to share implementation details within
a hierarchy.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 03-27

# Build and test a single exercise
./run exercise 03-27-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Basic Inheritance

**Files:** `ex01.h` (edit) | `ex01_test.cpp` (read-only)

A `Student` class inherits from `Person` via public inheritance. The
inheritance and constructor are already set up. You implement the
remaining methods.

### What to do

1. `Student::describe()` -- return `"Name, age Age, Major"` (e.g.,
   `"Alice, age 20, Computer Science"`). Use `name()`, `age()`, and
   `std::to_string()`.
2. `create_student()` -- construct and return a `Student`.

---

## Exercise 2: Virtual Method Dispatch

**Files:** `ex02.h` (edit) | `ex02_test.cpp` (read-only)

The `Animal` base class defines two pure virtual methods: `speak()` and
`type()`. Implement them in `Dog` and `Cat` so that virtual dispatch
selects the correct override when called through a base pointer.

### What to do

1. `Dog::speak()` -- return `"Woof"`.
2. `Cat::speak()` -- return `"Meow"`.
3. `Dog::type()` -- return `"Dog"`.
4. `Cat::type()` -- return `"Cat"`.
5. `make_dog()` / `make_cat()` -- return `std::make_unique<Dog/Cat>()`.

---

## Exercise 3: Abstract Interface

**Files:** `ex03.h` (edit) | `ex03_test.cpp` (read-only)

The `Shape` interface defines `area()` and `name()` as pure virtual
methods. Implement two concrete classes: `Circle` and `Rectangle`.

### What to do

1. `Circle::area()` -- return `M_PI * radius_ * radius_`.
2. `Circle::name()` -- return `"Circle"`.
3. `Rectangle::area()` -- return `width_ * height_`.
4. `Rectangle::name()` -- return `"Rectangle"`.
5. `make_circle()` / `make_rectangle()` -- factory functions.

---

## Exercise 4: Virtual Destructor

**Files:** `ex04.h` (edit) | `ex04_test.cpp` (read-only)

The `Resource` base class is missing `virtual` on its destructor. When a
`DerivedResource` is deleted through a `Resource*`, the derived destructor
does not run. Fix the base class destructor.

### What to do

1. Change `~Resource() = default;` to `virtual ~Resource() = default;`.
2. Implement `create_derived()` -- return `std::make_unique<DerivedResource>(...)`.
3. Implement `exercise_ready()` -- return `true`.

---

## Exercise 5: Override Keyword

**Files:** `ex05.h` (edit) | `ex05_test.cpp` (read-only)

`BrokenPrinter` intends to override `Printer::print(const std::string&)`
but has a signature mismatch (takes by value instead of by const ref).
Fix the signature and add `override`. Then implement `LoudPrinter`.

### What to do

1. Fix `BrokenPrinter::print()` parameter to `const std::string& message`,
   and add `override`.
2. Implement `to_upper()` -- convert each character with `std::toupper`.
3. Implement `LoudPrinter::print()` -- return `to_upper(message)`, add
   `override`.
4. Implement `make_loud_printer()`.

---

## Exercise 6: Final Keyword

**Files:** `ex06.h` (edit) | `ex06_test.cpp` (read-only)

Use `final` to prevent further overriding of `TimestampLogger::log()`.

### What to do

1. `Logger::log()` -- return `"LOG: " + message`.
2. `TimestampLogger::log()` -- return `"[TS] LOG: " + message`. Add
   `final` after `override`.
3. Implement factory functions and `exercise_ready()`.

---

## Exercise 7: Object Slicing

**Files:** `ex07.h` (edit) | `ex07_test.cpp` (read-only)

Demonstrate object slicing: passing a derived object by value to a
function that takes the base by value loses the derived part.

### What to do

1. `Instrument::play()` -- return `"..."`.
2. `Guitar::play()` -- return `"Twang!"`.
3. `Drum::play()` -- return `"Boom!"`.
4. `play_by_value(Instrument)` -- call `inst.play()`. Because the
   parameter is by value, slicing occurs.
5. `play_by_reference(const Instrument&)` -- call `inst.play()`. Because
   the parameter is by reference, polymorphism is preserved.

---

## Exercise 8: Protected Members

**Files:** `ex08.h` (edit) | `ex08_test.cpp` (read-only)

The `Account` base class has a `protected` balance_ member. Derived
classes can access it directly; outside code cannot.

### What to do

1. `SavingsAccount::add_interest()` -- `balance_ += balance_ * rate_`.
2. `CheckingAccount::withdraw(amount)` -- if `amount <= balance_`,
   subtract it and return `true`. Otherwise return `false`.
3. Implement `create_savings()` and `create_checking()` factory functions.
