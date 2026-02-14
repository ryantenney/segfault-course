// Exercise 04: Fix using-namespace Pollution
//
// PROBLEM:
//   The code below uses `using namespace std;` at namespace scope in a
//   header file. This dumps the entire std namespace into the global
//   namespace for every file that includes this header — a recipe for
//   name collisions and mysterious build errors.
//
// TODO:
//   1. Remove the `using namespace std;` directive.
//   2. Add specific `using` declarations OR fully qualify the std names
//      used in each function (string, vector, to_string, size_t).
//   3. Implement each function body.
//
// WHY:
//   `using namespace std;` in a header is one of the most common C++
//   antipatterns. It forces every consumer of the header to accept all
//   of std in their global scope, which can silently change which
//   overload gets called or cause ambiguous-name errors.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <vector>

// BAD: This pollutes every file that includes this header.
// TODO: Remove this and fix the code below to compile without it.
using namespace std;

namespace formatting {

inline string repeat_string(const string& s, int count) {
    TODO();
}

inline string join(const vector<string>& parts, const string& separator) {
    TODO();
}

inline string describe_size(const vector<int>& v) {
    TODO();
}

} // namespace formatting
