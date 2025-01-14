cmake_minimum_required(VERSION 3.31.3)
set(CMAKE_MODULE_PATH "/Users/thomas/code/chip-8_emulator/build/_deps/sdl2-src/cmake")
project(CheckOBJC OBJC)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/result.cmake"
  "set(CMAKE_OBJC_COMPILER \"${CMAKE_OBJC_COMPILER}\")\n"
  
  )