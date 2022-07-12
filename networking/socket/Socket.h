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

class Socket {
    std::string PORT;
    int BACKLOG;
    int sock_fd;
    int new_fd;
    char buff[512];
    char s[INET6_ADDRSTRLEN];

    addrinfo* getValidSocket(addrinfo *linked_list_of_ips);

public:
    Socket(
        std::string PORT = "4000",
        int BACKLOG = 10
    );
    ~Socket();

    std::string accept_new_connection();
    void respond_to_request(std::string http_response);

};
