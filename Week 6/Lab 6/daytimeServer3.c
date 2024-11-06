#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 34687 // Port the server listens on

void DieWithError(char *errorMessage) {
    perror(errorMessage);
    exit(1);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char *message = "Daytime Server Response\n";
    socklen_t clientLen = sizeof(clientAddr);

    // Create server socket
    if ((serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        DieWithError("socket() failed");
    }

    // Set up server address struct
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    // Bind socket to the address and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        DieWithError("bind() failed");
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) < 0) {
        DieWithError("listen() failed");
    }

    printf("Daytime server running on port %d. Waiting for connections...\n", PORT);

    // Accept client connection
    if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLen)) < 0) {
        DieWithError("accept() failed");
    }

    printf("Connection accepted from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

    // Send message to the client
    if (send(clientSocket, message, strlen(message), 0) != strlen(message)) {
        DieWithError("send() failed");
    }

    printf("Message sent to client. Pausing to keep connection open for inspection...\n");

    // Hold connection open for `netstat` observations
    getchar();

    // Close client and server sockets
    close(clientSocket);
    close(serverSocket);

    printf("Connection closed. Server shutting down.\n");

    return 0;
}