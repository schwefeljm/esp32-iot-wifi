#ifndef nvs
    #define nvs
    #include "nvs_flash.h"
    #include "globals.h"

    bool iot_nvs_set_str_value_if_exist(const char* key, char* value);
    char* iot_nvs_load_str_value_if_exist(const char* key);
    
    int32_t iot_nvs_load_int_value_if_exist(const char* key);
    bool iot_nvs_set_int_value_if_exist(const char* key, int32_t value);

    nvs_handle_t iot_init_flash(nvs_handle_t handle, char* namespace);


#endif