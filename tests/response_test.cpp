#include <gtest/gtest.h>

#include <networking/response.hpp>

/*HTTP/1.1 200 OK
Date: Mon, 27 Jul 2009 12:28:53 GMT
Server: Apache/2.2.14 (Win32)
Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT
Content-Length: 88
Content-Type: text/html
Connection: Closed
*/
static const Response http_res(
    "HTTP/1.1 203 OK\nContent-Length: 7\nContent-Type: text/plain\n\nContent"
);

static Response iotdcp_res(
    "1 OK IotDCP/0.1\nLength 5\nSalut"
);

TEST(ResponseTest, GetProtocol) {
    ASSERT_EQ(
        Utils::Protocol::HTTP,
        http_res.GetProtocol()
    );

    ASSERT_EQ(
        Utils::Protocol::IotDCP,
        iotdcp_res.GetProtocol()
    );
}

TEST(ResponseTest, GetResponseCode) {
    ASSERT_EQ(
        203,
        http_res.GetReponseCode()
    );

    ASSERT_EQ(
        1,
        iotdcp_res.GetReponseCode()
    );

    Response http_res_(
        "HTTP/1.1 401 Not Authorized\nContent-Length: 7\nContent-Type: text/plain\n\nContent"
    );
    ASSERT_EQ(
        401,
        http_res_.GetReponseCode()
    );
}

TEST(ResponseTest, GetRawResponse) {
    ASSERT_EQ(
        "HTTP/1.1 203 OK\nContent-Length: 7\nContent-Type: text/plain\n\nContent",
        http_res.GetRawResponse()
    );
    ASSERT_EQ(
        "1 OK IotDCP/0.1\nLength 5\nSalut",
        iotdcp_res.GetRawResponse()
    );
}

TEST(ResponseTest, Successful) {
    ASSERT_TRUE(http_res.Successful());
    ASSERT_TRUE(iotdcp_res.Successful());

    Response http_res_(
        "HTTP/1.1 401 Not Authorized\nContent-Length: 7\nContent-Type: text/plain\n\nContent"
    );
    Response iotdcp_res_(
        "0 Server Error IotDCP/0.1\nLength 5\nSalut"
    );
    ASSERT_FALSE(http_res_.Successful());
    ASSERT_FALSE(iotdcp_res_.Successful());
}
