---
title: "Lesson 43: Builder Pattern"
---

The **builder pattern** separates the construction of a complex object from its
representation, allowing the same construction process to produce different
representations.

## Why Builders?

When an object has many fields -- some required, some optional, some with
defaults -- constructors become unwieldy.  A builder collects configuration
step by step, validates it, and then produces the final object.

## Exercises

| # | Topic | Key Concept |
|---|-------|-------------|
| 1 | Basic Builder | Store fields via setters |
| 2 | Method Chaining | Return `*this` for fluent API |
| 3 | Build Method | Produce the final immutable product |
| 4 | Required vs Optional | Return `std::optional` on validation failure |
| 5 | Builder with Defaults | Sensible defaults, only override what differs |
| 6 | Type-State Builder | Template bool encodes "has URL" at compile time |
| 7 | Nested Builder | Sub-builders for sub-objects |
