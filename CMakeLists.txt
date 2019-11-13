cmake_minimum_required(VERSION 3.5)

project(blackengine-editor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BLACKENGINE_ROOT "" CACHE PATH "Blackengine root")
message(STATUS "Using blackengine at ${BLACKENGINE_ROOT}")

set(CONAN_DISABLE_CHECK_COMPILER ON)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(blackengine-editor
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/renderwindow.cpp
        src/renderwindow.h
        src/mainwindow.ui
        src/editor/Scene.h
        src/editor/Scene.cpp
        libs/glad/src/glad.c
)

target_link_directories(blackengine-editor PRIVATE ${BLACKENGINE_ROOT}/lib)
target_link_libraries(blackengine-editor PRIVATE Qt5::Widgets BlackEngine ${CONAN_LIBS})
target_include_directories(blackengine-editor PRIVATE ${BLACKENGINE_ROOT}/include ${CMAKE_SOURCE_DIR}/libs/glad/include)
