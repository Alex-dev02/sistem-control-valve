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
    std::string server;
    std::string PORT;
    int BACKLOG; // the maximum pending requests
    int max_data_size;
    int sockfd, new_fd;
    addrinfo *ip;
    sockaddr_storage their_addr;
    char s[INET6_ADDRSTRLEN];

    std::string message;

    void bindSocketToIP(addrinfo *serv_info, int &yes);
    void bindClientSocketToIP(addrinfo *serv_info);
    void acceptConnectionLoop();
    void createServer();
    void createClient();
public:
    Socket(
        std::string PORT = "4000",
        int BACKLOG = 10,
        std::string server = "",
        std::string message = "",
        int max_data_size = 256
    );
    ~Socket();
};
