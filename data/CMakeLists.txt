idf_component_register(
    SRCS "data_manager.c"
    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"
    REQUIRES
        freertos
        json
        log
        lvgl__lvgl
        network
        util
        data_handlers
)