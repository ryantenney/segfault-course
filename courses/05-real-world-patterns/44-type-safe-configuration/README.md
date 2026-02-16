# Lesson 44: Type-Safe Configuration

## Why This Lesson Exists

Every non-trivial program has configuration — ports, hosts, timeouts, feature
flags, TLS certificates.  The naive approach is `std::map<std::string, std::string>`:
flexible, but every access is a potential typo, every value needs manual
parsing, and there is no way to validate combinations at compile time.

A **typed configuration struct** replaces the string map with named, typed
fields.  You get autocomplete, compile-time errors for misspellings, and a
natural place to define defaults and validation logic.  This lesson builds
that pattern from basic defaults through parsing, merging, validation, nesting,
and diffing.

## Key Concepts

### In-Class Member Initializers

C++11 lets you provide default values directly in the struct definition:

```cpp
struct ServerConfig {
    int port = 8080;
    std::string host = "localhost";
    int max_connections = 100;
};
```

Creating a `ServerConfig{}` gives you the defaults.  Callers only override
what they need.

### Functional Updates (`with_*` Methods)

Instead of mutating a config in place, a functional approach returns a
modified copy:

```cpp
ServerConfig with_port(int p) const {
    auto copy = *this;
    copy.port = p;
    return copy;
}
```

The original is untouched, making it easy to derive variants from a base
config.

### Parsing from External Sources

Configuration often arrives as string key-value pairs from files, environment
variables, or command-line flags.  A `parse_config()` function converts
these into the typed struct, catching conversion errors (like a non-numeric
port) early and returning `std::optional` on failure.

### Config Overlay and Merging

When configuration comes from multiple sources (defaults → file → environment
→ command line), later sources should override earlier ones.  An overlay
struct uses `std::optional` fields to distinguish "not set" from "set to a
value":

```cpp
struct ConfigOverlay {
    std::optional<int> port;
    std::optional<std::string> host;
};
```

Merging applies only the fields that are present in the overlay.

### Validation

Individual field values may be fine on their own but invalid together (e.g.,
TLS enabled but no certificate path).  A `validate()` function inspects the
whole config and returns a vector of error strings — empty means valid.

### Config Diffing

For debugging and auditing, comparing two configs field-by-field and listing
the names of differing fields helps operators understand what changed between
deployments.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 05-44

# Build and test a single exercise
./run exercise 05-44-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Config Struct with Defaults

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Create a `ServerConfig` struct with in-class member initializers providing
sensible defaults.  Callers create a config and only override what they care
about.

### What to do

1. Set the default values: `port` = 8080, `host` = `"localhost"`,
   `max_connections` = 100.
2. Implement `get_port()`, `get_host()`, `get_max_connections()`.
3. Run: `./run exercise 05-44-ex01`

---

## Exercise 2: Override Methods

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Add `with_port()`, `with_host()`, and `with_max_connections()` methods that
each return a modified copy of the config, leaving the original unchanged.

### What to do

1. Implement `with_port(int p)` — copy `*this`, change `port`, return copy.
2. Implement `with_host(const std::string& h)` — same pattern.
3. Implement `with_max_connections(int mc)` — same pattern.
4. Run: `./run exercise 05-44-ex02`

---

## Exercise 3: Parse from Key-Value Pairs

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Implement `parse_config()` to convert a vector of string key-value pairs into
a typed `ServerConfig`.  Returns `std::nullopt` if any integer conversion
fails.

### What to do

1. Start from defaults (port=8080, host="localhost", max_connections=100).
2. Iterate the pairs.  Recognized keys: `"port"`, `"host"`,
   `"max_connections"`.
3. For `"port"` and `"max_connections"`, convert via `std::stoi`.  If it
   throws, return `std::nullopt`.
4. Unknown keys are ignored.
5. Return the resulting `ServerConfig`.
6. Run: `./run exercise 05-44-ex03`

---

## Exercise 4: Merge Two Configs

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Implement `merge_config()` to overlay a `ConfigOverlay` onto a base
`ServerConfig`.  The overlay uses `std::optional` fields — only fields
with values override the base.

### What to do

1. Start with the base config.
2. For each overlay field that `has_value()`, use it.
3. Return the merged `ServerConfig`.
4. Run: `./run exercise 05-44-ex04`

---

## Exercise 5: Validation

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Implement `validate()` to check a `ServerConfig` for constraint violations.
Returns a vector of error strings (empty means valid).

### What to do

1. If `port < 1` or `port > 65535`, add `"port out of range"`.
2. If `host` is empty, add `"host must not be empty"`.
3. If `max_connections < 1`, add `"max_connections must be positive"`.
4. If `max_connections > 10000`, add `"max_connections too large"`.
5. Return the error vector.
6. Run: `./run exercise 05-44-ex05`

---

## Exercise 6: Nested Config

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Add a `TlsConfig` sub-config to `ServerConfig`.  The nested config has its
own defaults and contributes additional validation rules.

### What to do

1. `TlsConfig` defaults: `enabled` = false, `cert_path` = `""`,
   `key_path` = `""`.
2. Implement `get_tls()` — return the `TlsConfig`.
3. Implement `with_tls()` — return a copy of `ServerConfig` with the new
   TLS config.
4. Implement `validate()`:
   - All rules from exercise 5 still apply.
   - If `tls.enabled` is true and `cert_path` is empty, add
     `"tls: cert_path required when enabled"`.
   - If `tls.enabled` is true and `key_path` is empty, add
     `"tls: key_path required when enabled"`.
5. Run: `./run exercise 05-44-ex06`

---

## Exercise 7: Config Diffing

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Implement `config_diff()` to compare two `ServerConfig` instances and return
the names of fields that differ.

### What to do

1. Compare each field of `lhs` and `rhs`.
2. If `port` differs, add `"port"` to the result.
3. If `host` differs, add `"host"`.
4. If `max_connections` differs, add `"max_connections"`.
5. Return the vector in the order: port, host, max_connections.
6. Run: `./run exercise 05-44-ex07`
