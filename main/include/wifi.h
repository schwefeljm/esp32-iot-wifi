#ifndef wifi
    #define wifi

    #include "nvs_flash.h"




    struct wifi_connection_s get_wifi_settings_from_nvs();
    bool init_wifi(bool override);

    //static void wifi_event_handler(void*, esp_event_base_t, int32_t, void*);
    void wifi_init_softap(struct wifi_connection_s settings);
    void wifi_init_sta(wifi_connection_s settings);
    //wifi_init_config_t cfg;

#endif