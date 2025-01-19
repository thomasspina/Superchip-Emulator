# Chip8 Emulator 

This project showcases a Chip8 emulator to run simple retro games and acts as a stepping stone for the Super Chip8 emulator and eventually more complex emulators. This project follows the exact specifications of the Chip8 emulator with a processor that runs at 500Hz.
There are multiple games included in this project as well which were not built with the project. The project was solely the Chip8 system emulator.

## Navigation
- [Features](#features)
  
- [Installation](#installation)
  - [MacOS](#macos)
  - [Windows](#windows)
    - [MinGW](#for-mingw)
    - [Visual Studio](#for-visual-studio)
- [Technology](#technology)
- [Future Improvements](#future-improvements)
- [Sources](#sources)

## Features

The project has comes with multiple games, the default one that is loaded is tetris. To change games, the game title must be changed in the constants.hpp file.

There are performance trackers at the very top, a configuration menu which handles basic simulation settings, and a rules menu which handles the weights attributed to each boid rule from the Cornell paper in the sources section. Most settings are self explanatory, for example there is a `Number of Boids` slider which adjusts the number of boids in the simulation (1000 boids should drop the framerate). Below are the less obvious settings.
#### Neighbourhood
You can show the neighbourhood in which the boids look for their flock neighbours using the `Show Boid Neighbourhood` checkbox. This neighbourhood radius is adjustable via the `Neighbourhood` slider.
![neighbourhood](https://github.com/user-attachments/assets/74e32f1a-fcc0-4372-9a0c-49e503236bd5)
#### Wandering
For the boids to look more natural there is a wander factor in the boid movement calculation that is indepedent of its neighbours. This wander factor adds randomness to boid and flock movements. This factor can be adjusted using the `Wander Factor` slider and can be enabled or disabled with the `Enable Boid Wandering` checkbox.
#### Grid and Screen Boundaries
Boids get warped to the other side of the screen upon reaching the edge of the screen by default. This behaviour can be changed using the `Avoid Screen Boundary` checkbox. There is also a checkbox named `Grid` which is used to overlay a grid on the display. This grid is part of the optimization where boids will only look for boids in neighbouring grid cells to check if they are in their neighbourhood radius. 
![avoid](https://github.com/user-attachments/assets/e2202adc-15b7-46e3-ac2c-d240da947dc2)
#### Avoid mouse
The `Enable Mouse Avoidance (Hold L-click)` checkbox enables or disables mouse avoidance. The boids will avoid the mouse if its near them and the user is left-clicking.
![mouse](https://github.com/user-attachments/assets/800f8a67-2cb4-4f44-8f35-b70ad8ca5dcc)
#### Rules 
The three rules explained in the Cornell paper in the sources can be toyed with using the three sliders and corresponding checkboxes in the menu. Very briefly the rules are:
* Separation: the boids avoid eachother
* Alignment: the boids head towards the same direction when in the same flock
* Cohesion: the boids move towards the center of the flock

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
http://devernay.free.fr/hacks/chip8/C8TECH10.HTM - technical reference for Chip8

