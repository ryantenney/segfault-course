// Exercise 06 -- Tests (read-only)
//
// Verifies type-state builder: build() only compiles after set_url().
// The compile-time check is gated behind a runtime TODO() call so
// unfinished code shows as "skipped" rather than a compile error.

#include <testkit/testkit.h>
#include <type_traits>
#include "ex06.h"

static testkit::TestRunner runner("05-43-ex06: Type-State Builder");

TEST(runner, "set_url transitions to HasUrl=true") {
    TypedRequestBuilder<false> b;
    auto b2 = b.set_url("/api");
    // b2 should be TypedRequestBuilder<true>
    static_assert(std::is_same_v<decltype(b2), TypedRequestBuilder<true>>,
                  "set_url must return TypedRequestBuilder<true>");
    ASSERT_TRUE(true);
}

TEST(runner, "set_method preserves HasUrl state") {
    TypedRequestBuilder<false> b;
    auto b2 = b.set_method("GET");
    static_assert(std::is_same_v<decltype(b2), TypedRequestBuilder<false>>,
                  "set_method on <false> must return <false>");

    TypedRequestBuilder<true> bt{TypedRequestBuilder<false>{}.set_url("/x")};
    auto b3 = bt.set_method("POST");
    static_assert(std::is_same_v<decltype(b3), TypedRequestBuilder<true>>,
                  "set_method on <true> must return <true>");
    ASSERT_TRUE(true);
}

TEST(runner, "build works after set_url") {
    // Gate: set_url must work first
    TypedRequestBuilder<false>{}.set_url("/test");

    auto r = TypedRequestBuilder<false>()
                 .set_method("POST")
                 .set_url("/api/data")
                 .set_body("payload")
                 .build();
    ASSERT_EQ(r.method, std::string("POST"));
    ASSERT_EQ(r.url, std::string("/api/data"));
    ASSERT_EQ(r.body, std::string("payload"));
}

TEST(runner, "build works with only url set") {
    // Gate: set_url must work first
    TypedRequestBuilder<false>{}.set_url("/test");

    auto r = TypedRequestBuilder<false>()
                 .set_url("/health")
                 .build();
    ASSERT_EQ(r.url, std::string("/health"));
    ASSERT_EQ(r.method, std::string(""));
    ASSERT_EQ(r.body, std::string(""));
}

TEST(runner, "chaining through set_url and set_body") {
    // Gate: set_url must work first
    TypedRequestBuilder<false>{}.set_url("/test");

    auto r = TypedRequestBuilder<false>()
                 .set_url("/items")
                 .set_body("{}")
                 .build();
    ASSERT_EQ(r.url, std::string("/items"));
    ASSERT_EQ(r.body, std::string("{}"));
}

TEST(runner, "set_method then set_url then build") {
    // Gate: set_url must work first
    TypedRequestBuilder<false>{}.set_url("/test");

    auto r = TypedRequestBuilder<false>()
                 .set_method("DELETE")
                 .set_url("/items/42")
                 .build();
    ASSERT_EQ(r.method, std::string("DELETE"));
    ASSERT_EQ(r.url, std::string("/items/42"));
}

TESTKIT_MAIN(runner)
