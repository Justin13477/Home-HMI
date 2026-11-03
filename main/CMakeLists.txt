idf_component_register(SRCS "main.c" "ui_build.c" "ui_styles.c" "ui_pages.c" "state_data_manager.c" "system_init.c"
                        INCLUDE_DIRS "include" 
                        REQUIRES bsp_extra bsp_display bsp_illuminate bsp_i2c
                                 esp_hw_support esp_timer freertos lvgl)
                                 