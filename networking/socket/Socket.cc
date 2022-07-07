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

void serverAcceptLoop(int sock_fd, int BACKLOG) {
    int new_sock;
    while (1) {
        if(listen(sock_fd, BACKLOG) == -1)
            std::cerr << "Could not listen()\n";
        sockaddr peer_adr;
        socklen_t peer_addr_size = sizeof(sockaddr);
        new_sock = accept(sock_fd, &peer_adr, &peer_addr_size);
        if (new_sock != -1)
            std::cout << "New sock accepted\n";
        send(new_sock, "Hai salut", 9, 0);

    }
}

Socket::Socket(std::string PORT, int BACKLOG, std::string server, std::string message, int max_data_size):
    PORT(PORT),
    BACKLOG(BACKLOG),
    server(server),
    message(message),
    max_data_size(max_data_size)
{
    int sock_fd, new_fd;

    // first we have to find an available ip address on the local machine
    // so we set the criteria for our desired ip
    addrinfo hints, *result;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC; // compatible with IPv4 and IPv6
    hints.ai_protocol = 0; // whatever protocol
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
