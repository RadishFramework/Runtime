#include "radish/application.hpp"

#include <SDL2/SDL.h>

namespace radish {

int run(int argc, char* argv[]) {
    auto appInit = application::create(application::init_params{ 
        static_cast<size_t>(argc), argv
    });

    if (appInit.failed()) {
        fmt::println("application::create failed: {}", appInit.failure());
        return 1;
    }

    auto app = std::move(appInit.value());
    while (app->isRunning())
        app->runFrame();

    return 0;
}

}

int main(int argc, char* argv[]) {
    SDL_version v{};
    SDL_GetVersion(&v);
    fmt::println("SDL version: {}.{}.{}", v.major, v.minor, v.patch);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fmt::println("SDL_Init failed: {}", SDL_GetError());
        return 1;
    }

    auto exitCode = radish::run(argc, argv);

    SDL_Quit();

    return exitCode;
}
