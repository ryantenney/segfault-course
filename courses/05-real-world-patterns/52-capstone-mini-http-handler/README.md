# Lesson 52: Capstone — Mini HTTP Handler Framework

## Why This Lesson Exists

This capstone ties together patterns from the entire course — builder,
configuration, middleware, serialization, observer, error handling — to build
a mini HTTP handler framework from scratch.  Each exercise is self-contained
and provides its own types, so you can tackle them in any order, but they
build toward a complete end-to-end pipeline in the final exercise.

This is a realistic microcosm of what web framework internals look like:
routing, parameter extraction, middleware chaining, request parsing, response
serialization, and structured error handling.

## Key Concepts

### Routing

A router maps `(method, path)` pairs to handler functions.  The simplest
approach concatenates method and path into a string key and looks it up in a
`std::map`:

```cpp
using Handler = std::function<Response(const Request&)>;
std::map<std::string, Handler> routes_;

void add_route(const std::string& method, const std::string& path, Handler h) {
    routes_[method + " " + path] = std::move(h);
}
```

### Path Parameters

Real web frameworks support patterns like `/users/:id`.  The router splits the
registered pattern and the incoming path into segments, matching literal
segments exactly and extracting `:param` segments into a map on the request.

### Middleware

Middleware wraps a handler to add cross-cutting concerns.  Each middleware is a
function that takes a `Handler` and returns a new `Handler`:

```cpp
using Middleware = std::function<Handler(Handler)>;
```

Applying multiple middleware composes them like an onion — each layer wraps the
next.

### Request Parsing and Response Serialization

At the system boundary, raw HTTP text must be parsed into structured `Request`
objects, and structured `Response` objects must be serialized back to text.
The format used here is simplified HTTP:

```
GET /path HTTP/1.1\r\n
Header: value\r\n
\r\n
body
```

### Error Handling

A robust dispatcher handles three error categories:
- **400 Bad Request**: malformed input (empty method or path)
- **404 Not Found**: no matching route
- **500 Internal Server Error**: handler threw an exception

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 05-52

# Build and test a single exercise
./run exercise 05-52-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Route Registration

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Implement a `Router` with `add_route()` for registering handlers and
`find_handler()` for looking them up by method and path.

### What to do

1. `add_route(method, path, handler)` — store the handler keyed by
   `method + " " + path`.
2. `find_handler(method, path)` — look up the handler.  Return `nullptr` if
   not found.
3. Run: `./run exercise 05-52-ex01`

---

## Exercise 2: Router Dispatch

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Extend the router with a `dispatch()` method that finds and calls the
matching handler, or returns a 404 response if no route matches.

### What to do

1. `add_route()` — same as exercise 1.
2. `dispatch(request)` — find the handler for the request's method and path.
   If found, call it.  If not, return `Response{404, "Not Found"}`.
3. Run: `./run exercise 05-52-ex02`

---

## Exercise 3: Path Parameters

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Add support for parameterized routes like `/users/:id`.  The router splits
patterns and incoming paths into segments, matching literals exactly and
extracting `:param` segments into a `params` map on the request.

### What to do

1. Use a `split()` helper to tokenize paths by `/`.
2. `add_route()` — store the pattern and handler.
3. `dispatch()` — iterate registered routes, compare segment by segment.
   Extract `:param` values into `request.params`.  Return 404 if no match.
4. Run: `./run exercise 05-52-ex03`

---

## Exercise 4: Middleware Integration

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Add middleware support.  Each middleware wraps a handler to add behavior (e.g.,
adding headers).  The `use()` method registers middleware; `dispatch()` applies
them in order around the matched handler.

### What to do

1. `use(middleware)` — store the middleware function.
2. `dispatch()` — find the handler, then apply all middleware in order
   (each wrapping the next).  Call the composed handler.
3. Run: `./run exercise 05-52-ex04`

---

## Exercise 5: Request Parsing

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Implement `parse_request()` to convert a raw HTTP-like string into a `Request`
struct.

### What to do

1. Parse the request line: `"METHOD /path HTTP/1.1\r\n"`.
2. Parse headers: `"Key: value\r\n"` lines until a blank `"\r\n"` line.
3. The remainder is the body.
4. Return a `Request` with method, path, version, headers map, and body.
5. Run: `./run exercise 05-52-ex05`

---

## Exercise 6: Response Serialization

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Implement `serialize_response()` and `reason_phrase()` to convert a `Response`
struct into an HTTP-like string.

### What to do

1. `reason_phrase(status)` — return the standard phrase for status codes
   200, 201, 400, 404, 500.
2. `serialize_response()` — format as `"HTTP/1.1 <status> <reason>\r\n"`
   followed by headers and body.
3. Run: `./run exercise 05-52-ex06`

---

## Exercise 7: Error Handling

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Implement robust error handling in the router's `dispatch()` method.

### What to do

1. Return 400 `"Bad Request"` if method or path is empty.
2. Return 404 `"Not Found"` if no route matches.
3. Catch `std::exception` from handler calls — return 500 with the exception
   message as the body.
4. Catch non-standard throws — return 500 `"Unknown error"`.
5. Run: `./run exercise 05-52-ex07`

---

## Exercise 8: JSON-like Body Parsing

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Implement `parse_body()` to parse a `key=value\n` format into a map, and
`handle_create_user()` to use it.

### What to do

1. `parse_body(body)` — split by newlines, then split each line by `=`.
   Return a `std::map<std::string, std::string>`.
2. `handle_create_user(request)` — parse the body, extract `"name"` and
   `"email"`.  Return 201 with `"created <name> <email>"` on success, or
   400 with `"missing field: <field>"` if a field is absent.
3. Run: `./run exercise 05-52-ex08`

---

## Exercise 9: End-to-End

**Files:** `ex09.h` (edit) · `ex09_test.cpp` (read-only)

Build the complete pipeline: parse a raw HTTP string, route it through
middleware, call the handler, and serialize the response back to a string.

### What to do

1. Implement `parse_request()` — same logic as exercise 5.
2. Implement `serialize_response()` — same logic as exercise 6.
3. Implement `Router::add_route()` and `Router::use()` — register handlers
   and middleware.
4. Implement `Router::dispatch()` — full routing with middleware wrapping,
   400/404/500 error handling.
5. Implement `handle_raw(raw_request, router)` — parse the raw string,
   dispatch through the router, serialize the response.
6. Run: `./run exercise 05-52-ex09`
