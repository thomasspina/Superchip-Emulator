#pragma once

#include "constants.hpp"

#include <SDL2/SDL.h>

class Graphics {
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    unsigned char gfx[C8_SCREEN_WIDTH * C8_SCREEN_HEIGHT] = {0};
public:
    void initializeGraphics();
    void destroyGraphics();
    void clearScreen();
};