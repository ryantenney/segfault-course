// Exercise 07: Static Member Per Instantiation
//
// PROBLEM:
//   Each instantiation of a class template is a distinct class with its
//   own static members.  Counter<int> and Counter<std::string> each have
//   their own independent count_ variable.
//
// TODO:
//   1. Add a static member variable `count_` (type int) to the Counter
//      class template, initialized to 0.
//   2. Implement increment() -- increase count_ by 1.
//   3. Implement count() -- return the current value of count_.
//   4. Implement reset() -- set count_ back to 0.
//
//   Don't forget to define the static member outside the class:
//     template<typename T>
//     int Counter<T>::count_ = 0;
//
// WHY:
//   Understanding that Counter<int>::count_ and Counter<double>::count_
//   are completely separate variables is key to understanding how the
//   compiler instantiates templates.  Each unique T produces a distinct
//   class with its own static storage.

#pragma once

#include <testkit/testkit.h>

template<typename T>
class Counter {
    // TODO: Add a static int member count_ here.

public:
    // Increment the counter for this type.
    static void increment() {
        TODO();
    }

    // Return the current count for this type.
    static int count() {
        TODO();
    }

    // Reset the counter for this type to 0.
    static void reset() {
        TODO();
    }
};

// TODO: Define the static member variable outside the class:
// template<typename T>
// int Counter<T>::count_ = 0;
