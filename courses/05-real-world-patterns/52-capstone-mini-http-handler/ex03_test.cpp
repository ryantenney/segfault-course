// Exercise 03 -- Tests (read-only)
//
// Verifies path parameter extraction from route patterns.

#include <testkit/testkit.h>
#include "ex03.h"

#include <string>

static testkit::TestRunner runner("05-52-ex03: Path Parameters");

TEST(runner, "exact path match still works") {
    Router router;
    router.add_route("GET", "/health", [](const Request&) {
        return Response{200, "ok"};
    });
    Response resp = router.dispatch(Request{"GET", "/health", "", {}});
    ASSERT_EQ(resp.status, 200);
    ASSERT_EQ(resp.body, std::string("ok"));
}

TEST(runner, "single path parameter is extracted") {
    Router router;
    router.add_route("GET", "/users/:id", [](const Request& req) {
        auto it = req.params.find("id");
        if (it == req.params.end()) return Response{500, "no id"};
        return Response{200, it->second};
    });
    Response resp = router.dispatch(Request{"GET", "/users/42", "", {}});
    ASSERT_EQ(resp.status, 200);
    ASSERT_EQ(resp.body, std::string("42"));
}

TEST(runner, "multiple path parameters are extracted") {
    Router router;
    router.add_route("GET", "/users/:uid/posts/:pid", [](const Request& req) {
        auto uid = req.params.find("uid");
        auto pid = req.params.find("pid");
        if (uid == req.params.end() || pid == req.params.end())
            return Response{500, "missing"};
        return Response{200, uid->second + ":" + pid->second};
    });
    Response resp = router.dispatch(Request{"GET", "/users/7/posts/99", "", {}});
    ASSERT_EQ(resp.status, 200);
    ASSERT_EQ(resp.body, std::string("7:99"));
}

TEST(runner, "wrong segment count returns 404") {
    Router router;
    router.add_route("GET", "/users/:id", [](const Request&) {
        return Response{200, "ok"};
    });
    Response resp = router.dispatch(Request{"GET", "/users/1/extra", "", {}});
    ASSERT_EQ(resp.status, 404);
}

TEST(runner, "literal segment mismatch returns 404") {
    Router router;
    router.add_route("GET", "/users/:id", [](const Request&) {
        return Response{200, "ok"};
    });
    Response resp = router.dispatch(Request{"GET", "/items/1", "", {}});
    ASSERT_EQ(resp.status, 404);
}

TEST(runner, "method mismatch returns 404") {
    Router router;
    router.add_route("GET", "/users/:id", [](const Request&) {
        return Response{200, "ok"};
    });
    Response resp = router.dispatch(Request{"POST", "/users/1", "", {}});
    ASSERT_EQ(resp.status, 404);
}

TESTKIT_MAIN(runner)
