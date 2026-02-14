// Exercise 05: Simulated Event Loop
//
// PROBLEM:
//   Implement a simple single-threaded event loop. The event loop maintains
//   a queue of callbacks and executes them in order when run() is called.
//
// TODO:
//   Implement the EventLoop class:
//   1. post(callback) — adds a callback to the queue.
//   2. run() — executes all queued callbacks in FIFO order, then returns.
//      Returns the number of callbacks executed.
//
// WHY:
//   Event loops are the heart of async I/O systems. Instead of blocking a
//   thread for each I/O operation, you register callbacks and a single thread
//   processes them in order. This is how Node.js, Python's asyncio, and
//   Boost.Asio work. This exercise builds a minimal version to understand
//   the core concept.

#pragma once
#include <testkit/testkit.h>
#include <functional>
#include <queue>

class EventLoop {
public:
    // Adds a callback to the event queue.
    void post(std::function<void()> callback) {
        TODO();
        // Hint: queue_.push(std::move(callback));
    }

    // Executes all queued callbacks in FIFO order.
    // Returns the number of callbacks executed.
    int run() {
        TODO();
        // Hint:
        //   int count = 0;
        //   while (!queue_.empty()) {
        //       auto cb = std::move(queue_.front());
        //       queue_.pop();
        //       cb();
        //       ++count;
        //   }
        //   return count;
    }

    // Returns the number of pending callbacks in the queue.
    size_t pending() const {
        TODO();
        // Hint: return queue_.size();
    }

private:
    std::queue<std::function<void()>> queue_;
};
