idf_component_register(
    SRCS "blue-bg-400x210.c" "gray-bg-400x210.c"
    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"
    REQUIRES lvgl__lvgl
)