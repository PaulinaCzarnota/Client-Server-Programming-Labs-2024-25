# Lab 7: Basic HTTP Server

## Exercise 1: Create a Basic HTTP Server

### Overview
In this exercise, you will create a basic HTTP server by copying and modifying the `echoServer.c` source code. The new application, suggested to be named `httpServer.c`, will perform basic HTTP server functionality, allowing it to interact with the `httpClient` from your previous lab exercise and a web browser like Firefox.

### Pseudocode and Functions
The following string functions will be used in this application:

1. **`char *strstr(const char *haystack, const char *needle)`**:
   - Used to search for a substring (`needle`) within another string (`haystack`).
   - Returns a pointer to the first occurrence of `needle` or `NULL` if not found. This will help you identify the end of the HTTP request. An appropriate string to search for could be `"\r\n\r\n"`.

2. **`int sscanf (const char * str, const char * format, ...);`**:
   - Parses input from a string based on a specified format.
   - Useful for extracting individual data entities from the HTTP request line, which has the format: `GET /index.html HTTP/1.1\r\n\r\n`.
   - You will extract the three components: command, path, and version, and store them in predefined character arrays (e.g., `cmd`, `path`, `vers`). 

   More details can be found [here](http://www.cplusplus.com/reference/clibrary/cstdio/sscanf/).

3. **`int strcmp(const char *s1, const char *s2);`**:
   - Compares two strings and returns an integer based on the comparison.
   - This function will be used to check the HTTP version and requested resource. For example, you can check if the path is `/index.html` and respond accordingly.

### Implementation Steps
1. **Define HTTP Responses**:
   ```c
   #define HOME_PAGE "HTTP/1.1 200 File Found\r\nContent-Length: 125\r\nConnection: close\r\n\r\n<HTML><HEAD><TITLE>File Found</TITLE></HEAD><BODY><h2>FILE Found</h2><hr><p>Your requested FILE was found.</p></BODY></HTML>"
   #define ERROR_PAGE "HTTP/1.1 404 File Not Found\r\nContent-Length: 215\r\nConnection: close\r\n\r\n<HTML><HEAD><TITLE>File Not Found</TITLE></HEAD><BODY><h2>FILE Not Found</h2><hr><p>Your requested FILE was not found.</p></BODY></HTML>"
   ```

2. **Set Up Character Arrays**:
   ```c
   // Command, path, and version arrays for parsing HTTP requests
   char cmd[16];  // Command (e.g., GET)
   char path[64]; // Requested resource path (e.g., /index.html)
   char vers[16]; // HTTP version (e.g., HTTP/1.1)
   ```

3. **Start the Infinite Loop**:
   - Accept connection requests and process incoming data.

4. **Read Data from the Socket**:
   - Store incoming data in a buffer and null-terminate it.
   - Print the received data for verification.

5. **Search for the End of the HTTP Request**:
   - Use `strstr()` to identify the end of the HTTP request.

6. **Extract HTTP Components**:
   - Use `sscanf()` to populate the `cmd`, `path`, and `vers` arrays.

7. **Determine Response**:
   - If the path is `/index.html`, send the `HOME_PAGE`.
   - Otherwise, send the `ERROR_PAGE`.

8. **Close the Connected Socket**:
   - Repeat the process for new connections.

### Example Pseudocode
```c
#define HOME_PAGE ...
#define ERROR_PAGE ...

char cmd[16], path[64], vers[16];

while (1) {
    // Accept connection
    // Loop to read from socket
    while (data to be read) {
        // Read data and null terminate
        // Print received data
        if (strstr(buffer, "\r\n\r\n")) {
            break;
        }
    }

    // Extract command, path, version
    sscanf(buffer, "%s %s %s", cmd, path, vers);

    // Check for requested path
    if (!strcmp(path, "/index.html")) {
        send(HOME_PAGE);
    } else {
        send(ERROR_PAGE);
    }

    // Close connection
}
```

---

## Exercise 2: Testing the Operation of the Basic HTTP Server

### Setup
1. **Run the Applications**:
   - Use two virtual machines (VM1 and VM2). 
   - VM1 IP Address: `192.168.1.11`
   - VM2 IP Address: `192.168.1.12`

2. **Start the HTTP Server**:
   - On VM2, run the HTTP server on port 80 using:
     ```bash
     sudo ./httpServer 80
     ```

3. **Run the HTTP Client**:
   - On VM1, execute the HTTP client to access the server:
     ```bash
     ./httpClient 192.168.1.12 80 $'GET /index.html HTTP/1.1\r\nHost: 192.168.1.12\r\n\r\n'
     ```

### Analyze Output
- Check the terminal output on both VMs.
- Try accessing non-existent pages and observe the server's response.

### Accessing via Browser
1. **Port Forwarding**:
   - Shut down VM2 using ACPI Shutdown.
   - In VirtualBox Manager, configure Port Forwarding for VM2’s NAT adapter to forward host port 8080 to guest port 80. This allows external access to the server running on VM2.

2. **Restart VM2**:
   - Access via PuTTY and restart the HTTP server on port 80.

3. **Using Firefox**:
   - Open Firefox and enter:
     ```
     http://localhost:8080/index.html
     ```

4. **Review Browser Output**:
   - Analyze the displayed data and terminal outputs for VM2. 
   - Test requests for non-existent pages and observe the server's error responses.
```