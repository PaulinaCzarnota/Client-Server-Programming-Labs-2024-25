This repository contains a collection of labs from the Client-Server Programming module, completed during the third year of the Computer Science program at TU Dublin.

# Lab Summaries

### Lab 1: Ubuntu 14.04.5 Setup & Basic Linux Commands
In this lab, I set up a Virtual Machine (VM) running Ubuntu 14.04.5 and connected to it via SSH. The lab covers essential Linux commands for directory and file management, system information, network configurations, and process management. Tools like PuTTY were used for SSH access, and I learned how to interact with the terminal to execute basic commands.

### Lab 2: Network Traffic Analysis with Wireshark
This lab focused on using Wireshark to capture and analyze network traffic. I generated network traffic by visiting websites and examined the HTTP packets captured. Key tasks included installing Wireshark, analyzing traffic through various protocol layers, and understanding the raw data transmitted over the network.

### Lab 3: Setting up the Virtual Network Environment
In this lab, I configured a virtual network environment using Oracle VM VirtualBox. Two VMs were downloaded and set up with proper network adapter configurations and IP addressing. The VMs were connected via SSH, and tools like the GCC compiler were installed to prepare the environment for further client-server development exercises.

### Lab 4: Basic Client-Server Application Development with Berkeley Sockets
This lab introduced me to client-server programming using the Berkeley Socket API. I developed a simple client-server application where the client requests the server’s date and time. I created the necessary directory structure, wrote and compiled the source code for both the client and server, and ensured successful communication between them using TCP/IP sockets.

### Lab 5: Client-Server Application Development Using Berkeley Socket API
In this lab, I extended my knowledge of client-server application development using the Berkeley Socket API. A simple echo server and client were created to communicate over a network. The lab also involved writing a script to automate the compilation of C source files, testing daytime client-server applications, and modifying the echo server/client to handle input messages.

### Lab 6: TCP Connections and HTTP Protocol
This lab reinforced my understanding of TCP connections using the `netstat` command and introduced the basics of HTTP communication using telnet. I ran and modified client-server applications from previous labs to integrate HTTP interaction. The lab also covered using `netstat` to observe TCP connection states and using telnet and command-line HTTP clients to make HTTP requests.

### Lab 7: Basic HTTP Server
In this lab, I created a basic HTTP server capable of responding to HTTP GET requests. The server was modified from the `echoServer.c` source code and implemented basic HTTP response handling. It returned a `200 OK` response for valid resources and a `404 error` response for missing ones. I tested the server using both a command-line HTTP client and a web browser.

### Lab 8: More Complex HTTP Server
In this lab, I extended the basic HTTP server to serve files from the local file system. The server now handles HTTP requests by returning the requested file along with HTTP headers like `Content-Length`, `Cache-Control`, and `Connection`. If the requested file is not found, the server returns a `404 Not Found` page. I served `index.html` for valid requests and `error.html` for errors, testing the server with a browser or `curl`.

### Lab 9: Using Hostnames
In this lab, I worked with hostnames for network communication in client-server applications:
1. **Exercise 1:** I compiled C programs to resolve hostnames to IP addresses using `getaddrinfo` and printed the IPs for hostnames like `www.google.com` and `www.tudublin.ie`.
2. **Exercise 2:** I modified a basic HTTP client to use hostnames instead of IP addresses, allowing it to connect to servers like TU Dublin's webserver and fetch HTML data.
3. **Exercise 3:** I edited the `/etc/hosts` file on VM1 to map VM2's IP address to a hostname (`ubuntu1404-2`), enabling hostname-based connections between the two VMs.
This lab helped me better understand hostname resolution and its use in networked applications.

## Environment Setup
To ensure the exercises run smoothly, the following networked environment must be in place as per instructions from previous lab exercises:
- **VM1** should be configured with IPv4 address: **192.168.1.11**
- **VM2** should be configured with IPv4 address: **192.168.1.12**

### Required Tools:
- **PuTTY** for SSH access
- **Wireshark** for network traffic analysis
- **GCC** compiler for C language code compilation
- **Oracle VM VirtualBox** for virtualized network environment setup
