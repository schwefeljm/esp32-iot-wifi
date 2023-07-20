#include <stdio.h>
#include "nvs_flash.h"

#include "globals.h"
#include "log.h"
#include "esp_log.h"
#include "nvs.h"
#include "wifi.h"
#include "httpd.h"
#include "utils.h"
#include "interrupt.h"

void app_main(void)
{
    ESP_LOGI(TAG, "Stating up");
  
    globals_init();


    ESP_ERROR_CHECK(gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_pull_mode(interruptPinMap[0], GPIO_PULLUP_ONLY));
    ESP_ERROR_CHECK(gpio_set_direction(interruptPinMap[0], GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_pull_mode(LED_PIN, GPIO_PULLDOWN_ONLY));
 
    config_interrupts();

    bool wifi_initialized = init_wifi(false);
    if (wifi_initialized) 
    {
        init_web_page_buffer();
        //httpd_handle_t* http = setup_server();
        setup_http_server();
    }


    ESP_LOGI(TAG, "Initialization COMPLETE!");

};