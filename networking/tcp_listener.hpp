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

#include "tcp_client.hpp"

class TcpListener {
public:
    TcpListener(std::string address, uint16_t port);
    
    void Start();
    void Stop();
    TcpClient AcceptTcpClient();
    NetworkStream GetStream();
private:
    std::string m_address;
    uint16_t m_port;
    int m_sock_fd;

    addrinfo* GetSockAddresses();
    void SetSockFd(addrinfo* sock_addresses);  
    void *GetInAddr(sockaddr *sa); 
};
