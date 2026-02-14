// Exercise 02 — Tests (read-only)
//
// Verifies that BankAccount has correct access specifiers and behavior.

#include <testkit/testkit.h>
#include <string>
#include "ex02.h"

static testkit::TestRunner runner("03-24-ex02: Add Access Specifiers");

TEST(runner, "can construct a BankAccount") {
    BankAccount acct("ACC-001", 100.0, 50.0);
    acct.account_id();  // gate: will throw TODO if not implemented
}

TEST(runner, "account_id returns the ID") {
    BankAccount acct("ACC-001", 100.0, 50.0);
    ASSERT_EQ(acct.account_id(), std::string("ACC-001"));
}

TEST(runner, "balance returns initial balance") {
    BankAccount acct("ACC-002", 250.0, 0.0);
    ASSERT_TRUE(acct.balance() == 250.0);
}

TEST(runner, "deposit increases balance") {
    BankAccount acct("ACC-003", 100.0, 0.0);
    bool ok = acct.deposit(50.0);
    ASSERT_TRUE(ok);
    ASSERT_TRUE(acct.balance() == 150.0);
}

TEST(runner, "deposit rejects non-positive amount") {
    BankAccount acct("ACC-004", 100.0, 0.0);
    ASSERT_FALSE(acct.deposit(0.0));
    ASSERT_FALSE(acct.deposit(-10.0));
    ASSERT_TRUE(acct.balance() == 100.0);
}

TEST(runner, "withdraw decreases balance") {
    BankAccount acct("ACC-005", 200.0, 0.0);
    bool ok = acct.withdraw(75.0);
    ASSERT_TRUE(ok);
    ASSERT_TRUE(acct.balance() == 125.0);
}

TEST(runner, "withdraw fails when insufficient funds") {
    BankAccount acct("ACC-006", 50.0, 0.0);
    ASSERT_FALSE(acct.withdraw(100.0));
    ASSERT_TRUE(acct.balance() == 50.0);
}

TEST(runner, "withdraw uses overdraft limit") {
    BankAccount acct("ACC-007", 50.0, 100.0);
    // Can withdraw up to balance + overdraft_limit = 150
    bool ok = acct.withdraw(120.0);
    ASSERT_TRUE(ok);
    ASSERT_TRUE(acct.balance() == -70.0);
}

TEST(runner, "withdraw respects overdraft boundary") {
    BankAccount acct("ACC-008", 50.0, 100.0);
    // Can withdraw exactly 150 (50 + 100 overdraft)
    ASSERT_TRUE(acct.withdraw(150.0));
    ASSERT_TRUE(acct.balance() == -100.0);
    // Cannot withdraw any more
    ASSERT_FALSE(acct.withdraw(1.0));
}

TESTKIT_MAIN(runner)
