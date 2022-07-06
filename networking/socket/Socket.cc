#include "Socket.h"

#include <iostream>

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void Socket::bindSocketToIP(addrinfo *serv_info, int &yes){
    for(ip = serv_info; ip != NULL; ip = ip->ai_next) {
        if ((sockfd = socket(ip->ai_family, ip->ai_socktype,
                ip->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, ip->ai_addr, ip->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }
}

void Socket::acceptConnectionLoop() {
    while(1) {  // main accept() loop
        socklen_t sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("server: got connection from %s\n", s);

        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener
            if (send(new_fd, "Hello, world!", 13, 0) == -1)
                perror("send");
            close(new_fd);
            exit(0);
        }
        close(new_fd);  // parent doesn't need this
    }
}

Socket::Socket(std::string PORT, int BACKLOG):
    PORT(PORT),
    BACKLOG(BACKLOG)
 {
    addrinfo sock_addr_info, *serv_info;
    struct sigaction sa;
    int serv_err;
    int yes = 1;

    memset(&sock_addr_info, 0, sizeof sock_addr_info);
    sock_addr_info.ai_family = AF_UNSPEC; // IPv4 / IPv6
    sock_addr_info.ai_socktype = SOCK_STREAM;
    sock_addr_info.ai_flags = AI_PASSIVE; // use my IP

    // get linked list of IPs assigned to host machine
    if ((serv_err = getaddrinfo(NULL, PORT.c_str(), &sock_addr_info, &serv_info)) != 0)
        std::cerr << "getaddrinfo: " + std::to_string(*gai_strerror(serv_err)); 

    bindSocketToIP(serv_info, yes);

    freeaddrinfo(serv_info);

    if (ip == NULL) {
        std::cerr << "server: failed to bind\n";
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    std::cout << ("server: waiting for connections...\n");

    acceptConnectionLoop();

}

Socket::~Socket() {}
