# Lesson 43: Builder Pattern

## Why This Lesson Exists

When an object has many fields — some required, some optional, some with
defaults — constructors become unwieldy.  A 7-parameter constructor is
hard to read, easy to get wrong (did the `int` argument go in position 3 or
4?), and provides no way to validate the combination of fields before the
object is created.

The **builder pattern** separates the construction of a complex object from its
representation.  A builder accumulates configuration step by step, validates
it, and then produces the final (often immutable) product.  This is the same
idea behind `std::ostringstream` for building strings, or builder APIs in
libraries like Protobuf and gRPC.

## Key Concepts

### Builder Basics

A builder is a mutable helper object with setter methods.  Each setter stores
one piece of configuration:

```cpp
RequestBuilder b;
b.set_method("POST");
b.set_url("/api/data");
b.set_body("payload");
```

### Method Chaining (Fluent API)

When each setter returns a reference to `*this`, callers can chain calls:

```cpp
auto req = RequestBuilder()
    .set_method("POST")
    .set_url("/api/data")
    .set_body("payload")
    .build();
```

The return type of each setter is `Builder&`.

### Build Method

The `build()` method produces the final product — typically a separate struct
or class that is immutable (or at least independent of the builder).  This
cleanly separates the mutable construction phase from the finished result.

### Validation and `std::optional`

Not all field combinations are valid.  A builder's `build()` method can
validate the accumulated state and return `std::optional<Product>` — returning
`std::nullopt` when required fields are missing or constraints are violated:

```cpp
std::optional<Request> build() const {
    if (url_.empty()) return std::nullopt;
    return Request{method_, url_, body_};
}
```

### Type-State Builder

A more advanced technique uses template parameters to encode builder state in
the type system.  For example, `TypedRequestBuilder<false>` has no `build()`
method — calling it is a compile error.  Only after `set_url()` returns a
`TypedRequestBuilder<true>` does `build()` become available.  This catches
missing-field bugs at compile time rather than runtime.

### Nested Builders

Complex objects often contain sub-objects.  A nested builder pattern lets you
build the inner parts with their own builders, then compose them:

```cpp
RequestBuilder()
    .set_method("POST")
    .set_url("/api");
builder.headers_builder().add("Content-Type", "application/json");
builder.body_builder().set_content("data");
auto req = builder.build();
```

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 05-43

# Build and test a single exercise
./run exercise 05-43-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Basic Builder

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Implement a `RequestBuilder` with individual setter methods (`set_method`,
`set_url`, `set_body`) and corresponding getters.  Each setter takes a
`const std::string&` and stores it in a private member.

### What to do

1. Implement `set_method()`, `set_url()`, `set_body()` to store the value.
2. Implement `get_method()`, `get_url()`, `get_body()` to return the value.
3. Run: `./run exercise 05-43-ex01`

---

## Exercise 2: Method Chaining

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Convert the builder to a fluent API by returning `RequestBuilder&` from each
setter.  This allows `builder.set_method("POST").set_url("/api").set_body("x")`.

### What to do

1. Implement `set_method()`, `set_url()`, `set_body()` — store the value and
   return `*this`.
2. Implement the three getters.
3. Run: `./run exercise 05-43-ex02`

---

## Exercise 3: Build Method

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Add a `build()` method that produces a separate `Request` struct.  This
separates the mutable construction phase from the immutable product.

### What to do

1. Implement `set_method()`, `set_url()`, `set_body()` returning `*this`.
2. Implement `build()` — return a `Request{method_, url_, body_}`.
3. Run: `./run exercise 05-43-ex03`

---

## Exercise 4: Required vs Optional Fields

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Not every request is valid.  A URL and method are required, but body is
optional.  The `build()` method validates and returns `std::optional<Request>`.

### What to do

1. Implement the three setters returning `*this`.
2. Implement `build()`:
   - Return `std::nullopt` if `url_` is empty.
   - Return `std::nullopt` if `method_` is empty.
   - Otherwise return a `Request` with the stored values.
3. Run: `./run exercise 05-43-ex04`

---

## Exercise 5: Builder with Defaults

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

A well-designed builder provides sensible defaults so callers only configure
what differs from the common case.  Method defaults to `"GET"` and headers
default to empty.

### What to do

1. Implement `set_method()`, `set_url()`, `set_body()`, `add_header()`
   returning `*this`.
2. Implement `build()`:
   - Method defaults to `"GET"` if not set.
   - URL is required: return `std::nullopt` if empty.
   - Otherwise return a `Request` with all stored values.
3. Run: `./run exercise 05-43-ex05`

---

## Exercise 6: Type-State Builder

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Use the type system to enforce that `set_url()` must be called before
`build()`.  The builder is parameterized by a `bool HasUrl` template
argument.  `set_url()` returns `TypedRequestBuilder<true>`, and `build()`
is only available when `HasUrl` is `true`.

### What to do

1. Implement `set_method()` — store method, return a builder with the same
   `HasUrl` state.
2. Implement `set_url()` — store url, return `TypedRequestBuilder<true>`.
3. Implement `set_body()` — store body, return builder with same state.
4. Implement `build()` — return a `Request` with stored values.
5. Run: `./run exercise 05-43-ex06`

---

## Exercise 7: Nested Builder

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

An `HttpRequest` contains `Headers` and `Body` sub-objects, each built by
their own builder.  The top-level `RequestBuilder` exposes references to its
inner `HeadersBuilder` and `BodyBuilder`.

### What to do

1. Implement `HeadersBuilder::add()` — store a key-value pair, return `*this`.
2. Implement `HeadersBuilder::build()` — return a `Headers` struct.
3. Implement `BodyBuilder::set_content()` and `set_content_type()` — store
   values, return `*this`.
4. Implement `BodyBuilder::build()` — return a `Body` struct.
5. Implement `RequestBuilder::set_method()`, `set_url()` returning `*this`.
6. Implement `headers_builder()` and `body_builder()` — return references to
   the inner builders.
7. Implement `RequestBuilder::build()` — compose the final `HttpRequest` by
   calling `build()` on both sub-builders.
8. Run: `./run exercise 05-43-ex07`
