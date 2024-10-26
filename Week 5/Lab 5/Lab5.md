# Lab 5: Client-Server Application Development Using Berkeley Socket API

## Purpose
This lab exercise aims to extend students’ understanding of client-server application development using the Berkeley Socket API through the development of various networked applications. Students will create a simple echo server and client and compile and test their applications in a networked environment.

## Environment Setup
To ensure the exercises run smoothly, the following networked environment must be in place, as per instructions from a previous lab exercise:

- **VM1** should be configured with IPv4 address: **192.168.1.11**
- **VM2** should be configured with IPv4 address: **192.168.1.12**

### Network Connectivity
- Both machines should be able to communicate with each other. Use the `ping` command to test connectivity:
  
  ```bash
  ping 192.168.1.12  # From VM1 to VM2
  ping 192.168.1.11  # From VM2 to VM1
  ```

- Both machines should have the command-line compiler, `gcc`, installed.

## Steps Involved
1. Creating a script to simplify the process of compiling code using `gcc`.
2. Compiling and testing daytime client and server source code.
3. Writing an Echo client-server application.

## Exercise 1: Simple Scripting
### Overview
To streamline the compilation process and reduce the chances of errors, we will create a simple script to automate the compilation of C source files.

### Instructions
1. **Create the compile script** on both VMs using a command-line text editor (e.g., `nano`):

   ```bash
   nano compile
   ```

2. **Add the following commands** to the script:

   ```bash
   gcc -c -std=gnu99 $1.c
   gcc -o $1 $1.o DieWithMessage.o
   ```

3. **Save and exit** the editor.
4. **Check file permissions**:

   ```bash
   ls -l compile
   ```

   Ensure that the permissions are set to executable for each user group. If not, change the permissions using:

   ```bash
   chmod +x compile
   ```

   For more information on file permissions, visit: [Linux File Permissions Cheat Sheet](https://www.stationx.net/linux-file-permissions-cheat-sheet/).

## Exercise 2: Testing the Compile Script on Daytime Application
### Overview
We will use the provided source files for the daytime client and server applications to ensure consistency in future labs.

### Instructions
1. **Download the source files**:
   - On VM1, download `daytimeClient2.c` using WinSCP.
   - On VM2, download `daytimeServer2.c` using WinSCP.

2. **Compile the daytime client application** on VM1 using the script:

   ```bash
   ./compile daytimeClient2
   ```

   **Note:** Do not include the file extension `.c` when passing the filename to the script. The command-line argument `daytimeClient2` will replace the `$1` variable in the script.

3. **Compile the daytime server application** on VM2 in the same manner:

   ```bash
   ./compile daytimeServer2
   ```

4. **Test the applications** across the networked environment to ensure that the date and time are returned to the client application.

## Exercise 3: Compiling the Echo Client-Server Application
### Overview
In this exercise, we will develop an echo client-server application that reads input from the command line, establishes a connection, and sends messages between the client and server.

### Instructions
1. **Create copies of the source files**:
   - On VM1, create a copy of the daytime client source file:

     ```bash
     cp daytimeClient2.c echoClient.c
     ```

   - On VM2, create a copy of the daytime server source file:

     ```bash
     cp daytimeServer2.c echoServer.c
     ```

2. **Modify the `echoClient.c` file** on VM1:
   - Declare a new buffer:

     ```c
     char sendbuffer[BUFSIZE];
     ```

   - Read a fourth argument from the command line:

     ```c
     char *echoString = argv[3];
     ```

   - Check for the correct number of command-line arguments. 

   - After `connect()`, include a call to `send()` with the format from `daytimeServer2.c`. Use `snprintf` to format the buffer:

     ```c
     snprintf(sendbuffer, sizeof(sendbuffer), "%s\r\n", echoString);
     send(sock, sendbuffer, strlen(sendbuffer), 0);
     ```

3. **Modify the `echoServer.c` file** on VM2:
   - Declare a new buffer and variable:

     ```c
     char recvbuffer[BUFSIZE];
     int numBytes = 0;
     ```

   - After `accept()`, add a call to `recv()` before sending back to the client.

4. **Compile and test the echoClient and echoServer applications** using the compile script from Exercise 1:

   ```bash
   ./compile echoClient
   ./compile echoServer
   ```

5. **Run the echoClient** with the following command on VM1:

   ```bash
   ./echoClient 192.168.1.12 5000 "This is a test string"
   ```

### Troubleshooting
- If the string does not appear on the client screen, look for the two characters appended to the echo string. You may use `strstr()` to locate these characters and exit the `recv()` while loop appropriately.
- Ensure both the server and client are running in the correct environment (correct VMs).
- Check firewall settings to ensure that the specified port is open.
- Verify the server IP and port number are correctly entered when running the client.