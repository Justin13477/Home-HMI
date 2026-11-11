FILE(GLOB_RECURSE component_sources "*.c")

set(i2c_driver_dependency driver)
if(IDF_VERSION_MAJOR GREATER_EQUAL 6)
    set(i2c_driver_dependency esp_driver_i2c)
endif()

idf_component_register(SRCS ${component_sources}
                        INCLUDE_DIRS "include"
                        REQUIRES ${i2c_driver_dependency} log)
