#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"  // Include practical error handling functions

int main(int argc, char *argv[]) {
    char recvbuffer[BUFSIZE]; // Buffer to hold received data
    int numBytes = 0;         // Number of bytes received

    // Check for the correct number of arguments
    if (argc < 3) {
        DieWithUserMessage("Parameter(s)", "<Server Address> <Server Port>");
    }

    // Extract the server IP address and port number from the command line arguments
    char *servIP = argv[1];
    in_port_t servPort = atoi(argv[2]); // Convert port argument to an integer

    // Create a reliable, stream socket using TCP
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        DieWithSystemMessage("socket() failed");
    }

    // Construct the server address structure
    struct sockaddr_in servAddr;            
    memset(&servAddr, 0, sizeof(servAddr)); // Zero out structure
    servAddr.sin_family = AF_INET;          // IPv4 address family

    // Convert address from text to binary form
    int rtnVal = inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);
    if (rtnVal == 0) {
        DieWithUserMessage("inet_pton() failed", "invalid address string");
    } else if (rtnVal < 0) {
        DieWithSystemMessage("inet_pton() failed");
    }

    servAddr.sin_port = htons(servPort); // Convert port to network byte order

    // Establish the connection to the server
    if (connect(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        DieWithSystemMessage("connect() failed");
    }

    // Receive data from the server
    while ((numBytes = recv(sock, recvbuffer, BUFSIZE - 1, 0)) > 0) {
        recvbuffer[numBytes] = '\0'; // Null-terminate the received data
        fputs(recvbuffer, stdout);    // Print the received data to stdout
    }

    // Check for errors during receiving
    if (numBytes < 0) {
        DieWithSystemMessage("recv() failed");
    }

    fputc('\n', stdout); // Print a final line feed

    close(sock); // Close the socket
    exit(0);     // Exit the program
}