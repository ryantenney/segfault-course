// Exercise 06: Shared Mutex for Readers
//
// PROBLEM:
//   When many threads read shared data and only a few write, using a
//   regular mutex serializes all access — even reads, which could
//   safely run concurrently. std::shared_mutex allows multiple
//   simultaneous readers OR one exclusive writer.
//
// TODO:
//   Implement ReadWriteMap with:
//   1. put(key, value) — acquires exclusive (write) lock, inserts or
//      updates the key-value pair.
//   2. get(key) — acquires shared (read) lock, returns the value.
//      Returns -1 if the key is not found.
//   3. contains(key) — acquires shared (read) lock, returns whether
//      the key exists.
//
// HINT:
//   Write lock: std::unique_lock<std::shared_mutex> lock(mtx_);
//   Read lock:  std::shared_lock<std::shared_mutex> lock(mtx_);
//
// WHY:
//   Read-heavy workloads benefit enormously from shared_mutex. If 90%
//   of operations are reads, a regular mutex forces them to run one at
//   a time. A shared_mutex lets all readers proceed in parallel.

#pragma once
#include <testkit/testkit.h>
#include <map>
#include <shared_mutex>
#include <string>

class ReadWriteMap {
    std::map<std::string, int> data_;
    mutable std::shared_mutex mtx_;

public:
    // Inserts or updates a key-value pair (exclusive lock).
    inline void put(const std::string& key, int value) {
        TODO();
    }

    // Returns the value for key, or -1 if not found (shared lock).
    inline int get(const std::string& key) const {
        TODO();
    }

    // Returns true if the key exists (shared lock).
    inline bool contains(const std::string& key) const {
        TODO();
    }
};
