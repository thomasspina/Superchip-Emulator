#include "chip8.hpp"
#include "graphics.hpp"
#include <chrono>
#include <iostream>

// Global variables
Chip8 emulator;
bool quit = false;
unsigned char key_id;
SDL_Event event;
float delta_time = 0;
float delta_acc_emulator = 0, delta_acc_timer = 0;
std::chrono::steady_clock::time_point curr_time, prev_time;

void initialize() {
    emulator = Chip8();
    graphics::initializeGraphics();
    graphics::clearScreen();
    emulator.loadROM();
    quit = false;
    prev_time = std::chrono::steady_clock::now();
}

void cleanup() {
    graphics::destroyGraphics();
}

void resetEmulator() {
    std::cout << "Game reset!\n";
    // Get current instance's game
    const std::string currGame = emulator.getGame();
    emulator = Chip8();
    graphics::clearScreen();
    graphics::clearBuffer();
  
    // Set current emulator instance as the reset game
    emulator.setGame(currGame);
    emulator.loadROM();
}

void handleEvents() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYDOWN:

                // Reset on pressing ENTER
                if (event.key.keysym.sym == SDLK_RETURN) {
                    resetEmulator();
                }

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
        }
    }
}

void mainLoop() {
    curr_time = std::chrono::steady_clock::now();
    delta_time = std::chrono::duration<float>(curr_time - prev_time).count();
    delta_acc_emulator += delta_time;
    delta_acc_timer += delta_time;
    prev_time = curr_time;

    static int frameCount = 0;
    static Uint32 startTime = SDL_GetTicks();

    handleEvents();

    // Tick the internal Chip8 timers at 60 Hz
    if (delta_acc_timer >= c8const::TIMER_FREQ) {
        emulator.tickDelayTimer();
        emulator.tickSoundTimer();
        delta_acc_timer = 0;
    }

    // Calculate how many cycles accumulated
    int cyclesToRun = static_cast<int>(delta_acc_emulator / (c8const::EMULATOR_FREQ));

    // Emulate cycles at 500 Hz
    for (int i = 0; i < cyclesToRun; ++i) {
        emulator.emulationCycle();
    }

    delta_acc_emulator -= cyclesToRun * (c8const::EMULATOR_FREQ);

    // Draw the screen
    if (emulator.getDrawFlag()) {
        graphics::drawScreen();
        emulator.setDrawFlag(false);
    }

    // Reset if exit flag
    if (emulator.getResetFlag()) {
        resetEmulator();
    }

    if (quit) {
        cleanup();
    }
}

int main(int argc, char* argv[]) {
    initialize();

    while (!quit) {
        mainLoop();
    }
    cleanup();

    return 0;
}

