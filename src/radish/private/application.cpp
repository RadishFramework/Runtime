#include "radish/application.hpp"

#include "SDL2/SDL.h"

namespace radish {

application::create_error application::create(const init_params& initParams) {
    
    constexpr auto flags = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE;
    auto* window = SDL_CreateWindow("Radish", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, flags);
    if (window == nullptr) {
        return create_error{SDL_GetError()};
    }

    auto* app = new application(initParams, window);

    return create_error{app};
}

application::application(const init_params& initParams, SDL_Window* window) : _window(window) {
    _args.reserve(initParams.argc);
    for (auto i = 0; i < initParams.argc; ++i) {
        _args.emplace_back(initParams.argv[i]);

        if (i == 0 ||!_args[i].starts_with('-'))
            continue;

        auto eqPos = _args[i].find_first_of('=');
        if (eqPos == std::string::npos)
            continue;

        auto key = _args[i].substr(1, eqPos - 1);
        auto value = _args[i].substr(eqPos + 1);

        _argKeyValues.insert_or_assign(key, value);
    }
}

application::~application() {
    if (_window) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
}

}