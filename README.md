# Power Line Integrated Network Controlling Electronic Devices (P-LINKED)
## Senior Design Capstone Project
This is an ESP32 project that will demonstrate a powerline based ESP32 Smart Home system.

## Diagram of P-LINKED network

<img src = "https://github.com/znicholson17/P-Linked/blob/main/Docs/Images/P-Linked_Final_NetMap.png" width="500" hiehgt="500">
The diagram shown above describes how nodes and hub communicate with each other. For hub and nodes, the devices are connected to an electrical outlet using a powerline transciever. 
From there, each device communicates over powerline.  
  
  
Each device is limited to a theoretical speed of up to 200Mbps and 300 meters of range for IP access.

## Overview
Plug-and-play smart home integration to connect and control IoT devices over powerline and Matter standard.
The project consists of two parts:
1. Hardware
2. Software

## Hardware
For the hardware, we have created a PCB based on a ESP32-S3 with built in ethernet jack (RJ45). This PCB serves as hardware attached on top of the WisLink LX200V20 EVB boards. In the future, we plan on adapting the powerline module onto the PCB as well.

- Raspberry Pi 4 Model B
- ESP32-S3 
- WisLink LX200V20 EVB
- Custom ESP32-S3 Ethernet PCB

## Software
- [esp-idf](https://docs.espressif.com/projects/esp-idf/en/v5.2/esp32s3/get-started/index.html)
- [esp-matter](https://docs.espressif.com/projects/esp-matter/en/latest/esp32s3/developing.html#)
- [Ubuntu 20.04 LTS](https://ubuntu.com/download/desktop) or later.
- [HomeAssistant](https://www.home-assistant.io/)


## Project Structure
The project follows the recommended project structure for ESP32 applications:
- `hub/`: This folder serves as the guide for setup of a Matter hub.
- `nodes/`: This folder serves as the guide for setup and installation of an individual node(s)
- `Docs/`: This folder serves as documentation for the P-LINKED project.
- `ESP32_S3_ETH/`: This folder serves as the KiCad project file for the project.

## Getting Started
To get started, first go to [Docs](https://github.com/znicholson17/P-Linked/tree/main/Docs) folder and read the [INSTALL.md](https://github.com/znicholson17/P-Linked/blob/main/Docs/INSTALL.md).
From there, build your applications using [BUILD.md](https://github.com/znicholson17/P-Linked/blob/main/Docs/BUILD.md) and commission using [COMMISSION.md](https://github.com/znicholson17/P-Linked/blob/main/Docs/COMMISSION.md)  


### Authors

- [Zachary Nicholson](https://github.com/znicholson17)
- [Theodore Tang](https://github.com/leunknown)
