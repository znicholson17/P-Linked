#include "wifi.h"
#include "esp_err.h"
#include "esp_mac.h"
#include "esp_netif_ip_addr.h"
#include "esp_netif_types.h"
#include "esp_wifi.h"
#include "esp_wifi_default.h"
#include "esp_wifi_types.h"


/** DEFINES **/
#define WIFI_SUCCESS 1 << 0
#define WIFI_FAILURE 1 << 1
#define TCP_SUCCESS 1 << 0
#define TCP_FAILURE 1 << 1
#define MAX_FAILURES 10
#define MAX_CONN 4
#define PORT 6789
#define ADDR 0x3d00000a

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1
/** GLOBALS **/

// event group to contain status information
static EventGroupHandle_t s_wifi_event_group;

// retry tracker
static int s_retry_num = 0;

// task tag
static const char *TAG_AP = "WIFI SoftAP";
#define SoftAP_SSID "ESP_Wifi"
#define SoftAP_PWORD "password"
static const char *TAG_STA = "WIFI STA";
#define STA_SSID "HZ AX"
#define STA_PWORD "ZachHillary66103"
#define EXAMPLE_ESP_MAXIMUM_RETRY 50


/** FUNCTIONS **/

//event handler for wifi events
static void wifi_apsta_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
	if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED){
    wifi_event_ap_staconnected_t *event = (wifi_event_ap_staconnected_t *) event_data;
    ESP_LOGI(TAG_AP, "Station"MACSTR"joined, AID=%d", 
              MAC2STR(event->mac), event->aid);
  } else if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED){
    wifi_event_ap_stadisconnected_t *event = (wifi_event_ap_stadisconnected_t *) event_data;
    ESP_LOGI(TAG_AP, "Station"MACSTR" left, AID = %d", 
                      MAC2STR(event->mac), event->aid);
  } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START){
    esp_wifi_connect();
    ESP_LOGI(TAG_STA, "Station Started");

  } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP){
    ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
    ESP_LOGI(TAG_STA, "Got IP:"IPSTR, IP2STR(&event->ip_info.ip));
    s_retry_num = 0;
    xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
  }
}

//event handler for wifi sta only
static void wifi_sta_event_handler(void* arg, esp_event_base_t event_base, 
                                   int32_t event_id, void* event_data){
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
        ESP_LOGI(TAG_STA, "Station has started");

    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG_STA, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG_STA,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG_STA, "Got IP:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}


// initialize SoftAPmain.c
esp_netif_t *wifi_init_softap(void){
  esp_netif_t *esp_netif_ap = esp_netif_create_default_wifi_ap();

  wifi_config_t wifi_ap_config = {
    .ap = {
          .ssid = SoftAP_SSID, 
          .ssid_len = strlen(SoftAP_SSID), 
          .password = SoftAP_PWORD, 
          .max_connection = MAX_CONN, 
          .authmode = WIFI_AUTH_WPA2_PSK, 
          .pmf_cfg = {
                      .required = false, 
          },
    },
  };

  if (strlen(SoftAP_PWORD) == 0){
    wifi_ap_config.ap.authmode = WIFI_AUTH_OPEN;
  }

  ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_ap_config));
 
  ESP_LOGI(TAG_AP, "wifi_init_softap finished. SSID = %s", SoftAP_SSID);
  
  return esp_netif_ap;
}


// connect to wifi as station and return the result
esp_netif_t *wifi_init_sta(void)
{
	esp_netif_t *esp_netif_sta = esp_netif_create_default_wifi_sta();

	

    /** START THE WIFI DRIVER **/
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = STA_SSID,
            .password = STA_PWORD,
            .scan_method = WIFI_ALL_CHANNEL_SCAN,
	          .threshold.authmode = WIFI_AUTH_WPA2_PSK,
            .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
        },
    };


    // set the wifi config
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );

    // start the wifi driver

    ESP_LOGI(TAG_STA, "STA initialization complete");

    return esp_netif_sta;
}


void wifi_begin(void)
{

	//initialize the esp network interface
	ESP_ERROR_CHECK(esp_netif_init());

	//initialize default esp event loop
	ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    //initialize storage
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
  

    /** EVENT LOOP CRAZINESS **/
	s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_sta_event_handler,
                                                        NULL,
                                                        NULL));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &wifi_sta_event_handler,
                                                        NULL,
                                                        NULL));
   	
    //setup wifi station with the default wifi configuration
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
	
    /*Initialize AP*/

    //ESP_LOGI(TAG_AP, "ESP_WIFI_MODE_AP");
    //esp_netif_t *esp_netif_ap = wifi_init_softap();

    /*initalize STA*/
    ESP_LOGI(TAG_STA, "ESP_WIFI_MODE_STA");
    esp_netif_t *esp_netif_sta = wifi_init_sta();

    /*Start all wifi*/
    ESP_ERROR_CHECK(esp_wifi_start());


    // wait till either connection established or max retries hit

    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group, 
                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);
    if (bits & WIFI_CONNECTED_BIT){
        ESP_LOGI(TAG_STA, "Connected to ap SSID:%s", STA_SSID);
    } else if (bits & WIFI_FAIL_BIT){
        ESP_LOGI(TAG_STA, " Failed to connect to ap SSID:%s", STA_SSID);
    } else {
        ESP_LOGE(TAG_STA, "UNEXPECTED EVENT");
        return;
    }

    /* Set sta as the default interface */
    esp_netif_set_default_netif(esp_netif_sta);

    /* Enable napt on the AP netif */
  //  if (esp_netif_napt_enable(esp_netif_ap) != ESP_OK) {
     //   ESP_LOGE(TAG_STA, "NAPT not enabled on the netif: %p", esp_netif_ap);
   // }
  	/*status = connect_tcp_server();
  	if (TCP_SUCCESS != status)
	  {
		  ESP_LOGI(TAG, "Failed to connect to remote server, dying...");
  		return;
        }*/
}
