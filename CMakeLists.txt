cmake_minimum_required(VERSION 3.31)
project(Chip-8_emulator LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(GLOB HEADERS include/*.hpp)
file(GLOB SOURCES src/*.cpp)
add_executable(Chip-8_emulator ${HEADERS} ${SOURCES})

target_include_directories(Chip-8_emulator 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(Chip-8_emulator PRIVATE cxx_std_23)