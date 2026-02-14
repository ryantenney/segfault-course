// Exercise 06: Timer in Event Loop
//
// PROBLEM:
//   Extend the event loop with delayed callbacks. Instead of executing
//   immediately, post_delayed() schedules a callback to run after a
//   specified tick count. The run() method processes callbacks in order
//   of their scheduled tick.
//
// TODO:
//   Implement the TimerEventLoop class:
//   1. post(callback) — schedules at tick 0 (immediate).
//   2. post_delayed(ticks, callback) — schedules at current_tick + ticks.
//   3. run() — processes all callbacks in tick order. Returns count executed.
//
// WHY:
//   Timers are a fundamental building block of event-driven systems.
//   Network timeouts, periodic tasks, and debouncing all use delayed
//   execution. A priority queue sorted by deadline is the standard
//   implementation — this is how real event loops (libuv, Boost.Asio)
//   handle timers internally.

#pragma once
#include <testkit/testkit.h>
#include <functional>
#include <queue>
#include <vector>

class TimerEventLoop {
public:
    // Schedules a callback for immediate execution (tick 0).
    void post(std::function<void()> callback) {
        TODO();
        // Hint: post_delayed(0, std::move(callback));
    }

    // Schedules a callback to run after `ticks` ticks from now.
    void post_delayed(int ticks, std::function<void()> callback) {
        TODO();
        // Hint: queue_.push({current_tick_ + ticks, seq_++, std::move(callback)});
    }

    // Processes all pending callbacks in tick order.
    // Callbacks posted at the same tick execute in insertion order.
    // Returns the number of callbacks executed.
    int run() {
        TODO();
        // Hint:
        //   int count = 0;
        //   while (!queue_.empty()) {
        //       auto entry = std::move(const_cast<Entry&>(queue_.top()));
        //       queue_.pop();
        //       current_tick_ = entry.tick;
        //       entry.callback();
        //       ++count;
        //   }
        //   return count;
    }

    // Returns the current tick value.
    int current_tick() const {
        TODO();
        // Hint: return current_tick_;
    }

private:
    struct Entry {
        int tick;
        int sequence;  // for stable ordering within same tick
        std::function<void()> callback;

        // Priority queue is max-heap, so invert comparison for min-heap.
        bool operator<(const Entry& other) const {
            if (tick != other.tick) return tick > other.tick;
            return sequence > other.sequence;
        }
    };

    std::priority_queue<Entry> queue_;
    int current_tick_ = 0;
    int seq_ = 0;
};
