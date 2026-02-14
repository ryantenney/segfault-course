// Exercise 02: Add Access Specifiers
//
// PROBLEM:
//   The BankAccount below is a struct — all members are public.
//   Anyone can directly modify balance_ or account_id_, bypassing
//   all validation. Good encapsulation uses access specifiers to
//   control what's exposed.
//
// TODO:
//   1. Change `struct` to `class`.
//   2. Add access specifiers so that:
//      - account_id_ and balance_ are private
//      - overdraft_limit_ is protected (for future subclasses)
//      - The constructor and all methods are public
//   3. Implement the methods as described.
//
// WHY:
//   Access specifiers are the primary tool for encapsulation in C++.
//   By making data private, you ensure the class controls its own
//   invariants — no outside code can put the object in an invalid state.

#pragma once

#include <testkit/testkit.h>
#include <string>

struct BankAccount {
    // TODO: Change struct to class and add access specifiers.
    // Data members (should become private / protected):
    std::string account_id_;
    double balance_;
    double overdraft_limit_;

    explicit BankAccount(std::string id, double initial_balance,
                         double overdraft_limit)
        : account_id_(std::move(id))
        , balance_(initial_balance)
        , overdraft_limit_(overdraft_limit) {}

    // Returns the account ID.
    std::string account_id() const {
        TODO();
    }

    // Returns the current balance.
    double balance() const {
        TODO();
    }

    // Deposit amount into the account. Amount must be positive.
    // Returns true on success, false if amount <= 0.
    bool deposit(double amount) {
        TODO();
    }

    // Withdraw amount from the account.
    // Withdrawal succeeds if balance - amount >= -overdraft_limit_.
    // Returns true on success, false if insufficient funds.
    bool withdraw(double amount) {
        TODO();
    }
};
