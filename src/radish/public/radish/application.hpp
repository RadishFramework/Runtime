#pragma once

#include "radish.hpp"
#include "error.hpp"

struct SDL_Window;

namespace radish {

class application final {
public:
    using create_error = error<application*, std::string>;
    using cmdline_map = std::unordered_map<std::string, std::string>;
    using cmdline = std::vector<std::string>;

    struct init_params {
        size_t argc{};
        const char* const* argv{};
    };

    /// @brief Creates a new instance of the application. Can return nullptr if creation fails.
    /// @param initParams 
    /// @return 
    static create_error create(const init_params& initParams);

    ~application();

    [[nodiscard]]
    const cmdline_map& argumentMap() const { return _argKeyValues; }
    
    [[nodiscard]]
    const cmdline& args() const { return _args; }

    [[nodiscard]]
    const std::string& basePath() const { return _basePath; }

    [[nodiscard]]
    SDL_Window* window() const { return _window; }

private:
    application(const init_params& initParams, SDL_Window* window);

    cmdline_map _argKeyValues{};
    cmdline _args{};
    std::string _basePath{};
    SDL_Window* _window{};
};

}