#include <iostream>

#include "TcpListener.hpp"

TcpListener::TcpListener(std::string m_address, std::string m_port):
    m_address(m_address),
    m_port(m_port)
{}


void TcpListener::Start() {
    addrinfo* sock_addresses = GetSockAddresses();
    SetSockFd(sock_addresses);
    freeaddrinfo(sock_addresses);
}

addrinfo* TcpListener::GetSockAddresses() {
    addrinfo hints;
    addrinfo *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC; // compatible with IPv4 and IPv6
    hints.ai_flags = AI_PASSIVE; // can bind() and accept() connections

    // now that we set the criteria, we must get the linked list of available
    // ips with getaddrinfo()

    int err = getaddrinfo(NULL, m_port.c_str(), &hints, &result);

    if (err != 0)
        std::cerr << "getaddrinfo: " << gai_strerror(err) << '\n';

    return result;
}

void TcpListener::SetSockFd(addrinfo* sock_addresses) {
    addrinfo *address;
    int one = 1;
    for (address = sock_addresses; address != NULL; address = address->ai_next) {
        //getting a socket descriptor
        m_sock_fd = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
        if (m_sock_fd == -1)
            continue; // invalid socket

        if (setsockopt(m_sock_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int)) == -1) {
            std::cerr << "Faild to setsockopt\n";
            exit(1);
        }

        if (bind(m_sock_fd, address->ai_addr, address->ai_addrlen) == 0) {
            break;// found a valid socket and binded to it
        }
    }
    if (address == nullptr) {
        std::cerr << "Could not bind\n";
        exit(1);
    }
    if (listen(m_sock_fd, 10) == -1 ) {
        std::cerr << "Could not listen()\n";
        exit(1);
    }
}

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
