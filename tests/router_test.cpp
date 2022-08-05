#include <gtest/gtest.h>

#include "../networking/router.hpp"

static Router router;

Response TestPath(Request request) {
    return Response("1 OK IotDCP/0.1\nLength 0\n");
}

Response OtherPath(Request request) {
    return Response("0 Server Error IotDCP/0.1\nLength 0\n");
}

TEST(RouterTest, AddPath) {
    ASSERT_TRUE(router.AddPath("/test", TestPath));
    ASSERT_TRUE(router.AddPath("/other/path", OtherPath));
}

TEST(RouterTest, GetResponse) {
    router.AddPath("/test", TestPath);
    router.AddPath("/other/path", OtherPath);
    ASSERT_EQ(
        (Response("1 OK IotDCP/0.1\nLength 0\n")).GetRawResponse(),
        router.GetResponse(Request("GET /test IotDCP/0.1")).GetRawResponse()
    );
    ASSERT_EQ(
        (Response("0 Server Error IotDCP/0.1\nLength 0\n")).GetRawResponse(),
        router.GetResponse(Request("GET /other/path IotDCP/0.1")).GetRawResponse()
    );
}
