#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"
#include <unistd.h>

#define BUFSIZE 1024  // Buffer size for incoming requests
#define HOME_PAGE "HTTP/1.1 200 OK\r\nContent-Length: 131\r\nConnection: close\r\n\r\n<HTML><HEAD><TITLE>File Found</TITLE></HEAD><BODY><h2>FILE Found</h2><hr><p>Your requested FILE was found.</p></BODY></HTML>"
#define ERROR_PAGE "HTTP/1.1 404 Not Found\r\nContent-Length: 215\r\nConnection: close\r\n\r\n<HTML><HEAD><TITLE>File Not Found</TITLE></HEAD><BODY><h2>FILE Not Found</h2><hr><p>Your requested FILE was not found.</p></BODY></HTML>"

static const int MAXPENDING = 3; // Maximum outstanding connection requests

int main(int argc, char *argv[]) {
    // Check command line arguments
    if (argc != 2) {
        DieWithUserMessage("Parameter(s)", "<Server Port>");
    }

    in_port_t servPort = atoi(argv[1]); // Convert argument to port number
    int servSock; // Socket descriptor for server

    // Create socket
    if ((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        DieWithSystemMessage("socket() failed");
    }

    // Setup server address structure
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));       
    servAddr.sin_family = AF_INET;                
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(servPort);
  
    // Bind the server to the address and port
    if (bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        DieWithSystemMessage("bind() failed");
    }

    // Listen for incoming connections
    if (listen(servSock, MAXPENDING) < 0) {
        DieWithSystemMessage("listen() failed");
    }

    // Server loop to accept and handle incoming connections
    for (;;) { 
        int clntSock = accept(servSock, (struct sockaddr*) NULL, NULL);
        if (clntSock < 0) {
            DieWithSystemMessage("accept() failed");
        }

        // Initialize buffers and other variables
        char recvbuffer[BUFSIZE], sendbuffer[BUFSIZE];
        char cmd[16], path[64], vers[16];
        int totalBytes = 0;
        
        // Clear buffers
        memset(recvbuffer, '\0', sizeof(recvbuffer));
        memset(sendbuffer, '\0', sizeof(sendbuffer));

        // Receive HTTP request
        while (1) {  
            int numBytes = recv(clntSock, recvbuffer + totalBytes, BUFSIZE - totalBytes - 1, 0);
            if (numBytes < 0) {
                DieWithSystemMessage("recv() failed");
            } else if (numBytes == 0) { // Connection closed by client
                break;
            }
            totalBytes += numBytes; // Update the offset
            recvbuffer[totalBytes] = '\0'; // Null-terminate the received string

            // Check for end of HTTP request
            if (strstr(recvbuffer, "\r\n\r\n") != NULL) {
                break; // End of HTTP request found
            }

            // Prevent buffer overflow
            if (totalBytes >= BUFSIZE - 1) {
                fprintf(stderr, "Received data too large, closing connection.\n");
                break; // Exit loop if too large
            }
        }

        // Print received request for verification
        fputs(recvbuffer, stdout);

        // Parse the HTTP request line
        sscanf(recvbuffer, "%s %s %s", cmd, path, vers);

        // Check for the requested path
        if (strcmp(path, "/index.html") == 0) {
            snprintf(sendbuffer, sizeof(sendbuffer), HOME_PAGE);
        } else {
            snprintf(sendbuffer, sizeof(sendbuffer), ERROR_PAGE);
        }

        // Send the response to the client
        ssize_t numBytesSent = send(clntSock, sendbuffer, strlen(sendbuffer), 0);
        if (numBytesSent < 0) {
            DieWithSystemMessage("send() failed");
        }
        
        // Close the client socket
        close(clntSock);
    }

    // Close the server socket (never reached in this infinite loop)
    close(servSock);
    return 0; // Although this point won't be reached
}