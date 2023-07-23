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
//#include "esp_sleep.h"
#include "sleep.h"
//#include <sys/time.h>
//#include "driver/uart.h"
//#include "esp_timer.h"
//#include "mqtt_client.h"
#include "mqtt.h"



#define wakePin GPIO_NUM_0
#define GPIO_WAKEUP_NUM wakePin
#define TIMER_WAKEUP_TIME_US    (2 * 1000 * 1000)




void app_main(void)
{
    ESP_LOGI(TAG, "Stating up");
    //gpio_set_level(GPIO_NUM_1, 1);



    globals_init();

 
    ESP_ERROR_CHECK(gpio_set_pull_mode(LED_PIN, GPIO_PULLDOWN_ONLY));
    ESP_ERROR_CHECK(gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_pull_mode(interruptPinMap[0], GPIO_PULLUP_ONLY));
    ESP_ERROR_CHECK(gpio_set_direction(interruptPinMap[0], GPIO_MODE_INPUT));

    config_interrupts();

    bool wifi_initialized = init_wifi(false);
    if (wifi_initialized) 
    {
        //httpd_handle_t* http = setup_server();
        setup_http_server();
    }

    //char* mac_half_low = get_mac_address_half_low();
    ESP_LOGI(TAG, "MAC adEdress last four: %s", mac_half_low);


    // Need to actually check if WiFi is connected.
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    iot_start_mqtt();



    // set_gpio_wake_task();
};


