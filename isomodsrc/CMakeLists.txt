cmake_minimum_required(VERSION 3.5)

project(isomod LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mno-ms-bitfields")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mno-ms-bitfields")
endif(WIN32)

if(WIN32)
    set(PROJECT_SOURCES
      isomod-win.cpp
    )
else()
    set(PROJECT_SOURCES
      isomod.cpp
)
endif(WIN32)

add_executable(isomod 
  ${PROJECT_SOURCES}
) 
