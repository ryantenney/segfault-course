// Exercise 01 — Tests (read-only)

#include <testkit/testkit.h>
#include "ex01.h"

static testkit::TestRunner runner("05-46-ex01: To/From Map");

TEST(runner, "to_map produces correct keys") {
    Person p{"Alice", 30, "alice@example.com"};
    auto m = to_map(p);
    ASSERT_EQ(m.size(), std::size_t(3));
    ASSERT_TRUE(m.count("name") == 1);
    ASSERT_TRUE(m.count("age") == 1);
    ASSERT_TRUE(m.count("email") == 1);
}

TEST(runner, "to_map produces correct values") {
    Person p{"Bob", 25, "bob@example.com"};
    auto m = to_map(p);
    ASSERT_EQ(m.at("name"), std::string("Bob"));
    ASSERT_EQ(m.at("age"), std::string("25"));
    ASSERT_EQ(m.at("email"), std::string("bob@example.com"));
}

TEST(runner, "from_map reconstructs person") {
    std::map<std::string, std::string> m = {
        {"name", "Charlie"}, {"age", "35"}, {"email", "charlie@test.com"}
    };
    Person p = from_map(m);
    ASSERT_EQ(p.name, std::string("Charlie"));
    ASSERT_EQ(p.age, 35);
    ASSERT_EQ(p.email, std::string("charlie@test.com"));
}

TEST(runner, "round-trip preserves data") {
    Person original{"Dana", 42, "dana@corp.io"};
    auto m = to_map(original);
    Person restored = from_map(m);
    ASSERT_EQ(original.name, restored.name);
    ASSERT_EQ(original.age, restored.age);
    ASSERT_EQ(original.email, restored.email);
}

TEST(runner, "from_map handles missing keys with defaults") {
    std::map<std::string, std::string> m;
    Person p = from_map(m);
    ASSERT_EQ(p.name, std::string(""));
    ASSERT_EQ(p.age, 0);
    ASSERT_EQ(p.email, std::string(""));
}

TESTKIT_MAIN(runner)
