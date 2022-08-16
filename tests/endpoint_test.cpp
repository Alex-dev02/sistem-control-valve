#include <gtest/gtest.h>

#include <networking/endpoint.hpp>

static const Endpoint endpoint("127.0.0.1", 4000);
static const Endpoint second_endpoint("168.172.15.1", 5000);

TEST(EndpointTests, GetIPAddress) {
    EXPECT_EQ(endpoint.GetIPAddress(), "127.0.0.1");
    EXPECT_EQ(second_endpoint.GetIPAddress(), "168.172.15.1");

}

TEST(EndpointTests, GetPort) {
    EXPECT_EQ(endpoint.GetPort(), 4000);
    EXPECT_EQ(second_endpoint.GetPort(), 5000);
}

TEST(EndpointTests, OperatorEQ) {
    Endpoint third_endpoint("127.0.0.1", 4000);

    EXPECT_TRUE(endpoint == third_endpoint);
    EXPECT_FALSE(endpoint == second_endpoint);
}
