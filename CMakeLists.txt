# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS
    "${CMAKE_CURRENT_LIST_DIR}/peripheral"
    "${CMAKE_CURRENT_LIST_DIR}/network"
    "${CMAKE_CURRENT_LIST_DIR}/ui"
    "${CMAKE_CURRENT_LIST_DIR}/ui/components"
    "${CMAKE_CURRENT_LIST_DIR}/ui/components/ui_handlers"
    "${CMAKE_CURRENT_LIST_DIR}/util"
    "${CMAKE_CURRENT_LIST_DIR}/data"
    "${CMAKE_CURRENT_LIST_DIR}/data/data_handlers"
)

include("$ENV{IDF_PATH}/tools/cmake/project.cmake")
project(Home-HMI)
