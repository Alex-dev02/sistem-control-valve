#include <gtest/gtest.h>

#include "../networking/tcp/TcpClient.hpp"

TEST(TcpClientTest, GetStream) {
    TcpClient client("4000");
    client.Close();
}
