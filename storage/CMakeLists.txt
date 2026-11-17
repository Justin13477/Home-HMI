idf_component_register(
    SRCS "storage_manager.c"
    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"
    REQUIRES
        bsp_sd
)