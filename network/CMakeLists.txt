idf_component_register(
    SRCS "mqtt_manager.c" "wifi_manager.c"
    INCLUDE_DIRS "include"
    REQUIRES
        esp_event
        esp_hw_support
        esp_netif
        esp_wifi
        freertos
        log
        mqtt
        nvs_flash
        util
)