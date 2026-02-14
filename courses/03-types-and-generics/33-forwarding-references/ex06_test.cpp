// Exercise 06 -- Tests (read-only)

#include <testkit/testkit.h>

#include "ex06.h"

static testkit::TestRunner runner("03-33-ex06: Factory Function");

TEST(runner, "make<Product> constructs correctly") {
    auto p = make<Product>("Widget", 9.99, 5);
    ASSERT_EQ(p.name, std::string("Widget"));
    ASSERT_EQ(p.price, 9.99);
    ASSERT_EQ(p.quantity, 5);
}

TEST(runner, "make<std::string> from count and char") {
    auto s = make<std::string>(3, 'z');
    ASSERT_EQ(s, std::string("zzz"));
}

TEST(runner, "make<Product> forwards rvalue string") {
    std::string name = "Gadget";
    auto p = make<Product>(std::move(name), 19.99, 10);
    ASSERT_EQ(p.name, std::string("Gadget"));
}

TEST(runner, "make_on_heap<Product> returns valid unique_ptr") {
    auto ptr = make_on_heap<Product>("Item", 4.50, 3);
    ASSERT_TRUE(ptr != nullptr);
    ASSERT_EQ(ptr->name, std::string("Item"));
    ASSERT_EQ(ptr->price, 4.50);
    ASSERT_EQ(ptr->quantity, 3);
}

TEST(runner, "make_on_heap<std::string> constructs on heap") {
    auto ptr = make_on_heap<std::string>("heap_string");
    ASSERT_TRUE(ptr != nullptr);
    ASSERT_EQ(*ptr, std::string("heap_string"));
}

TEST(runner, "make_on_heap<int> constructs int on heap") {
    auto ptr = make_on_heap<int>(42);
    ASSERT_TRUE(ptr != nullptr);
    ASSERT_EQ(*ptr, 42);
}

TESTKIT_MAIN(runner)
