#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "socket_server.h"
#include "wifi.h"

#define pdSECOND pdMS_TO_TICKS(1000)

static const char* TAG = "Main";
void app_main() {
    esp_log_level_set(TAG, ESP_LOG_INFO);
    
    
    wifi_begin();
    socket_server_init();
    socket_server_start();

    while (1) {
        // Your main application code can go here
        //
        vTaskDelay(pdSECOND * 2);
    }
}
    
