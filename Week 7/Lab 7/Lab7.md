# Lab 7: Basic HTTP Server

## Exercise 1: Create a Basic HTTP Server

### Overview
In this exercise, I created a basic HTTP server by modifying the `echoServer.c` source code. My new application, `httpServer.c`, performs basic HTTP server functions, allowing it to interact with the `httpClient` from my previous lab and with a web browser like Firefox.

### Pseudocode and Functions
I used the following string functions in this application:

1. **`char *strstr(const char *haystack, const char *needle);`**
   - This function searches for a substring (`needle`) within another string (`haystack`).
   - It returns a pointer to the first occurrence of `needle`, or `NULL` if not found. I used this to identify the end of the HTTP request. An appropriate string to search for is `"\r\n\r\n"`.

2. **`int sscanf(const char *str, const char *format, ...);`**
   - This function parses input from a string based on a specified format.
   - It’s useful for extracting individual data entities from the HTTP request line, which has the format: `GET /index.html HTTP/1.1\r\n\r\n`.
   - Using this function, I extracted three components: command, path, and version, which are stored in predefined character arrays (e.g., `cmd`, `path`, `vers`). 

   More details can be found [here](http://www.cplusplus.com/reference/cstdio/sscanf/).

3. **`int strcmp(const char *s1, const char *s2);`**
   - This function compares two strings and returns an integer based on the comparison.
   - I used this function to check the HTTP version and requested resource. For example, I checked if the path is `/index.html` to respond accordingly.

### Implementation Steps
1. **Define HTTP Responses**:
   ```c
   #define HOME_PAGE "HTTP/1.1 200 OK\r\nContent-Length: 125\r\nConnection: close\r\n\r\n<HTML><HEAD><TITLE>File Found</TITLE></HEAD><BODY><h2>File Found</h2><hr><p>Your requested file was found.</p></BODY></HTML>"
   #define ERROR_PAGE "HTTP/1.1 404 Not Found\r\nContent-Length: 215\r\nConnection: close\r\n\r\n<HTML><HEAD><TITLE>File Not Found</TITLE></HEAD><BODY><h2>File Not Found</h2><hr><p>Your requested file was not found.</p></BODY></HTML>"
   ```

2. **Set Up Character Arrays**:
   ```c
   // Arrays for parsing HTTP requests
   char cmd[16];  // Command (e.g., GET)
   char path[64]; // Requested resource path (e.g., /index.html)
   char vers[16]; // HTTP version (e.g., HTTP/1.1)
   ```

3. **Start the Infinite Loop**:
   - I set up an infinite loop to accept connection requests and process incoming data.

4. **Read Data from the Socket**:
   - I stored incoming data in a buffer and null-terminated it.
   - I printed the received data for verification.

5. **Search for the End of the HTTP Request**:
   - Using `strstr()`, I identified the end of the HTTP request.

6. **Extract HTTP Components**:
   - Using `sscanf()`, I populated the `cmd`, `path`, and `vers` arrays.

7. **Determine Response**:
   - If the path is `/index.html`, I send the `HOME_PAGE`.
   - Otherwise, I send the `ERROR_PAGE`.

8. **Close the Connected Socket**:
   - I repeat the process for new connections.

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
   - I used two virtual machines (VM1 and VM2).
   - VM1 IP Address: `192.168.1.11`
   - VM2 IP Address: `192.168.1.12`

2. **Start the HTTP Server**:
   - On VM2, I ran the HTTP server on port 80 using:
     ```bash
     sudo ./httpServer 80
     ```

3. **Run the HTTP Client**:
   - On VM1, I executed the HTTP client to access the server:
     ```bash
     ./httpClient 192.168.1.12 80 $'GET /index.html HTTP/1.1\r\nHost: 192.168.1.12\r\n\r\n'
     ```

### Analyze Output
- I checked the terminal output on both VMs.
- I also tried accessing non-existent pages to observe the server’s response.

### Accessing via Browser
1. **Port Forwarding**:
   - I shut down VM2 using ACPI Shutdown.
   - In VirtualBox Manager, I configured Port Forwarding for VM2’s NAT adapter to forward host port 8080 to guest port 80. This setup allows external access to the server running on VM2.

2. **Restart VM2**:
   - I used PuTTY to access VM2 and restarted the HTTP server on port 80.

3. **Using Firefox**:
   - In Firefox, I entered:
     ```
     http://localhost:8080/index.html
     ```

4. **Review Browser Output**:
   - I analyzed the displayed data and terminal outputs for VM2.
   - I tested requests for non-existent pages to observe the server’s error responses.