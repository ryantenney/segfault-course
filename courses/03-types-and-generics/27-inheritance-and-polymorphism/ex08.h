// Exercise 08: Protected Members
//
// `protected` members are accessible to the class itself and its derived
// classes, but not to outside code. This lets a base class share
// implementation details with its children without exposing them publicly.
//
// Access levels:
//   public:     accessible to everyone
//   protected:  accessible to the class and its derived classes
//   private:    accessible only to the class itself
//
// In this exercise, Account has a protected balance_ member. Derived
// classes can read and modify balance_ directly, but outside code can
// only access it through the public balance() getter.
//
// TODO:
//   1. Implement SavingsAccount::add_interest() — increases balance_
//      by balance_ * rate_ (e.g., 5% interest on $100 adds $5).
//   2. Implement CheckingAccount::withdraw() — decreases balance_ by
//      amount. Return true if successful. Return false (and don't
//      change balance_) if amount > balance_.
//   3. Implement create_savings() and create_checking() factory functions.

#pragma once

#include <memory>
#include <string>
#include <testkit/testkit.h>

class Account {
protected:
    double balance_;
    std::string owner_;

public:
    Account(std::string owner, double balance)
        : balance_(balance), owner_(std::move(owner)) {}

    virtual ~Account() = default;

    double balance() const { return balance_; }
    const std::string& owner() const { return owner_; }
};

// A savings account that earns interest.
class SavingsAccount : public Account {
    double rate_;

public:
    SavingsAccount(std::string owner, double balance, double rate)
        : Account(std::move(owner), balance), rate_(rate) {}

    double rate() const { return rate_; }

    // Add interest: balance_ += balance_ * rate_.
    // The balance_ member is accessible because it's protected in Account.
    void add_interest() {
        TODO();
    }
};

// A checking account that supports withdrawals.
class CheckingAccount : public Account {
public:
    CheckingAccount(std::string owner, double balance)
        : Account(std::move(owner), balance) {}

    // Withdraw `amount` from the account.
    // Return true if the withdrawal succeeded (amount <= balance_).
    // Return false if insufficient funds (don't change balance_).
    bool withdraw(double amount) {
        TODO();
    }
};

// Create a SavingsAccount and return it as a unique_ptr<Account>.
inline std::unique_ptr<Account> create_savings(
    std::string owner, double balance, double rate) {
    TODO();
}

// Create a CheckingAccount and return it as a unique_ptr<Account>.
inline std::unique_ptr<Account> create_checking(
    std::string owner, double balance) {
    TODO();
}
