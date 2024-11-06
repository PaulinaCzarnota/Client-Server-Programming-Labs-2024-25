# Lab 4: Basic Client-Server Application Development with Berkeley Sockets

## Purpose
This lab introduces the fundamental elements of client-server application development using the Berkeley Socket API. You will create, compile, and execute applications that communicate over a network.

---

## Steps

### Prerequisites
Before starting, confirm that the network environment is set up as follows:
   - **VM1**: IPv4 address set to `192.168.1.11`.
   - **VM2**: IPv4 address set to `192.168.1.12`.
   - **Connectivity Test**: Ensure both VMs can communicate using `ping`.
   - **Compiler Installed**: Both machines should have the `gcc` command-line compiler installed.

---

## Exercises

### Exercise 1: Creating the Directory Structure
1. **Objective**: Create a directory for storing project files on both VMs.
   
2. **Instructions**:
   - On each VM, create and navigate to a directory named `csp`:
     ```bash
     soc@ubuntu-1404-1: mkdir csp
     soc@ubuntu-1404-1: cd csp
     ```

3. **Download Required Files**:
   - Use **WinSCP** to transfer the following files from the `Resources` folder into the `csp` directory on each VM:
     - `Practical.h`
     - `DieWithMessage.o`

---

### Exercise 2: Writing the Daytime Client Source File

1. **Objective**: Write source code for a daytime client application that will request and display the server’s date and time.

2. **Instructions**:
   - On **VM1**, use a command-line editor like `nano` to create two versions of the client application:
     - **Simplistic version** (no error handling): `daytimeClientSimple.c`
     - **Complex version** (with error handling): `daytimeClient.c`
   
3. **Create Source File**:
   - Open an empty file in `nano` for each version:
     ```bash
     soc@ubuntu-1404-1/csp: nano daytimeClientSimple.c
     ```
   - Type the code for each version from the screenshots provided (Figures 1 & 2 in the lab document). **Do not copy-paste** as this may introduce hidden characters.

4. **Save and Exit**:
   - Use `Ctrl + O`, press **Enter** to save, and `Ctrl + X` to exit `nano`.

---

### Exercise 3: Compiling the Client Application

1. **Objective**: Compile the `daytimeClientSimple.c` source file to create an executable.

2. **Instructions**:
   - Run the following commands in order to compile and link the client program on **VM1**:
     ```bash
     soc@ubuntu-1404-1/csp: gcc -c -std=gnu99 daytimeClientSimple.c
     soc@ubuntu-1404-1/csp: gcc -o daytimeClientSimple daytimeClientSimple.o DieWithMessage.o
     ```
   - **Notes**:
     - Ensure all commands are case-sensitive.
     - `daytimeClientSimple.o` will be created as the object file from `daytimeClientSimple.c`.
     - The executable `daytimeClientSimple` will be created by linking `DieWithMessage.o`.

---

### Exercise 4: Executing the Client and Server Applications

1. **Objective**: Start the daytime server and connect the client to retrieve the date and time.

2. **Instructions**:

   - **On VM2**:
     - Download `daytimeserver` (no file extension) from the **Resources** folder.
     - Check file permissions using:
       ```bash
       soc@ubuntu-1404-2/csp: ls -l daytimeserver
       ```
     - Grant execute permission:
       ```bash
       soc@ubuntu-1404-2/csp: chmod a+x daytimeserver
       ```
     - Run the server application on port `1234` (or another available port):
       ```bash
       soc@ubuntu-1404-2/csp: ./daytimeserver 1234
       ```

   - **On VM1**:
     - Execute the client application, specifying the server's IP address and port:
       ```bash
       soc@ubuntu-1404-1/csp: ./daytimeClientSimple 192.168.1.12 1234
       ```
   - **Verify Output**: The client should display the date and time as returned by the server.

---

### Exercise 5: Writing, Compiling, and Executing the Server Application

1. **Objective**: Create, compile, and execute the daytime server application.

2. **Instructions**:
   - **Write Server Code**:
     - On **VM2**, use a text editor to write the server code provided in **Figure 3** and save it as `daytimeServer.c`.
   - **Compile Server Code**:
     - Run the following to create the server executable:
       ```bash
       soc@ubuntu-1404-2/csp: gcc -o daytimeServer daytimeServer.c DieWithMessage.o
       ```
   - **Execute**: Test the server and client interaction as per **Exercise 4**.

3. **Modify and Re-test**:
   - Modify `daytimeServer.c` to include your name with the date and time message.
   - Recompile and re-run the server to verify the modification.