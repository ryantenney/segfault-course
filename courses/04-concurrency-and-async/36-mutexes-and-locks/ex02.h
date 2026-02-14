// Exercise 02: lock_guard Scope
//
// PROBLEM:
//   When transferring between two accounts, you need to lock each
//   account's mutex — but hold the lock only as long as needed.
//   lock_guard locks for its entire scope, so use braces to limit it.
//
// TODO:
//   Implement transfer() that:
//   1. Locks `from` and subtracts `amount` from its balance.
//   2. Locks `to` and adds `amount` to its balance.
//   Lock each account separately in its own scope — do not hold
//   both locks at the same time (we'll handle that in exercise 03).
//   Return true if the transfer succeeded (from had enough balance),
//   false otherwise.
//
// NOTE:
//   This simple approach (lock one, then the other) is safe here because
//   we never hold both locks simultaneously. If you needed both locks at
//   once, you'd need scoped_lock to avoid deadlock (see exercise 03).
//
// WHY:
//   Minimizing lock scope reduces contention and improves performance.
//   Holding a lock longer than necessary blocks other threads that need
//   the same mutex.

#pragma once
#include <testkit/testkit.h>
#include <mutex>

class GuardedAccount {
    int balance_;
    mutable std::mutex mtx_;

public:
    explicit GuardedAccount(int initial) : balance_(initial) {}

    // These are used by transfer() — the student must lock the mutex.
    std::mutex& mutex() const { return mtx_; }
    int balance() const { return balance_; }
    void add(int amount) { balance_ += amount; }
    void subtract(int amount) { balance_ -= amount; }
};

// Transfers amount from `from` to `to`.
// Returns true if from had sufficient balance, false otherwise.
// Lock each account in its own scope using lock_guard.
inline bool transfer(GuardedAccount& from, GuardedAccount& to, int amount) {
    TODO();
}
