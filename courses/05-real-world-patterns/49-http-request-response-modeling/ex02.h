// Exercise 02: Status Code Enum
//
// HTTP responses carry a three-digit status code that indicates the
// result of the request. Status codes are grouped into categories:
//   1xx informational, 2xx success, 3xx redirect, 4xx client error,
//   5xx server error.
//
// TODO:
//   1. Implement is_success(code)      -- true for 200-299
//   2. Implement is_redirect(code)     -- true for 300-399
//   3. Implement is_client_error(code) -- true for 400-499
//   4. Implement is_server_error(code) -- true for 500-599
//   5. Implement reason_phrase(code)   -- return standard phrase for
//      common codes (200->"OK", 404->"Not Found", etc.)

#pragma once

#include <testkit/testkit.h>
#include <string>

// We model status codes as a simple int wrapper for flexibility.
// Common codes are provided as constants.
struct StatusCode {
    int code;

    explicit StatusCode(int c) : code(c) {}
};

inline bool is_success(StatusCode sc) {
    TODO();
}

inline bool is_redirect(StatusCode sc) {
    TODO();
}

inline bool is_client_error(StatusCode sc) {
    TODO();
}

inline bool is_server_error(StatusCode sc) {
    TODO();
}

// Return the standard reason phrase for well-known codes.
// At minimum handle: 200 OK, 201 Created, 204 No Content,
// 301 Moved Permanently, 302 Found, 304 Not Modified,
// 400 Bad Request, 401 Unauthorized, 403 Forbidden,
// 404 Not Found, 405 Method Not Allowed,
// 500 Internal Server Error, 502 Bad Gateway, 503 Service Unavailable.
// Return "Unknown" for unrecognized codes.
inline std::string reason_phrase(StatusCode sc) {
    TODO();
}
