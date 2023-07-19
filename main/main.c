#include <stdio.h>
#include "nvs_flash.h"

#include "globals.h"
#include "log.h"
#include "esp_log.h"
#include "nvs.h"
#include "wifi.h"
#include "httpd.h"
#include "utils.h"

void app_main(void)
{
    ESP_LOGI(TAG, "Stating up");
  
    globals_init();


    bool wifi_initialized = init_wifi(false);
    if (wifi_initialized) 
    {
        init_web_page_buffer();
        //httpd_handle_t* http = setup_server();
        setup_http_server();
    }






    //invalid_nvs_return[0] = 0x18; // ASCII Cancel character

    //iot_nvs_user_handle = iot_init_flash(iot_nvs_user_handle, "user_config");

    //handle = iot_nvs_user_handle;
/* 
    char string[] = "wifi-ssid=fuck&wifi-passwd=duckduck";
    char delimeter[] = "&";

    int count = tokenCount(string, delimeter);
	
    char* tokenArray[count+1];

    stringSplitter(string, delimeter, tokenArray);

    for(int i = 0; i <= count; i++) 
    {
        char* paramArray[2];
        printf("Token Array: %s", tokenArray[1]);
        
        stringSplitter(tokenArray[i], "=", paramArray);
        printf("Paramarray: %s ====== %s", paramArray[0], paramArray[1]);
        char* curKey = iot_nvs_load_str_value_if_exist(paramArray[0]);
        printf("Current NVS:\tKey: %s\tValue: %s\n", paramArray[0], curKey);
        printf("-----------------------------------------------------\n\n\n\n");
        bool setKey = iot_nvs_set_str_value_if_exist(paramArray[0], paramArray[1]);
        char* newKey = iot_nvs_load_str_value_if_exist(paramArray[0]);
        printf("New NVS:\tKey: %s\tValue: %s\n", paramArray[0], newKey);
        printf("-----------------------------------------------------\n\n\n\n");


    }

 */

    //iot_nvs_set_str_value_if_exist(tokenArray[0], tokenArray[1]);

/*
    int count = tokenCount(string, delimeter);
	char* tokenArray[count+1];
    
    stringSplitter(string, delimeter, tokenArray);



    int arrayElements = (sizeof(tokenArray) / sizeof(tokenArray[0]));
    for(int i=0; i <= arrayElements-1; i++)
    {
        char* paramArray[2]; // params are just key/value pairs. Always 2
        printf("%s -- %i\n", tokenArray[i], strlen(tokenArray[i]));
        int stringSize = strlen(tokenArray[i]);
        char string[stringSize];
        strncpy((char*)string, (char*)tokenArray[i], stringSize);

        //strncpy((char*)string, (char*)tokenArray[i], sizeof(tokenArray[i]));
        char delimeter[] = "=";
        stringSplitter(string, delimeter, paramArray);
        //printf("\n---------------------------\n%s:%s\n-------------------------\n", paramArray[0], paramArray[1]); 
        //printf("\n---------------------------\n%s:%s\n-------------------------\n", paramArray[0], paramArray[1]); 

    }
    
  */ 

// Initialize Globals
    //handle = init_flash(handle, "user_config");
    
    //printf("%s\n", postSearch("ssid"));
    //printf("%s\n", postSearch("passwd"));


/*   
    bool wifi_initialized = init_wifi(false);
    if (wifi_initialized) 
    {
        init_web_page_buffer();
        //httpd_handle_t* http = setup_server();
        setup_http_server();
    };

  */
 

    ESP_LOGI(TAG, "Initialization COMPLETE!");

};