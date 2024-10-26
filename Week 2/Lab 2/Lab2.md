# Lab 2: Network Traffic Analysis with Wireshark

## Purpose
This lab exercise aims to build an understanding of protocol hierarchy by exploring network traffic captured on a host interface using the Wireshark utility.

---

## Steps

### 1. Wireshark Introduction
   - **Objective**: Learn to capture and analyze packets from a network interface.
   - **Resource**: [YouTube Video - Wireshark Overview](https://www.youtube.com/watch?v=r0l_54thSYU) (19 minutes)

### 2. Generating Traffic
   - **Objective**: Generate network traffic by connecting to an HTTP website.
   - **Instructions**: Visit `http://httpforever.com` to create recognizable HTTP traffic, which will then be captured and analyzed in Wireshark.

---

## Exercises

### Exercise 1: Installing Wireshark

1. **Download Wireshark**:
   - Locate and download the `Wireshark.zip`.
   - Extract the folder and run `wireshark.exe` to launch Wireshark.

2. **Lab Host Capture Limitations**:
   - Note that lab hosts may restrict capturing live traffic from the network interface. 
   - **Alternative**: If using a personal computer, you can capture packets directly from your home network interface.

### Exercise 2: Analyzing Network Traffic

1. **Launching Wireshark**:
   - Open Wireshark and navigate to the `CaptureFiles` folder to access provided sample capture files.
   - Alternatively, if your environment allows live capture, use your network interface to capture real-time traffic from the browser visit to `http://httpforever.com`.

2. **Capturing Live Traffic (if permitted)**:
   - **Start Capture**: Select the network interface and begin capture in Wireshark.
   - **Generate Traffic**: Use a web browser to connect to `http://httpforever.com`.
   - **Stop Capture**: Once the webpage has loaded, stop the capture in Wireshark.
   - **Apply Filter**: Use the filter `http` in the display filter box to focus on HTTP packets.

---

## Analysis and Observations

1. **Wireshark Screen Layout**:
   - Note the three main sections:
     - **Packet List Pane**: Displays captured packets sequentially.
     - **Packet Details Pane**: Shows the protocol details for the selected packet.
     - **Packet Bytes Pane**: Presents the raw byte data of the selected packet.

2. **Header Fields**:
   - Examine the structure and contents of the header fields for each protocol layer, from Ethernet to HTTP.

3. **Addressing Fields**:
   - Observe and identify addressing fields within each layer (e.g., MAC addresses at the Data Link layer, IP addresses at the Network layer, etc.).

4. **Raw Data on the Wire**:
   - Explore the “on the wire” raw data view in the Packet Bytes Pane to understand the exact data transmitted at the physical layer.