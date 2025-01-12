#include "chip8.hpp"
#include "graphics.hpp"

int main() {
    // init Chip8
    //Chip8 emulator = Chip8();

    // initialize graphics
    Graphics graphics = Graphics();
    graphics.initializeGraphics();


    // load ROM for games
    // emulator.loadROM("flightrunner");

    // while system is running, execute instructions, etc
    bool quit = false;
    SDL_Event event;
    graphics.clearScreen();
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // emulate a single cycle
        //emulator.emulationCycle();
    }

    graphics.destroyGraphics();

    return 0;
}