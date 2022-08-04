#include <gtest/gtest.h>

#include "../networking/tcp/tcp_client.hpp"

TEST(TcpClientTest, GetStream) {
    static TcpClient client("4000");
    static TcpClient second_client(client.GetStream());
    ASSERT_LT(
        0,
        client.GetStream()
    );
    ASSERT_LT(
        0,
        second_client.GetStream()
    );
}
