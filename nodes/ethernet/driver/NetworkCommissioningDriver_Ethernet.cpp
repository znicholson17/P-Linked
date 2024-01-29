/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#include "esp_eth.h"
#include "esp_eth_mac.h"
#include "esp_eth_phy.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_mac.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "sdkconfig.h"
#include <platform/ESP32/NetworkCommissioningDriver.h>

typedef struct {
    uint8_t spi_cs_gpio;
    uint8_t int_gpio;
    int8_t phy_reset_gpio;
    uint8_t phy_addr;
    uint8_t *mac_addr;
}spi_eth_module_config_t;

using namespace ::chip;
using namespace ::chip::DeviceLayer::Internal;
namespace chip {
namespace DeviceLayer {
namespace NetworkCommissioning {

static const char *TAG = "eth_init";


static void on_eth_event(void * esp_netif, esp_event_base_t event_base, int32_t event_id, void * event_data)
{
    switch (event_id)
    {
    case ETHERNET_EVENT_CONNECTED: {
        esp_netif_t * eth_netif = (esp_netif_t *) esp_netif;
        ChipLogProgress(DeviceLayer, "Ethernet Connected");
        ESP_ERROR_CHECK(esp_netif_create_ip6_linklocal(eth_netif));
    }
    break;
    default:
        break;
    }
}

static esp_err_t spi_bus_init(void){

    esp_err_t ret = ESP_OK;


    //static const char *TAG = "eth_init";

    // Install GPIO ISR handler to be able to service SPI Eth modules interrupts
    ret = gpio_install_isr_service(0);
    if (ret != ESP_OK) {
        if (ret == ESP_ERR_INVALID_STATE) {
            ESP_LOGW(TAG, "GPIO ISR handler has been already installed");
            ret = ESP_OK; // ISR handler has been already installed so no issues
        } else {
            ESP_LOGE(TAG, "GPIO ISR handler install failed");
        }
    }

    // Init SPI bus
    spi_bus_config_t buscfg = {
        .mosi_io_num = 12,
        .miso_io_num = 3,
        .sclk_io_num = 11,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));
    //ret = spi_bus_initialize(SPI1_HOST, &buscfg, SPI_DMA_CH_AUTO);
                     
    ESP_ERROR_CHECK(ret);

