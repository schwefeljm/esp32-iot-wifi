#ifndef globals
    #define globals
    #include "nvs_flash.h"


    #define IOT_WIFI_MODE wifi-mode
    #define IOT_WIFI_SSID wifi-ssid
    #define IOD_WIFI_PASSWORD wifi-passwd


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
        

    #else
        extern nvs_handle_t iot_nvs_user_handle;
        extern nvs_handle_t handle;
        extern iot_configuration_s iot_configuration;
        extern char* invalid_nvs_return;
        

    #endif



#endif