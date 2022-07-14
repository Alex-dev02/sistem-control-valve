#pragma once

class NetworkStream {
public:
    NetworkStream(int sock_fd);
private:
    int m_sock_fd;
};