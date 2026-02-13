// testkit — Single-header test framework for segfault-course
//
// Provides:
//   TODO()               — Throws not_implemented; test runner reports as "skipped"
//   TEST(runner, "name")  — Registers a test case with the runner
//   ASSERT_EQ / NE / TRUE / FALSE / THROWS / NO_THROW
//   TESTKIT_MAIN(runner)  — Generates main()
//
// Author: Ryan Tenney

#pragma once

#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace testkit {

// ---------------------------------------------------------------------------
// Exceptions
// ---------------------------------------------------------------------------

/// Thrown by the TODO() macro to signal unfinished code.
/// The test runner catches this and reports the test as "skipped."
class not_implemented : public std::exception {
public:
    const char* what() const noexcept override { return "not implemented"; }
};

/// Thrown by ASSERT_* macros when an assertion fails.
class assertion_error : public std::exception {
    std::string message_;
public:
    explicit assertion_error(std::string message) : message_(std::move(message)) {}
    const char* what() const noexcept override { return message_.c_str(); }
};

// ---------------------------------------------------------------------------
// TestRunner
// ---------------------------------------------------------------------------

struct TestCase {
    std::string name;
    std::function<void()> body;
};

class TestRunner {
    std::string suite_name_;
    std::vector<TestCase> tests_;

public:
    explicit TestRunner(std::string name) : suite_name_(std::move(name)) {}

    void add(std::string name, std::function<void()> body) {
        tests_.push_back({std::move(name), std::move(body)});
    }

    int run() {
        int passed = 0, failed = 0, skipped = 0;

        std::cout << "\n " << suite_name_ << "\n\n";

        for (const auto& test : tests_) {
            try {
                test.body();
                std::cout << "  \033[32m✓\033[0m " << test.name << "\n";
                ++passed;
            } catch (const not_implemented&) {
                std::cout << "  \033[33m○\033[0m " << test.name
                          << " \033[33m(not implemented)\033[0m\n";
                ++skipped;
            } catch (const assertion_error& e) {
                std::cout << "  \033[31m✗\033[0m " << test.name
                          << ": " << e.what() << "\n";
                ++failed;
            } catch (const std::exception& e) {
                std::cout << "  \033[31m✗\033[0m " << test.name
                          << ": unexpected exception: " << e.what() << "\n";
                ++failed;
            } catch (...) {
                std::cout << "  \033[31m✗\033[0m " << test.name
                          << ": unknown exception\n";
                ++failed;
            }
        }

        std::cout << "\n " << passed << " passed";
        if (failed > 0) std::cout << ", " << failed << " failed";
        if (skipped > 0) std::cout << ", " << skipped << " skipped";
        std::cout << "\n\n";

        // Return 0 if everything passed or was skipped (no failures).
        return failed > 0 ? 1 : 0;
    }
};

} // namespace testkit

// ---------------------------------------------------------------------------
// Macros
// ---------------------------------------------------------------------------

/// Helper for token pasting across macro expansion boundaries.
#define TESTKIT_CONCAT_IMPL(a, b) a##b
#define TESTKIT_CONCAT(a, b) TESTKIT_CONCAT_IMPL(a, b)

/// Placeholder for unfinished code. Throws testkit::not_implemented,
/// which the test runner catches and reports as "skipped."
#define TODO() throw ::testkit::not_implemented()

/// Registers a test case with the given runner.
///
///   static testkit::TestRunner runner("suite name");
///   TEST(runner, "descriptive test name") {
///       ASSERT_EQ(1 + 1, 2);
///   }
///
#define TEST(runner, name)                                                    \
    static void TESTKIT_CONCAT(testkit_fn_, __LINE__)();                     \
    [[maybe_unused]] static int TESTKIT_CONCAT(testkit_reg_, __LINE__) =     \
        ((runner).add(name, TESTKIT_CONCAT(testkit_fn_, __LINE__)), 0);      \
    static void TESTKIT_CONCAT(testkit_fn_, __LINE__)()

/// Generates main() that runs all registered tests and returns the exit code.
#define TESTKIT_MAIN(runner)                                                  \
    int main() { return (runner).run(); }

// ---------------------------------------------------------------------------
// Assertion macros
// ---------------------------------------------------------------------------

#define ASSERT_EQ(lhs, rhs)                                                  \
    do {                                                                      \
        const auto& testkit_lhs_ = (lhs);                                    \
        const auto& testkit_rhs_ = (rhs);                                    \
        if (!(testkit_lhs_ == testkit_rhs_)) {                               \
            std::ostringstream testkit_ss_;                                   \
            testkit_ss_ << "expected " << testkit_lhs_                        \
                        << " == " << testkit_rhs_;                            \
            throw ::testkit::assertion_error(testkit_ss_.str());              \
        }                                                                     \
    } while (0)

#define ASSERT_NE(lhs, rhs)                                                  \
    do {                                                                      \
        const auto& testkit_lhs_ = (lhs);                                    \
        const auto& testkit_rhs_ = (rhs);                                    \
        if (!(testkit_lhs_ != testkit_rhs_)) {                               \
            std::ostringstream testkit_ss_;                                   \
            testkit_ss_ << "expected " << testkit_lhs_                        \
                        << " != " << testkit_rhs_;                            \
            throw ::testkit::assertion_error(testkit_ss_.str());              \
        }                                                                     \
    } while (0)

#define ASSERT_TRUE(expr)                                                     \
    do {                                                                      \
        if (!(expr)) {                                                        \
            throw ::testkit::assertion_error(                                 \
                "expected true, got false: " #expr);                          \
        }                                                                     \
    } while (0)

#define ASSERT_FALSE(expr)                                                    \
    do {                                                                      \
        if ((expr)) {                                                         \
            throw ::testkit::assertion_error(                                 \
                "expected false, got true: " #expr);                          \
        }                                                                     \
    } while (0)

#define ASSERT_THROWS(expr, exception_type)                                   \
    do {                                                                      \
        bool testkit_caught_ = false;                                         \
        try { (expr); }                                                       \
        catch (const exception_type&) { testkit_caught_ = true; }             \
        catch (...) {}                                                        \
        if (!testkit_caught_) {                                               \
            throw ::testkit::assertion_error(                                 \
                "expected " #exception_type " to be thrown");                  \
        }                                                                     \
    } while (0)

/// ASSERT_NO_THROW re-throws not_implemented so TODO() inside the
/// expression still counts as "skipped" rather than a false pass.
#define ASSERT_NO_THROW(expr)                                                 \
    do {                                                                      \
        try { (expr); }                                                       \
        catch (const ::testkit::not_implemented&) { throw; }                  \
        catch (const std::exception& e) {                                     \
            throw ::testkit::assertion_error(                                 \
                std::string("expected no exception, but caught: ") +          \
                e.what());                                                    \
        }                                                                     \
        catch (...) {                                                         \
            throw ::testkit::assertion_error(                                 \
                "expected no exception, but one was thrown");                  \
        }                                                                     \
    } while (0)
