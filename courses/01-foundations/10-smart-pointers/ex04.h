// Exercise 04: unique_ptr in Containers
//
// Standard containers like std::vector can hold unique_ptrs. Since unique_ptr
// is move-only, you must use std::move when inserting or transferring elements.
// This pattern is common for polymorphic collections or when objects are
// expensive to copy.
//
// TODO:
//   Implement the functions below. Use push_back with std::move to insert
//   unique_ptrs into vectors.

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <testkit/testkit.h>

struct Part {
    std::string code;
    explicit Part(std::string c) : code(std::move(c)) {}
};

// Create a vector of unique_ptr<Part> containing parts with the given codes.
inline std::vector<std::unique_ptr<Part>> make_parts(const std::vector<std::string>& codes) {
    TODO();
}

// Return the number of non-null parts in the vector.
inline std::size_t count_parts(const std::vector<std::unique_ptr<Part>>& parts) {
    TODO();
}

// Remove the last element from the vector and return it.
// Precondition: the vector is not empty.
inline std::unique_ptr<Part> pop_part(std::vector<std::unique_ptr<Part>>& parts) {
    TODO();
}

// Move all elements from `source` into `dest` (appending), leaving source empty.
inline void merge_parts(std::vector<std::unique_ptr<Part>>& source,
                        std::vector<std::unique_ptr<Part>>& dest) {
    TODO();
}
