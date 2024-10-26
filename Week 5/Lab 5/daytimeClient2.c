#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void DieWithMessage(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Server-IP>\n", argv[0]);
        exit(1);
    }

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        DieWithMessage("socket() failed");
    }

    // Configure server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        DieWithMessage("connect() failed");
    }

    // Receive the message from the server
    ssize_t bytesReceived = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived < 0) {
        DieWithMessage("recv() failed");
    }

    buffer[bytesReceived] = '\0';  // Null-terminate the string
    printf("Received: %s", buffer);

    // Close socket
    close(sockfd);
    return 0;
}