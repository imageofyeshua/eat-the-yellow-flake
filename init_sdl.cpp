#include "init_sdl.h"

void Game::initSdl() {
    if (SDL_Init(SDL_FLAGS) != 0) {
        auto error = fmt::format("Error initializing SDL2: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    if ((IMG_Init(IMG_FLAGS) & IMG_FLAGS) != IMG_FLAGS) {
        auto error =
            fmt::format("Error initializing SDL_image: {}", IMG_GetError());
        throw std::runtime_error(error);
    }

    this->window.reset(SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                        WINDOW_HEIGHT, 0));
    if (!this->window) {
        auto error = fmt::format("Error creating Window: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    this->renderer.reset(
        SDL_CreateRenderer(this->window.get(), -1, SDL_RENDERER_ACCELERATED),
        SDL_DestroyRenderer);
    if (!this->renderer) {
        auto error = fmt::format("Error creating Renderer: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> icon_surf{
        IMG_Load("images/yellow.png"), SDL_FreeSurface};
    if (!icon_surf) {
        auto error = fmt::format("Error creating Surface: {}", IMG_GetError());
        throw std::runtime_error(error);
    }
    SDL_SetWindowIcon(this->window.get(), icon_surf.get());
}
