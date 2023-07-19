#include "nvs_flash.h"
#include "log.h"
#define MAIN_FILE
#include "globals.h"

#include "nvs.h"



char* iot_nvs_load_str_value_if_exist(const char* key)
{
  
    // Try to get the size of the item
    size_t value_size;
    if(nvs_get_str(handle, key, NULL, &value_size) != ESP_OK){
        ESP_LOGE(TAG, "Failed to get size of key: %s", key);
        // This will crash program
        return NULL;
    }

    char* value = malloc(value_size);
    if(nvs_get_str(handle, key, value, &value_size) != ESP_OK){
        ESP_LOGE(TAG, "Failed to load key: %s", key);
        // This will crash program
        return NULL;
    }
    // Need to fix this
    return value;
}

bool iot_nvs_set_str_value_if_exist(const char* key, char* value)
{
    size_t value_size;
    if(nvs_get_str(handle, key, NULL, &value_size) == ESP_OK)
    {
        if(nvs_set_str(handle, key, value) == ESP_OK)
        {
            return true;
        }
        else
        {
            return false;
        }
    } 
    return false;

}

bool iot_nvs_set_int_value_if_exist(const char* key, int32_t value)
{
    int32_t value_pass = value;
    if(nvs_set_i32(handle, key, value_pass) == ESP_OK)
    {
        return true;
    } 

    return false;

}

int32_t iot_nvs_load_int_value_if_exist(const char* key)
{
    int32_t value = -1;
  
    esp_err_t err = nvs_get_i32(handle, key, &value);
    assert(err == ESP_OK || err == ESP_ERR_NVS_NOT_FOUND); //Should I change this?
    // if ESP_ERR_NVS_NOT_FOUND was returned, max_buffer_size will still
    // have its default value.
    return value;
}


nvs_handle_t iot_init_flash(nvs_handle_t handle, char* namespace) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) 
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(nvs_open(namespace, NVS_READWRITE, &handle) != ESP_OK);

    ESP_ERROR_CHECK(ret); 
    
    return handle;
};
