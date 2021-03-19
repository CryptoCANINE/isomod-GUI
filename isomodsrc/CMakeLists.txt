cmake_minimum_required(VERSION 3.5)

project(isomod LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(PROJECT_SOURCES
  isomod.cpp
)

add_executable(isomod 
  ${PROJECT_SOURCES}
) 
