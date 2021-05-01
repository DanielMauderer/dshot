cmake_minimum_required(VERSION 3.13)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(esp32_dshot CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

#add_subdirectory(dshot)
#add_subdirectory(tests)