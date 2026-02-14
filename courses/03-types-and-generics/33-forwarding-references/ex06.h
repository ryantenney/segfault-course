// Exercise 06: Factory Function
//
// A factory function creates objects of a given type T by forwarding
// constructor arguments. This is the pattern behind std::make_unique
// and std::make_shared:
//
//   template <typename T, typename... Args>
//   std::unique_ptr<T> make_unique(Args&&... args) {
//       return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
//   }
//
// TODO:
//   1. Implement make<T>(args...): return a T constructed by perfectly
//      forwarding all arguments to T's constructor.
//
//   2. Implement make_on_heap<T>(args...): return a std::unique_ptr<T>
//      by constructing T on the heap with perfectly forwarded arguments.

#pragma once

#include <testkit/testkit.h>
#include <memory>
#include <string>
#include <utility>

// A type to verify forwarding behavior.
struct Product {
    std::string name;
    double price;
    int quantity;

    Product(std::string n, double p, int q)
        : name(std::move(n)), price(p), quantity(q) {}
};

// Create and return a T by perfectly forwarding constructor arguments.
template <typename T, typename... Args>
T make(Args&&... args) {
    TODO();
    // Hint: return T(std::forward<Args>(args)...);
}

// Create a T on the heap and return a unique_ptr to it.
template <typename T, typename... Args>
std::unique_ptr<T> make_on_heap(Args&&... args) {
    TODO();
    // Hint: return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    // Or: return std::make_unique<T>(std::forward<Args>(args)...);
}
