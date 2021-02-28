cmake_minimum_required(VERSION 3.13)

file(GLOB_RECURSE DSHOT_SOURCES "${PROJECT_SOURCE_DIR}/dshot/include/*.h" "${PROJECT_SOURCE_DIR}/dshot/src/*.cpp")
include_directories("${PROJECT_SOURCE_DIR}/dshot/include")
message(STATUS ${DSHOT_SOURCES})

add_library(dshot ${DSHOT_SOURCES})