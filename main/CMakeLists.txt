idf_component_register(
    SRCS "main.c" "system_init.c"

    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"

    REQUIRES
        bsp_extra
        bsp_display
        bsp_illuminate
        bsp_i2c
        components
        esp_hw_support
        esp_timer
        freertos
        log
        lvgl__lvgl
        network
        ui
        data
)