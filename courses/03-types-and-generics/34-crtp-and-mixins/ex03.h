// Exercise 03: CRTP for Operator Generation
//
// Before C++20's spaceship operator (<=>), a common CRTP pattern was to
// define operator!= (and <, <=, >, >=) in a base class, in terms of
// operator== (and <) provided by the derived class.
//
// The base class:
//
//   template <typename Derived>
//   class EqualityComparable {
//   public:
//       friend bool operator!=(const Derived& a, const Derived& b) {
//           return !(a == b);
//       }
//   };
//
// The derived class only needs to define operator==. The CRTP base
// generates operator!= automatically.
//
// TODO:
//   1. Implement Token::operator== -- two Tokens are equal when both
//      type and value match.
//   2. Implement Coordinate::operator== -- two Coordinates are equal
//      when x, y, and z all match.
//   3. Implement Coordinate::operator< -- compare lexicographically
//      by (x, y, z).
//
// WHY:
//   This pattern was the standard way to reduce operator boilerplate
//   before C++20. Understanding it helps you read pre-C++20 code and
//   appreciate the design space that <=> was created to address.

#pragma once

#include <testkit/testkit.h>
#include <string>
#include <tuple>

// --- CRTP bases (provided, do not modify) ---

template <typename Derived>
class EqualityComparable {
public:
    friend bool operator!=(const Derived& a, const Derived& b) {
        return !(a == b);
    }
};

template <typename Derived>
class LessThanComparable {
public:
    friend bool operator>(const Derived& a, const Derived& b) {
        return b < a;
    }
    friend bool operator<=(const Derived& a, const Derived& b) {
        return !(b < a);
    }
    friend bool operator>=(const Derived& a, const Derived& b) {
        return !(a < b);
    }
};

// --- Student implements below ---

class Token : public EqualityComparable<Token> {
    std::string type_;
    std::string value_;

public:
    Token(std::string type, std::string value)
        : type_(std::move(type)), value_(std::move(value)) {}
    ~Token() = default;

    const std::string& type() const { return type_; }
    const std::string& value() const { return value_; }

    // Two Tokens are equal when both type and value match.
    friend bool operator==(const Token& a, const Token& b) {
        TODO();
    }
};

class Coordinate : public EqualityComparable<Coordinate>,
                   public LessThanComparable<Coordinate> {
    int x_;
    int y_;
    int z_;

public:
    Coordinate(int x, int y, int z) : x_(x), y_(y), z_(z) {}
    ~Coordinate() = default;

    int x() const { return x_; }
    int y() const { return y_; }
    int z() const { return z_; }

    // Two Coordinates are equal when x, y, and z all match.
    friend bool operator==(const Coordinate& a, const Coordinate& b) {
        TODO();
    }

    // Lexicographic ordering: compare x first, then y, then z.
    // Hint: std::tie(a.x_, a.y_, a.z_) < std::tie(b.x_, b.y_, b.z_)
    friend bool operator<(const Coordinate& a, const Coordinate& b) {
        TODO();
    }
};
