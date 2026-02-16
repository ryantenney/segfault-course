---
title: "Lesson 44: Type-Safe Configuration"
---

Configuration structs turn stringly-typed settings into compile-time-checked
values.  Instead of passing `map<string, string>` everywhere, a typed struct
gives you autocomplete, type safety, and clear documentation of what each
setting means.

## Why Typed Config?

- **Compile-time errors** when you misspell a field name
- **Validation** that catches bad combinations early
- **Defaults** that are visible in the struct definition
- **Diffing and merging** become simple struct operations

## Exercises

| # | Topic | Key Concept |
|---|-------|-------------|
| 1 | Config Struct with Defaults | In-class member initializers |
| 2 | Override Methods | `with_*()` returns modified copies |
| 3 | Parse from Key-Value | Convert string pairs to typed config |
| 4 | Merge Two Configs | Overlay with `std::optional` fields |
| 5 | Validation | Return vector of error strings |
| 6 | Nested Config | Sub-config for TLS settings |
| 7 | Config Diffing | Compare two configs, list differences |
