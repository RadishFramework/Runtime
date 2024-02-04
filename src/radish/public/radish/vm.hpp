#pragma once

#include "radish.hpp"
#include "radish/error.hpp"

#include <wasmtime.hh>

namespace radish {

class virtual_machine {
public:
    using create_error = error<virtual_machine*, std::string>;

    static create_error create();

private:
    wasmtime::Engine* _engine{};
};

}