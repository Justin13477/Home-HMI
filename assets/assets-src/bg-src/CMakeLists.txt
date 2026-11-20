idf_component_register(
    SRCS "blue-bg.c" "gray-bg.c"
    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"
    REQUIRES lvgl__lvgl
)