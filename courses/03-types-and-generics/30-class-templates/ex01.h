// Exercise 01: Generic Stack
//
// PROBLEM:
//   A stack is one of the most fundamental data structures.  Your job is
//   to implement a generic Stack<T> backed by std::vector<T>.
//
// TODO:
//   1. Implement push() -- add an element to the top of the stack.
//   2. Implement pop()  -- remove the top element; throw std::out_of_range
//      if the stack is empty.
//   3. Implement top()  -- return a const reference to the top element;
//      throw std::out_of_range if the stack is empty.
//   4. Implement empty() -- return true if the stack has no elements.
//   5. Implement size()  -- return the number of elements.
//
// WHY:
//   Class templates let you write a single implementation that works for
//   any type T.  The compiler generates a separate class for each T you
//   actually use (e.g., Stack<int>, Stack<std::string>).

#pragma once

#include <testkit/testkit.h>
#include <stdexcept>
#include <vector>

template<typename T>
class Stack {
    std::vector<T> data_;

public:
    // Push a value onto the top of the stack.
    void push(const T& value) {
        TODO();
    }

    // Remove the top element. Throws std::out_of_range if empty.
    void pop() {
        TODO();
    }

    // Return a const reference to the top element.
    // Throws std::out_of_range if empty.
    const T& top() const {
        TODO();
    }

    // Return true if the stack is empty.
    bool empty() const {
        TODO();
    }

    // Return the number of elements in the stack.
    std::size_t size() const {
        TODO();
    }
};
