# Senior Design Capstone Project
This is an ESP32 project that will demonstrate a powerline based ESP32 Smart Home system.

## Overview
Plug-and-play smart home integration to connect and control IoT devices over powerline and Matter standard.
The project consists of two parts:
1. Hardware
2. Software

## Hardware
For the hardware, we have created a PCB based on a ESP32-S3 with built in ethernet jack (RJ45). This PCB serves as hardware attached on top of the WisLink LX200V20 EVB boards.

## Software
For software, we have coding in C

## Project Structure
The project follows the recommended project structure for ESP32 applications:
- `hub/`: This folder serves as the guide for setup of a Matter hub.
- `nodes/`: This folder serves as the guide for setup and installation of an individual node(s)
- `Docs/`: This folder serves as documentation for the P-LINKED project.
- `ESP32_S3_ETH/`: This folder serves as the KiCad project file for the project.

## Getting Started
To get started, first go to [Docs](https://github.com/znicholson17/P-Linked/tree/main/Docs) folder and read the [INSTALL.md](https://github.com/znicholson17/P-Linked/blob/main/Docs/INSTALL.md).
From there, build your applications using BUILD.md and commission using COMMISSION.md


### Authors

- [Zachary Nicholson](https://github.com/znicholson17)
- [Theodore Tang](https://github.com/leunknown)
