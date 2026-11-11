idf_component_register(
    SRCS "mqtt_manager.c" "wifi_manager.c"

    INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include"

    REQUIRES esp_wifi mqtt freertos esp_hw_support 
             esp_netif nvs_flash esp_event util
)