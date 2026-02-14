// Exercise 08: Non-Copyable RAII
//
// PROBLEM:
//   If an RAII class that owns a resource (file handle, heap memory,
//   mutex lock) is copied, both the original and the copy think they
//   own the resource. When both destructors run, the resource is
//   released twice — double-free, double-close, double-unlock.
//
// TODO:
//   Implement UniqueBuffer — an RAII wrapper around a dynamically
//   allocated char array. Make it non-copyable by deleting the copy
//   constructor and copy assignment operator. Implement a static
//   method that demonstrates why copying would be a bug.
//
// WHY:
//   Most RAII types should be non-copyable (or use move semantics,
//   which we'll cover later). Deleting copy operations is a simple
//   way to prevent accidental double-ownership bugs.

#pragma once
#include <cstring>
#include <string>
#include <testkit/testkit.h>

// Tracks active allocations for testing.
struct BufferTracker {
    static inline int active = 0;
};

class UniqueBuffer {
    // TODO: Add members:
    //   char* data_  — pointer to the allocated buffer
    //   int   size_  — size of the buffer
public:
    // Allocate a buffer of the given size, filled with the given char.
    UniqueBuffer(int size, char fill) {
        TODO();
        // HINT:
        //   data_ = new char[size];
        //   size_ = size;
        //   std::memset(data_, fill, size);
        //   BufferTracker::active++;
    }

    // Deallocate the buffer.
    ~UniqueBuffer() {
        // TODO: delete[] data_; BufferTracker::active--;
    }

    // Copying is deleted — both copies would own the same buffer,
    // leading to double-free when both destructors run.
    UniqueBuffer(const UniqueBuffer&) = delete;
    UniqueBuffer& operator=(const UniqueBuffer&) = delete;

    // Return the size of the buffer.
    int size() const {
        TODO();
    }

    // Return the character at the given index.
    char at(int index) const {
        TODO();
    }

    // Set the character at the given index.
    void set(int index, char c) {
        TODO();
    }

    // Return the buffer contents as a std::string.
    std::string as_string() const {
        TODO();
    }
};

// Return a string explaining why copying a UniqueBuffer would be a bug.
// This is a conceptual exercise — return the correct answer.
inline std::string why_no_copy() {
    TODO();
    // Return one of:
    //   "double free"
    //   "memory leak"
    //   "data race"
    //
    // HINT: If both the original and the copy call delete[] on the same
    //       pointer in their destructors, that's a double free.
}
