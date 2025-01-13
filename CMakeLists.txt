cmake_minimum_required(VERSION 3.26)
project(Chip-8_emulator LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.x
    GIT_SHALLOW ON
    SYSTEM
)

set( SDL_STATIC ON CACHE BOOL "" FORCE ) # Build SDL as a static library
set( SDL_SHARED OFF CACHE BOOL "" FORCE ) # Disable building SDL as a shared library
set(SDL_TEST OFF CACHE BOOL "" FORCE) # Disable SDL tests
FetchContent_MakeAvailable(SDL2)

file(GLOB HEADERS include/*.hpp)
file(GLOB SOURCES src/*.cpp)
add_executable(Chip-8_emulator ${HEADERS} ${SOURCES})

target_link_libraries(Chip-8_emulator PRIVATE 
    SDL2::SDL2-static
    SDL2::SDL2main
)

target_include_directories(Chip-8_emulator 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(Chip-8_emulator PRIVATE cxx_std_23)

# handle warnings on Apple platforms
if(APPLE)
    # silence deprecation warnings
    target_compile_definitions(Chip-8_emulator PRIVATE
        GL_SILENCE_DEPRECATION
    )
    
    # silence specific warnings for the project
    target_compile_options(Chip-8_emulator PRIVATE
        -Wno-deprecated-declarations
    )
    
    # silence warnings for SDL2 internal code
    target_compile_options(SDL2-static PRIVATE
        -Wno-deprecated-declarations
    )
endif()
