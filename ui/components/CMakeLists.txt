idf_component_register(
    SRCS "ui_build.c" "ui_pages.c" "ui_styles.c" "ui_page_switcher.c"
    INCLUDE_DIRS "include"
    REQUIRES log lvgl__lvgl ui_handlers
)