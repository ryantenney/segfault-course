// Exercise 03: Bounded Buffer
//
// PROBLEM:
//   A bounded buffer (also called a blocking queue) is a fixed-capacity
//   container where producers call put() to add items and consumers call
//   take() to remove them. If the buffer is full, put() blocks. If the
//   buffer is empty, take() blocks.
//
//   This is the classic producer-consumer pattern, and condition variables
//   are the standard tool for implementing it.
//
// TODO:
//   Implement BoundedBuffer<T>:
//     1. Constructor takes a size_t capacity.
//     2. put(T item) -- add item to the buffer; block if full.
//     3. take() -- remove and return the front item; block if empty.
//     4. size() -- return the current number of items.
//
// HINT:
//   - Use std::queue<T> as the internal container.
//   - Use two condition variables: one for "not full" and one for "not empty".
//   - put() waits on the "not full" CV, then pushes, then notifies "not empty".
//   - take() waits on the "not empty" CV, then pops, then notifies "not full".

#pragma once

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <queue>
#include <testkit/testkit.h>

template <typename T>
class BoundedBuffer {
    std::mutex mtx_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
    std::queue<T> queue_;
    std::size_t capacity_;

public:
    explicit BoundedBuffer(std::size_t capacity) : capacity_(capacity) {}

    // Add an item to the buffer. Blocks if the buffer is full.
    void put(T item) {
        TODO();
    }

    // Remove and return the front item. Blocks if the buffer is empty.
    T take() {
        TODO();
    }

    // Return the current number of items in the buffer.
    std::size_t size() {
        TODO();
    }
};
