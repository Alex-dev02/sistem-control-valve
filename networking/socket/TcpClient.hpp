#pragma once

class TcpClient {
public:
    TcpClient();

private:
    int m_sock_fd;
};
