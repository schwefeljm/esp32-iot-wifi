#ifndef globals
    #define globals
    //#include "nvs_flash.h"

    typedef struct wifi_connection_s
    {  
        int32_t mode;
        char* ssid;
        char* passwd;
    } wifi_connection_s;

    typedef struct iot_configuration_s
    {
        wifi_connection_s wifi_settings_t;
    } iot_configuration_s;

    #ifdef  MAIN_FILE
        nvs_handle_t handle;
        iot_configuration_s iot_configuration_t;
        

    #else
        extern nvs_handle_t handle;
        extern iot_configuration_s iot_configuration_t;
    #endif



#endif