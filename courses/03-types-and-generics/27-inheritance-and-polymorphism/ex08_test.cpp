// Exercise 08 -- Tests (read-only)

#include <testkit/testkit.h>
#include <cmath>
#include <memory>
#include <string>

#include "ex08.h"

static testkit::TestRunner runner("03-27-ex08: Protected Members");

static bool approx_eq(double a, double b, double epsilon = 0.001) {
    return std::abs(a - b) < epsilon;
}

TEST(runner, "SavingsAccount inherits owner and balance") {
    SavingsAccount sa("Alice", 1000.0, 0.05);
    sa.add_interest();  // gate on TODO()
    ASSERT_EQ(sa.owner(), std::string("Alice"));
    // After interest, should not be original value
    ASSERT_FALSE(approx_eq(sa.balance(), 1000.0));
}

TEST(runner, "SavingsAccount add_interest increases balance correctly") {
    SavingsAccount sa("Bob", 1000.0, 0.05);
    sa.add_interest();
    ASSERT_TRUE(approx_eq(sa.balance(), 1050.0));
}

TEST(runner, "SavingsAccount add_interest compounds") {
    SavingsAccount sa("Carol", 1000.0, 0.10);
    sa.add_interest();  // 1100
    sa.add_interest();  // 1210
    ASSERT_TRUE(approx_eq(sa.balance(), 1210.0));
}

TEST(runner, "SavingsAccount with zero rate does not change balance") {
    SavingsAccount sa("Dave", 500.0, 0.0);
    sa.add_interest();
    ASSERT_TRUE(approx_eq(sa.balance(), 500.0));
}

TEST(runner, "CheckingAccount withdraw succeeds when funds sufficient") {
    CheckingAccount ca("Eve", 500.0);
    bool ok = ca.withdraw(200.0);
    ASSERT_TRUE(ok);
    ASSERT_TRUE(approx_eq(ca.balance(), 300.0));
}

TEST(runner, "CheckingAccount withdraw fails when insufficient funds") {
    CheckingAccount ca("Frank", 100.0);
    bool ok = ca.withdraw(150.0);
    ASSERT_FALSE(ok);
    ASSERT_TRUE(approx_eq(ca.balance(), 100.0));  // unchanged
}

TEST(runner, "create_savings returns a polymorphic Account") {
    auto acct = create_savings("Grace", 2000.0, 0.03);
    ASSERT_EQ(acct->owner(), std::string("Grace"));
    ASSERT_TRUE(approx_eq(acct->balance(), 2000.0));
}

TEST(runner, "create_checking returns a polymorphic Account") {
    auto acct = create_checking("Hank", 750.0);
    ASSERT_EQ(acct->owner(), std::string("Hank"));
    ASSERT_TRUE(approx_eq(acct->balance(), 750.0));
}

TESTKIT_MAIN(runner)
