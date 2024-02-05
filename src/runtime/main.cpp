#include "radish/application.hpp"
#include "radish/logging.hpp"

#include <SDL2/SDL.h>

namespace radish {

int run(int argc, char* argv[]) {
    auto appInit = application::create(application::init_params{ 
        static_cast<size_t>(argc), argv
    });

    if (appInit.failed()) {
        RADISH_LOG(LogLevel::Error, "application::create failed: {}", appInit.failure());
        return 1;
    }

    auto app = std::move(appInit.value());
    while (app->isRunning()) {
        app->runFrame();
    }

    return 0;
}

}

int main(int argc, char* argv[]) {
    SDL_version v{};
    SDL_GetVersion(&v);
    RADISH_LOG(radish::LogLevel::Info, "SDL version: {}.{}.{}", v.major, v.minor, v.patch);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        RADISH_LOG(radish::LogLevel::Info, "SDL_Init failed: {}", SDL_GetError());
        return 1;
    }

    auto exitCode = radish::run(argc, argv);

    SDL_Quit();

    return exitCode;
}
