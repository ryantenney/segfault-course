// Exercise 07: Eliminate a Cast
//
// PROBLEM:
//   Sometimes the best cast is no cast at all. If you find yourself
//   needing a cast, it may indicate a design problem. Refactoring the
//   API to return the right type eliminates the cast entirely.
//
// TODO:
//   The initial design uses a void* "generic container" that requires
//   casts everywhere. Refactor the Container class to be a simple
//   type-safe template, eliminating all casts.
//
// WHY:
//   The safest code is code that doesn't need casts. Templates and
//   proper type design make C++ code both safer and more readable
//   than C-style void* patterns.

#pragma once
#include <string>
#include <testkit/testkit.h>

// BAD DESIGN (void* requires casts):
//
//   class Container {
//       void* data_;
//   public:
//       void store(void* ptr) { data_ = ptr; }
//       void* retrieve() { return data_; }
//   };
//
//   int x = 42;
//   Container c;
//   c.store(&x);
//   int* p = static_cast<int*>(c.retrieve());  // Cast needed!
//
// GOOD DESIGN (template, no casts needed):
//
//   template<typename T>
//   class Container {
//       T value_;
//   public:
//       void store(const T& val) { value_ = val; }
//       const T& retrieve() const { return value_; }
//   };

// TODO: Implement Container as a class template parameterized on T.
// - store(const T&) saves the value
// - retrieve() returns const T&
// No casts should appear anywhere in your implementation.
template<typename T>
class Container {
public:
    void store(const T& val) {
        TODO();
    }

    const T& retrieve() const {
        TODO();
    }
};

// Use a Container<int> to store and retrieve a value. No casts needed!
inline int store_and_get_int(int value) {
    TODO();
}

// Use a Container<std::string> to store and retrieve a value. No casts!
inline std::string store_and_get_string(const std::string& value) {
    TODO();
}
