#pragma once

class NetworkStream {
public:
    NetworkStream(int sock_fd);

    void Close();
private:
    int m_sock_fd;
};