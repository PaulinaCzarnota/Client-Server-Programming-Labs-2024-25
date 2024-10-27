# Lab 5: Client-Server Application Development Using Berkeley Socket API

## Purpose
This lab exercise aims to extend my understanding of client-server application development using the Berkeley Socket API through developing various networked applications. I created a simple echo server and client, then compiled and tested these applications in a networked environment.

## Environment Setup
To ensure the exercises run smoothly, I set up the following networked environment, as per instructions from a previous lab exercise:

- **VM1** was configured with IPv4 address: **192.168.1.11**
- **VM2** was configured with IPv4 address: **192.168.1.12**

### Network Connectivity
- Both machines were set to communicate with each other. I used the `ping` command to test connectivity:
  
  ```bash
  ping 192.168.1.12  # From VM1 to VM2
  ping 192.168.1.11  # From VM2 to VM1
  ```

- Both machines also had the command-line compiler, `gcc`, installed.

## Steps Involved
1. I created a script to simplify the process of compiling code using `gcc`.
2. I compiled and tested daytime client and server source code.
3. I wrote an Echo client-server application.

## Exercise 1: Simple Scripting
### Overview
To streamline the compilation process and reduce the chances of errors, I created a simple script to automate the compilation of C source files.

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

   I ensured that the permissions were set to executable for each user group. If not, I changed the permissions using:

   ```bash
   chmod +x compile
   ```

   For more information on file permissions, I referred to the [Linux File Permissions Cheat Sheet](https://www.stationx.net/linux-file-permissions-cheat-sheet/).

## Exercise 2: Testing the Compile Script on Daytime Application
### Overview
I used the provided source files for the daytime client and server applications to ensure consistency in future labs.

### Instructions
1. **Download the source files**:
   - On VM1, I downloaded `daytimeClient2.c` using WinSCP.
   - On VM2, I downloaded `daytimeServer2.c` using WinSCP.

2. **Compile the daytime client application** on VM1 using the script:

   ```bash
   ./compile daytimeClient2
   ```

   **Note:** I did not include the file extension `.c` when passing the filename to the script, as the command-line argument `daytimeClient2` replaced the `$1` variable in the script.

3. **Compile the daytime server application** on VM2 in the same manner:

   ```bash
   ./compile daytimeServer2
   ```

4. **Test the applications** across the networked environment to ensure that the date and time were returned to the client application.

## Exercise 3: Compiling the Echo Client-Server Application
### Overview
In this exercise, I developed an echo client-server application that reads input from the command line, establishes a connection, and sends messages between the client and server.

### Instructions
1. **Create copies of the source files**:
   - On VM1, I created a copy of the daytime client source file:

     ```bash
     cp daytimeClient2.c echoClient.c
     ```

   - On VM2, I created a copy of the daytime server source file:

     ```bash
     cp daytimeServer2.c echoServer.c
     ```

2. **Modify the `echoClient.c` file** on VM1:
   - I declared a new buffer:

     ```c
     char sendbuffer[BUFSIZE];
     ```

   - I read a fourth argument from the command line:

     ```c
     char *echoString = argv[3];
     ```

   - I checked for the correct number of command-line arguments. 

   - After `connect()`, I included a call to `send()` with the format from `daytimeServer2.c`. I used `snprintf` to format the buffer:

     ```c
     snprintf(sendbuffer, sizeof(sendbuffer), "%s\r\n", echoString);
     send(sock, sendbuffer, strlen(sendbuffer), 0);
     ```

3. **Modify the `echoServer.c` file** on VM2:
   - I declared a new buffer and variable:

     ```c
     char recvbuffer[BUFSIZE];
     int numBytes = 0;
     ```

   - After `accept()`, I added a call to `recv()` before sending back to the client.

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
- If the string didn’t appear on the client screen, I checked for the two characters appended to the echo string. I used `strstr()` to locate these characters and exited the `recv()` while loop appropriately.
- I ensured both the server and client were running in the correct environment (correct VMs).
- I checked firewall settings to ensure that the specified port was open.
- I verified the server IP and port number were correctly entered when running the client.