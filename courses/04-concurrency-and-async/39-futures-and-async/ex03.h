// Exercise 03: Promise-Future Channel
//
// PROBLEM:
//   Set a value on a promise so that the corresponding future receives it.
//
// TODO:
//   Implement send_value() to call p.set_value(val).
//
// WHY:
//   std::promise and std::future form a one-shot communication channel.
//   The promise is the write end; the future is the read end. This pattern
//   lets one thread produce a value that another thread consumes.

#pragma once
#include <testkit/testkit.h>
#include <future>

// Sets val on the promise p.
inline void send_value(std::promise<int>& p, int val) {
    TODO();
}
