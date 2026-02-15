# Lesson 52: Capstone — Mini HTTP Handler Framework

This capstone ties together patterns from the entire course to build a
mini HTTP handler framework. Each exercise is self-contained and provides
its own types.

## Exercises

| # | Title | Concept |
|---|-------|---------|
| 01 | Route Registration | `Router` with `add_route` and handler lookup |
| 02 | Router Dispatch | Route matching with 404 fallback |
| 03 | Path Parameters | Extract `:id` params from `/users/:id` patterns |
| 04 | Middleware Integration | Chain of middleware wrapping handlers |
| 05 | Request Parsing | Parse raw HTTP-like strings into Request structs |
| 06 | Response Serialization | Serialize Response to HTTP-like strings |
| 07 | Error Handling | 400/404/500 for bad requests, missing routes, exceptions |
| 08 | JSON-like Body | Parse `key=value` body format, use in handlers |
| 09 | End-to-End | Full pipeline: raw string through the entire framework |

## Key Ideas

- **Routing**: Map (method, path) pairs to handler functions with a simple
  string-keyed dispatch table.
- **Path parameters**: Pattern matching with `:param` segments extracted into a
  map on the request.
- **Middleware**: Higher-order functions that wrap handlers to add cross-cutting
  concerns like logging, auth headers, and timing.
- **Parsing and serialization**: Convert between raw text and structured types
  at the boundary of the system.
- **Error handling**: Validate inputs (400), handle missing routes (404), and
  catch handler exceptions (500) for robust dispatch.
- **Composition**: The final exercise chains all of these patterns into a single
  end-to-end pipeline.
