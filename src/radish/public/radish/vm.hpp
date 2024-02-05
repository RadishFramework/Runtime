#pragma once

#include "radish.hpp"
#include "radish/error.hpp"

#include "hermes/hermes.h"

namespace radish {

namespace fbhm = facebook::hermes;

class virtual_machine {
public:
    using create_error = error<std::unique_ptr<virtual_machine>, std::string>;

    static create_error create();

private:
    std::unique_ptr<fbhm::HermesRuntime> _runtime{};
};

}