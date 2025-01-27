#pragma once

#include "constants.hpp"

#include <SDL2/SDL.h>

namespace graphics {
    void initializeGraphics();
    void destroyGraphics();
    void clearScreen();
    void clearBuffer();
    void drawScreen();
    void invert();
    void scrollLeft(int N);
    void scrollRight(int N);
    void scrollDown(int N);

    extern unsigned char gfx[SC8_SCREEN_HEIGHT][SC8_SCREEN_WIDTH];
};
