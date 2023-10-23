# My WIP Senior Design Capstone

This is an ESP32 project that will demonstrate a powerline based ESP32 Smart Home system.

## Project Structure

The project follows the recommended project structure for ESP32 applications. The key directories and files are organized as follows:

- `components/`: Custom ESP32 components
    - `socket_server/`: Custom component for the socket server functionality
- `main/`: Main application source code
- `CMakeLists.txt`: Top-level CMake configuration for the entire project
- `sdkconfig`: Project-specific ESP-IDF configuration
- `README.md`: Project documentation

## Getting Started

To build and run this project on your ESP32-S3, follow these steps:

1. Set up your development environment by installing the ESP-IDF framework. Follow the instructions in the [ESP-IDF documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html).

2. Clone or download this project to your development environment.

3. Configure your Wi-Fi credentials:
    - Open the `sdkconfig` file.
    - Update `CONFIG_WIFI_SSID` and `CONFIG_WIFI_PASSWORD` with your Wi-Fi network name (SSID) and password.

4. Build the project:
    ```bash
    idf.py build
    ```

5. Flash the project to your ESP32-S3:
    ```bash
    idf.py -p (PORT) flash
    ```
   Replace `(PORT)` with the COM port or USB device of your ESP32-S3.

6. Monitor the output:
    ```bash
    idf.py -p (PORT) monitor
    ```
   This will display the serial output of your ESP32-S3.

Your ESP32-S3 will start as a Wi-Fi station, create a socket server, and listen for incoming connections.

## Customization

- You can extend the functionality of the project by adding custom components or features to the `components/` directory.
- Modify the `main/main.c` file to include additional application-specific code.

## License

This project is distributed under the MIT License. See [LICENSE](LICENSE) for more details.

## Acknowledgments

This project is based on the ESP-IDF framework and follows best practices recommended by Espressif.

## Author

- [Zachary Nicholson](https://github.com/znicholson17)
