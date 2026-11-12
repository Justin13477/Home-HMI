idf_component_register(
    SRCS "ui_build_handlers.c"
    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"
    REQUIRES lvgl data
)