#include "TcpClient.hpp"

#include <iostream>

TcpClient::TcpClient(std::string address, std::string port):
    m_address(address),
    m_port(port) {

    addrinfo* addresses = GetSockAddresses();
    SetSockFd(addresses);
    freeaddrinfo(addresses);
}

TcpClient::TcpClient(int sock_fd):
    m_sock_fd(sock_fd)
{}

addrinfo* TcpClient::GetSockAddresses() {
    addrinfo hints;
    addrinfo *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    int err = getaddrinfo(
        m_address.empty() ? NULL : m_address.c_str(), 
        m_port.c_str(),
        &hints,
        &result
    );

    if (err != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(err) << '\n';
        exit(1);
    }
    return result;
}

void TcpClient::SetSockFd(addrinfo* sock_addresses) {
    addrinfo* address;
    for (address = sock_addresses; address != NULL; address = address->ai_next) {
        if ((m_sock_fd = socket(address->ai_family, address->ai_socktype, address->ai_protocol)) == -1){
            std::cerr << "client: socket\n";
            continue;
        }

        if (connect(m_sock_fd, address->ai_addr, address->ai_addrlen) == -1) {
            close(m_sock_fd);
            std::cerr << "client: connect\n";
        }
        break;
    }

    if (address == NULL){
        std::cerr << "client: failed to connect\n";
        exit(2);
    }
}

int TcpClient::GetStream() {
    return m_sock_fd;
}

void TcpClient::Close() {
    close(m_sock_fd);
}
