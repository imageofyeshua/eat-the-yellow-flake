#include <memory>
#define FMT_HEADER_ONLY

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <fmt/format.h>
#include <iostream>
#include <memory>

constexpr Uint32 SDL_FLAGS = (SDL_INIT_VIDEO | SDL_INIT_AUDIO);
constexpr char WINDOW_TITLE[] = "Don't Eat the Yellow Snow!";
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

class Game {
    public:
        Game()
            : window{nullptr, SDL_DestroyWindow},
              renderer{nullptr, SDL_DestroyRenderer} {}
        ~Game();

        void initSdl();
        void run();

    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
        std::shared_ptr<SDL_Renderer> renderer;
};

Game::~Game() {
    this->renderer.reset();
    this->window.reset();

    SDL_Quit();
};

void Game::initSdl() {
    if (SDL_Init(SDL_FLAGS) != 0) {
        auto error = fmt::format("Error initializing SDL2: {}", SDL_GetError());
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

    if (!renderer) {
        auto error = fmt::format("Error creating Renderer: {}", SDL_GetError());
        throw std::runtime_error(error);
    }
}

void Game::run() {
    SDL_RenderClear(this->renderer.get());
    SDL_RenderPresent(this->renderer.get());
    SDL_Delay(5000);
}

int main(void) {
    try {
        Game game;
        game.initSdl();
        game.run();
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
