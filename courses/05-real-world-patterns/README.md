# Course 5: Real-World Patterns for Web Development

Applying everything from the previous courses to patterns you will encounter in
HTTP servers, API clients, middleware frameworks, and service infrastructure.
This course focuses on design patterns and architectural building blocks, from
builder and observer patterns through serialization, resource pooling, and a
capstone project that ties it all together into a mini HTTP handler framework.

## Prerequisites

Complete Courses 1 through 4 first. These exercises draw on the full range of
concepts covered earlier: RAII, smart pointers, move semantics, templates,
`std::variant`, `std::expected`, lambdas, `std::function`, threading, and
synchronization. Each lesson applies multiple earlier concepts in combination.

## Lessons

| # | Lesson | Exercises | Description |
|---|--------|-----------|-------------|
| 43 | [Builder Pattern](43-builder-pattern/) | 7 | Fluent interfaces, method chaining, required vs optional fields, type-state builders |
| 44 | [Type-Safe Configuration](44-type-safe-configuration/) | 7 | Strongly-typed config, parsing, validation, merging, nested config structs |
| 45 | [Middleware and Chain of Responsibility](45-middleware-and-chain-of-responsibility/) | 8 | Request pipelines, `std::function` chains, short-circuit, error-handling middleware |
| 46 | [Serialization and Structured Data](46-serialization-and-structured-data/) | 8 | Dynamic value types with `variant`, stringify/parse, visitor pattern |
| 47 | [Resource Pools](47-resource-pools/) | 7 | Object/connection pools, RAII checkout handles, thread-safe bounded pools |
| 48 | [Observer and Event System](48-observer-and-event-system/) | 8 | Pub-sub, event emitters, auto-unsubscribe, weak observers, event filtering |
| 49 | [HTTP Request/Response Modeling](49-http-request-response-modeling/) | 8 | Method/status enums, headers, request/response types, query string parsing |
| 50 | [Logging and Diagnostics](50-logging-and-diagnostics/) | 8 | Log levels, `std::source_location`, structured entries, sinks, thread-safe logging |
| 51 | [Error Propagation Patterns](51-error-propagation-patterns/) | 8 | `Result<T,E>` monad, `transform`/`and_then`/`or_else`, error context, pipelines |
| 52 | [Capstone: Mini HTTP Handler Framework](52-capstone-mini-http-handler/) | 9 | Router, middleware, path params, request parsing, response serialization, end-to-end |

**Total: 10 lessons, 78 exercises**

## How to Run

```bash
# Run all tests for this course
./run course 05

# Run all tests for a specific lesson (e.g., lesson 45)
./run lesson 05-45

# Run a single exercise (e.g., lesson 45, exercise 01)
./run exercise 05-45-ex01
```

Unfinished exercises show as **skipped** (not-implemented). Completed exercises
show as **passed** or **failed**. The capstone lesson (52) integrates concepts
from the entire course and is best attempted after completing all prior lessons.
