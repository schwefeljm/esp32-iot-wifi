#include <stdio.h>
#include "nvs_flash.h"

#include "globals.h"
#include "log.h"
#include "esp_log.h"
#include "nvs.h"
#include "wifi.h"
#include "httpd.h"
#include "hashmap.h"

void app_main(void)
{
    ESP_LOGI(TAG, "Stating up");
  

    postData = (struct hashMap_s*)malloc(sizeof(struct hashMap_s));
    initializeHashMap(1023);
    insertHashEntry("AnotherTestKey", "ValueTestAnother");
    insertHashEntry("TestKey", "TestAnother");
    char string[] = "ssid=WIFI_SSID&passwd=WIFI&bob=john";
    char delimeter[] = "&";

    createPostHashFromPostData(string, delimeter);

    printf("%s\n", searchHashEntry("AnotherTestKey"));
    printf("%s\n", searchHashEntry("TestKey"));
//    printf("%s\n", searchHashEntry("ssid"));
//    printf("%s\n", searchHashEntry("passwd"));

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