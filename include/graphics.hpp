#pragma once

#include "constants.hpp"

#include <SDL2/SDL.h>

namespace graphics {
    void initializeGraphics();
    void destroyGraphics();
    void clearScreen();
    void drawScreen();
};