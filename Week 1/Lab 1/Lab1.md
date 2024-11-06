# Lab 1: Ubuntu 14.04.5 Setup & Basic Linux Commands

## VM Configuration and SSH Access

- **VM Details**: Ubuntu 14.04.5 LTS Server with minimal setup (SSH only).
- **VM Specs**: 512MB RAM, 3GB HDD
- **User**: `soc` / **Password**: `letmein`

### Starting the VMs

1. **Ubuntu14.04-1**:
   - Open the `Ubuntu14.04-1.vbox` file.
   - In VirtualBox, select `Ubuntu14.04-1` and click **Start**.
   
2. **Ubuntu14.04-2**:
   - Open the `Ubuntu14.04-2.vbox` file.
   - Start `Ubuntu14.04-2` in VirtualBox.

### SSH Connections

Using PuTTY:

- **Ubuntu14.04-1**: 
  - **Hostname**: `localhost`
  - **Port**: `2122`
- **Ubuntu14.04-2**:
  - **Hostname**: `localhost`
  - **Port**: `2222`

---

## Essential Linux Commands

### Directory & File Management

- `ls`: List directory contents (use `-l` for details, `-a` for hidden files).
- `cd [directory]`: Change directory (`cd ..` to go up one level).
- `mkdir [directory]`: Create a new directory.
- `rm [file]`: Remove a file (`-r` for directories).
- `cp [source] [destination]`: Copy files or directories (`-r` for recursive copy).
- `mv [source] [destination]`: Move/rename files or directories.

### File Viewing & Editing

- `cat [file]`: Display file content.
- `more [file]`: Paginate file content.
- `nano [file]`: Edit files in Nano.
  
### System & Disk Info

- `df -h`: Show disk space.
- `du -h [directory]`: Show disk usage for a directory.
- `free -m`: Show memory usage.
- `uname -a`: Display system info.

### Network Commands

- `ifconfig`: Show network configuration.
- `ping [host]`: Test connectivity.
- `netstat -tuln`: Show network connections.

### Process Management

- `ps aux`: View active processes.
- `top`: Real-time process monitor.
- `kill [PID]`: Terminate a process.

### Updates & Package Management

- `sudo apt-get update`: Update package lists.
- `sudo apt-get upgrade`: Upgrade installed packages.
- `sudo apt-get install [package]`: Install a package.

### Help & Manuals

- `man [command]`: Command manual.
- `[command] --help`: Basic command usage.

---

## Apollo Server Access (University Only)

1. Connect to **Apollo** using PuTTY:
   - **Hostname**: `147.252.250.34`
   - **Port**: `22`
2. Login with University credentials.

---

## Reference Resource

- **[Dr. Bob’s Low Fat Linux](http://lowfatlinux.com)**: A comprehensive Linux/Unix online guide.