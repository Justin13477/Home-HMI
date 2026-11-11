idf_component_register(
    SRCS "ui_build.c" "ui_pages.c" "ui_styles.c"
    INCLUDE_DIRS "include"
    REQUIRES log lvgl__lvgl ui
)