#pragma once

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include "network_stream.hpp"

class TcpClient {
public:
    TcpClient(std::string address, uint16_t port);
    TcpClient(int sock_fd);

    NetworkStream GetStream();
    void Close();
private:
    std::string m_address;
    uint16_t m_port;
    int m_sock_fd;

    addrinfo* GetSockAddresses();
    void SetSockFd(addrinfo* sock_addresses);
};
