// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("01-10-ex06: shared_ptr Aliasing");

TEST(runner, "make_person creates a valid shared_ptr") {
    auto p = make_person("Alice", "Seattle", "98101");
    ASSERT_EQ(p->name, std::string("Alice"));
    ASSERT_EQ(p->address.city, std::string("Seattle"));
    ASSERT_EQ(p->address.zip, std::string("98101"));
}

TEST(runner, "get_address_ptr returns an alias to the address member") {
    auto p = make_person("Bob", "Portland", "97201");
    auto addr = get_address_ptr(p);
    ASSERT_EQ(addr->city, std::string("Portland"));
    ASSERT_EQ(addr->zip, std::string("97201"));
}

TEST(runner, "address alias shares ownership with person") {
    auto p = make_person("Carol", "Denver", "80201");
    auto addr = get_address_ptr(p);
    ASSERT_EQ(p.use_count(), 2L); // person + alias
    p.reset();
    // Person object is still alive because addr holds a shared reference
    ASSERT_EQ(addr->city, std::string("Denver"));
}

TEST(runner, "get_name_ptr returns an alias to the name member") {
    auto p = make_person("Dave", "Austin", "73301");
    auto name = get_name_ptr(p);
    ASSERT_EQ(*name, std::string("Dave"));
}

TEST(runner, "name alias keeps person alive") {
    auto p = make_person("Eve", "Miami", "33101");
    auto name = get_name_ptr(p);
    ASSERT_EQ(p.use_count(), 2L);
    p.reset();
    ASSERT_EQ(*name, std::string("Eve"));
}

TESTKIT_MAIN(runner)
