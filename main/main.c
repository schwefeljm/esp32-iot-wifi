#include <stdio.h>
#include "nvs_flash.h"

#include "globals.h"
#include "log.h"
#include "esp_log.h"
#include "nvs.h"
#include "wifi.h"
#include "httpd.h"

void app_main(void)
{
    ESP_LOGI(TAG, "Stating up");
    handle = init_flash(handle, "user_config");

    bool wifi_initialized = init_wifi(false);
    if (wifi_initialized) 
    {
        init_web_page_buffer();
        //httpd_handle_t* http = setup_server();
        setup_http_server();
    };


    ESP_LOGI(TAG, "Initialization COMPLETE!");

};