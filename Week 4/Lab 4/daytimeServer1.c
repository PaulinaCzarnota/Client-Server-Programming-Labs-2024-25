#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"
#include <unistd.h>
#include <time.h>

static const int MAXPENDING = 5; // Maximum outstanding connection requests

int main(int argc, char *argv[]) {
    time_t ticks;                      // Variable to hold date and time data
    char sendbuffer[BUFSIZE];          // Buffer for sending data to the client 

    // Check for the correct number of arguments
    if (argc != 2) {
        DieWithUserMessage("Parameter(s)", "<Server Port>");
    }

    // Get the server port number from the command line argument
    in_port_t servPort = atoi(argv[1]);

    // Create socket for incoming connections
    int servSock; 
    if ((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        DieWithSystemMessage("socket() failed");
    }

    // Construct local address structure
    struct sockaddr_in servAddr;                  
    memset(&servAddr, 0, sizeof(servAddr));       // Zero out structure
    servAddr.sin_family = AF_INET;                 // IPv4 address family
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Any incoming interface
    servAddr.sin_port = htons(servPort);           // Local port

    // Bind to the local address
    if (bind(servSock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0) {
        DieWithSystemMessage("bind() failed");
    }

    // Mark the socket so it will listen for incoming connections
    if (listen(servSock, MAXPENDING) < 0) {
        DieWithSystemMessage("listen() failed");
    }

    for (;;) { // Run forever
        // Accept a new connection
        int clntSock = AcceptTCPConnection(servSock);

        // Create a string for the current time
        ticks = time(NULL);
        snprintf(sendbuffer, sizeof(sendbuffer), "%.24s\r\n", ctime(&ticks));

        // Send the current time to the client
        if (send(clntSock, sendbuffer, strlen(sendbuffer), 0) != strlen(sendbuffer)) {
            DieWithSystemMessage("send() failed");
        }

        close(clntSock); // Close the socket
    }
}