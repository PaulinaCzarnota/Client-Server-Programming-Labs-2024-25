#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h" // Include error handling functions
#include <unistd.h>

// Predefined HTTP response for a successful request
#define HOME_PAGE "HTTP/1.0 200 OK\r\nContent-Length: 131\r\nConnection: close\r\nServer: httpserver\r\n\r\n<HTML><HEAD><TITLE>File Found</TITLE></HEAD><BODY><h2>FILE Found</h2><hr><p>Your requested INDEX FILE was found.</p></BODY></HTML>"

// Predefined HTTP response for a resource not found
#define ERROR_PAGE "HTTP/1.0 404 Not Found\r\nContent-Length: 142\r\nConnection: close\r\nServer: httpserver\r\n\r\n<HTML><HEAD><TITLE>File NOT Found</TITLE></HEAD><BODY><h2>FILE NOT Found</h2><hr><p>Your requested INDEX FILE was NOT found.</p></BODY></HTML>"

// Maximum number of pending client connections
static const int MAXPENDING = 2;

int main(int argc, char *argv[]) {
    // Buffers for receiving and sending data, and parsing URIs
    char recvbuffer[BUFSIZE], sendbuffer[BUFSIZE], uri[200] = {""};
    char discard1[50], discard2[50];

    // Variables for storing client address information
    socklen_t clntAddrLen;
    struct sockaddr_in cliaddr;
    char clntName[INET_ADDRSTRLEN];

    // Validate that the correct number of arguments is provided
    if (argc != 2)
        DieWithUserMessage("Parameter(s)", "<Server Port>");

    // Convert the server port from string to integer
    in_port_t servPort = atoi(argv[1]);

    // Create a socket for incoming connections
    int servSock;
    if ((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithSystemMessage("socket() failed");

    // Configure the server address structure
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));       // Zero out the structure
    servAddr.sin_family = AF_INET;                // IPv4
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any IP
    servAddr.sin_port = htons(servPort);          // Convert port to network byte order

    // Bind the socket to the local address and port
    if (bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
        DieWithSystemMessage("bind() failed");

    // Listen for incoming client connections
    if (listen(servSock, MAXPENDING) < 0)
        DieWithSystemMessage("listen() failed");

    printf("Server is listening on port %d\n", servPort);

    for (;;) { // Main loop to handle incoming connections
        // Set the length of the client address structure
        clntAddrLen = sizeof(cliaddr);

        // Accept an incoming client connection
        int clntSock = accept(servSock, (struct sockaddr*)&cliaddr, &clntAddrLen);
        if (clntSock < 0)
            DieWithSystemMessage("accept() failed");

        // Log the client's IP address and port
        printf("Connection from %s, port %d\n",
               inet_ntop(AF_INET, &cliaddr.sin_addr, clntName, sizeof(clntName)),
               ntohs(cliaddr.sin_port));

        // Clear buffers for the new request
        memset(recvbuffer, '\0', sizeof(recvbuffer));
        memset(sendbuffer, '\0', sizeof(sendbuffer));
        memset(uri, '\0', sizeof(uri));

        // Receive data from the client
        ssize_t numBytesReceived = recv(clntSock, recvbuffer, BUFSIZE - 1, 0);
        if (numBytesReceived < 0)
            DieWithSystemMessage("recv() failed");

        // Null-terminate the received data
        recvbuffer[numBytesReceived] = '\0';
        printf("Received request:\n%s\n", recvbuffer);

        // Parse the incoming request to extract the requested URI
        sscanf(recvbuffer, "%s %s %s", discard1, uri, discard2);

        // Ignore requests for /favicon.ico
        if (strcmp(uri, "/favicon.ico") == 0) {
            printf("Ignoring favicon.ico request\n");
            close(clntSock); // Close the client socket
            continue;        // Go back to accepting new connections
        }

        // Determine the response based on the requested URI
        if (strcmp(uri, "/index.html") == 0) {
            snprintf(sendbuffer, sizeof(sendbuffer), HOME_PAGE); // Prepare the home page response
        } else {
            snprintf(sendbuffer, sizeof(sendbuffer), ERROR_PAGE); // Prepare the error page response
        }

        // Send the response back to the client
        ssize_t numBytesSent = send(clntSock, sendbuffer, strlen(sendbuffer), 0);
        if (numBytesSent < 0)
            DieWithSystemMessage("send() failed");

        // Log the response sent to the client
        printf("Response sent to client:\n%s\n", sendbuffer);

        // Pause execution to allow netstat inspection of the connection
        getchar();

        // Close the client connection
        close(clntSock);
    }
}