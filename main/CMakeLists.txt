idf_component_register(SRCS 
                            "nvs.c"
                            "wifi.c"
                            "httpd.c"
                            "main.c"
                            "globals.c"
                            "utils.c"
                    INCLUDE_DIRS "." "./include")
target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-error=uninitialized -Wno-error=format-overflow)
spiffs_create_partition_image(storage ../data FLASH_IN_PROJECT)