// Exercise 05: Auto-unsubscribe
//
// PROBLEM:
//   Forgetting to call off() leads to dangling listeners that reference
//   destroyed objects. An RAII Subscription handle automatically removes
//   the listener when it goes out of scope — the same pattern as
//   unique_ptr or lock_guard.
//
// TODO:
//   1. Implement SubEmitter (same as IdEmitter from ex02, provided here
//      for self-containment):
//        - on(callback) returns uint64_t ID
//        - off(id) removes listener
//        - emit() calls all listeners
//        - listener_count()
//
//   2. Implement Subscription:
//        - Constructor: takes a SubEmitter* and a subscription ID.
//        - Destructor: calls emitter->off(id) if still active.
//        - Move constructor / move assignment: transfer ownership.
//        - Delete copy operations.
//        - release(): disarm the subscription (don't unsubscribe on
//          destruction). Return the ID.
//
// HINT:
//   - Use a pointer-to-emitter and an optional<uint64_t> for the ID.
//     If the optional is empty, the subscription is disarmed.

#pragma once

#include <cstdint>
#include <functional>
#include <optional>
#include <vector>
#include <testkit/testkit.h>

class SubEmitter {
    struct Entry {
        uint64_t id;
        std::function<void()> callback;
    };
    std::vector<Entry> listeners_;
    uint64_t next_id_ = 1;

public:
    uint64_t on(std::function<void()> callback) {
        TODO();
    }

    bool off(uint64_t id) {
        TODO();
    }

    void emit() {
        TODO();
    }

    std::size_t listener_count() const {
        TODO();
    }
};

class Subscription {
    SubEmitter* emitter_ = nullptr;
    std::optional<uint64_t> id_;

public:
    // Construct a subscription that will auto-unsubscribe on destruction.
    Subscription(SubEmitter* emitter, uint64_t id)
        : emitter_(emitter), id_(id) {}

    // Destructor: unsubscribe if still active.
    // Do NOT use TODO() here.
    ~Subscription() {
        // TODO: if id_.has_value(), call emitter_->off(*id_);
    }

    // Move constructor.
    Subscription(Subscription&& other) noexcept
        : emitter_(other.emitter_), id_(other.id_) {
        other.id_.reset();
    }

    // Move assignment.
    Subscription& operator=(Subscription&& other) noexcept {
        if (this != &other) {
            if (id_.has_value()) {
                emitter_->off(*id_);
            }
            emitter_ = other.emitter_;
            id_ = other.id_;
            other.id_.reset();
        }
        return *this;
    }

    // Non-copyable.
    Subscription(const Subscription&) = delete;
    Subscription& operator=(const Subscription&) = delete;

    // Disarm: prevent auto-unsubscribe. Returns the subscription ID.
    uint64_t release() {
        TODO();
    }
};
