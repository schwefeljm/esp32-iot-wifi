#define GLOBALS_FILE
#include "globals.h"
#include "nvs.h"
#include <string.h>



void globals_init(void)
{

    //invalid_nvs_return[0] = 0x18; // ASCII Cancel character

    iot_nvs_user_handle = iot_init_flash(iot_nvs_user_handle, "user_config");

    handle = iot_nvs_user_handle;

    mac_half_low = get_mac_address_half_low();
};



