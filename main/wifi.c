#include <string.h>
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs.h"
#include "log.h"

#include "wifi.h"
#include "globals.h"


bool init_wifi(bool override)
{

    iot_configuration_t.wifi_settings_t = get_wifi_settings_from_nvs();
    switch (iot_configuration_t.wifi_settings_t.mode) 
    {
        case -1:
        //Put panic here
        break;

        //Factory Default in AP Mode
        case 1:
        wifi_init_softap(iot_configuration_t.wifi_settings_t);

    }

    return true;
}


wifi_connection_s get_wifi_settings_from_nvs()
{
    struct wifi_connection_s settings;
    settings.mode = nvs_load_int_value_if_exist("wifi-mode");
    settings.ssid = nvs_load_str_value_if_exist("wifi-ssid");
    settings.passwd = nvs_load_str_value_if_exist("wifi-passwd"); 

    return settings;
}



//static const char *TAG = "Jason's App";

//wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
  if (event_id == WIFI_EVENT_AP_STACONNECTED) {
      wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
      ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                MAC2STR(event->mac), event->aid);
  } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
      wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
      ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                MAC2STR(event->mac), event->aid);

  }
}


void wifi_init_softap(wifi_connection_s settings)
    {
    ESP_LOGI(TAG, "WiFi Start");
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));

    ESP_LOGI(TAG, "esp_event_handler_instance_register Complete");
    wifi_config_t wifi_config = {
        .ap = {
            .channel = 5,
            .max_connection = 1,
            .authmode = WIFI_AUTH_WPA2_PSK,
            .pmf_cfg = {
                    .required = true,
            },
        },
  };

    strncpy((char*)wifi_config.ap.ssid, (char*)settings.ssid, 32);
    strncpy((char*)wifi_config.ap.password, (char*)settings.passwd, 64);
  
  

    ESP_LOGI(TAG, "AP Configuration Complete.");

    ESP_LOGI(TAG, "Mode set to AP.");
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_LOGI(TAG, "Enabling WIFI.");
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_LOGI(TAG, "Starting AP.");
    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s", settings.ssid, settings.passwd);

  
    ESP_ERROR_CHECK(esp_wifi_start());

  
}

