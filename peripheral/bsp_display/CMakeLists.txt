FILE(GLOB_RECURSE component_sources "*.c")

idf_component_register(SRCS ${component_sources}
                        INCLUDE_DIRS "include"
                        REQUIRES espressif__esp_lcd_touch_gt911 bsp_i2c
                                 freertos log)
