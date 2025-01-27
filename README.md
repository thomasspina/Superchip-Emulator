# Super-CHIP Emulator 

This project showcases a Super-CHIP emulator to run simple retro games and acts as a stepping stone for more complex emulators. This project follows the exact specifications of the Super-CHIP emulator. There are multiple games included in this project as well which were found online. The Super-CHIP is an upgraded version of the Chip8 emulator with a bigger screen and faster processor. The Super-CHIP is also able to run games for the less powerfull chip8 system.

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
*The Super-CHIP emulator running UFO on the web*

## Demo
### Breakout (Chip8)
<img src="https://github.com/user-attachments/assets/91e574aa-d5bc-457a-b6b9-80bf8166a8ff" width="1500" />

### Space Invaders (Chip8)
<img src="https://github.com/user-attachments/assets/8b2cbe0e-da3d-4e3d-9c09-6ad972c373a3" width="1500" />
 
### Pong2 (Chip8)
<img src="https://github.com/user-attachments/assets/004568b1-1778-414a-b18f-361d75cf34fd" width="1500" />

### Tetris (Chip8)
<img src="https://github.com/user-attachments/assets/ddf05a7e-e1db-4660-9b3d-041035659d72" width="1500" />

### Piper (Super-CHIP)
![piper](https://github.com/user-attachments/assets/d8eccbef-2c53-49bb-9d76-ed4b54426dab)

### Alien (Super-CHIP)
![alien](https://github.com/user-attachments/assets/ec6dc7a4-d810-487f-a763-97fd04b8f6e8)

## Specs and Features

### Specs
The Super-CHIP emulator specs can all be found in the sources portion of this README. Here are just a few that are worth mentionning.
#### Processor
The Super-CHIP processor has 16 8-bit registers, 4KB of RAM, and two 8-bit timers. The timers run, according to the specs, at 60 Hz. Finding the processor clock frequency though was much harder and we ended up settling on 500 Hz for the chip8 and 2000 Hz for the Super-CHIP.
#### Graphics
The emulator has a 128x64 display, which isn't much. So in this rendition of the emulator, the screen is scaled up by a factor of 10. This scale can be changed according to your needs by modifying the following line in the [constants](include/constants.hpp) file.
```cpp
#define C8_SCREEN_SCALE 10
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
#define GAME "Brix"
```
and change Brix to one of the file names in the [games](games) folder.
You can also add other chip8 and super chip games that you find online to that file and run them the same way.
The games with names in all caps are Super-CHIP games. Super-CHIP games that are added must also be added to the line which modifies the frequency based on the game (chip8 or Super-CHIP). The line is in [constants](include/constants.hpp) 
```cpp
constexpr float EMULATOR_FREQ = (str_equals(GAME, "WORM3") || 
                                    str_equals(GAME, "PIPER") || 
                                    str_equals(GAME, "JOUST") || 
                                    str_equals(GAME, "ALIEN")) ? 1 / 2000.0 : 1 / 500.0;
```

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
git clone https://github.com/thomasspina/Superchip-emulator.git
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
./bin/Superchip-emulator
~~~

### Windows

Install Cmake (PATH recommended) (https://cmake.org/download/)

Then clone the github repo onto your computer
~~~
git clone https://github.com/thomasspina/Superchip-emulator.git
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
msbuild build/Superchip-emulator.sln /p:Configuration=Release
~~~

#### Lastly

Run the generated binary in the bin directory within the build directory
~~~
./bin/Superchip-emulator
~~~

## Technology

C++ was chosen to be the building blocks for the project because of the low level control over memory and its performance. C++ projects can, with the help of CMake, be easily deployed to any system with a C++ compiler. Which makes it ideal for cross compatibility on both Mac and Windows. 

#### SDL2
[SDL2](https://www.libsdl.org/) is the graphics, sound and periferals library chosen since it is lightweight and had all the basics required for a Chip8 system which isn't super complex to start with.

## Future Improvements

This project is the final evolution of the chip8. Any improvements would simply be another system.

## Sources
Technical references for Chip8: 
  - https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/ 
  - http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
Technical references for Super-CHIP:
  - https://chip-8.github.io/extensions/#super-chip-10
  - http://devernay.free.fr/hacks/chip8/schip.txt

Super-CHIP and Chip8 Game Library:
  - https://www.zophar.net/pdroms/chip8/super-chip-games-pack.html
  - https://archive.org/details/chip-8-games

