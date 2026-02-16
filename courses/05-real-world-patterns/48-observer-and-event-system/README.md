# Lesson 48: Observer and Event System

## Why This Lesson Exists

The Observer pattern (also called Publish/Subscribe) is one of the most widely
used patterns in software engineering.  GUI frameworks, game engines, message
brokers, and reactive systems all rely on it.  The core idea: an **emitter**
fires events without knowing who is listening, and **observers** register
callbacks that react when notified.  This decouples producers from consumers.

In C++, `std::function` and lambdas make it natural to implement observers as
callbacks.  This lesson builds an event system from scratch, progressively
adding unsubscription, typed payloads, RAII lifetime management, weak
references, filtering, and priority ordering.

## Key Concepts

### Simple Emitter

The simplest emitter stores a vector of callbacks.  `on()` adds a listener;
`emit()` invokes them all in registration order:

```cpp
class Emitter {
    std::vector<std::function<void()>> listeners_;
public:
    void on(std::function<void()> cb) { listeners_.push_back(std::move(cb)); }
    void emit() { for (auto& cb : listeners_) cb(); }
};
```

### Subscription IDs and Unsubscription

To remove a listener, `on()` returns a unique ID.  `off(id)` finds and
removes that specific entry.  This is essential for avoiding dangling
callbacks when a subscriber is destroyed.

### Named Events (Dispatcher)

A dispatcher maps event names (strings) to separate listener lists, so
`"click"` and `"hover"` have independent sets of callbacks:

```cpp
std::unordered_map<std::string, std::vector<std::function<void()>>> listeners_;
```

### Typed Payloads

Events usually carry data.  A `TypedEmitter<T>` parameterizes the callback
signature on the payload type: `std::function<void(const T&)>`.

### RAII Subscriptions

Forgetting to call `off()` leads to dangling listeners.  An RAII
`Subscription` handle automatically unsubscribes when it goes out of scope —
the same pattern as `std::lock_guard` or `std::unique_ptr`.

### Weak Observers

When observers are managed by `std::shared_ptr`, the emitter should not
prevent their destruction.  Storing `std::weak_ptr<Observer>` lets the emitter
skip expired observers on `emit()` and clean them up lazily.

### Event Filtering

A filtering emitter lets each subscriber provide a predicate.  The callback is
only invoked when the predicate returns true for the emitted value, reducing
unnecessary work in listeners.

### Priority-based Dispatch

Some systems guarantee notification order.  Each listener gets a priority
(lower = called first).  Listeners with the same priority are called in
registration order.

## Running the Exercises

```bash
# Build everything for this lesson
./run lesson 05-48

# Build and test a single exercise
./run exercise 05-48-ex01
```

Unfinished exercises show as **skipped** (yellow circles).  Implemented
exercises show as **passed** (green checkmarks) or **failed** (red crosses).

---

## Exercise 1: Simple Event Emitter

**Files:** `ex01.h` (edit) · `ex01_test.cpp` (read-only)

Implement `Emitter` — the most basic event emitter with `on()`, `emit()`,
and `listener_count()`.

### What to do

1. `on(callback)` — store the callback in a vector.
2. `emit()` — invoke all registered callbacks in registration order.
3. `listener_count()` — return the number of listeners.
4. Run: `./run exercise 05-48-ex01`

---

## Exercise 2: Subscription ID

**Files:** `ex02.h` (edit) · `ex02_test.cpp` (read-only)

Implement `IdEmitter` — an emitter where `on()` returns a unique integer ID
and `off(id)` removes that specific listener.

### What to do

1. `on(callback)` — assign the next ID (starting at 1), store the entry,
   return the ID.
2. `off(id)` — find and remove the listener.  Return `true` if found.
3. `emit()` — invoke all remaining callbacks in registration order.
4. `listener_count()` — number of active listeners.
5. Run: `./run exercise 05-48-ex02`

---

## Exercise 3: Multi-event Dispatcher

**Files:** `ex03.h` (edit) · `ex03_test.cpp` (read-only)

Implement `Dispatcher` — an emitter that supports multiple named events, each
with its own listener list.

### What to do

1. `on(event_name, callback)` — register a callback for the named event.
2. `emit(event_name)` — invoke all callbacks for that event.  Do nothing if
   no listeners exist.
3. `listener_count(event_name)` — return the count for that event.
4. Run: `./run exercise 05-48-ex03`

---

## Exercise 4: Event with Payload

**Files:** `ex04.h` (edit) · `ex04_test.cpp` (read-only)

Implement `TypedEmitter<T>` — a template emitter where callbacks receive a
typed payload value.

### What to do

1. `on(callback)` — register a `std::function<void(const T&)>`.
2. `emit(value)` — call all callbacks with the given value.
3. `listener_count()` — number of registered listeners.
4. Run: `./run exercise 05-48-ex04`

---

## Exercise 5: Auto-unsubscribe

**Files:** `ex05.h` (edit) · `ex05_test.cpp` (read-only)

Implement `SubEmitter` (same as `IdEmitter`) and a `Subscription` RAII handle
that automatically calls `off()` when destroyed.

### What to do

1. Implement `SubEmitter::on()`, `off()`, `emit()`, `listener_count()` — same
   as exercise 2.
2. `Subscription` destructor: call `emitter_->off(*id_)` if still active.
3. Move constructor / move assignment: transfer ownership; moved-from handle
   must not unsubscribe.
4. `release()` — disarm the subscription (don't unsubscribe on destruction).
   Return the ID.
5. Run: `./run exercise 05-48-ex05`

---

## Exercise 6: Weak Observer

**Files:** `ex06.h` (edit) · `ex06_test.cpp` (read-only)

Implement `Observer` (pure virtual interface) and `WeakEmitter` — an emitter
that holds non-owning `std::weak_ptr<Observer>` references and skips expired
observers on emit.

### What to do

1. `subscribe(std::weak_ptr<Observer>)` — store the weak pointer.
2. `emit()` — for each stored `weak_ptr`, call `lock()`.  If the observer
   still exists, call `on_event()`.  If expired, skip it.
3. `cleanup()` — remove all expired `weak_ptr` entries.
4. `subscriber_count()` — total entries (including potentially expired).
5. Run: `./run exercise 05-48-ex06`

---

## Exercise 7: Event Filtering

**Files:** `ex07.h` (edit) · `ex07_test.cpp` (read-only)

Implement `FilterEmitter<T>` — a typed emitter where each listener has a
predicate.  The callback is only invoked when the predicate returns true.

### What to do

1. `on(predicate, callback)` — store both the predicate and callback.
2. `emit(value)` — for each entry, call the callback only if
   `predicate(value)` is true.
3. `listener_count()` — total listeners (regardless of filter).
4. Run: `./run exercise 05-48-ex07`

---

## Exercise 8: Ordered Dispatch

**Files:** `ex08.h` (edit) · `ex08_test.cpp` (read-only)

Implement `OrderedEmitter` — an emitter where each listener has an integer
priority.  Lower priority values are invoked first; ties are broken by
registration order.

### What to do

1. `on(priority, callback)` — store the entry with priority and a sequence
   number.
2. `emit()` — invoke callbacks sorted by (priority, sequence number).
3. `listener_count()` — number of registered listeners.
4. Run: `./run exercise 05-48-ex08`
