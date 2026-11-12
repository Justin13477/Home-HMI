idf_component_register(
    SRCS "ui_manager.c"
    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"
    REQUIRES
        components
        freertos
        log
        lvgl__lvgl
        network
        data
)