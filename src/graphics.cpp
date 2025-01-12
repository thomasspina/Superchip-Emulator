#include "graphics.hpp"

#include <iostream>

void Graphics::initializeGraphics() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return;
    }

    if (SDL_CreateWindowAndRenderer(C8_SCREEN_WIDTH*C8_SCREEN_SCALE, C8_SCREEN_HEIGHT*C8_SCREEN_SCALE, 0, &this->window, &this->renderer)) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
    SDL_RenderSetScale(this->renderer, C8_SCREEN_SCALE, C8_SCREEN_SCALE);
}

void Graphics::destroyGraphics() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Graphics::clearScreen() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
    SDL_RenderPresent(this->renderer);
}

