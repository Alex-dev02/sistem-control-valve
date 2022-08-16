#include <gtest/gtest.h>

#include <networking/http.hpp>

static const HTTP http;

// Get Version Unit Tests

TEST(HTTPTests, CheckVersion) {
    EXPECT_EQ("1.1", http.GetVersion());
}

// Create Response Unit Tests

TEST(HTTPTests, CreateOKResponse) {
    Response response = http.CreateResponse(Utils::HTTPResponseCode::H_OK, "OK");
    EXPECT_EQ(
        "HTTP/1.1 200 OK\nContent-Length: 2\nContent-Type: text/plain\n\nOK",
        response.GetRawResponse()
    );
}

TEST(HTTPTests, CreateServErrResponse) {
    Response response = http.CreateResponse(Utils::HTTPResponseCode::H_ServErr, "Not ok");
    EXPECT_EQ(
        "HTTP/1.1 500 Server Error\nContent-Length: 6\nContent-Type: text/plain\n\nNot ok",
        response.GetRawResponse()
    );
}

TEST(HTTPTests, CreateNotFoundResponse) {
    Response response = http.CreateResponse(Utils::HTTPResponseCode::H_NotFound, "Not Found");
    EXPECT_EQ(
        "HTTP/1.1 404 Not Found\nContent-Length: 9\nContent-Type: text/plain\n\nNot Found",
        response.GetRawResponse()
    );
}

TEST(HTTPTests, CreateNotAuthResponse) {
    Response response = http.CreateResponse(Utils::HTTPResponseCode::H_NotAuth, "Not Auth");
    EXPECT_EQ(
        "HTTP/1.1 401 Not Authorized\nContent-Length: 8\nContent-Type: text/plain\n\nNot Auth",
        response.GetRawResponse()
    );
}

