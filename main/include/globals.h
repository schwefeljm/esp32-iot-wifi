#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "driver/gpio.h"



#ifndef globals
    #define globals



    #define IOT_WIFI_MODE                   wifi-mode
    #define IOT_WIFI_SSID                   wifi-ssid
    #define IOD_WIFI_PASSWORD               wifi-passwd
    #define ESP_INTR_FLAG_DEFAULT           0 
    #define LED_PIN                         GPIO_NUM_1
    #define GPIO_WAKEUP_LEVEL_HIGH          1
    #define GPIO_WAKEUP_LEVEL_LOW           0

    void globals_init(void);

    typedef struct wifi_connection_s
    {  
        int32_t mode;
        char* ssid;
        char* passwd;
    } wifi_connection_s;

    typedef struct iot_configuration_s
    {
        wifi_connection_s wifi_settings;
    } iot_configuration_s;


    #ifdef  GLOBALS_FILE
        nvs_handle_t iot_nvs_user_handle;
        nvs_handle_t handle;
        iot_configuration_s iot_configuration;
        char* invalid_nvs_return;
            

        QueueHandle_t interputQueue;
        int interruptPinMap[8] = {GPIO_NUM_0
                                ,GPIO_NUM_1
                                ,INT32_MAX
                                ,INT32_MAX
                                ,INT32_MAX
                                ,INT32_MAX
                                ,INT32_MAX
                                ,INT32_MAX
                                };

    #else
        extern nvs_handle_t iot_nvs_user_handle;
        extern nvs_handle_t handle;
        extern iot_configuration_s iot_configuration;
        extern char* invalid_nvs_return;
        extern QueueHandle_t interputQueue;
        extern int interruptPinMap[];


    #endif

#endif

