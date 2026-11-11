idf_component_register(
    SRCS "data_handlers.c"
    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include"
    REQUIRES util json log
)