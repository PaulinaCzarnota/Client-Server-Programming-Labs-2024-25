#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"  // Assuming you have a Practical.h for error handling

#define BUFSIZE 1024  // Define buffer size for sending and receiving messages

int main(int argc, char *argv[]) {
    char recvbuffer[BUFSIZE];  // Buffer to store received messages
    char sendbuffer[BUFSIZE];  // Buffer to store message to send
    int numBytes = 0;          // Variable to count number of bytes received

    // Check command line arguments
    if (argc != 4) {
        DieWithUserMessage("Parameters", "<Server Address> <Server Port> <String Message>");
    }

    // Assign command line arguments to variables
    char *servIP = argv[1];           // Server IP address
    char *echoString = argv[3];       // Message to echo
    in_port_t servPort = atoi(argv[2]);  // Server port number

    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        DieWithSystemMessage("socket() failed");
    }

    // Set up server address structure
    struct sockaddr_in servAddr;  // Server address structure
    memset(&servAddr, 0, sizeof(servAddr));  // Zero out the structure
    servAddr.sin_family = AF_INET;  // Set the address family
    int rtnVal = inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);  // Convert IP address
    if (rtnVal == 0) {
        DieWithUserMessage("inet_pton() failed", "Invalid address string");
    } else if (rtnVal < 0) {
        DieWithSystemMessage("inet_pton() failed");
    }
    servAddr.sin_port = htons(servPort);  // Convert port number to network byte order

    // Connect to the server
    if (connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        DieWithSystemMessage("connect() failed");
    }

    // Prepare the message to send
    snprintf(sendbuffer, sizeof(sendbuffer), "%s\r\n", echoString);  // Append \r\n for protocol
    ssize_t numBytesSent = send(sock, sendbuffer, strlen(sendbuffer), 0);  // Send the message
    if (numBytesSent < 0) {
        DieWithSystemMessage("send() failed");
    }

    // Receive the echoed message from the server
    while ((numBytes = recv(sock, recvbuffer, BUFSIZE - 1, 0)) > 0) {
        recvbuffer[numBytes] = '\0';  // Null-terminate the received string
        fputs(recvbuffer, stdout);     // Print the received message
    }
    if (numBytes < 0) {
        DieWithSystemMessage("recv() failed");
    }

    fputc('\n', stdout);  // Print a newline for better formatting

    // Close the socket and exit
    close(sock);
    exit(0);
}