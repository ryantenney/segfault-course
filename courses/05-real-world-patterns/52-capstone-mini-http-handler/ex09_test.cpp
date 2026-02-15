// Exercise 09 -- Tests (read-only)
//
// Verifies the complete end-to-end pipeline: raw request string ->
// parse -> route -> middleware -> handler -> serialized response.

#include <testkit/testkit.h>
#include "ex09.h"

#include <string>

static testkit::TestRunner runner("05-52-ex09: End-to-end");

TEST(runner, "full pipeline: simple GET") {
    Router router;
    router.add_route("GET", "/hello", [](const Request&) {
        return Response{200, {}, "world"};
    });

    std::string raw = "GET /hello HTTP/1.1\r\n\r\n";
    std::string result = handle_raw(router, raw);

    ASSERT_TRUE(result.find("HTTP/1.1 200 OK") == 0);
    ASSERT_TRUE(result.find("world") != std::string::npos);
}

TEST(runner, "full pipeline: POST with body") {
    Router router;
    router.add_route("POST", "/echo", [](const Request& req) {
        return Response{200, {}, req.body};
    });

    std::string raw = "POST /echo HTTP/1.1\r\n"
                      "Content-Type: text/plain\r\n"
                      "\r\n"
                      "hello there";
    std::string result = handle_raw(router, raw);

    ASSERT_TRUE(result.find("200 OK") != std::string::npos);
    ASSERT_TRUE(result.find("hello there") != std::string::npos);
}

TEST(runner, "full pipeline: 404 for unknown route") {
    Router router;
    std::string raw = "GET /missing HTTP/1.1\r\n\r\n";
    std::string result = handle_raw(router, raw);

    ASSERT_TRUE(result.find("404 Not Found") != std::string::npos);
}

TEST(runner, "full pipeline: 400 for bad request") {
    Router router;
    std::string raw = "";
    std::string result = handle_raw(router, raw);

    ASSERT_TRUE(result.find("400 Bad Request") != std::string::npos);
}

TEST(runner, "full pipeline: 500 when handler throws") {
    Router router;
    router.add_route("GET", "/fail", [](const Request&) -> Response {
        throw std::runtime_error("oops");
    });

    std::string raw = "GET /fail HTTP/1.1\r\n\r\n";
    std::string result = handle_raw(router, raw);

    ASSERT_TRUE(result.find("500 Internal Server Error") != std::string::npos);
    ASSERT_TRUE(result.find("oops") != std::string::npos);
}

TEST(runner, "full pipeline: middleware adds header") {
    Router router;
    router.add_route("GET", "/test", [](const Request&) {
        return Response{200, {}, "ok"};
    });
    router.use([](Handler next) -> Handler {
        return [next](const Request& req) {
            Response resp = next(req);
            resp.headers["X-Processed"] = "true";
            return resp;
        };
    });

    std::string raw = "GET /test HTTP/1.1\r\n\r\n";
    std::string result = handle_raw(router, raw);

    ASSERT_TRUE(result.find("200 OK") != std::string::npos);
    ASSERT_TRUE(result.find("X-Processed: true") != std::string::npos);
    ASSERT_TRUE(result.find("ok") != std::string::npos);
}

TEST(runner, "full pipeline: middleware execution order") {
    Router router;
    router.add_route("GET", "/chain", [](const Request&) {
        return Response{200, {}, "base"};
    });
    router.use([](Handler next) -> Handler {
        return [next](const Request& req) {
            Response resp = next(req);
            resp.body = "A(" + resp.body + ")";
            return resp;
        };
    });
    router.use([](Handler next) -> Handler {
        return [next](const Request& req) {
            Response resp = next(req);
            resp.body = "B(" + resp.body + ")";
            return resp;
        };
    });

    std::string raw = "GET /chain HTTP/1.1\r\n\r\n";
    std::string result = handle_raw(router, raw);

    ASSERT_TRUE(result.find("A(B(base))") != std::string::npos);
}

TEST(runner, "full pipeline: request header visible to handler") {
    Router router;
    router.add_route("GET", "/auth", [](const Request& req) {
        auto it = req.headers.find("Authorization");
        if (it == req.headers.end()) return Response{401, {}, "Unauthorized"};
        return Response{200, {}, "Welcome"};
    });

    std::string raw = "GET /auth HTTP/1.1\r\n"
                      "Authorization: Bearer token123\r\n"
                      "\r\n";
    std::string result = handle_raw(router, raw);

    ASSERT_TRUE(result.find("200 OK") != std::string::npos);
    ASSERT_TRUE(result.find("Welcome") != std::string::npos);
}

TESTKIT_MAIN(runner)
