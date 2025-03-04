#include "game.h"

Game::~Game() {
    this->renderer.reset();
    this->window.reset();

    SDL_Quit();

    std::cout << "All Clean!" << '\n';
};

void Game::run() {
    while (this->running) {
        while (SDL_PollEvent(&this->event)) {
            switch (this->event.type) {
            case SDL_QUIT:
                this->running = false;
                return;
            default:
                break;
            }
        }
        SDL_RenderClear(this->renderer.get());
        SDL_RenderPresent(this->renderer.get());
        SDL_Delay(16);
    }
}
