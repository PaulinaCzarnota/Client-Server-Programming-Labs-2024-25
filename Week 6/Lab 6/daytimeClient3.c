#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 34687
#define BUFFER_SIZE 1024

void DieWithError(char *errorMessage) {
    perror(errorMessage);
    exit(1);
}

int main(int argc, char *argv[]) {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    ssize_t bytesReceived;

    // Verify usage
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Server IP>\n", argv[0]);
        exit(1);
    }

    // Create client socket
    if ((clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        DieWithError("socket() failed");
    }

    // Set up server address struct
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);

    // Convert and store IP address
    if (inet_pton(AF_INET, argv[1], &serverAddr.sin_addr) <= 0) {
        DieWithError("inet_pton() failed");
    }

    // Connect to server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        DieWithError("connect() failed");
    }

    printf("Connected to server at %s:%d\n", argv[1], SERVER_PORT);

    // Receive message from server
    bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived < 0) {
        DieWithError("recv() failed");
    }

    buffer[bytesReceived] = '\0'; // Null-terminate the received string
    printf("Received from server: %s\n", buffer);

    // Pause to keep connection open for inspection
    getchar();

    // Close client socket
    close(clientSocket);
    printf("Connection closed. Client exiting.\n");

    return 0;
}