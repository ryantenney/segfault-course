// Exercise 07: Multiple Pending Operations
//
// PROBLEM:
//   Implement an operation tracker that manages multiple async operations
//   in an event loop. Each operation is submitted with a name and a tick
//   delay. The tracker records completion order as operations finish.
//
// TODO:
//   Implement the OperationTracker class:
//   1. submit(name, delay, loop) — posts a delayed callback that records
//      the operation name when it executes.
//   2. completed() — returns the list of completed operation names in order.
//   3. pending_count() — returns how many operations have been submitted
//      but not yet completed.
//
// WHY:
//   Real async systems manage many pending operations simultaneously.
//   Understanding how multiple operations interleave in an event loop is
//   key to writing correct async code. This exercise demonstrates that
//   operations complete based on their scheduled time, not submission order.

#pragma once
#include <testkit/testkit.h>
#include <functional>
#include <queue>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// TimerEventLoop — provided (same as exercise 06, but self-contained)
// ---------------------------------------------------------------------------
class TimerEventLoop {
public:
    void post(std::function<void()> callback) {
        post_delayed(0, std::move(callback));
    }

    void post_delayed(int ticks, std::function<void()> callback) {
        queue_.push({current_tick_ + ticks, seq_++, std::move(callback)});
    }

    int run() {
        int count = 0;
        while (!queue_.empty()) {
            auto entry = std::move(const_cast<Entry&>(queue_.top()));
            queue_.pop();
            current_tick_ = entry.tick;
            entry.callback();
            ++count;
        }
        return count;
    }

    int current_tick() const { return current_tick_; }

private:
    struct Entry {
        int tick;
        int sequence;
        std::function<void()> callback;

        bool operator<(const Entry& other) const {
            if (tick != other.tick) return tick > other.tick;
            return sequence > other.sequence;
        }
    };

    std::priority_queue<Entry> queue_;
    int current_tick_ = 0;
    int seq_ = 0;
};

// ---------------------------------------------------------------------------
// Student implements this class
// ---------------------------------------------------------------------------
class OperationTracker {
public:
    // Submits an operation with the given name, scheduled to complete
    // after `delay` ticks in the event loop.
    void submit(const std::string& name, int delay, TimerEventLoop& loop) {
        TODO();
        // Hint:
        //   ++pending_;
        //   loop.post_delayed(delay, [this, name] {
        //       completed_.push_back(name);
        //       --pending_;
        //   });
    }

    // Returns the names of completed operations in completion order.
    const std::vector<std::string>& completed() const {
        TODO();
        // Hint: return completed_;
    }

    // Returns the number of operations that have been submitted but
    // not yet completed.
    int pending_count() const {
        TODO();
        // Hint: return pending_;
    }

private:
    std::vector<std::string> completed_;
    int pending_ = 0;
};
