# Lab 9: Using Hostnames

## Overview

In this lab, we will explore the use of hostnames and IP addresses, and how to resolve hostnames to IP addresses in a C program. We will also extend a simple HTTP client to use hostnames, and create a mapping between IP addresses and hostnames on VM2 for local resolution.

This lab consists of three exercises:

1. **Printing the IP address(es) for a given hostname**  
2. **Using hostnames instead of IP addresses in a basic HTTP client**  
3. **Creating an “IP address – Hostname” mapping for VM2**

## Exercise 1 – Printing the IP address(es) for a given hostname

In this exercise, you will compile and run a C program that resolves the IP address(es) for a given hostname.

### Steps

1. **Download and Compile the Source Files**  
   Download the source files from the Resources folder: `GetAddrInfo.c`, `DieWithMessage.c`, and `AddressUtility.c`. The compile script used previously will not be sufficient, so use the following commands instead:

   ```bash
   gcc -std=gnu99 -c AddressUtility.c GetAddrInfo.c
   gcc -o GetAddress GetAddrInfo.o AddressUtility.o DieWithMessage.o
   ```

   These commands compile the source files and create the executable `GetAddress`.

2. **Run the Program**  
   Run the program from the command line, passing different hostnames and services as arguments. Use the following examples:

   ```bash
   ./GetAddress www.google.com 0
   ./GetAddress www.tudublin.ie http
   ```

   **Expected Output:**
   The program should return a list of IP addresses for the provided hostname. Example output for `www.google.com`:

   ```
   74.125.193.99
   74.125.193.147
   74.125.193.106
   74.125.193.104
   74.125.193.103
   74.125.193.105
   2a00:1450:400b:c02::93
   2a00:1450:400b:c02::6a
   2a00:1450:400b:c02::69
   2a00:1450:400b:c02::63
   ```

## Exercise 2 – Using Hostnames instead of IP Addresses

This exercise extends the previous simple HTTP client to allow the use of hostnames instead of IP addresses.

### Steps

1. **Copy and Modify the HTTP Client**  
   Copy the basic HTTP client source code and rename it to `httpClientHostname.c`.

   Study the sample code and incorporate the relevant parts into the basic HTTP client. Specifically, replace the code related to IP address handling with code that uses hostnames.

2. **Modify the Code**  
   You will need to make the following changes:
   - Use the following declarations to retrieve the server address/hostname and server port/service from the command line:

     ```c
     char *host = argv[1];  // Server address/name
     char *service = argv[2]; // Server port/service
     ```

   - Include `<netdb.h>` for handling hostnames.

3. **Compile and Test the Application**  
   Use the original compile script to build the application. Once compiled, run the application with the following command to test it against the TU Dublin webserver:

   ```bash
   ./httpClientHostname www.tudublin.ie http $'GET / HTTP/1.1\r\nHost: www.tudublin.ie\r\n\r\n'
   ```

   **Expected Output:**
   The program should retrieve HTML data from the server.

## Exercise 3 – Creating an “IP address – Hostname” mapping for VM2

In this exercise, you will create a local mapping for a server running on VM2. This will allow you to use a hostname instead of an IP address (e.g., `ubuntu1404-2` instead of `192.168.1.12`).

### Steps

1. **Modify the `/etc/hosts` File**  
   On VM1, modify the `/etc/hosts` file to create a mapping for VM2. First, create a backup of the original hosts file:

   ```bash
   sudo cp /etc/hosts /etc/hostsOLD
   ```

   Then, open the `/etc/hosts` file in a text editor and add the following entry:

   ```bash
   192.168.1.12 ubuntu1404-2
   ```

2. **Run the HTTP Client on VM1**  
   Now, you can run the `httpClientHostname` application on VM1, using the hostname `ubuntu1404-2` instead of the IP address. Use the following command to test it:

   ```bash
   ./httpClientHostname ubuntu1404-2 http $'GET / HTTP/1.1\r\nHost: 192.168.1.12\r\n\r\n'
   ```

   **Expected Output:**
   The program should successfully connect to the server on VM2 and retrieve HTML data.