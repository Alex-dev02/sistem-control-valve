#include <gtest/gtest.h>

#include <networking/endpoint.hpp>

static const Endpoint endpoint("127.0.0.1", 4000);
static const Endpoint second_endpoint("168.172.15.1", 5000);

TEST(EndpointTests, GetIPAddress) {
    EXPECT_EQ("127.0.0.1", endpoint.GetIPAddress());
    EXPECT_EQ("168.172.15.1", second_endpoint.GetIPAddress());

}

TEST(EndpointTests, GetPort) {
    EXPECT_EQ(4000, endpoint.GetPort());
    EXPECT_EQ(5000, second_endpoint.GetPort());
}

TEST(EndpointTests, OperatorEQ) {
    Endpoint third_endpoint("127.0.0.1", 4000);

    EXPECT_TRUE(endpoint == third_endpoint);
    EXPECT_FALSE(endpoint == second_endpoint);
}
