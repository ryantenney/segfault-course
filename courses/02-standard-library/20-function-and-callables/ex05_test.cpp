// Exercise 05 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex05.h"

#include <vector>

static testkit::TestRunner runner("02-20-ex05: Template Parameter vs Type Erasure");

TEST(runner, "apply_erased invokes std::function") {
    ASSERT_EQ(apply_erased([](int x) { return x * 2; }, 5), 10);
}

TEST(runner, "apply_erased works with a capturing lambda") {
    int offset = 100;
    ASSERT_EQ(apply_erased([&offset](int x) { return x + offset; }, 7), 107);
}

TEST(runner, "apply_template invokes a lambda") {
    ASSERT_EQ(apply_template([](int x) { return x * 3; }, 4), 12);
}

TEST(runner, "apply_template works with a capturing lambda") {
    int factor = 10;
    ASSERT_EQ(apply_template([&factor](int x) { return x * factor; }, 5), 50);
}

TEST(runner, "transform_all_erased transforms every element") {
    std::vector<int> input = {1, 2, 3, 4};
    auto result = transform_all_erased(input, [](int x) { return x * x; });
    ASSERT_EQ(result.size(), 4u);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 4);
    ASSERT_EQ(result[2], 9);
    ASSERT_EQ(result[3], 16);
}

TEST(runner, "transform_all_erased handles empty vector") {
    std::vector<int> input;
    auto result = transform_all_erased(input, [](int x) { return x; });
    ASSERT_EQ(result.size(), 0u);
}

TEST(runner, "transform_all_template transforms every element") {
    std::vector<int> input = {10, 20, 30};
    auto result = transform_all_template(input, [](int x) { return x + 1; });
    ASSERT_EQ(result.size(), 3u);
    ASSERT_EQ(result[0], 11);
    ASSERT_EQ(result[1], 21);
    ASSERT_EQ(result[2], 31);
}

TEST(runner, "both versions produce identical results") {
    std::vector<int> input = {5, 10, 15, 20};
    auto fn = [](int x) { return x / 5; };
    auto erased_result = transform_all_erased(input, fn);
    auto template_result = transform_all_template(input, fn);
    ASSERT_EQ(erased_result.size(), template_result.size());
    for (std::size_t i = 0; i < erased_result.size(); ++i) {
        ASSERT_EQ(erased_result[i], template_result[i]);
    }
}

TESTKIT_MAIN(runner)
