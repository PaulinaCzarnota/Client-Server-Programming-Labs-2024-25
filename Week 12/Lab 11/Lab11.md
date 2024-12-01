# Lab 11 - CliAddr Netstat

## Overview
This lab demonstrates key concepts in TCP socket programming. It involves:
1. Capturing and displaying client address information (IP and port).
2. Handling HTTP GET requests.
3. Using the `netstat` utility to inspect TCP connections and buffers (`Recv-Q` and `Send-Q`).

The lab highlights how a TCP connection operates and allows observation of data flow during HTTP requests and responses.

---

## Objectives
1. Capture and log client address details (Exercise 1).
2. Respond to HTTP GET requests for `/index.html` with a predefined page or return an error page for invalid requests.
3. Use the `netstat` utility to inspect active TCP connections, including Recv-Q and Send-Q data buffers.

---

## Prerequisites
1. **Linux or WSL Environment**:
   - Ensure the following are installed:
     ```bash
     sudo apt update
     sudo apt install gcc curl net-tools -y
     ```

2. **Files**:
   - `basic_httpServer.c`: Implements the server.
   - `DieWithMessage.c`: Handles error reporting.
   - `Practical.h`: Includes utility constants and function declarations.

3. **Network Setup**:
   - Use two Virtual Machines (VMs) or equivalent systems:
     - **VM1**: Client system.
     - **VM2**: Server system.

---

## Implementation Steps

### Exercise 1: Capturing Client Address Information
The server captures and logs the client's IP address and port when a connection is accepted.

#### Code Explanation:
In `basic_httpServer.c`, the following code handles client address capture:
```c
socklen_t clntAddrLen;
struct sockaddr_in cliaddr;
char clntName[INET_ADDRSTRLEN];

clntAddrLen = sizeof(cliaddr);
int clntSock = accept(servSock, (struct sockaddr*)&cliaddr, &clntAddrLen);

printf("Connection from %s, port %d\n",
       inet_ntop(AF_INET, &cliaddr.sin_addr, clntName, sizeof(clntName)),
       ntohs(cliaddr.sin_port));
```

#### Steps:
1. The `accept()` function initializes the `cliaddr` structure with the client's address details.
2. The `inet_ntop()` function converts the client's IP address to a human-readable string.
3. The `ntohs()` function converts the client's port to host byte order.

---

### Exercise 2: Using the `netstat` Command
The `netstat` utility allows observation of active TCP connections.

#### Commands:
1. View all active TCP connections:
   ```bash
   sudo netstat -ntap
   ```

2. Filter for the server's port (e.g., 8080):
   ```bash
   sudo netstat -ntap | grep 8080
   ```

#### Columns to Observe:
- **Recv-Q**: Bytes received by the server but not yet read.
- **Send-Q**: Bytes sent by the server but not yet acknowledged by the client.

---

### Exercise 3: TCP Buffers and HTTP Responses
#### Steps:
1. **Run the Server** (VM2):
   ```bash
   ./basic_httpServer 8080
   ```

2. **Send Requests from Client** (VM1):
   - For `/index.html`:
     ```bash
     curl http://<server_ip>:8080/index.html
     ```
     Expected Output:
     ```html
     <HTML><HEAD><TITLE>File Found</TITLE></HEAD><BODY><h2>FILE Found</h2><hr><p>Your requested INDEX FILE was found.</p></BODY></HTML>
     ```

   - For `/invalid.html`:
     ```bash
     curl http://<server_ip>:8080/invalid.html
     ```
     Expected Output:
     ```html
     <HTML><HEAD><TITLE>File NOT Found</TITLE></HEAD><BODY><h2>FILE NOT Found</h2><hr><p>Your requested INDEX FILE was NOT found.</p></BODY></HTML>
     ```

3. **Inspect Buffers**:
   Run the `netstat` command while the server is paused (using `getchar()`):
   ```bash
   sudo netstat -ntap | grep 8080
   ```
   - Observe the `Recv-Q` and `Send-Q` columns for data waiting to be processed or acknowledged.

---

## Server Source Code
The main server code (`basic_httpServer.c`) performs the following tasks:
1. **Accepts Connections**:
   - Captures and logs client IP and port.
2. **Parses Requests**:
   - Reads HTTP GET requests and extracts the requested URI.
3. **Generates Responses**:
   - Responds with a predefined HTML page for `/index.html`.
   - Sends a 404 error page for invalid URIs.
4. **Pauses for Inspection**:
   - Uses `getchar()` to pause before closing connections, allowing time for `netstat` inspection.

---

## Testing Steps
1. **Compile the Server**:
   ```bash
   gcc -o basic_httpServer basic_httpServer.c DieWithMessage.c -Wall
   ```

2. **Run the Server**:
   ```bash
   ./basic_httpServer 8080
   ```

3. **Send Client Requests**:
   - Valid Request:
     ```bash
     curl http://localhost:8080/index.html
     ```
   - Invalid Request:
     ```bash
     curl http://localhost:8080/invalid.html
     ```

4. **Inspect Connections**:
   ```bash
   sudo netstat -ntap | grep 8080
   ```

5. **Press Enter in the Server Terminal**:
   - Allows the server to process data and close the connection.

---

## Cleanup
1. Close all connections by pressing `Enter` in the server terminal.
2. Stop the server:
   ```bash
   Ctrl+C
   ```

---

## Troubleshooting
1. **Server Not Responding**:
   - Ensure the server is running and listening on the correct port.
   - Verify network connectivity.

2. **No Connections in `netstat`**:
   - Confirm that a client is actively sending requests.

3. **Firewall Blocking**:
   - Temporarily disable the firewall:
     ```bash
     sudo ufw disable
     ```

---

## References
- [Netstat Command Examples](http://www.thegeekstuff.com/2010/03/netstat-command-examples/)
- [FAQs on Linux Networking](http://www.faqs.org/docs/linux_network/x-087-2-iface.netstat.html)