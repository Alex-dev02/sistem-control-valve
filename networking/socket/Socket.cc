#include "Socket.h"

#include <memory>
#include <iostream>

addrinfo* Socket::search_sock_fd(addrinfo *linked_list_of_ips, int &valid_sock_fd) {
    addrinfo *ip;
    int one;
    for (ip = linked_list_of_ips; ip != NULL; ip = ip->ai_next) {
        //getting a socket descriptor
        valid_sock_fd = socket(ip->ai_family, ip->ai_socktype, ip->ai_protocol);
        if (valid_sock_fd == -1)
            continue; // invalid socket

        if (setsockopt(valid_sock_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int)) == -1) {
            std::cerr << "Faild to setsockopt\n";
            exit(1);
        }

        if (bind(valid_sock_fd, ip->ai_addr, ip->ai_addrlen) == 0) {
            return ip; // found a valid socket and binded to it
        }
    }
    return NULL;
}

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

std::string Socket::accept_new_connection(int sock_fd, int &new_fd) {
    struct sockaddr_storage their_addr;
    socklen_t sin_size = sizeof their_addr;

    new_fd = accept(sock_fd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd != -1)
        std::cout << "New sock accepted\n";
    inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
    int bytes = recv(new_fd, buff, 511, 0);
    buff[bytes] = '\0';
    return buff;
}


void Socket::respond_to_request(std::string http_response, int new_fd) {
    int err = send(new_fd, http_response.c_str(), http_response.length(), 0);
    if (err == -1)
        std::cerr << "Failed to send res " << gai_strerror(err) << "\n";
    close(new_fd);
}

int Socket::get_sock_fd(std::string ip_canonname, std::string PORT, int BACKLOG) {
    int valid_sock_fd;
    addrinfo hints;
    addrinfo *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC; // compatible with IPv4 and IPv6
    hints.ai_flags = AI_PASSIVE; // can bind() and accept() connections
    if (ip_canonname != "")
        hints.ai_canonname = (char*)(ip_canonname.c_str());

    // now that we set the criteria, we must get the linked list of available
    // ips with getaddrinfo()

    int err;

    err = getaddrinfo(NULL, PORT.c_str(), &hints, &result);
    if (err != 0)
        std::cerr << "getaddrinfo: " << gai_strerror(err) << '\n';

    // now that we have the ips in the 'result' var, we must loop through it
    addrinfo *ip = search_sock_fd(result, valid_sock_fd);
    if (ip == NULL){
        std::cerr << "Could not bind\n";
        exit(1);
    }

    // free *ip?

    freeaddrinfo(result);

    if (listen(valid_sock_fd, BACKLOG) == -1 ) {
        perror("listen");
        exit(1);
    }

    return valid_sock_fd;
}

void Socket::send_request_to_server(int sock_to_write, std::string http_req) {
    write(sock_to_write, http_req.c_str(), http_req.length());
    close(sock_to_write);
}

Socket::Socket() {}

Socket::~Socket() {}
