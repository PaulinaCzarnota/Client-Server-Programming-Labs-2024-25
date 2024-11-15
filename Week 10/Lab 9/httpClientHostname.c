#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "Practical.h"

#define BUFSIZE 512 // Define buffer size

/**
 * Establishes a connection to the given server using hostname and service.
 * @param host Hostname or address of the server.
 * @param service Port or service name.
 * @return Socket descriptor for the connection.
 */
int ConnectToServer(const char *host, const char *service) {
    struct addrinfo hints, *res, *p;
    int sockfd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;       // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;  // Stream socket

    int status = getaddrinfo(host, service, &hints, &res);
    if (status != 0) {
        DieWithUserMessage("getaddrinfo() failed", gai_strerror(status));
    }

    for (p = res; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) continue;

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == 0) break;

        close(sockfd);
    }

    freeaddrinfo(res);
    if (p == NULL) {
        DieWithUserMessage("Could not connect to", host);
    }

    return sockfd;
}

/**
 * Main function for the HTTP client application.
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        DieWithUserMessage("Usage", "<hostname> <service> <HTTP request>");
    }

    const char *host = argv[1];
    const char *service = argv[2];
    const char *request = argv[3];

    int sockfd = ConnectToServer(host, service);

    send(sockfd, request, strlen(request), 0);

    char buffer[BUFSIZE];
    ssize_t n;
    while ((n = recv(sockfd, buffer, BUFSIZE - 1, 0)) > 0) {
        buffer[n] = '\0';
        fputs(buffer, stdout);
    }

    close(sockfd);
    return 0;
}