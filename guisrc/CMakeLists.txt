cmake_minimum_required(VERSION 3.5)

project(isomod-gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mno-ms-bitfields")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mno-ms-bitfields")
endif(WIN32)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../out)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        console.cpp
        console.h
        console.ui
        log.cpp
        log.h
        window.cpp
        window.h
        window.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(isomod-gui
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(isomod-gui SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(isomod-gui
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(isomod-gui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)



