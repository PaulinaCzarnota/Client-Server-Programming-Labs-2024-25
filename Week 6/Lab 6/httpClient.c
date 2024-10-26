#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 4096  // Buffer size for receiving data

void DieWithMessage(const char *message) {
    perror(message);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Server-IP> <Resource-Path>\n", argv[0]);
        fprintf(stderr, "Example: %s 93.184.216.34 /index.html\n", argv[0]);
        exit(1);
    }

    char *serverIP = argv[1];      // IP address of the server
    char *resourcePath = argv[2];  // Resource path to request (e.g., "/index.html")

    // Create TCP socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        DieWithMessage("socket() failed");
    }

    // Set up server address structure
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));       // Zero out structure
    serverAddr.sin_family = AF_INET;                  // IPv4
    serverAddr.sin_port = htons(80);                  // HTTP port 80

    // Convert IP address from string to binary form
    if (inet_pton(AF_INET, serverIP, &serverAddr.sin_addr.s_addr) <= 0) {
        DieWithMessage("inet_pton() failed");
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        DieWithMessage("connect() failed");
    }

    // Create HTTP GET request string
    char request[BUFFER_SIZE];
    snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", 
             resourcePath, serverIP);

    // Send HTTP request to server
    ssize_t numBytesSent = send(sockfd, request, strlen(request), 0);
    if (numBytesSent < 0) {
        DieWithMessage("send() failed");
    } else if (numBytesSent != strlen(request)) {
        DieWithMessage("send() sent unexpected number of bytes");
    }

    // Receive and print the response from the server
    char buffer[BUFFER_SIZE];
    ssize_t numBytes;
    printf("Received response:\n");

    // Loop to receive the entire response
    while ((numBytes = recv(sockfd, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[numBytes] = '\0';  // Null-terminate the received data
        printf("%s", buffer);     // Print the response chunk
    }

    if (numBytes < 0) {
        DieWithMessage("recv() failed");
    }

    // Close socket and exit
    close(sockfd);
    return 0;
}