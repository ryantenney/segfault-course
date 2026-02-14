// Exercise 07: Deadlock Identification
//
// PROBLEM:
//   The broken_transfer() function below has a classic deadlock bug:
//   it locks account A then account B, but another thread might lock
//   B then A — and both threads wait forever.
//
//   Your job: implement safe_transfer() that avoids deadlock by
//   locking both mutexes simultaneously with std::scoped_lock.
//
// TODO:
//   Implement safe_transfer() that:
//   1. Uses std::scoped_lock to lock both account mutexes at once.
//   2. If `from` has sufficient balance, subtracts amount and adds
//      it to `to`. Return true.
//   3. If insufficient balance, return false without modifying either.
//
// WHY:
//   Deadlock is insidious: it may not happen in testing but surfaces
//   under load in production. The fix is simple — never acquire locks
//   in an inconsistent order. std::scoped_lock does this for you.

#pragma once
#include <testkit/testkit.h>
#include <mutex>

class Account {
    int balance_;
    mutable std::mutex mtx_;

public:
    explicit Account(int initial) : balance_(initial) {}

    std::mutex& mutex() const { return mtx_; }
    int balance() const { return balance_; }
    void add(int amount) { balance_ += amount; }
    void subtract(int amount) { balance_ -= amount; }
};

// BAD: This function can deadlock! (Do not use — for demonstration only.)
// Thread 1: broken_transfer(A, B, 10) — locks A, then B
// Thread 2: broken_transfer(B, A, 10) — locks B, then A
// Both threads block waiting for the other's lock → deadlock.
//
// inline void broken_transfer(Account& from, Account& to, int amount) {
//     std::lock_guard<std::mutex> lock_from(from.mutex());
//     std::lock_guard<std::mutex> lock_to(to.mutex());
//     from.subtract(amount);
//     to.add(amount);
// }

// SAFE: Use std::scoped_lock to lock both mutexes without deadlock.
// Returns true if transfer succeeded, false if insufficient funds.
inline bool safe_transfer(Account& from, Account& to, int amount) {
    TODO();
}
