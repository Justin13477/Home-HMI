idf_component_register(
    SRCS "weather_manager.c"
    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"
    REQUIRES 
    json
    network 
    esp_http_client 
    log
    util
    freertos
)