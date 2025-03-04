#define FMT_HEADER_ONLY

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <fmt/format.h>
#include <iostream>
/*#include <memory>*/

constexpr Uint32 SDL_FLAGS = (SDL_INIT_VIDEO | SDL_INIT_AUDIO);
constexpr char WINDOW_TITLE[] = "Don't Eat the Yellow Snow!";
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

int main(void) {
    try {
        SDL_Window *window{nullptr};
        SDL_Renderer *renderer{nullptr};

        if (SDL_Init(SDL_FLAGS) != 0) {
            auto error =
                fmt::format("Error initializing SDL2: {}", SDL_GetError());
            throw std::runtime_error(error);
        }

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, 0);

        if (!window) {
            auto error =
                fmt::format("Error creating Window: {}", SDL_GetError());
            throw std::runtime_error(error);
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (!renderer) {
            auto error =
                fmt::format("Error creating Renderer: {}", SDL_GetError());
            throw std::runtime_error(error);
        }

        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(5000);

        SDL_DestroyRenderer(renderer);
        renderer = nullptr;

        SDL_DestroyWindow(window);
        window = nullptr;

        SDL_Quit();
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
