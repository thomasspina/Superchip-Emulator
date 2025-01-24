#include "graphics.hpp"
#include <iostream>

namespace graphics {
    namespace { // anonymous namespace for private variables
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
    }

    unsigned char gfx[SC8_SCREEN_HEIGHT][SC8_SCREEN_WIDTH] = {0};

    bool isInvert = false;
}


void graphics::initializeGraphics() {

    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return;
    }

    if (SDL_CreateWindowAndRenderer(SC8_SCREEN_WIDTH*SC8_SCREEN_SCALE, SC8_SCREEN_HEIGHT*SC8_SCREEN_SCALE, 0, &window, &renderer)) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    // since screen is 64 x 32, we need to scale up everything we draw
    SDL_RenderSetScale(renderer, SC8_SCREEN_SCALE, SC8_SCREEN_SCALE);
}

void graphics::destroyGraphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void graphics::clearScreen() {

    if (isInvert) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    SDL_RenderClear(renderer);
}

// Clears all sprite on screen
void graphics::clearBuffer() {
    memset(gfx, 0, sizeof(gfx));
}

void graphics::drawScreen() {
    clearScreen();

    if (isInvert) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    
    for (int i = 0; i < SC8_SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SC8_SCREEN_WIDTH; j++) {

            // Render a pixel at (j, i) as white if gfx[i][j] is non-zero
            if (gfx[i][j]) {
                SDL_RenderDrawPoint(renderer, j, i);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void graphics::invert() {
    isInvert = !isInvert;
}

void graphics::scrollLeft(int N) {
    // TODO:
}

void graphics::scrollRight(int N) {
    // TODO:
}

void graphics::scrollDown(int N) {
    // TODO:   
}

