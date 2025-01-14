#include "graphics.hpp"

#include <iostream>

namespace graphics {
    namespace { // anonymous namespace for private variables
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
    }

    unsigned char gfx[C8_SCREEN_HEIGHT][C8_SCREEN_WIDTH] = {0};
}


void graphics::initializeGraphics() {

    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return;
    }

    if (SDL_CreateWindowAndRenderer(C8_SCREEN_WIDTH*C8_SCREEN_SCALE, C8_SCREEN_HEIGHT*C8_SCREEN_SCALE, 0, &window, &renderer)) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    // since screen is 64 x 32, we need to scale up everything we draw
    SDL_RenderSetScale(renderer, C8_SCREEN_SCALE, C8_SCREEN_SCALE);
}

void graphics::destroyGraphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void graphics::clearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void graphics::drawScreen() {
    clearScreen();
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    for (int i = 0; i < C8_SCREEN_HEIGHT; i++) {
        for (int j = 0; j < C8_SCREEN_WIDTH; j++) {
            if (gfx[i][j]) {
                SDL_RenderDrawPoint(renderer, j, i);
            }
        }
    }

    SDL_RenderPresent(renderer);
}