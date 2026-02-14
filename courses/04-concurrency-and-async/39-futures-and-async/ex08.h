// Exercise 08: Packaged Task
//
// PROBLEM:
//   Return a packaged_task<int()> that, when invoked, produces n * n + n.
//
// TODO:
//   Implement make_task() to create and return a packaged_task wrapping
//   a lambda that computes n * n + n.
//
// WHY:
//   std::packaged_task wraps a callable and provides a future for its
//   result, but unlike std::async it does not launch a thread. You control
//   when and where the task runs. This is the building block for thread
//   pools and task queues.

#pragma once
#include <testkit/testkit.h>
#include <future>

// Returns a packaged_task that computes n * n + n when invoked.
inline std::packaged_task<int()> make_task(int n) {
    TODO();
}
