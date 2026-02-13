// Exercise 01: Include Guards
//
// PROBLEM:
//   This header has no include guards. If any translation unit includes
//   it more than once (directly or via other headers), the compiler sees
//   duplicate definitions of `struct Point` and reports an error.
//
// TODO:
//   1. Add traditional include guards using the macro name EX01_H:
//        #ifndef EX01_H
//        #define EX01_H
//        ... (existing contents) ...
//        #endif
//
//   2. Implement the two functions below so the tests pass.
//
// WHY:
//   In C++, #include is textual substitution — the preprocessor copies
//   the header contents into each file that includes it. Without guards,
//   a header included twice in the same translation unit causes
//   "redefinition" errors.

struct Point {
    int x;
    int y;
};

// Returns the sum of two integers.
inline int add(int a, int b) {
    TODO();
}

// Returns the squared distance between two points.
inline int distance_squared(Point p1, Point p2) {
    TODO();
}
