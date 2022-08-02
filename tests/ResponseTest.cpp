#include <gtest/gtest.h>

#include "../networking/communication/Response.hpp"

/*HTTP/1.1 200 OK
Date: Mon, 27 Jul 2009 12:28:53 GMT
Server: Apache/2.2.14 (Win32)
Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT
Content-Length: 88
Content-Type: text/html
Connection: Closed
*/
static Response http_res(
    "HTTP/1.1 200 OK\nContent-Length: 7\nContent-Type: text/plain\n\nContent",
    Utils::Protocol::HTTP
);

static Response iotdcp_res(
    "1 OK IotDCP/0.1\nLength 5\nSalut",
    Utils::Protocol::IotDCP
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
        200,
        http_res.GetReponseCode()
    );

    ASSERT_EQ(
        1,
        iotdcp_res.GetReponseCode()
    );
}
