file(GLOB ASSET_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/*.c"
)

idf_component_register(
    SRCS ${ASSET_SOURCES}
    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"
    REQUIRES lvgl__lvgl
)