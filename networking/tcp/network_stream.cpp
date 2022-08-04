#include "network_stream.hpp"

#include <unistd.h>
#include <sys/socket.h>
#include <iostream>

NetworkStream::NetworkStream(int sock_fd): 
    m_sock_fd(sock_fd)
{}

std::string NetworkStream::Read() {
    char buff[512];
    int bytes = recv(m_sock_fd, buff, 512, 0);
    if (bytes == -1) {
        std::cerr << "Failed to recv()\n";
        return "";
    }
    buff[bytes] = '\0';
    return buff;
}

void NetworkStream::Write(std::string message) {
    int err = write(m_sock_fd, message.c_str(), message.length());
    if (err == -1) {
        std::cerr << "Failed to write\n";
    }
}

void NetworkStream::Close() {
    close(m_sock_fd);
}
