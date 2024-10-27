# Lab 6: TCP Connections and HTTP Protocol

## Purpose
This lab reinforces my understanding of TCP connections using `netstat` and introduces HTTP communication basics using `telnet`. I built on the existing client-server applications developed in previous labs and made modifications to integrate HTTP interaction.

## Lab Exercises

### Prerequisites
I ensured that the following applications from previous labs were working correctly:
- `echoClient` and `echoServer` applications.
- `daytimeClient2` and `daytimeServer2` applications.

### Steps Involved
1. I ran client-server applications while holding the underlying TCP connection open.
2. I used `netstat` to view connection details.
3. I interacted with an HTTP server using `telnet`.
4. I adapted `echoClient` to interact with HTTP servers.

---

### Exercise 1: The `netstat` Command
1. I researched the `netstat` utility:
   - [Netstat Examples](http://www.thegeekstuff.com/2010/03/netstat-command-examples/)
   - [YouTube Guide](http://www.youtube.com/watch?v=O0iQ6-ybZak)
   - [FAQs on `netstat`](http://www.faqs.org/docs/linux_network/x-087-2-iface.netstat.html)

2. I used `netstat` to observe TCP connections linked to active client and server applications.

### Exercise 2: TCP Connections and TCP Data Buffers
1. **Setup**: I opened four PuTTY sessions (two to each VM).
   - **VM1**: I ran `daytimeClient3` and `netstat`.
   - **VM2**: I ran `daytimeServer3` and `netstat`.

2. **View Sockets**: I ran the following command on each VM:
   ```bash
   netstat -ntap
   ```
   - I observed column headers like `Recv-Q` and `Send-Q`.

3. **Filter Output**:
   - I used `grep` to limit output to specific ports:
     ```bash
     netstat -ntap | grep <PORT_NUMBER>
     ```
4. **Hold Connections Open**:
   - I inserted `getchar();` before `close()` in the server code to keep the connection open.
5. **Observe TCP Recv-Q Buffer**:
   - I added `getchar();` in the client application at appropriate points to keep data in the TCP layer.

### Exercise 3: HTTP Client-Server Exercises Using `telnet`
1. **Get Server IP**:
   - I pinged `www.example.com` to get the IP address:
     ```bash
     ping www.example.com
     ```
2. **Connect via `telnet`**:
   - I replaced `XXX.XXX.XXX.XXX` with the IP from step 1:
     ```bash
     telnet XXX.XXX.XXX.XXX 80
     ```
   - Then, I entered the following commands:
     ```
     GET /index.html HTTP/1.1<CR>
     Host: www.example.com<CR>
     Connection: close<CR>
     <CR>
     ```
3. **Verify Output**: I confirmed that the response aligned with a web server’s expected output.

### Exercise 4: Command-line HTTP Client
1. **Copy and Modify Source File**:
   - I created `httpClient.c` as a copy of `echoClient.c`.
   
2. **Format HTTP GET Request**:
   - I modified `snprintf()` to construct a GET request:
     ```c
     "GET /index.html HTTP/1.1\r\nHost: www.example.com\r\nConnection: close\r\n\r\n"
     ```
3. **Compile and Run**:
   - I compiled and executed:
     ```bash
     ./httpClient <IP_ADDRESS> 80
     ```
4. **Pass Resource from Command-line** (Optional):
   ```bash
   ./httpClient <IP_ADDRESS> 80 $'GET /index.html HTTP/1.0\r\n\r\n'
   ```

---

## Notes
- `Recv-Q` and `Send-Q`: Represent queued data in TCP buffers.
- `\r\n`: Denotes a carriage return and newline, required by the HTTP protocol.
- I used `Ctrl-c` to stop the `ping` output.