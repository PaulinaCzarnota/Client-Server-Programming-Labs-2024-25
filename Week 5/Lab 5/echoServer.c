#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"  // Include for error handling and utility functions
#include <unistd.h>

static const int MAXPENDING = 5;  // Maximum number of pending connections

int main(int argc, char *argv[]) {
    char sendbuffer[BUFSIZE];  // Buffer to send messages back to the client
    char recvbuffer[BUFSIZE];  // Buffer to receive messages from the client
    int numBytes = 0;          // Variable to count the number of bytes received

    // Check command line arguments
    if (argc != 2) {
        DieWithUserMessage("Parameters", "<Server Port>");  // Display error message if arguments are incorrect
    }

    // Assign server port from command line argument
    in_port_t servPort = atoi(argv[1]);

    // Create server socket
    int servSock;
    if ((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        DieWithSystemMessage("socket() failed");  // Handle socket creation error
    }

    // Set up server address structure
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));  // Zero out the structure
    servAddr.sin_family = AF_INET;           // Set address family to IPv4
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Bind to all available interfaces
    servAddr.sin_port = htons(servPort);     // Convert port number to network byte order

    // Bind the server socket
    if (bind(servSock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0) {
        DieWithSystemMessage("bind() failed");  // Handle binding error
    }

    // Listen for incoming connections
    if (listen(servSock, MAXPENDING) < 0) {
        DieWithSystemMessage("listen() failed");  // Handle listen error
    }

    // Main server loop
    for (;;) {
        // Accept a new client connection
        int clntSock = accept(servSock, (struct sockaddr *) NULL, NULL);
        if (clntSock < 0) {
            DieWithSystemMessage("accept() failed");  // Handle acceptance error
        }

        // Receive data from the client
        while ((numBytes = recv(clntSock, recvbuffer, BUFSIZE - 1, 0)) > 0) {
            recvbuffer[numBytes] = '\0';  // Null-terminate the received string
            fputs(recvbuffer, stdout);     // Print the received message to stdout

            // Check for the termination condition
            if (strstr(recvbuffer, "\r\n") != NULL) {
                break;  // Exit loop if termination sequence is received
            }
        }

        // Handle receive errors
        if (numBytes < 0) {
            DieWithSystemMessage("recv() failed");  // Handle receive error
        }

        // Send the received message back to the client
        snprintf(sendbuffer, sizeof(sendbuffer), "%s", recvbuffer);  // Prepare message to send
        ssize_t numBytesSent = send(clntSock, sendbuffer, strlen(sendbuffer), 0);  // Send the message
        if (numBytesSent < 0) {
            DieWithSystemMessage("send() failed");  // Handle send error
        }

        // Close the client socket
        close(clntSock);
    }
}