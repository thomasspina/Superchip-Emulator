#include "chip8.hpp"
#include "graphics.hpp"

int main() {
    // init Chip8
    Chip8 emulator = Chip8();

    // initialize graphics
    graphics::initializeGraphics();
    graphics::clearScreen();

    // load ROM for games
    emulator.loadROM("flightrunner");

    // Main loop
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) { // poll for close window event
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // emulate a single cycle
        //emulator.emulationCycle();
    }

    graphics::destroyGraphics();

    return 0;
}