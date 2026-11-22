file(GLOB ASSET_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/bg-src/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/icons-src-48/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/icons-src-128/*.c"
)

idf_component_register(
    SRCS ${ASSET_SOURCES}
    INCLUDE_DIRS
        "."
        "bg-src/include"
        "icons-src-48/include"
        "icons-src-128/include"
    REQUIRES lvgl__lvgl
)