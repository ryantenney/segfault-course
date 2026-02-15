// Exercise 01 -- Tests (read-only)
//
// Verifies route registration and handler lookup.

#include <testkit/testkit.h>
#include "ex01.h"

#include <string>

static testkit::TestRunner runner("05-52-ex01: Route Registration");

TEST(runner, "find_handler returns nullptr for unknown route") {
    Router router;
    auto handler = router.find_handler("GET", "/unknown");
    ASSERT_TRUE(handler == nullptr);
}

TEST(runner, "add_route and find_handler for GET") {
    Router router;
    router.add_route("GET", "/hello", [](const Request&) {
        return Response{200, "Hello!"};
    });
    auto handler = router.find_handler("GET", "/hello");
    ASSERT_TRUE(handler != nullptr);
}

TEST(runner, "found handler produces correct response") {
    Router router;
    router.add_route("GET", "/hello", [](const Request&) {
        return Response{200, "Hello!"};
    });
    auto handler = router.find_handler("GET", "/hello");
    Request req{"GET", "/hello", ""};
    Response resp = handler(req);
    ASSERT_EQ(resp.status, 200);
    ASSERT_EQ(resp.body, std::string("Hello!"));
}

TEST(runner, "different methods on same path are separate routes") {
    Router router;
    router.add_route("GET", "/item", [](const Request&) {
        return Response{200, "get"};
    });
    router.add_route("POST", "/item", [](const Request&) {
        return Response{201, "post"};
    });

    auto get_h = router.find_handler("GET", "/item");
    auto post_h = router.find_handler("POST", "/item");
    ASSERT_TRUE(get_h != nullptr);
    ASSERT_TRUE(post_h != nullptr);

    Request req_get{"GET", "/item", ""};
    Request req_post{"POST", "/item", ""};
    ASSERT_EQ(get_h(req_get).body, std::string("get"));
    ASSERT_EQ(post_h(req_post).body, std::string("post"));
}

TEST(runner, "unregistered method returns nullptr") {
    Router router;
    router.add_route("GET", "/item", [](const Request&) {
        return Response{200, "ok"};
    });
    auto handler = router.find_handler("DELETE", "/item");
    ASSERT_TRUE(handler == nullptr);
}

TEST(runner, "multiple routes can be registered") {
    Router router;
    router.add_route("GET", "/a", [](const Request&) {
        return Response{200, "a"};
    });
    router.add_route("GET", "/b", [](const Request&) {
        return Response{200, "b"};
    });
    router.add_route("POST", "/c", [](const Request&) {
        return Response{201, "c"};
    });

    ASSERT_TRUE(router.find_handler("GET", "/a") != nullptr);
    ASSERT_TRUE(router.find_handler("GET", "/b") != nullptr);
    ASSERT_TRUE(router.find_handler("POST", "/c") != nullptr);
    ASSERT_TRUE(router.find_handler("GET", "/c") == nullptr);
}

TESTKIT_MAIN(runner)
