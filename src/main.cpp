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
    unsigned char key_id;
    SDL_Event event;
    // TODO: don't forget to tick the timers at 60Hz
    // TODO: also, how to calculate time between emulator ticks? is it really 60Hz for emulator or is it more (like 500Hz)
    while (!quit) {
        // handle user events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                break;

                case SDL_KEYDOWN:
                    // update emulator key buffer if keydown is on keypad
                    if (c8const::key_map.contains(*SDL_GetKeyName(event.key.keysym.sym))) {
                        key_id = c8const::key_map.at(*SDL_GetKeyName(event.key.keysym.sym));
                        emulator.setKeyState(key_id, 1);
                    }
                break;

                case SDL_KEYUP:
                    // update emulator key buffer if keyup is on keypad
                    if (c8const::key_map.contains(*SDL_GetKeyName(event.key.keysym.sym))) {
                        key_id = c8const::key_map.at(*SDL_GetKeyName(event.key.keysym.sym));
                        emulator.setKeyState(key_id, 0);
                    }
                break;

                default:
                break;
            }
        }

        // emulate a single cycle
        //emulator.emulationCycle();


        // draw screen
        if (emulator.getDrawFlag()) {
            graphics::drawScreen();
            emulator.setDrawFlag(false);
        }
    }

    graphics::destroyGraphics();

    return 0;
}