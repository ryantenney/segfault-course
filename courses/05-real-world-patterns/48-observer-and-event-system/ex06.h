// Exercise 06: Weak Observer
//
// PROBLEM:
//   When observers are managed by shared_ptr, the emitter should not
//   prevent them from being destroyed. A weak_ptr lets the emitter
//   hold a non-owning reference. On emit, if the observer has been
//   destroyed (lock() returns nullptr), the emitter silently skips it.
//
// TODO:
//   Implement Observer (interface) and WeakEmitter:
//
//   Observer:
//     - Pure virtual void on_event() = 0.
//     - Virtual destructor.
//
//   WeakEmitter:
//     1. subscribe(std::weak_ptr<Observer>) -- add a weak observer.
//     2. emit() -- for each stored weak_ptr, lock() it. If the
//        observer still exists, call on_event(). If expired, skip it.
//     3. cleanup() -- remove all expired weak_ptrs from the list.
//     4. subscriber_count() -- total entries (including expired).
//
// HINT:
//   - Store std::vector<std::weak_ptr<Observer>>.
//   - cleanup() can use erase-remove with expired().

#pragma once

#include <memory>
#include <vector>
#include <testkit/testkit.h>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void on_event() = 0;
};

class WeakEmitter {
    std::vector<std::weak_ptr<Observer>> subscribers_;

public:
    // Add a weak reference to an observer.
    void subscribe(std::weak_ptr<Observer> obs) {
        TODO();
    }

    // Notify all live observers. Skip expired ones.
    void emit() {
        TODO();
    }

    // Remove expired weak_ptrs from the list.
    void cleanup() {
        TODO();
    }

    // Total entries (including potentially expired).
    std::size_t subscriber_count() const {
        TODO();
    }
};
