// Exercise 08: Launch N Threads
//
// PROBLEM:
//   Divide work across multiple threads for parallel computation.
//   Split a vector of integers into chunks, sum each chunk in a
//   separate thread, and combine the results.
//
// TODO:
//   Implement parallel_sum() that:
//   1. Splits the data vector into num_threads chunks.
//   2. Launches a thread for each chunk to compute its partial sum.
//   3. Joins all threads and returns the total sum.
//
// HINT:
//   Each thread should write its partial sum to a separate element
//   of a results vector (no synchronization needed since each thread
//   writes to a different index).
//
// WHY:
//   Dividing work across threads is the most common parallel pattern.
//   The key insight: if each thread writes to non-overlapping memory,
//   you don't need synchronization. This "embarrassingly parallel"
//   pattern is simple, safe, and scales well.

#pragma once
#include <testkit/testkit.h>
#include <vector>

// Returns the sum of all elements in data, using num_threads threads.
// num_threads is guaranteed to be >= 1.
inline long long parallel_sum(const std::vector<int>& data, int num_threads) {
    TODO();
}
