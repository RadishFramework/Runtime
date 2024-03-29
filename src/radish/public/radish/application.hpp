#pragma once

#include "radish.hpp"
#include "error.hpp"
#include "vm.hpp"

struct SDL_Window;

namespace radish {

class application final {
public:
    using create_error = error<std::unique_ptr<application>, std::string>;
    using cmdline_map = std::unordered_map<std::string, std::string>;
    using cmdline = std::vector<std::string>;

    struct init_params {
        size_t argc{};
        const char* const* argv{};
    };

    /// @brief Creates a new instance of the application.
    /// @param initParams Parameters to initialize the app with.
    /// @return An error object containing the application pointer, or an error string.
    static create_error create(const init_params& initParams);

    ~application();

    bool isRunning() const;

    void runFrame();

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

    void pollEvents();

    cmdline_map _argKeyValues{};
    cmdline _args{};
    std::string _basePath{};
    std::unique_ptr<virtual_machine> _vm{};
    SDL_Window* _window{};
    bool _isRunning{true};
};

}