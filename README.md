This repository contains a collection of labs from the Client-Server Programming module, completed during my third year of the Computer Science program at TU Dublin.

# Lab Summaries

### Lab 1: Ubuntu 14.04.5 Setup & Basic Linux Commands  
In this lab, I set up an Ubuntu 14.04.5 server with SSH access, focusing on configuring the system for remote management. I practiced essential Linux commands such as `ls`, `cd`, `mkdir`, and `rm`, which allowed me to navigate the file system and manage directories and files effectively. This foundational knowledge will support my work in subsequent labs, ensuring I can operate efficiently within the Linux environment.

### Lab 2: Network Traffic Analysis with Wireshark  
I captured and analyzed network packets using Wireshark to understand how data travels across the network. By generating HTTP traffic through web browsing, I was able to filter and examine packets, learning to identify various protocols and data structures. This experience improved my understanding of network protocols, enabling me to recognize important aspects like TCP handshakes and HTTP request-response cycles.

### Lab 3: Setting up the Virtual Network Environment  
In this lab, I configured a virtual network environment with two Ubuntu VMs, ensuring they could communicate effectively. I set the appropriate IPv4 addresses (192.168.1.11 for VM1 and 192.168.1.12 for VM2) and tested connectivity using the `ping` command. This setup involved managing network adapters and installing necessary software, which prepared me for more complex networking tasks in subsequent labs.

### Lab 4: Basic Client-Server Application Development with Berkeley Sockets  
This lab introduced the fundamentals of client-server application development using the Berkeley Socket API. I created a daytime server that provided the current date and time, while the client application requested this information. I implemented error handling in the more complex client version and ensured both applications could communicate over the network by compiling and executing them on the respective VMs. This experience solidified my understanding of socket programming and network communication.

### Lab 5: Client-Server Application Development Using Berkeley Socket API  
I expanded my understanding of client-server applications by developing a simple echo client-server application. This involved creating a script to automate the compilation of C source files, which reduced the chances of errors during the compilation process. I tested the applications in a networked environment, ensuring they correctly echoed messages sent between the client and server. This lab reinforced my skills in network programming and application development.

### Lab 6: TCP Connections and HTTP Protocol  
In this lab, I explored TCP connections using the `netstat` command to monitor active connections and view network statistics. I held TCP connections open while running the client-server applications and observed the associated data buffers. Additionally, I learned to interact with an HTTP server using `telnet`, gaining insights into the HTTP protocol. I modified the echo client to communicate with HTTP servers, enhancing my understanding of web protocols and their interactions.

### Lab 7: Basic HTTP Server  
I created a basic HTTP server by modifying the echo server code to handle HTTP requests. This involved setting up functions to parse incoming requests, determine the requested resource, and formulate appropriate HTTP responses. I tested the server using both the HTTP client developed in the previous lab and a web browser, confirming that it could serve valid requests and return error messages for invalid ones. This lab deepened my knowledge of web server functionality and HTTP interactions.
