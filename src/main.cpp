#include "chip8.hpp"
#include "graphics.hpp"

#include <chrono>
#include <iostream>
// TODO: add sound during sound timer

int main() {
    // init Chip8
    Chip8 emulator = Chip8();

    // initialize graphics
    graphics::initializeGraphics();
    graphics::clearScreen();

    // load ROM for games
    emulator.loadROM("pong2");

    
    bool quit = false;
    unsigned char key_id;
    SDL_Event event;
    float delta_time = 0;
    float delta_acc_emulator = 0, delta_acc_timer = 0;
    std::chrono::steady_clock::time_point curr_time, prev_time = std::chrono::steady_clock::now();

    // Main loop
    while (!quit) {
        curr_time = std::chrono::steady_clock::now();
        delta_time = std::chrono::duration<float>(curr_time - prev_time).count();
        delta_acc_emulator += delta_time; 
        delta_acc_timer += delta_time;
        prev_time = curr_time;

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
            }
        }

        // tick the internal C8 timers at 60 Hz
        if (delta_acc_timer >= c8const::TIMER_FREQ) {
            emulator.tickDelayTimer();
            emulator.tickSoundTimer();
            delta_acc_timer = 0;
        }

        // emulate a single cycle at 500 Hz
        if (delta_acc_emulator >= c8const::EMULATOR_FREQ) {
            emulator.emulationCycle();
            delta_acc_emulator = 0;
        }


        // draw screen
        if (emulator.getDrawFlag()) {
            graphics::drawScreen();
            emulator.setDrawFlag(false);
        }
    }

    graphics::destroyGraphics();

    return 0;
}