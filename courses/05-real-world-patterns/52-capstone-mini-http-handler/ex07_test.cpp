// Exercise 07 -- Tests (read-only)
//
// Verifies error handling: 400, 404, and 500 responses.

#include <testkit/testkit.h>
#include "ex07.h"

#include <stdexcept>
#include <string>

static testkit::TestRunner runner("05-52-ex07: Error Handling");

TEST(runner, "valid request returns handler response") {
    Router router;
    router.add_route("GET", "/ok", [](const Request&) {
        return Response{200, "fine"};
    });
    Response resp = router.dispatch(Request{"GET", "/ok", ""});
    ASSERT_EQ(resp.status, 200);
    ASSERT_EQ(resp.body, std::string("fine"));
}

TEST(runner, "empty method returns 400") {
    Router router;
    Response resp = router.dispatch(Request{"", "/path", ""});
    ASSERT_EQ(resp.status, 400);
    ASSERT_EQ(resp.body, std::string("Bad Request"));
}

TEST(runner, "empty path returns 400") {
    Router router;
    Response resp = router.dispatch(Request{"GET", "", ""});
    ASSERT_EQ(resp.status, 400);
    ASSERT_EQ(resp.body, std::string("Bad Request"));
}

TEST(runner, "unmatched route returns 404") {
    Router router;
    router.add_route("GET", "/exists", [](const Request&) {
        return Response{200, "here"};
    });
    Response resp = router.dispatch(Request{"GET", "/missing", ""});
    ASSERT_EQ(resp.status, 404);
    ASSERT_EQ(resp.body, std::string("Not Found"));
}

TEST(runner, "handler throwing std::exception returns 500 with message") {
    Router router;
    router.add_route("GET", "/crash", [](const Request&) -> Response {
        throw std::runtime_error("db connection failed");
    });
    Response resp = router.dispatch(Request{"GET", "/crash", ""});
    ASSERT_EQ(resp.status, 500);
    ASSERT_EQ(resp.body, std::string("db connection failed"));
}

TEST(runner, "handler throwing non-std exception returns 500") {
    Router router;
    router.add_route("GET", "/crash2", [](const Request&) -> Response {
        throw 42;
    });
    Response resp = router.dispatch(Request{"GET", "/crash2", ""});
    ASSERT_EQ(resp.status, 500);
    ASSERT_EQ(resp.body, std::string("Internal Server Error"));
}

TESTKIT_MAIN(runner)
