This repository contains a collection of labs from the Client-Server Programming module, completed during my third year of Computer Science at TU Dublin.

# Lab Summaries

### Lab 1: Ubuntu 14.04.5 Setup & Basic Linux Commands
In this lab, we set up a Virtual Machine (VM) running Ubuntu 14.04.5 and connected to it via SSH. We explored essential Linux commands for directory and file management, system info, network configurations, and process management. Additionally, we practiced using tools like PuTTY for SSH access and learned to interact with the terminal to execute basic commands.

### Lab 2: Network Traffic Analysis with Wireshark
This lab focused on using Wireshark to capture and analyze network traffic. We learned how to generate network traffic by visiting websites and examined the HTTP packets captured. Key tasks included installing Wireshark, analyzing traffic through various protocol layers, and understanding the raw data transmitted over the network.

### Lab 3: Setting up the Virtual Network Environment
In this lab, we configured a virtual network environment using Oracle VM VirtualBox. We downloaded and set up two VMs, ensuring proper network adapter configurations and IP addressing. We then connected to the VMs using SSH and installed necessary tools like the GCC compiler, preparing the environment for further client-server development exercises.

### Lab 4: Basic Client-Server Application Development with Berkeley Sockets
This lab introduced client-server programming using the Berkeley Socket API. We developed a simple client-server application where the client requests the server’s date and time. We created the necessary directory structure, wrote and compiled the source code for the client and server, and executed them on separate VMs, ensuring successful communication between the two using TCP/IP sockets.

### Lab 5: Client-Server Application Development Using Berkeley Socket API
In this lab, we extended our knowledge of client-server application development using the Berkeley Socket API. We created a simple echo server and client that communicated over a networked environment. The exercise also involved writing a script to automate the process of compiling C source files, testing daytime client and server applications, and modifying the echo server and client to handle input messages.

### Lab 6: TCP Connections and HTTP Protocol
This lab reinforced the understanding of TCP connections using the `netstat` command and introduced the HTTP communication basics using telnet. We ran client-server applications developed in previous labs and modified them to integrate HTTP interaction. The lab also covered using `netstat` to observe the TCP connection states and HTTP requests using telnet and command-line HTTP clients.

### Lab 7: Basic HTTP Server
In this lab, we created a basic HTTP server that could respond to HTTP GET requests. We started by modifying the `echoServer.c` source code and then implemented basic HTTP response handling, including providing a 200 OK response for a valid resource and a 404 error response for missing resources. The server handled incoming HTTP requests, extracted the necessary information, and sent appropriate responses to clients. We tested the server using both a command-line HTTP client and a web browser.

# Environment Setup

To ensure the exercises run smoothly, the following networked environment must be in place, as per instructions from previous lab exercises:

- **VM1** should be configured with IPv4 address: **192.168.1.11**
- **VM2** should be configured with IPv4 address: **192.168.1.12**

### Required Tools:
- **PuTTY** for SSH access
- **Wireshark** for network traffic analysis
- **GCC** compiler for C language code compilation
- **Oracle VM VirtualBox** for virtualized network environment setup
