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
    bool server;
    std::string PORT;
    int BACKLOG; // the maximum pending requests
    int sockfd, new_fd;
    addrinfo *ip;
    sockaddr_storage their_addr;
    char s[INET6_ADDRSTRLEN];

    void bindSocketToIP(addrinfo *serv_info, int &yes);
    void acceptConnectionLoop();
public:
    Socket(std::string PORT = "4000", int BACKLOG = 10);
    ~Socket();
};
