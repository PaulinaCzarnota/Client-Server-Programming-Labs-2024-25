#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024  // Size of the buffer for reading data and files

// Function to send the HTTP response (headers + file content) to the client
void send_response(SOCKET client_socket, const char *status, const char *content_type, const char *content, size_t content_length) {
    char response[BUFFER_SIZE];

    // Prepare the HTTP response header
    snprintf(response, sizeof(response),
             "HTTP/1.1 %s\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %zu\r\n"
             "Cache-Control: no-cache\r\n"
             "Connection: close\r\n"
             "\r\n", 
             status, content_type, content_length);
    
    // Send the HTTP header to the client
    send(client_socket, response, strlen(response), 0);

    // Send the actual file content
    send(client_socket, content, content_length, 0);
}

// Function to handle HTTP requests and serve files
void handle_request(SOCKET client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received < 0) {
        printf("Error receiving request\n");
        return;
    }

    buffer[bytes_received] = '\0';  // Null-terminate the incoming data

    // Print the request data to the server terminal for debugging
    printf("Received request:\n%s\n", buffer);

    // Parse the HTTP request to extract the requested file path
    char method[8], path[64], discard[50];
    sscanf(buffer, "%s %s %s", method, path, discard);

    // If the path is empty (i.e., "/"), serve the index.html file
    if (strcmp(path, "/") == 0) {
        strcpy(path, "/index.html");
    }

    // Remove the leading '/' from the path (file path)
    char *file_path = path + 1;

    // Check if the file exists
    struct stat file_info;
    FILE *file = fopen(file_path, "rb");

    if (file != NULL) {
        // File exists, get the file size
        stat(file_path, &file_info);
        size_t file_size = file_info.st_size;

        // Allocate memory for the file content
        char *file_content = (char *)malloc(file_size);
        if (!file_content) {
            printf("Memory allocation failed\n");
            fclose(file);
            return;
        }

        // Read the file content
        fread(file_content, 1, file_size, file);
        fclose(file);

        // Send HTTP response with the file content (200 OK)
        send_response(client_socket, "200 OK", "text/html", file_content, file_size);

        // Free the allocated memory for the file content
        free(file_content);
    } else {
        // File not found, return 404 error page
        printf("File not found: %s\n", file_path);

        // Prepare the error message for 404 page
        const char *error_message = "<html><head><title>File Not Found</title></head>"
                                    "<body><h2>The requested file was not found on the server.</h2></body></html>";
        send_response(client_socket, "404 Not Found", "text/html", error_message, strlen(error_message));
    }
}

// Main function to set up and run the server
int main() {
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create a socket for the server
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return 1;
    }

    // Set up the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Listen on all available network interfaces
    server_addr.sin_port = htons(8080);  // Set the port to 8080

    // Bind the socket to the address and port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == SOCKET_ERROR) {
        printf("Listen failed\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port 8080...\n");

    // Accept incoming connections and handle requests
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == INVALID_SOCKET) {
            printf("Accept failed\n");
            continue;
        }

        printf("New connection established\n");

        // Handle the client's HTTP request
        handle_request(client_socket);

        // Close the client socket after the request is handled
        closesocket(client_socket);
    }

    // Close the server socket when done
    closesocket(server_socket);
    WSACleanup();
    return 0;
}