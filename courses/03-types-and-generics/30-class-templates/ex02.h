// Exercise 02: Member Functions Out-of-Line
//
// PROBLEM:
//   When class template member functions are defined inside the class body,
//   the class definition can become hard to read.  You can define them
//   outside the class body, but you need to repeat the template parameter
//   list and qualify the function name with the class name.
//
// TODO:
//   Move the member function bodies OUTSIDE the class body (below the
//   class definition).  The signatures are provided below the class as
//   stubs with TODO().
//
//   Syntax for out-of-line member function of a class template:
//
//     template<typename T>
//     ReturnType ClassName<T>::method_name(params) {
//         // body
//     }
//
// WHY:
//   Separating the class interface (declaration) from implementation
//   (definition) makes the class easier to read at a glance.  For class
//   templates, out-of-line definitions must still be in the header file
//   (the compiler needs to see them at instantiation time), but the
//   separation aids readability.

#pragma once

#include <testkit/testkit.h>
#include <stdexcept>
#include <vector>

template<typename T>
class Queue {
    std::vector<T> data_;

public:
    // Add an element to the back of the queue.
    void enqueue(const T& value);

    // Remove and return the front element.
    // Throws std::out_of_range if the queue is empty.
    T dequeue();

    // Return a const reference to the front element.
    // Throws std::out_of_range if the queue is empty.
    const T& front() const;

    // Return true if the queue is empty.
    bool empty() const;

    // Return the number of elements.
    std::size_t size() const;
};

// ---------------------------------------------------------------------------
// Out-of-line definitions -- implement these below
// ---------------------------------------------------------------------------

template<typename T>
void Queue<T>::enqueue(const T& value) {
    TODO();
}

template<typename T>
T Queue<T>::dequeue() {
    TODO();
}

template<typename T>
const T& Queue<T>::front() const {
    TODO();
}

template<typename T>
bool Queue<T>::empty() const {
    TODO();
}

template<typename T>
std::size_t Queue<T>::size() const {
    TODO();
}
