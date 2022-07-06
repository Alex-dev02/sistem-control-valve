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
    int BACKLOG;
    int sockfd, new_fd;
    addrinfo hints, *servinfo, *p;
    sockaddr_storage their_addr;
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    void bindSocketToIP();
    void acceptConnectionLoop();
public:
    Socket(std::string PORT = "4000", int BACKLOG = 10);
    ~Socket();
};
