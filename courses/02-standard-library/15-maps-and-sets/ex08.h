// Exercise 08: Custom Hash Function
//
// When using a struct as a key in std::unordered_map, the standard library
// doesn't know how to hash it. You must provide:
//   1. An equality operator: operator== on your struct
//   2. A hash functor: a type with std::size_t operator()(const Key&) const
//
// A simple way to combine hash values for multiple fields:
//   std::size_t h1 = std::hash<Type1>{}(field1);
//   std::size_t h2 = std::hash<Type2>{}(field2);
//   return h1 ^ (h2 << 1);
//
// TODO:
//   1. Add operator== to the Point struct.
//   2. Implement the PointHash functor.
//   3. Implement build_point_map and lookup_point.

#pragma once

#include <testkit/testkit.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <cstddef>

struct Point {
    int x;
    int y;

    // Add operator== so that two Points with the same x and y are equal.
    // Do NOT mark this noexcept in the stub; add it after implementing.
    bool operator==(const Point& other) const {
        TODO();
    }
};

// Hash functor for Point.
// Combine the hashes of x and y using:
//   h1 ^ (h2 << 1)
// where h1 = hash<int>{}(p.x) and h2 = hash<int>{}(p.y).
struct PointHash {
    std::size_t operator()(const Point& p) const {
        TODO();
    }
};

// Type alias for convenience.
using PointMap = std::unordered_map<Point, std::string, PointHash>;

// Build an unordered_map with Point keys from a list of (Point, string) pairs.
inline PointMap build_point_map(
        const std::vector<std::pair<Point, std::string>>& entries) {
    TODO();
}

// Look up a point in the map. Return the associated string if found,
// or "not found" if the point is not in the map.
inline std::string lookup_point(const PointMap& m, Point p) {
    TODO();
}
