#include "network_stream.hpp"

#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <string>

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
    if (err == -1)
        throw std::runtime_error("Failed to write: " + *strerror(err));
}

void NetworkStream::Close() {
    close(m_sock_fd);
}
