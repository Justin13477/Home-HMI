idf_component_register(SRCS "main.c" "ui_build.c" "ui_styles.c" "ui_pages.c" "state_data_manager.c" "tag_map.c"
                             "system_init.c" "wifi_manager.c" "mqtt_manager.c"
                        INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"
                        REQUIRES bsp_extra bsp_display bsp_illuminate bsp_i2c
                                 esp_event esp_hw_support esp_netif esp_timer
                                 esp_wifi freertos json lvgl mqtt nvs_flash)
                                 