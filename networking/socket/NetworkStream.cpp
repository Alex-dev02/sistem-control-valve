#include "NetworkStream.hpp"

#include <unistd.h>

NetworkStream::NetworkStream(int sock_fd): 
    m_sock_fd(sock_fd)
{}

void NetworkStream::Close() {
    close(m_sock_fd);
}
