// Exercise 04 -- Tests (read-only)
//
// Verifies middleware chain execution around handlers.

#include <testkit/testkit.h>
#include "ex04.h"

#include <string>

static testkit::TestRunner runner("05-52-ex04: Middleware Integration");

TEST(runner, "dispatch without middleware works normally") {
    Router router;
    router.add_route("GET", "/hello", [](const Request&) {
        return Response{200, "world", {}};
    });
    Request req{"GET", "/hello", "", {}};
    Response resp = router.dispatch(req);
    ASSERT_EQ(resp.status, 200);
    ASSERT_EQ(resp.body, std::string("world"));
}

TEST(runner, "single middleware wraps handler") {
    Router router;
    router.add_route("GET", "/test", [](const Request&) {
        return Response{200, "ok", {}};
    });
    router.use([](Handler next) -> Handler {
        return [next](const Request& req) {
            Response resp = next(req);
            resp.headers["X-Middleware"] = "applied";
            return resp;
        };
    });
    Request req{"GET", "/test", "", {}};
    Response resp = router.dispatch(req);
    ASSERT_EQ(resp.body, std::string("ok"));
    ASSERT_EQ(resp.headers["X-Middleware"], std::string("applied"));
}

TEST(runner, "middleware can modify request before handler") {
    Router router;
    router.add_route("GET", "/echo-header", [](const Request& req) {
        auto it = req.headers.find("X-Added");
        std::string val = (it != req.headers.end()) ? it->second : "missing";
        return Response{200, val, {}};
    });
    router.use([](Handler next) -> Handler {
        return [next](const Request& req) {
            Request modified = req;
            modified.headers["X-Added"] = "by-middleware";
            return next(modified);
        };
    });
    Request req{"GET", "/echo-header", "", {}};
    Response resp = router.dispatch(req);
    ASSERT_EQ(resp.body, std::string("by-middleware"));
}

TEST(runner, "middleware execution order is correct") {
    Router router;
    router.add_route("GET", "/order", [](const Request&) {
        return Response{200, "handler", {}};
    });
    // First middleware added = outermost
    router.use([](Handler next) -> Handler {
        return [next](const Request& req) {
            Response resp = next(req);
            resp.body = "A(" + resp.body + ")";
            return resp;
        };
    });
    // Second middleware added = inner
    router.use([](Handler next) -> Handler {
        return [next](const Request& req) {
            Response resp = next(req);
            resp.body = "B(" + resp.body + ")";
            return resp;
        };
    });
    Request req{"GET", "/order", "", {}};
    Response resp = router.dispatch(req);
    ASSERT_EQ(resp.body, std::string("A(B(handler))"));
}

TEST(runner, "middleware does not run for 404") {
    Router router;
    bool middleware_ran = false;
    router.use([&middleware_ran](Handler next) -> Handler {
        return [next, &middleware_ran](const Request& req) {
            middleware_ran = true;
            return next(req);
        };
    });
    Request req{"GET", "/missing", "", {}};
    Response resp = router.dispatch(req);
    ASSERT_EQ(resp.status, 404);
    ASSERT_FALSE(middleware_ran);
}

TESTKIT_MAIN(runner)
