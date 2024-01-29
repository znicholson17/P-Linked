#include "socket_client.h"
#include "esp_log.h"
#include "lwip/sockets.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "socket_client";
static const char *SERVER_IP = "";
static const int SERVER_PORT = 12345;




void socket_client_task(void *pvParameters) {
    struct sockaddr_in server_addr;
    int client_socket;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        ESP_LOGE(TAG, "Failed to create socket");
        vTaskDelete(NULL);
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        ESP_LOGE(TAG, "Failed to connect to server");
        close(client_socket);
        vTaskDelete(NULL);
        return;
    }

    while (1) {
        send_sensor_data(client_socket);
        vTaskDelay(pdMS_TO_TICKS(5000));  // Send sensor data every 5 seconds
    }

    close(client_socket);
    vTaskDelete(NULL);
}

