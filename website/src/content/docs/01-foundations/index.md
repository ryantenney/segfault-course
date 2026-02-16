---
title: "Course 1: Foundations -- The C++ Mental Model"
description: "The C++ Mental Model"
---

The bridge from "I know C" to "I can write correct modern C++." This course
covers the compilation model, organizational primitives, type system, memory
model, and ownership semantics that every line of C++ code depends on. By the
end, you will have the mental model needed to reason about copies, moves,
lifetimes, and error handling in idiomatic C++.

## Prerequisites

This course assumes you can read C and have shipped production code in at least
one systems-adjacent language. You should be comfortable with pointers, control
flow, and basic data structures. No prior C++ experience is required.

## Lessons

| # | Lesson | Exercises | Description |
|---|--------|-----------|-------------|
| 01 | [Compilation Model](01-compilation-model/) | 8 | Translation units, headers, ODR, include guards, `inline`, linkage |
| 02 | [Namespaces](02-namespaces/) | 8 | Namespace organization, `using` declarations, ADL, anonymous namespaces |
| 03 | [Value Semantics, const, and References](03-value-semantics/) | 8 | Value vs reference semantics, `const` correctness, parameter passing |
| 04 | [Strings and String Views](04-strings/) | 8 | `std::string` vs `std::string_view`, lifetime pitfalls, substring operations |
| 05 | [Scoped Enums and Strong Types](05-enums/) | 7 | `enum class`, underlying types, bitflags, strong typedefs |
| 06 | [auto, Type Deduction, and Type Aliases](06-auto-and-type-deduction/) | 8 | `auto`, `decltype`, trailing return types, `using` aliases |
| 07 | [Structured Bindings](07-structured-bindings/) | 7 | Decomposing pairs, tuples, structs, and maps with `auto [a, b]` |
| 08 | [C++ Casts](08-casts/) | 8 | `static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast` |
| 09 | [RAII and Scope-Based Lifetime](09-raii/) | 8 | Resource acquisition is initialization, deterministic cleanup |
| 10 | [Smart Pointers](10-smart-pointers/) | 8 | `unique_ptr`, `shared_ptr`, `weak_ptr`, ownership semantics |
| 11 | [Move Semantics](11-move-semantics/) | 8 | Rvalue references, `std::move`, move constructors, RVO |
| 12 | [optional, variant, and expected](12-optional-variant-expected/) | 8 | Sum types: `std::optional`, `std::variant`, `std::expected` (C++23) |
| 13 | [Error Handling Patterns](13-error-handling/) | 8 | Exceptions, error codes, `noexcept`, exception safety guarantees |

**Total: 13 lessons, 102 exercises**

## How to Run

```bash
# Run all tests for this course
./run course 01

# Run all tests for a specific lesson (e.g., lesson 03)
./run lesson 01-03

# Run a single exercise (e.g., lesson 03, exercise 01)
./run exercise 01-03-ex01
```

Unfinished exercises show as **skipped** (not-implemented). Completed exercises
show as **passed** or **failed**. You can work through exercises in any order
within a lesson, but lessons build on each other and are best done sequentially.
