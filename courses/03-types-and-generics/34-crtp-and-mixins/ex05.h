// Exercise 05: Composable Policies
//
// Policy-based design lets you customize a class's behavior by passing
// template parameters that implement specific policies. Each policy is
// a small, focused class that handles one aspect of behavior.
//
// For example, a Buffer class might be parameterized by:
//   - StoragePolicy: how elements are stored (fixed array vs. dynamic)
//   - ThreadingPolicy: how concurrent access is handled (no-op vs. mutex)
//
//   template <typename StoragePolicy, typename ThreadingPolicy>
//   class Buffer : private StoragePolicy, private ThreadingPolicy { ... };
//
// The policies are "mixed in" via inheritance. The Buffer delegates
// storage operations to StoragePolicy and locking to ThreadingPolicy.
//
// TODO:
//   1. Implement FixedStorage<N>::store() -- store a value at the
//      given index.
//   2. Implement FixedStorage<N>::get() -- return the value at the
//      given index.
//   3. Implement FixedStorage<N>::capacity() -- return N.
//   4. Implement DynamicStorage::store() -- if index >= data size,
//      resize to index + 1 (fill with 0). Then store the value.
//   5. Implement DynamicStorage::get() -- return the value at the
//      given index (assume index is valid).
//   6. Implement DynamicStorage::capacity() -- return current size.
//
// WHY:
//   Policy-based design is a powerful alternative to runtime polymorphism.
//   The C++ standard library uses it extensively (allocators are policies).
//   It gives zero-overhead customization decided at compile time.

#pragma once

#include <testkit/testkit.h>
#include <array>
#include <vector>
#include <mutex>

// --- Threading policies (provided, do not modify) ---

class NoLocking {
public:
    void lock() {}
    void unlock() {}
};

class MutexLocking {
    std::mutex mtx_;

public:
    void lock() { mtx_.lock(); }
    void unlock() { mtx_.unlock(); }
};

// --- Storage policies (student implements) ---

template <std::size_t N>
class FixedStorage {
    std::array<int, N> data_{};

public:
    // Store value at index. Assume index < N.
    void store(std::size_t index, int value) {
        TODO();
    }

    // Return the value at index. Assume index < N.
    int get(std::size_t index) const {
        TODO();
    }

    // Return the fixed capacity N.
    std::size_t capacity() const {
        TODO();
    }
};

class DynamicStorage {
    std::vector<int> data_;

public:
    // Store value at index. If index >= current size, resize
    // the vector to (index + 1), filling new slots with 0.
    void store(std::size_t index, int value) {
        TODO();
    }

    // Return the value at index. Assume index < size.
    int get(std::size_t index) const {
        TODO();
    }

    // Return the current size of the internal vector.
    std::size_t capacity() const {
        TODO();
    }
};

// --- Scope guard (provided, do not modify) ---
// Ensures unlock() is called even if an exception is thrown.

template <typename Policy>
class ScopedLock {
    Policy& policy_;

public:
    explicit ScopedLock(Policy& p) : policy_(p) { policy_.lock(); }
    ~ScopedLock() { policy_.unlock(); }
    ScopedLock(const ScopedLock&) = delete;
    ScopedLock& operator=(const ScopedLock&) = delete;
};

// --- Buffer template (provided, do not modify) ---
// Composes a StoragePolicy and a ThreadingPolicy.

template <typename StoragePolicy, typename ThreadingPolicy>
class Buffer : private StoragePolicy, private ThreadingPolicy {
public:
    void put(std::size_t index, int value) {
        ScopedLock<ThreadingPolicy> guard(*this);
        StoragePolicy::store(index, value);
    }

    int read(std::size_t index) {
        ScopedLock<ThreadingPolicy> guard(*this);
        return StoragePolicy::get(index);
    }

    std::size_t capacity() const {
        return StoragePolicy::capacity();
    }
};

// Convenient type aliases.
using FixedBuffer = Buffer<FixedStorage<64>, NoLocking>;
using DynamicBuffer = Buffer<DynamicStorage, NoLocking>;
using ThreadSafeFixedBuffer = Buffer<FixedStorage<64>, MutexLocking>;
using ThreadSafeDynamicBuffer = Buffer<DynamicStorage, MutexLocking>;
