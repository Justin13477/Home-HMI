idf_component_register(
    SRCS "gray-bg-120x100.c" "gray-bg-120x120.c" "blue-bg-400x210.c" "gray-bg-400x210.c"
    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"
    REQUIRES lvgl__lvgl
)