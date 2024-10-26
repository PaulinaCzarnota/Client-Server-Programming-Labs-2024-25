# Lab 3: Setting up the Virtual Network Environment

## Purpose
This lab exercise is intended to establish a virtual network environment using Oracle VM VirtualBox. These virtual machines (VMs) will serve as the foundation for future lab exercises.

---

## Steps

### 1. Download and Install VirtualBox
   - **Objective**: Download and install the Oracle VM VirtualBox Manager on your local machine.
   - **Instructions**: Visit the [Oracle VirtualBox download page](https://www.virtualbox.org/wiki/Downloads) and select the appropriate version for your host platform. Follow the installation steps as prompted.

### 2. Download Preconfigured Virtual Machines
   - **Objective**: Obtain and set up the VMs to use for network configuration and testing.
   - **Instructions**:
     - Download `2xUbuntuVMs.7z` from the Resources folder and unzip it.
     - Open the `Ubuntu14.04-1` folder and double-click the `Ubuntu14.04-1.vbox` file to load the VM in VirtualBox Manager.
     - To add a second VM, go to the **Machine** tab, select **Add**, and navigate to `Ubuntu14.04-2` on the D: drive. Select the `Ubuntu14.04-2.vbox` file.

---

## Exercises

### Exercise 1: Configuring Network Adapters

1. **Objective**: Configure network adapters for each VM to ensure they can communicate effectively.
   
2. **Instructions**:
   - For each VM, click on the machine’s icon in VirtualBox Manager and go to **Settings > Network**:
     - **Adapter 1**: Set to NAT mode. Enable both **Enable Network Adapter** and **Cable Connected**. Open **Port Forwarding** and verify the following mappings:
       - **VM1**: Host Port `2122` -> Guest Port `22`
       - **VM2**: Host Port `2222` -> Guest Port `22`
     - **Adapter 2**: Set to Internal Network. Enable **Enable Network Adapter** and **Cable Connected**.

### Exercise 2: Starting the VMs and Initial Login

1. **Objective**: Launch each VM and log in with the provided credentials.
   
2. **Instructions**:
   - In VirtualBox Manager, select each VM and click **Start**. Close any gray dialog boxes that appear as the machine boots.
   - **Login credentials**:
     - **Username**: `soc`
     - **Password**: `letmein`

### Exercise 3: Configuring Network Interfaces

1. **Objective**: Assign unique IP addresses to each VM to allow connectivity.
   
2. **Instructions**:
   - Refer to the **Linux Network Configuration PDF** for detailed steps, including screenshots, for setting unique IP addresses on each VM.
   - After configuring each IP address, reboot the VM using:
     ```bash
     soc@ubuntu-1404-2: sudo reboot
     ```

3. **Connecting to the VMs from the Lab Host**:
   - Use **PuTTY** or **WinSCP** with the following configuration:
     - **Connection Type (PuTTY)**: SSH
     - **File Protocol (WinSCP)**: SFTP
     - **Hostname (IP Address)**: `localhost`
     - **Port**: `2122` (Ubuntu14.04-1), `2222` (Ubuntu14.04-2)

### Exercise 4: Installing GCC on Each VM

1. **Objective**: Install the `gcc` compiler on each VM to enable compiling applications.

2. **Instructions**:
   - Log into each VM using PuTTY and run the following commands:
     ```bash
     soc@ubuntu-1404-2: sudo apt-get update
     soc@ubuntu-1404-2: sudo apt-get install gcc
     ```
   - **Check the GCC Version**:
     ```bash
     soc@ubuntu-1404-2: gcc --version
     ```

---

## Finalizing the Lab: Preserving VM States

- **Objective**: Ensure that the state and any created files are saved after the lab session.
- **Instructions**:
  - Perform an **ACPI Shutdown** from the **Machine** tab in VirtualBox Manager for each VM. This will save the VM state, preserving any session progress.