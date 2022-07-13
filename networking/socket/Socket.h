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
    char buff[512];
    char s[INET6_ADDRSTRLEN];
    
    addrinfo* search_sock_fd(addrinfo *linked_list_of_ips, int &valid_sock_fd);

public:
    Socket();
    ~Socket();

    int get_sock_fd(std::string ip_canonname, std::string PORT, int BACKLOG);
    void set_sock_fd(int sock_fd);
    void set_new_fd(int sock_fd);
    std::string accept_new_connection(int sock_fd, int &new_fd);
    void respond_to_request(std::string http_response, int new_fd);
    std::string send_request_to_server(int sock_to_write, std::string http_req);
};
