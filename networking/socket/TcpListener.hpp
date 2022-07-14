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

#include "TcpClient.hpp"

class TcpListener {
public:
    TcpListener(std::string m_address, std::string m_port);
    void Start();
    void Stop();
    // should return a client
    TcpClient AcceptTcpClient();
private:
    std::string m_address;
    std::string m_port;
    int m_sock_fd;

    addrinfo* GetSockAddresses();
    void SetSockFd(addrinfo* sock_addresses);
    
    addrinfo* search_sock_fd(addrinfo *linked_list_of_ips, int &valid_sock_fd);
};
