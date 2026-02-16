---
title: "Course 3: Types and Generic Programming"
description: "Designing types, APIs, and writing generic code"
---

Designing types, APIs, and generic code -- where C++ diverges most from Java
and Rust. This course covers class design, operator overloading, inheritance,
special member functions, and the full template system including concepts
(C++20), type traits, perfect forwarding, and the CRTP. By the end, you will
be able to design expressive, type-safe APIs and write generic code with
clear constraints.

## Prerequisites

Complete Courses 1 and 2 first. You should be comfortable with value semantics,
move semantics, smart pointers, lambdas, and the standard containers. This
course builds directly on those foundations to explore how custom types and
generic code are designed in C++.

## Lessons

| # | Lesson | Exercises | Description |
|---|--------|-----------|-------------|
| 24 | [Classes and Encapsulation](24-classes-and-encapsulation/) | 8 | Access specifiers, getters/setters, static members, friend functions |
| 25 | [Constructors, Initialization, and the Minefield](25-constructors-and-initialization/) | 9 | Member init lists, delegating ctors, `explicit`, aggregate init, most vexing parse |
| 26 | [Operator Overloading](26-operator-overloading/) | 8 | `==`, `<=>` (spaceship), `<<`, `[]`, arithmetic operators, C++20 defaulted comparisons |
| 27 | [Inheritance and Polymorphism](27-inheritance-and-polymorphism/) | 8 | Virtual functions, `override`, `final`, abstract classes, object slicing |
| 28 | [Rule of Zero / Five](28-rule-of-zero-five/) | 8 | Special member functions, `= default`, `= delete`, copy-and-swap idiom |
| 29 | [Function Templates](29-function-templates/) | 8 | Type deduction, non-type parameters, specialization, variadic templates |
| 30 | [Class Templates](30-class-templates/) | 8 | Template classes, CTAD, partial and full specialization, dependent types |
| 31 | [Concepts and Constraints (C++20)](31-concepts-and-constraints/) | 8 | `concept`, `requires` clauses, constrained overloading, standard concepts |
| 32 | [Type Traits and constexpr](32-type-traits-and-constexpr/) | 8 | `<type_traits>`, `if constexpr`, `constexpr`/`consteval` functions, `static_assert` |
| 33 | [Forwarding References and Perfect Forwarding](33-forwarding-references/) | 8 | `T&&` in templates, `std::forward`, reference collapsing, `decltype(auto)` |
| 34 | [CRTP and Mixin Patterns](34-crtp-and-mixins/) | 7 | Static polymorphism, mixin classes, composable policy-based design |

**Total: 11 lessons, 88 exercises**

## How to Run

```bash
# Run all tests for this course
./run course 03

# Run all tests for a specific lesson (e.g., lesson 29)
./run lesson 03-29

# Run a single exercise (e.g., lesson 29, exercise 01)
./run exercise 03-29-ex01
```

Unfinished exercises show as **skipped** (not-implemented). Completed exercises
show as **passed** or **failed**. Lessons in this course build on each other
heavily. Work through them in order.
