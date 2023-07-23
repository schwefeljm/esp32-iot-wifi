#include "utils.h"
#include <string.h>
#include "esp_interface.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "hal/efuse_hal.h"
#include "esp_log.h"


void stringSplitter(char *string, char *delimeter, char *tokenArray[])
{
    int tokenArrayPos = 0;
    char* token;

    char* delim = delimeter;
    char* str = string;

    while
            (
            (token = strtok_r(str, delim, &str))
            )
    {
        tokenArray[tokenArrayPos] = token;
        tokenArrayPos++;
    }
}

int tokenCount(char *string, char *delimeter)
{
	const char letter = delimeter[0];
	int count = 0;
	
    for(int i = 0; string[i]; i++)  
    {
    	if(string[i] == letter)
    	{
          count++;
        }
    }
	return count;
}


char* get_mac_address_half_low()
{
    uint8_t mac[6];
    efuse_hal_get_mac(mac);
    char *macLastSix = malloc(7);
    //ESP_LOGI("MAC address", "MAC address successfully set to %02x:%02x:%02x:%02x:%02x:%02x", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
    sprintf((char*)macLastSix, "%02x%02x%02x", mac[2], mac[1], mac[0]);
    //ESP_LOGI("MAC address", "MAC address last four: %s", macLastSix);
    return macLastSix;
}
