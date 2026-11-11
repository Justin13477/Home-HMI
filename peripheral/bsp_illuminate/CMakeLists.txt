FILE(GLOB_RECURSE component_sources "*.c")

idf_component_register(SRCS ${component_sources}
                        INCLUDE_DIRS "include"
                        REQUIRES driver log espressif__esp_lcd_ek79007
                                 lvgl__lvgl espressif__esp_lvgl_port
                                 bsp_display)
                        