#include "socket_server.h"
#include "esp_log.h"
#include "lwip/sockets.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "socket_server";

static void socket_server_task(void *pvParameters) {
    int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket < 0) {
        ESP_LOGE(TAG, "Failed to create socket");
        vTaskDelete(NULL);
        return;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        ESP_LOGE(TAG, "Socket bind failed");
        close(listen_socket);
        vTaskDelete(NULL);
        return;
    }

    if (listen(listen_socket, 5) < 0) {
        ESP_LOGE(TAG, "Socket listen failed");
        close(listen_socket);
        vTaskDelete(NULL);
        return;
    }

    ESP_LOGI(TAG, "Socket server started");

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket = accept(listen_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            ESP_LOGE(TAG, "Socket accept failed");
            break;
        }

        const char *response = "Hello, ESP32!\n";
        send(client_socket, response, strlen(response), 0);
        close(client_socket);
    }

    close(listen_socket);
    vTaskDelete(NULL);
}

void socket_server_init(void) {
    // You can add any initialization code here.
}

void socket_server_start(void) {
    xTaskCreate(&socket_server_task, "socket_server_task", 2048, NULL, 5, NULL);
}

