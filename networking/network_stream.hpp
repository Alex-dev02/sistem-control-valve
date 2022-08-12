#pragma once

#include <string>

class NetworkStream {
public:
    NetworkStream(int sock_fd);

    std::string Read();
    void Write(std::string message);
    void Close();
private:
    int m_sock_fd;
};