#ifndef globals
    #define globals
    #include "nvs_flash.h"

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

    typedef struct hashMap_s
    {
	    // Current number of elements in hashMap
    	// and capacity of hashMap
    	int numOfElements, capacity;

	    // hold base address array of linked list
	    struct node_s** arr;
    } hashMap_s;

    typedef struct node_s {

        // key is string
        char* key;

        // value is also string
        char* value;
        struct node_s* next;
    } node_s;


    #ifdef  MAIN_FILE
        nvs_handle_t handle;
        iot_configuration_s iot_configuration_t;
        hashMap_s hashMap;
        //node_s node;
        struct hashMap_s* postData;

    #else
        extern nvs_handle_t handle;
        extern iot_configuration_s iot_configuration_t;
        extern hashMap_s hashMap;
        extern struct hashMap_s* postData;


    #endif



#endif