// Exercise 02 -- Tests (read-only)
//
// Verifies Router::dispatch() routes requests or returns 404.

#include <testkit/testkit.h>
#include "ex02.h"

#include <string>

static testkit::TestRunner runner("05-52-ex02: Router Dispatch");

TEST(runner, "dispatch returns handler response for matching route") {
    Router router;
    router.add_route("GET", "/hello", [](const Request&) {
        return Response{200, "world"};
    });
    Request req{"GET", "/hello", ""};
    Response resp = router.dispatch(req);
    ASSERT_EQ(resp.status, 200);
    ASSERT_EQ(resp.body, std::string("world"));
}

TEST(runner, "dispatch returns 404 for unknown route") {
    Router router;
    Request req{"GET", "/missing", ""};
    Response resp = router.dispatch(req);
    ASSERT_EQ(resp.status, 404);
    ASSERT_EQ(resp.body, std::string("Not Found"));
}

TEST(runner, "dispatch returns 404 for wrong method") {
    Router router;
    router.add_route("POST", "/data", [](const Request&) {
        return Response{201, "created"};
    });
    Request req{"GET", "/data", ""};
    Response resp = router.dispatch(req);
    ASSERT_EQ(resp.status, 404);
}

TEST(runner, "dispatch passes request to handler") {
    Router router;
    router.add_route("POST", "/echo", [](const Request& req) {
        return Response{200, req.body};
    });
    Request req{"POST", "/echo", "ping"};
    Response resp = router.dispatch(req);
    ASSERT_EQ(resp.status, 200);
    ASSERT_EQ(resp.body, std::string("ping"));
}

TEST(runner, "dispatch selects correct route among many") {
    Router router;
    router.add_route("GET", "/a", [](const Request&) {
        return Response{200, "route-a"};
    });
    router.add_route("GET", "/b", [](const Request&) {
        return Response{200, "route-b"};
    });
    router.add_route("POST", "/a", [](const Request&) {
        return Response{201, "post-a"};
    });

    ASSERT_EQ(router.dispatch(Request{"GET", "/a", ""}).body, std::string("route-a"));
    ASSERT_EQ(router.dispatch(Request{"GET", "/b", ""}).body, std::string("route-b"));
    ASSERT_EQ(router.dispatch(Request{"POST", "/a", ""}).body, std::string("post-a"));
}

TESTKIT_MAIN(runner)
