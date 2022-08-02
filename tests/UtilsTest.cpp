#include <gtest/gtest.h>

#include "../networking/communication/Utils.hpp"

TEST(UtilsTest, ResponseCodeToString) {
    ASSERT_EQ(
        "200 OK",
        Utils::ResponseCodeToString(200)
    );
    ASSERT_EQ(
        "299 OK",
        Utils::ResponseCodeToString(299)
    );
    ASSERT_EQ(
        "250 OK",
        Utils::ResponseCodeToString(250)
    );
    ASSERT_EQ(
        "401 Not Authorized",
        Utils::ResponseCodeToString(401)
    );
    ASSERT_EQ(
        "404 Not Found",
        Utils::ResponseCodeToString(404)
    );
    ASSERT_EQ(
        "500 Server Error",
        Utils::ResponseCodeToString(500)
    );
    ASSERT_EQ(
        "509 Server Error",
        Utils::ResponseCodeToString(509)
    );
    ASSERT_EQ(
        "0 Server Error",
        Utils::ResponseCodeToString(0)
    );
    ASSERT_EQ(
        "1 OK",
        Utils::ResponseCodeToString(1)
    );
    ASSERT_EQ(
        "2 Not Found",
        Utils::ResponseCodeToString(2)
    );
    ASSERT_EQ(
        "3 Not Authorized",
        Utils::ResponseCodeToString(3)
    );
}
