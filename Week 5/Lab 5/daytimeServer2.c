#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 5000
#define BUFFER_SIZE 1024

void DieWithMessage(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    time_t currentTime;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        DieWithMessage("socket() failed");
    }

    // Configure server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        DieWithMessage("bind() failed");
    }

    // Listen for connections
    if (listen(sockfd, 5) < 0) {
        DieWithMessage("listen() failed");
    }

    // Accept a connection
    socklen_t clientLen = sizeof(clientAddr);
    if ((newsockfd = accept(sockfd, (struct sockaddr *) &clientAddr, &clientLen)) < 0) {
        DieWithMessage("accept() failed");
    }

    // Get current time and send to client
    currentTime = time(NULL);
    snprintf(buffer, sizeof(buffer), "Current time: %s", ctime(&currentTime));
    send(newsockfd, buffer, strlen(buffer), 0);

    // Close sockets
    close(newsockfd);
    close(sockfd);
    return 0;
}