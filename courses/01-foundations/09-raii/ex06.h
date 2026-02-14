// Exercise 06: Scope Guard
//
// PROBLEM:
//   Sometimes you need to run a cleanup action at scope exit, but you
//   don't want to write a full RAII class for it. A "scope guard" is
//   a generic RAII wrapper that runs any callable (lambda, function
//   pointer, etc.) in its destructor.
//
// TODO:
//   Implement ScopeGuard as a template class:
//   - Constructor: store the callable
//   - Destructor: invoke the callable
//   - Also implement the make_scope_guard helper function
//
// WHY:
//   Scope guards are a powerful generalization of RAII. Libraries like
//   Folly provide ScopeGuard, and C++26 may standardize something
//   similar. This pattern lets you write ad-hoc cleanup code without
//   creating a dedicated class.

#pragma once
#include <string>
#include <utility>
#include <testkit/testkit.h>

template<typename Func>
class ScopeGuard {
    // TODO: Add member(s) to store the callable
public:
    // Store the callable to execute on destruction.
    explicit ScopeGuard(Func fn) {
        TODO();
    }

    // Execute the stored callable.
    ~ScopeGuard() {
        // TODO: invoke the stored callable
    }

    // Non-copyable
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
};

// Helper function: creates a ScopeGuard from any callable.
// Uses template argument deduction so the caller doesn't need to
// spell out the lambda type.
template<typename Func>
ScopeGuard<Func> make_scope_guard(Func fn) {
    TODO();
}
