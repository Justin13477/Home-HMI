idf_component_register(
    SRCS "ui_build.c" "ui_pages.c" "ui_styles.c"

    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"

    REQUIRES ui lvgl
    )