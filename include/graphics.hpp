#pragma once

#include "constants.hpp"

#include <SDL2/SDL.h>

namespace graphics {
    void initializeGraphics();
    void destroyGraphics();
    void clearScreen();
    void clearBuffer();
    void drawScreen();

    extern unsigned char gfx[C8_SCREEN_HEIGHT][C8_SCREEN_WIDTH];
};
