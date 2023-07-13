#ifndef nvs
    #define nvs
    #include "nvs_flash.h"
    #include "globals.h"

    char* nvs_load_str_value_if_exist(const char* key);
    int32_t nvs_load_int_value_if_exist(const char* key);

    nvs_handle_t init_flash(nvs_handle_t handle, char* namespace);


#endif