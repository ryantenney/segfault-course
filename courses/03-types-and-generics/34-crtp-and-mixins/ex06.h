// Exercise 06: CRTP vs Virtual Dispatch
//
// This exercise compares two ways of achieving polymorphism:
//
//   1. Virtual dispatch: base class has virtual methods; derived classes
//      override them. Calls go through a vtable at runtime.
//
//   2. CRTP dispatch: base class is a template that static_cast's to the
//      derived class. Calls are resolved at compile time and can be inlined.
//
// The virtual version is provided. You implement the CRTP version with
// identical behavior.
//
// TODO:
//   1. Implement CrtpAdd::apply_impl(a, b) -- return a + b.
//   2. Implement CrtpMultiply::apply_impl(a, b) -- return a * b.
//   3. Implement the free function crtp_compute(op, x, y) that
//      calls op.apply(x, y).
//
// WHY:
//   Virtual dispatch is the right tool when the set of types is open
//   (plugins, user-defined classes). CRTP is better when all types are
//   known at compile time and you want maximum performance. Knowing both
//   patterns -- and when to choose each -- is essential.

#pragma once

#include <testkit/testkit.h>

// =====================================================
// PART A: Virtual dispatch (provided, do not modify)
// =====================================================

class VirtualOp {
public:
    virtual ~VirtualOp() = default;
    virtual int apply(int a, int b) const = 0;
};

class VirtualAdd : public VirtualOp {
public:
    int apply(int a, int b) const override { return a + b; }
};

class VirtualMultiply : public VirtualOp {
public:
    int apply(int a, int b) const override { return a * b; }
};

// Calls op->apply through virtual dispatch.
inline int virtual_compute(const VirtualOp& op, int x, int y) {
    return op.apply(x, y);
}

// =====================================================
// PART B: CRTP dispatch (student implements)
// =====================================================

// --- CRTP base (provided, do not modify) ---

template <typename Derived>
class CrtpOp {
public:
    int apply(int a, int b) const {
        return static_cast<const Derived*>(this)->apply_impl(a, b);
    }
};

// --- Student implements below ---

class CrtpAdd : public CrtpOp<CrtpAdd> {
public:
    // Return a + b.
    int apply_impl(int a, int b) const {
        TODO();
    }
};

class CrtpMultiply : public CrtpOp<CrtpMultiply> {
public:
    // Return a * b.
    int apply_impl(int a, int b) const {
        TODO();
    }
};

// Call op.apply(x, y) through CRTP dispatch.
template <typename Derived>
int crtp_compute(const CrtpOp<Derived>& op, int x, int y) {
    TODO();
}
