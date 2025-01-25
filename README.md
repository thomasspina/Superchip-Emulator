
# Building the Web Version of the Chip-8 Emulator

This guide will help you download and set up [Emscripten](https://emscripten.org/), activate its compiler, and build the Chip-8 emulator for the web using the given `emcc` command.

## Prerequisites

- Ensure you have Python 3 installed on your system, as Emscripten requires it to run.

---

## Steps to Set Up and Compile

### 1. Download and Install Emscripten

1. Visit the [Emscripten download page](https://emscripten.org/docs/getting_started/downloads.html).
2. Follow the instructions to clone the Emscripten SDK:
   ```bash
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   ```

3. Install and activate the latest Emscripten tools:
   ```bash
   ./emsdk install latest
   ./emsdk activate latest
   ```

4. For Windows users, use the `emsdk_env.bat` script to activate Emscripten in your environment. For other operating systems, adding it to your shell configuration (e.g., `.bashrc` or `.zshrc`) should not be too different.
   ```bash
   source ./emsdk_env.sh
   ```

---

### 2. Verify the Installation

1. Check if `emcc` is installed correctly:
   ```bash
   emcc --version
   ```
   You should see the version of Emscripten printed in the terminal.

---

### 3. Compile the Project

Once you have activated the Emscripten environment using `emsdk_env.bat` (Windows) or the appropriate command for your OS, navigate to your project directory and run the following `emcc` command to compile the emulator for the web:

```bash
emcc src/main.cpp src/chip8.cpp src/audio.cpp src/graphics.cpp -Iinclude -sUSE_SDL=2 -std=c++20 -o index.js --preload-file games -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -s EXPORTED_FUNCTIONS="['_invert','_loadROM', '_main']"
```

**Explanation of the command:**
- `src/main.cpp src/chip8.cpp src/audio.cpp src/graphics.cpp`: Specifies the source files to compile.
- `-Iinclude`: Includes the header files from the `include` directory.
- `-sUSE_SDL=2`: Enables SDL2 support.
- `-std=c++20`: Sets the C++ standard to C++20.
- `-o index.js`: Outputs the JavaScript/WASM files for the browser as `index.js`.
- `--preload-file games`: Includes the `games` directory in the output, making it accessible to the WASM environment.
- `-s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']"`: Exports specific runtime methods for JavaScript interaction.
- `-s EXPORTED_FUNCTIONS="['_invert','_loadROM', '_main']"`: Exports specific C++ functions for JavaScript interaction.

---

### 4. Move Output Files to the Correct Directory

After running the `emcc` command, move the generated files (`index.js`, `index.wasm`, etc.) to the desired directory for deployment, such as your web server root or the branch dedicated to the web build.

---

### Useful Sources
Compiling Chip8 to WASM:
- https://dominikrys.com/posts/compiling-chip8-to-wasm/#file-system-access-in-emscripten
=======
# Chip8 Emulator 

This project showcases a Chip8 emulator to run simple retro games and acts as a stepping stone for the Super Chip8 emulator and eventually more complex emulators. This project follows the exact specifications of the Chip8 emulator. There are multiple games included in this project as well which were found online.

## Navigation
- [Web Build](#web-build)
- [Demo](#demo)
- [Specs and Features](#specs-and-features)
  - [Specs](#specs)
    - [Processor](#processor)
    - [Graphics](#graphics)
    - [Keyboard](#keyboard)
  - [Features](#feature)
- [Installation](#installation)
  - [MacOS](#macos)
  - [Windows](#windows)
    - [MinGW](#for-mingw)
    - [Visual Studio](#for-visual-studio)
- [Technology](#technology)
- [Future Improvements](#future-improvements)
- [Sources](#sources)

## Web Build
This emulator is now runnable in the browser through WebAssembly (WASM). To access or use the web version, refer to the dedicated branch containing all relevant information and setup instructions.
- **Website link (Github Pages)**: [Website](https://thomasspina.github.io/Chip8-emulator/)
- **Browser Version Branch**: [Branch](https://github.com/thomasspina/Chip8-emulator/tree/website)

<img src="https://github.com/user-attachments/assets/01892a5f-f720-4204-979e-e124b2276c69" width="1500" />
*The Chip-8 emulator running UFO on the web*

## Demo
### Breakout 
<img src="https://github.com/user-attachments/assets/91e574aa-d5bc-457a-b6b9-80bf8166a8ff" width="1500" />

### Space Invaders
<img src="https://github.com/user-attachments/assets/8b2cbe0e-da3d-4e3d-9c09-6ad972c373a3" width="1500" />

### Pong2
<img src="https://github.com/user-attachments/assets/004568b1-1778-414a-b18f-361d75cf34fd" width="1500" />

### Tetris
<img src="https://github.com/user-attachments/assets/ddf05a7e-e1db-4660-9b3d-041035659d72" width="1500" />



## Specs and Features

### Specs
The Chip8 emulator specs can all be found in the sources portion of this README. Here are just a few that are worth mentionning.
#### Processor
The Chip8 processor has 16 8-bit registers, 4KB of RAM, and two 8-bit timers. The timers run, according to the specs, at 60 Hz. Finding the processor clock frequency though was much harder and we ended up settling on 500 Hz. This frequency can be modified in the [constants](include/constants.hpp) file by modifiying this line
```cpp
constexpr float EMULATOR_FREQ = 1 / 500.0;
```
this would make the emulator run faster, which could be beneficial for certain games like space invaders.
#### Graphics
The emulator has a 64x32 display, which isn't much. So in this rendition of the emulator, the screen is scaled up by a factor of 20. This scale can be changed according to your needs by modifying the following line in the [constants](include/constants.hpp) file.
```cpp
#define C8_SCREEN_SCALE 20
```
#### Keyboard
The Chip8 system uses a 4x4 button pad which we mapped the following way onto the keyboard. <br />
CHIP-8 Keyboard
| 1 | 2 | 3 | C |
|---|---|---|---|
| 4 | 5 | 6 | D |
| 7 | 8 | 9 | E |
| A | 0 | B | F |


Interpreter Keyboard
| 1 | 2 | 3 | 4 |
|---|---|---|---|
| Q | W | E | R |
| A | S | D | F |
| Z | X | C | V |
### Features
The project has comes with multiple games, the default one that is loaded is tetris. To change games, the game title must be changed in the [constants](include/constants.hpp) file.
To do so simply change this line at the beginning of the file 
```cpp
#define GAME "Tetris"
```
and change tetris to one of the file names in the [games](games) folder.
You can also add other chip8 games that you find online to that file and run them the same way.

## Installation
### MacOS

To run this program on MacOS you need to have XCode Command line tools installed
~~~
xcode-select --install
~~~

Then install CMake using [Homebrew](https://brew.sh)
~~~
brew install cmake
~~~

Then clone the github repo onto your computer
~~~
git clone https://github.com/thomasspina/chip-8_emulator.git
~~~

In the repo make a build directory in which the project will be built and switch to that directory
~~~
mkdir build && cd ./build
~~~

From within this build directory you can build the project using cmake and make with the following command
~~~
cmake .. && make -j 4
~~~

Then to run the project you have to run the generated binary in the bin directory within the build directory
~~~
./bin/Chip-8_emulator
~~~

### Windows

Install Cmake (PATH recommended) (https://cmake.org/download/)

Then clone the github repo onto your computer
~~~
git clone https://github.com/thomasspina/chip-8_emulator.git
~~~

#### Choose one of the following toolchains:
  - **MinGW**: Install via [MSYS2](https://www.msys2.org/) or the standalone MinGW installer.
  - **Visual Studio**: Install Visual Studio 2019+ with "Desktop Development with C++" workload.

Within the root directory, run the following commands based on the chosen toolchain:

#### For MinGW
~~~
cmake -S . -B build -G "MinGW Makefiles"
mingw32-make -C build
~~~

#### For Visual Studio
~~~
cmake -S . -B build -G "Visual Studio 17 2022"
msbuild build/Chip-8_emulator.sln /p:Configuration=Release
~~~

#### Lastly

Run the generated binary in the bin directory within the build directory
~~~
./bin/Chip-8_emulator
~~~

## Technology

C++ was chosen to be the building blocks for the project because of the low level control over memory and its performance. C++ projects can, with the help of CMake, be easily deployed to any system with a C++ compiler. Which makes it ideal for cross compatibility on both Mac and Windows. 

#### SDL2
[SDL2](https://www.libsdl.org/) is the graphics, sound and periferals library chosen since it is lightweight and had all the basics required for a Chip8 system which isn't super complex to start with.

## Future Improvements

As mentionned in the description, this project is a stepping stone to the Super Chip8 emulator which can emulate much more interesting games. These improvements can be made through a few extra opcodes and an improvement to the graphics and memory.

## Sources
Technical reference for Chip8: 
  - https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/ 
  - http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

Chip8 Game Library:
  - https://archive.org/details/chip-8-games

