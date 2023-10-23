#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "socket_server.h"
#include "wifi.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "ssd1306.h"

#define pdSECOND pdMS_TO_TICKS(1000)

static const char* TAG = "Main";

#define I2C_MASTER_SCL_IO 19        /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 18       /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM 0 /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ 100000   /*!< I2C master clock frequency */

static ssd1306_handle_t ssd1306_dev = NULL;

void app_main() {
    esp_log_level_set(TAG, ESP_LOG_INFO);
    
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = (gpio_num_t)I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = (gpio_num_t)I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);

    ssd1306_dev = ssd1306_create(I2C_MASTER_NUM, SSD1306_I2C_ADDRESS);
    ssd1306_refresh_gram(ssd1306_dev);
    ssd1306_clear_screen(ssd1306_dev, 0x00);

    char data_str[10] = {0};
    sprintf(data_str, "P LINKED");
    ssd1306_draw_string(ssd1306_dev, 0, 16, (const uint8_t *)data_str, 16, 1);
    ssd1306_refresh_gram(ssd1306_dev);

    gpio_config_t button_io_conf;
    button_io_conf.intr_type = GPIO_INTR_NEGEDGE; // Trigger on the falling edge (button press)
    button_io_conf.pin_bit_mask = (1ULL << 5);
    button_io_conf.mode = GPIO_MODE_INPUT;
    button_io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    button_io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&button_io_conf);
    
    wifi_begin();
    socket_server_init();
    socket_server_start();

    while (1) {
        // Your main application code can go here
        //
        if(!gpio_get_level(5)){
            char data_str[10] = {0};
            sprintf(data_str, "Temp: 27C");
            ssd1306_draw_string(ssd1306_dev, 0, 16, (const uint8_t *)data_str, 16, 1);
            ssd1306_refresh_gram(ssd1306_dev);

            vTaskDelay(pdSECOND * 5);
            ssd1306_clear_screen(ssd1306_dev, 0x00);

        }
        char data_str[10] = {0};
        sprintf(data_str, "P LINKED");
        ssd1306_draw_string(ssd1306_dev, 0, 16, (const uint8_t *)data_str, 16, 1);
        ssd1306_refresh_gram(ssd1306_dev);

    }
}
    
