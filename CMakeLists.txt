cmake_minimum_required(VERSION 3.5)

project(isomod-gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/bin)

add_subdirectory(isomodsrc)
add_subdirectory(guisrc)
