# Lesson 51: Error Propagation Patterns

Since `std::expected` is not available on Apple Clang, this lesson builds a
`Result<T, E>` type on top of `std::variant`. Each exercise progressively adds
a new capability to the type.

## Exercises

| # | Title | Concept |
|---|-------|---------|
| 01 | Result Type | `Result<T, E>` with `is_ok`, `is_error`, `value`, `error` |
| 02 | Monadic Transform | `transform(F)` maps the success value |
| 03 | Monadic and_then | `and_then(F)` chains failable operations |
| 04 | Monadic or_else | `or_else(F)` attempts error recovery |
| 05 | Map Error | `map_error(F)` transforms the error type |
| 06 | Error Context | `context(msg)` wraps errors with descriptive messages |
| 07 | Collect Results | `collect(vector<Result>)` gathers all-or-nothing |
| 08 | Pipeline with Results | Chain 4+ operations into a complete pipeline |

## Key Ideas

- **Variant-based sum type**: `std::variant<Ok<T>, Err<E>>` disambiguates even
  when `T` and `E` are the same type.
- **Monadic operations**: `transform`, `and_then`, and `or_else` let you compose
  pipelines without manual error checking at each step.
- **Error context**: Wrapping errors with descriptive messages produces
  human-readable error chains like `"initializing app: reading config: ENOENT"`.
- **Collect**: The all-or-nothing pattern gathers a batch of results into a
  single success-or-first-error outcome.
