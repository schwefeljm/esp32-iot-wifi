#ifndef httpd
    #define httpd
    #include "esp_http_server.h"

    void init_web_page_buffer(void);
    httpd_handle_t setup_http_server(void);





    //static void list(char *path, char *match);

#endif