    return ret;
    
}

static esp_eth_handle_t eth_init_spi(spi_eth_module_config_t *spi_eth_module_config, esp_eth_mac_t **mac_out, esp_eth_phy_t **phy_out){
    
    //esp_eth_handle_t ret = NULL;

   

    // Init specific SPI Ethernet module configuration from Kconfig (CS GPIO, Interrupt GPIO, etc.)
    

    // Init common MAC and PHY configs to default
    eth_mac_config_t mac_config = ETH_MAC_DEFAULT_CONFIG();
    eth_phy_config_t phy_config = ETH_PHY_DEFAULT_CONFIG();

    // Update PHY config based on board specific configuration
    phy_config.phy_addr = spi_eth_module_config->phy_addr;
    phy_config.reset_gpio_num = spi_eth_module_config->phy_reset_gpio;

    // Configure SPI interface for specific SPI module
    spi_device_interface_config_t spi_devcfg = {
        .mode = 0,
        .clock_speed_hz = 50 * 1000 * 1000,
        .spics_io_num = spi_eth_module_config->spi_cs_gpio,
        .queue_size = 20
        
    };
     eth_w5500_config_t w5500_config = ETH_W5500_DEFAULT_CONFIG(SPI2_HOST, &spi_devcfg);
    w5500_config.int_gpio_num = spi_eth_module_config->int_gpio;
    esp_eth_mac_t *mac = esp_eth_mac_new_w5500(&w5500_config, &mac_config);
    esp_eth_phy_t *phy = esp_eth_phy_new_w5500(&phy_config);

    // Init Ethernet driver to default and install it
    esp_eth_handle_t eth_handle;
    esp_eth_config_t eth_config_spi = ETH_DEFAULT_CONFIG(mac, phy);
    ESP_ERROR_CHECK(esp_eth_driver_install(&eth_config_spi, &eth_handle));

    // The SPI Ethernet module might not have a burned factory MAC address, we can set it manually.
    if (spi_eth_module_config->mac_addr != NULL) {
        ESP_ERROR_CHECK(esp_eth_ioctl(eth_handle, ETH_CMD_S_MAC_ADDR, spi_eth_module_config->mac_addr));
    }

     /*if (mac_out != NULL) {
        *mac_out = mac;
    }
    if (phy_out != NULL) {
        *phy_out = phy;
    } */
    //return eth_handle;
    return eth_handle;
//

}
    

CHIP_ERROR ESPEthernetDriver::Init(NetworkStatusChangeCallback * networkStatusChangeCallback)
{
    /* Currently default ethernet board supported is IP101, if you want to use other types of
     * ethernet board then you can override this function in your application. 

    

    // Init MAC and PHY configs to default
    eth_mac_config_t mac_config               = ETH_MAC_DEFAULT_CONFIG();
    eth_phy_config_t phy_config               = ETH_PHY_DEFAULT_CONFIG();
    phy_config.phy_addr                       = CONFIG_ETH_PHY_ADDR;
    phy_config.reset_gpio_num                 = CONFIG_ETH_PHY_RST_GPIO;
    eth_esp32_emac_config_t esp32_emac_config = ETH_ESP32_EMAC_DEFAULT_CONFIG();
    esp32_emac_config.smi_mdc_gpio_num        = CONFIG_ETH_MDC_GPIO;
    esp32_emac_config.smi_mdio_gpio_num       = CONFIG_ETH_MDIO_GPIO;
    esp_eth_mac_t * mac                       = esp_eth_mac_new_esp32(&esp32_emac_config, &mac_config);
    esp_eth_phy_t * phy                       = esp_eth_phy_new_ip101(&phy_config);

    esp_eth_config_t config     = ETH_DEFAULT_CONFIG(mac, phy);
    esp_eth_handle_t eth_handle = NULL;
    ESP_ERROR_CHECK(esp_eth_driver_install(&config, &eth_handle));

    */
    //esp_err_t ret = ESP_OK;
   // esp_err_t err = ESP_OK;

   // ESP_GOTO_ON_ERROR(spi_bus_init(), err, TAG, "SPI bus init failed");
    spi_bus_init();

    spi_eth_module_config_t spi_eth_module_config; 

    spi_eth_module_config.spi_cs_gpio = 10;
    spi_eth_module_config.int_gpio = 9;
    spi_eth_module_config.phy_reset_gpio = 5;
    spi_eth_module_config.phy_addr = 1;

        
    // The SPI Ethernet module(s) might not have a burned factory MAC address, hence use manually configured address(es).
    // In this example, Locally Administered MAC address derived from ESP32x base MAC address is used.
    // Note that Locally Administered OUI range should be used only when testing on a LAN under your control!


    esp_eth_handle_t eth_handle = eth_init_spi(&spi_eth_module_config, NULL, NULL);
















    esp_netif_config_t cfg  = ESP_NETIF_DEFAULT_ETH();
    esp_netif_t * eth_netif = esp_netif_new(&cfg);





    /* attach Ethernet driver to TCP/IP stack */
    ESP_ERROR_CHECK(esp_netif_attach(eth_netif, esp_eth_new_netif_glue(eth_handle)));

    ESP_ERROR_CHECK(esp_event_handler_register(ETH_EVENT, ETHERNET_EVENT_CONNECTED, &on_eth_event, eth_netif));

    ESP_ERROR_CHECK(esp_eth_start(eth_handle));

    return CHIP_NO_ERROR;


    
//err:
        //free(eth_handle);
        //return CHIP_ERROR;
}

} // namespace NetworkCommissioning
} // namespace DeviceLayer
} // namespace chip
