# Lab 12 - TCP Operations

## Overview
This lab demonstrates how TCP manages connection establishment, data transfer, and connection termination using the `open_close.pcap` capture file in Wireshark. The exercise involves analyzing TCP messages, including `SYN`, `ACK`, `FIN`, and calculating sequence (`Seq`) and acknowledgment (`Ack`) values.  

---

## Objectives 

1. **Understand Connection Establishment:** Analyze the TCP three-way handshake using `SYN`, `SYN-ACK`, and `ACK`.  
2. **Analyze Data Transfer:** Calculate byte positions using sequence and acknowledgment numbers from the HTTP request/response.  
3. **Understand Connection Termination:** Inspect TCP closing messages using `FIN` and `ACK`.  

---

## Prerequisites

1. **Software:**  
   - **Wireshark:** Network Protocol Analyzer.  

2. **Files:**  
   - `open_close.pcap`.  
---

## Lab Steps and Solutions  

---

### Exercise 1: Installing Wireshark

1. Download the Wireshark zip folder from Brightspace.  
2. Extract the zip file.  
3. Run `wireshark.exe` to launch the program.  

---

### Exercise 2: Analyzing the Capture File

---

### **Step 1: Loading the Packet Capture File**  

1. Launch Wireshark.  
2. Open the file `open_close.pcap`.  
3. Apply a filter to isolate relevant packets using the following command:  

   ```shell
   tcp.port == 42532
   ```

---

### **Step 2: TCP Connection Establishment (Lines 1-3)**  

#### **Observed Packets:**  

- **Line 1:** `SYN` (Client → Server)  
- **Line 2:** `SYN-ACK` (Server → Client)  
- **Line 3:** `ACK` (Client → Server)  

---

#### **Detailed Analysis:**  

1. **Packet 1:** `SYN` (Client → Server)  
   - **Seq:** 0 (Initial sequence number from the client).  
   - **Ack:** Not set (`0`).  
   - **Explanation:** The client initiates the connection by sending a `SYN` segment to request synchronization.

2. **Packet 2:** `SYN-ACK` (Server → Client)  
   - **Seq:** 1000 (Initial sequence number from the server).  
   - **Ack:** 1 (Client's sequence number + 1).  
   - **Explanation:** The server acknowledges the client's `SYN` request and sends its own `SYN`.  

3. **Packet 3:** `ACK` (Client → Server)  
   - **Seq:** 1 (Client's next expected byte).  
   - **Ack:** 1001 (Server's sequence number + 1).  
   - **Explanation:** The client acknowledges the server’s `SYN-ACK`, completing the handshake.

---

### **Step 3: HTTP Request Analysis (Line 4)**  

---

#### **Analyzing Packet 4 - HTTP GET Request**  

1. **Seq Value of Line 4 (HTTP Request):**  
   - **Starting Byte:** Use the `Seq` field from Line 3, which was `1`.  

2. **Calculating the Byte for the First Character `G` in the GET Request:**  
   - Since the HTTP payload starts immediately after the TCP header, the byte number of the first character (`G`) is the value of the `Seq` field from Line 3:  

     ```
     Byte Number of G = Seq Value of Line 3 = 1
     ```

3. **Last Byte of the Request:**  
   - Use the TCP Segment Length from Line 4, representing the payload length (e.g., `150` bytes).  
   - The last byte position will be:  

     ```
     Last Byte = Seq Value of Line 4 + TCP Segment Length - 1
               = 1 + 150 - 1
               = 150
     ```

4. **Verification:**  
   - Look at the `Ack` value in Line 5. It should be `151`, confirming receipt of the entire payload.

---

### **Step 4: HTTP Response Analysis (Line 8)**  

---

#### **Analyzing HTTP Response from Server (Line 8)**  

1. **Starting Byte:** `Seq` value of the server in Line 8.  

2. **Last Byte:** Use the `Seq` value + TCP Segment Length - 1.  

   ```
   Last Byte = Seq Value (Line 8) + TCP Segment Length - 1
   ```

3. **Verification:**  
   - Check the `Ack` field in Packet 9, which should match the last byte + 1.

---

### **Step 5: Connection Termination (Lines 9-15)**  

---

#### **Closing the Connection (TCP Termination)**  

1. **Line 9:** `FIN` (Server → Client)  
   - **Seq:** Last byte of the response segment + 1.  
   - **Ack:** Last byte + 1 of the client request.

2. **Line 10:** `ACK` (Client → Server)  
   - **Seq:** Last byte + 1 of the client request.  
   - **Ack:** Last byte + 1 of the server’s response.  

3. **Line 11:** Duplicate `ACK` for the HTTP Response.  

4. **Line 14:** `FIN` (Client → Server)  
   - **Seq:** Last byte of the client request + 1.  

5. **Line 15:** Final `ACK` (Server → Client)  

---

### **Verification Steps:**  

1. Confirm that the **Server Initiates the Connection Closure** using the `FIN` packet in Line 9.  

2. **Acknowledgment Field Observations:**  
   - **Lines 10 & 11:** Different ACK values confirm acknowledgment of the HTTP response and the first `FIN`.  
   - **Lines 11 & 14:** Same ACK values confirm the server's acknowledgment of the client's `FIN`.  
   - **Lines 9 & 15:** Final acknowledgment by the server, incrementing by one.

---

## **Conclusion**  

This lab demonstrated TCP’s three phases of operation:  

1. **Connection Establishment:** Using `SYN`, `SYN-ACK`, and `ACK` messages.  
2. **Data Transfer:** Tracing sequence and acknowledgment values through HTTP requests and responses.  
3. **Connection Termination:** Understanding how connections close using `FIN` and `ACK` messages.