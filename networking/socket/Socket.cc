#include "Socket.h"

#include <iostream>

addrinfo* getValidSocket(addrinfo *linked_list_of_ips, int &sock_fd) {
    addrinfo *ip;
    int one;
    for (ip = linked_list_of_ips; ip != NULL; ip = ip->ai_next) {
        //getting a socket descriptor
        sock_fd = socket(ip->ai_family, ip->ai_socktype, ip->ai_protocol);
        if (sock_fd == -1)
            continue; // invalid socket

        if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int)) == -1) {
            std::cerr << "Faild to setsockopt\n";
            exit(1);
        }

        if (bind(sock_fd, ip->ai_addr, ip->ai_addrlen) == 0)
            return ip; // found a valid socket and binded to it
    }
    return NULL;
}

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


void serverAcceptLoop(int sock_fd, int BACKLOG) {
    int new_sock;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];
    char buff[256];
    while (1) {
        sin_size = sizeof their_addr;
        if(listen(sock_fd, BACKLOG) == -1)
            std::cerr << "Could not listen()\n";
        new_sock = accept(sock_fd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_sock != -1)
            std::cout << "New sock accepted\n";
        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        recv(new_sock, buff, 255, 0);
        std::string mes = "HTTP/1.1 200 OK\r\nHost: 127.0.0.1:4000\r\nContent-Length: 4\r\nContent-Type: text/plain\r\n\r\npong\r\n";
        int err = send(new_sock, mes.c_str(), mes.length(), 0);
        if (err = -1)
            std::cerr << "Failed to send res " << gai_strerror(err) << "\n";
        close(new_sock);
        buff[256] = '\0';
        std::cout << buff;
    }
}

Socket::Socket(std::string PORT, int BACKLOG):
    PORT(PORT),
    BACKLOG(BACKLOG)
{
    std::cout << PORT << '\n';
    int sock_fd, new_fd;

    // first we have to find an available ip address on the local machine
    // so we set the criteria for our desired ip
    addrinfo hints, *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC; // compatible with IPv4 and IPv6
    hints.ai_flags = AI_PASSIVE; // can bind() and accept() connections

    // now that we set the criteria, we must get the linked list of available
    // ips with getaddrinfo()

    int err;

    err = getaddrinfo(NULL, PORT.c_str(), &hints, &result);
    if (err != 0)
        std::cerr << "getaddrinfo: " << gai_strerror(err) << '\n';

    // now that we have the ips in the 'result' var, we must loop through it
    addrinfo *ip = getValidSocket(result, sock_fd);
    if (ip == NULL){
        std::cerr << "Could not bind\n";
        exit(1);
    }

    freeaddrinfo(result);
    
    serverAcceptLoop(sock_fd, BACKLOG);
    
    close(sock_fd);

}

Socket::~Socket() {}
