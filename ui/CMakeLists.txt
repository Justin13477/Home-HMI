idf_component_register(
    SRCS "state_data_manager.c"
    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"
    REQUIRES
        components
        esp_wifi
        freertos
        json
        log
        lvgl__lvgl
        network
        util
        data
)