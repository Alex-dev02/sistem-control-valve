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
    TcpListener(std::string port, std::string address = "");
    
    void Start();
    void Stop();
    TcpClient AcceptTcpClient();
private:
    std::string m_address;
    std::string m_port;
    int m_sock_fd;

    addrinfo* GetSockAddresses();
    void SetSockFd(addrinfo* sock_addresses);  
    void *GetInAddr(sockaddr *sa); 
};
