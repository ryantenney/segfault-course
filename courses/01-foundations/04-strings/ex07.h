// Exercise 07: Dangling View
//
// A string_view does NOT own the data it points to. If the underlying
// string is destroyed or modified, the view becomes a dangling reference.
//
// This is the most common mistake with string_view — and it's not caught
// by the compiler.
//
// EXAMPLE OF THE BUG:
//
//   std::string_view make_label(std::string_view prefix, int id) {
//       std::string result = std::string(prefix) + "-" + std::to_string(id);
//       return result;  // DANGLING! `result` is destroyed here
//   }
//
// The function builds a local std::string, implicitly converts it to a
// string_view, and returns that view. But the local string is destroyed
// when the function returns — the view now points to freed memory.
//
// TODO:
//   Implement each function so it returns valid (non-dangling) data.
//   Read the comments to understand what return type is appropriate.

#pragma once

#include <string>
#include <string_view>
#include <testkit/testkit.h>

// This function assembles a label like "item-42" from a prefix and an id.
// It must build a NEW string (concatenation always creates new data).
// Return type: std::string (the caller takes ownership).
inline std::string make_label(std::string_view prefix, int id) {
    TODO();
}

// Extract the first word (before the first space) from a sentence.
// If no space is found, return the entire sentence.
//
// HINT: You have two safe approaches:
//   a) Return std::string (always safe, but allocates)
//   b) Take std::string_view as parameter and return std::string_view
//      (safe because string_view::substr returns a sub-view, not a copy)
//
// Approach (b) is preferred — use string_view for both parameter and return.
inline std::string_view first_word(std::string_view sentence) {
    TODO();
}

// This function is provided as a reference — it's already correct.
// It takes a string_view and returns a sub-view. The data is owned by
// the caller, so the returned view is valid as long as the caller's
// string exists.
inline std::string_view trim_prefix(std::string_view sv, std::size_t n) {
    if (n >= sv.size()) return {};
    return sv.substr(n);
}
