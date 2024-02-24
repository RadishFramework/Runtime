#pragma once

#include "radish.hpp"
#include "radish/error.hpp"

struct JSRuntime;
struct JSContext;

namespace radish {

class virtual_machine {
public:
    using create_error = error<std::unique_ptr<virtual_machine>, std::string>;

    static create_error create();
    virtual ~virtual_machine();

private:
    JSRuntime* _runtime{};
    JSContext* _context{};
};

}