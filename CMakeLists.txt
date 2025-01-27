cmake_minimum_required(VERSION 3.26)
project(Superchip-emulator LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.x
    GIT_SHALLOW ON
    SYSTEM
)

set(SDL_STATIC ON CACHE BOOL "" FORCE) # Build SDL as a static library
set(SDL_SHARED OFF CACHE BOOL "" FORCE) # Disable building SDL as a shared library
set(SDL_TEST OFF CACHE BOOL "" FORCE) # Disable SDL tests
FetchContent_MakeAvailable(SDL2)

file(GLOB HEADERS include/*.hpp)
file(GLOB SOURCES src/*.cpp)
add_executable(Superchip-emulator ${HEADERS} ${SOURCES})

# Native platform: Link SDL2 static libraries
target_link_libraries(Superchip-emulator PRIVATE 
    SDL2::SDL2-static
    SDL2::SDL2main
)

set(GAMES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/games/")
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
    ${CMAKE_BINARY_DIR}/config.h
)

target_include_directories(Superchip-emulator 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_BINARY_DIR}
)

target_compile_features(Superchip-emulator PRIVATE cxx_std_23)

# handle warnings on Apple platforms
if(APPLE)
    # silence deprecation warnings
    target_compile_definitions(Superchip-emulator PRIVATE
        GL_SILENCE_DEPRECATION
    )
    
    # silence specific warnings for the project
    target_compile_options(Superchip-emulator PRIVATE
        -Wno-deprecated-declarations
    )
    
    # silence warnings for SDL2 internal code
    target_compile_options(SDL2-static PRIVATE
        -Wno-deprecated-declarations
    )
endif()
